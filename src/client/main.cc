//
// Created by Pawel Burzynski on 09/02/2017.
//

#include <src/utils/stopwatch.h>
#include <src/data-point-reader.h>
#include "session-manager.h"

int main() {
  shakadb::SessionManager manager;
  int session_id = manager.OpenSession("localhost", 8099);

  if (session_id == shakadb::SessionManager::kInvalidSession) {
    printf("Unable to connect\n");
    return -1;
  }

  if (!manager.GetSessionById(session_id)->Ping()) {
    printf("Ping failure\n");
    return -1;
  }

  shakadb::Session *session = manager.GetSessionById(session_id);
  shakadb::DataPointReader *reader = session->ReadPoints("USD_AUD", A_MIN_TIMESTAMP, A_MAX_TIMESTAMP);

  for (int i = 0; i < reader->GetDataPointsCount(); i++) {
    printf("%llu -> %f\n", reader->GetDataPoints()[i].time, reader->GetDataPoints()[i].value);
  }

  delete reader;

//  shakadb::data_point_t points[100] = {0};
//  shakadb::Stopwatch sw;
//  shakadb::Session *session = manager.GetSessionById(session_id);
//
//  sw.Start();
//
//  for (int i = 0; i < 10; i++) {
//    for (int j = 0; j < 100; j++) {
//      points[j].time = i * 100 + j + 1;
//      points[j].value = j;
//    }
//
//    session->WritePoints("USD_AUD", points, 100);
//  }
//
//  sw.Stop();
//  printf("Elapsed: %f[s]\n", sw.GetElapsedSeconds());

  return 0;
}