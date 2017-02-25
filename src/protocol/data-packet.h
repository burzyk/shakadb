//
// Created by Pawel Burzynski on 01/02/2017.
//

#ifndef SHAKADB_STORAGE_DATA_PACKET_H
#define SHAKADB_STORAGE_DATA_PACKET_H

#include <cstdint>
#include <src/utils/ring-buffer.h>
#include <memory>
#include <vector>
#include <src/utils/buffer.h>

namespace shakadb {

enum PacketType {
  kPing = 1,
  kWriteRequest = 2,
  kWriteResponse = 3,
  kReadRequest = 4,
  kReadResponse = 5
};

struct data_packet_header_t {
  PacketType type;
  uint32_t packet_length;
};

class DataPacket {
 public:
  DataPacket();
  virtual ~DataPacket();
  static DataPacket *Load(Stream *stream);

  virtual PacketType GetType() = 0;
  std::vector<Buffer *> GetFragments();
 protected:
  virtual bool Deserialize(Buffer *payload) = 0;
  virtual std::vector<Buffer *> Serialize() = 0;
 private:
  std::vector<Buffer *> fragments;
};

}

#endif //SHAKADB_STORAGE_DATA_PACKET_H
