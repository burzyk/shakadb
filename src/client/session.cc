/*
 * Copyright (c) 2016 Pawel Burzynski. All rights reserved.
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */
//
// Created by Pawel Burzynski on 08/02/2017.
//

#include "src/client/session.h"

#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <netdb.h>
#include <cstdlib>

namespace shakadb {

Session::Session(sdb_socket_t sock)
    : sock(sock) {
}

Session *Session::Open(std::string server, int port) {
  // TODO(burzyk): put this to common init code
  signal(SIGPIPE, SIG_IGN);

  struct addrinfo hints = {0};
  struct addrinfo *result;
  int sock = -1;
  std::string port_string = std::to_string(port);

  hints.ai_family = AF_UNSPEC;
  hints.ai_socktype = SOCK_STREAM;
  hints.ai_flags = 0;
  hints.ai_protocol = 0;

  if (getaddrinfo(server.c_str(), port_string.c_str(), &hints, &result) != 0) {
    return nullptr;
  }

  for (addrinfo *rp = result; rp != NULL; rp = rp->ai_next) {
    if ((sock = socket(rp->ai_family, rp->ai_socktype, rp->ai_protocol)) == -1) {
      continue;
    }

    if (connect(sock, rp->ai_addr, rp->ai_addrlen) != -1) {
      break;
    }

    close(sock);
    sock = -1;
  }

  freeaddrinfo(result);
  return sock != -1 ? new Session(sock) : nullptr;
}

bool Session::WritePoints(sdb_data_series_id_t series_id, sdb_data_point_t *points, int count) {
  sdb_packet_t *request = sdb_write_request_create(series_id, points, count);

  if (!sdb_packet_send_and_destroy(request, this->sock)) {
    return false;
  }

  sdb_packet_t *packet = sdb_packet_receive(this->sock);

  if (packet == NULL) {
    return false;
  }

  if (packet->header.type != SDB_WRITE_RESPONSE) {
    sdb_packet_destroy(packet);
    return false;
  }

  sdb_write_response_t *response = (sdb_write_response_t *)packet->payload;
  bool result = response->code == SDB_RESPONSE_OK;
  sdb_packet_destroy(packet);

  return result;
}

sdb_data_points_iterator_t *Session::ReadPoints(sdb_data_series_id_t series_id,
                                                sdb_timestamp_t begin,
                                                sdb_timestamp_t end) {
  if (!sdb_packet_send_and_destroy(sdb_read_request_create(series_id, begin, end), this->sock)) {
    return nullptr;
  }

  return sdb_data_points_iterator_create(this->sock);
}

}  // namespace shakadb
