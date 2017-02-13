//
// Created by Pawel Burzynski on 12/02/2017.
//

#ifndef SHAKADB_STORAGE_SERVERCLIENT_H
#define SHAKADB_STORAGE_SERVERCLIENT_H

#include <cstdint>
#include "data-packet.h"

namespace shakadb {

class ServerClient {
 public:
  class ReceiveListener {
   public:
    virtual void OnReceived(ServerClient *client, data_packet_t *packet) = 0;
  };

  class DisconnectListener {
   public:
    virtual void OnDisconnected(ServerClient *client) = 0;
  };

  virtual ~ServerClient() {};

  virtual void AddReceivedListener(ReceiveListener *listener) = 0;
  virtual void AddDisconnectedListener(DisconnectListener *listener) = 0;
  virtual void SendPacket(PacketType type, uint8_t *data, int data_size) = 0;
  virtual void Close() = 0;
};

}

#endif //SHAKADB_STORAGE_SERVERCLIENT_H