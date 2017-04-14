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
// Created by Pawel Burzynski on 19/02/2017.
//

#ifndef SRC_MIDDLEWARE_CLIENT_HANDLER_H_
#define SRC_MIDDLEWARE_CLIENT_HANDLER_H_

#include <src/server/server.h>
#include <src/storage/database.h>

namespace shakadb {

class ClientHandler : public Server::ServerListener {
 public:
  ClientHandler(Server *server, Database *db, int points_per_packet);

  void OnClientConnected(int client_id);
  void OnClientDisconnected(int client_id);
  void OnPacketReceived(int client_id, DataPacket *packet);

 private:
  Server *server;
  Database *db;
  int points_per_packet;
};

}  // namespace shakadb

#endif  // SRC_MIDDLEWARE_CLIENT_HANDLER_H_