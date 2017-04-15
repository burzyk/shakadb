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
// Created by Pawel Burzynski on 20/02/2017.
//

#ifndef SRC_CLIENT_READ_POINTS_ITERATOR_H_
#define SRC_CLIENT_READ_POINTS_ITERATOR_H_

#include <src/utils/network.h>
#include <src/protocol.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct sdb_data_points_iterator_s {
  sdb_data_point_t *points;
  int points_count;
  sdb_packet_t *_current;
  sdb_socket_t _sock;
} sdb_data_points_iterator_t;

sdb_data_points_iterator_t *sdb_data_points_iterator_create(sdb_socket_t sock);
void sdb_data_points_iterator_destroy(sdb_data_points_iterator_t *iterator);
int sdb_data_points_iterator_next(sdb_data_points_iterator_t *iterator);

#ifdef __cplusplus
}
#endif

#endif  // SRC_CLIENT_READ_POINTS_ITERATOR_H_