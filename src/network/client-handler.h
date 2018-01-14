//
// Created by Pawel Burzynski on 13/01/2018.
//

#ifndef SRC_NETWORK_CLIENT_HANDLER_H_
#define SRC_NETWORK_CLIENT_HANDLER_H_

#include "src/storage/database.h"
#include "src/network/server.h"

typedef struct client_handler_s {
  sdb_database_t *_db;
} client_handler_t;

client_handler_t *client_handler_create(sdb_database_t *db);
void client_handler_destroy(client_handler_t *handler);
int client_handler_process_message(client_t *client, uint8_t *data, size_t size, void *context);

#endif  // SRC_NETWORK_CLIENT_HANDLER_H_