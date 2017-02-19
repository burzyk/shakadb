//
// Created by Pawel Burzynski on 19/02/2017.
//

#include <src/protocol/read-request.h>
#include <src/protocol/read-response.h>
#include <src/utils/common.h>
#include "read-handler.h"

namespace shakadb {

ReadHandler::ReadHandler(Database *db, int points_per_packet) {
  this->db = db;
  this->points_per_packet = points_per_packet;
}
void ReadHandler::OnReceived(ServerClient *client, DataPacket *packet) {
  if (packet->GetType() != kReadRequest) {
    return;
  }

  ReadRequest *request = (ReadRequest *)packet;

  auto reader = this->db->Read(request->GetSeriesName(), request->GetBegin(), request->GetEnd());
  data_point_t *points = reader->GetDataPoints();
  int points_count = reader->GetDataPointsCount();

  while (points_count > 0) {
    int to_send = MIN(points_count, this->points_per_packet);
    client->SendPacket(new ReadResponse(points, to_send));
    points += to_send;
    points_count -= to_send;
  }
}

}