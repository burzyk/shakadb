//
// Created by Pawel Burzynski on 29/01/2017.
//

#ifndef SHAKADB_STORAGE_PERFORMANCE_TESTS_H
#define SHAKADB_STORAGE_PERFORMANCE_TESTS_H

#include <src/database.h>
#include <memory>
#include <test/framework/assert.h>
#include <src/file-log.h>
#include <src/utils/stopwatch.h>
#include <cstdlib>
#include <chrono>
#include <thread>
#include "base-database-tests.h"

namespace shakadb {
namespace test {

class DatabasePerformanceTests : public BaseDatabaseTest {
 public:
  DatabasePerformanceTests(DatabaseContextFactory *context_factory)
      : BaseDatabaseTest(context_factory) {
  }

  Stopwatch sequential_write_small(TestContext ctx) {
    return this->SequentialWrite(ctx, 1000, 100);
  };

  Stopwatch sequential_write_medium(TestContext ctx) {
    return this->SequentialWrite(ctx, 10000, 100);
  };

  Stopwatch sequential_write_large(TestContext ctx) {
    return this->SequentialWrite(ctx, 100000, 100);
  };

  Stopwatch read_small(TestContext ctx) {
    return this->Read(ctx, 1000, 100);
  };

  Stopwatch read_medium(TestContext ctx) {
    return this->Read(ctx, 10000, 100);
  };

  Stopwatch read_large(TestContext ctx) {
    return this->Read(ctx, 100000, 100);
  };

  Stopwatch random_write_small(TestContext ctx) {
    return this->RandomWrite(ctx, 100, 100);
  };

  Stopwatch random_write_medium(TestContext ctx) {
    return this->RandomWrite(ctx, 1000, 100);
  };

  Stopwatch random_write_large(TestContext ctx) {
    return this->RandomWrite(ctx, 10000, 100);
  };

 private:
  Stopwatch SequentialWrite(TestContext ctx, int batches, int batch_size) {
    auto c = std::unique_ptr<DatabaseContext>(this->CreateContext(10000, 100, ctx));
    Stopwatch sw;

    sw.Start();
    WriteToDatabase(c->GetDb(), "usd_gbp", batches, batch_size);
    sw.Stop();

    return sw;
  };

  Stopwatch Read(TestContext ctx, int windows_count, int window_size) {
    auto c = std::unique_ptr<DatabaseContext>(this->CreateContext(10000, 100, ctx));
    Stopwatch sw;

    WriteToDatabase(c->GetDb(), "usd_gbp", windows_count, window_size);

    sw.Start();
    for (int i = 0; i < windows_count; i++) {
      validate_read(c->GetDb(),
                    "usd_gbp",
                    i == 0 ? window_size - 1 : window_size,
                    (timestamp_t)(i * window_size),
                    (timestamp_t)((i + 1) * window_size));
    }
    sw.Stop();

    return sw;
  };

  Stopwatch RandomWrite(TestContext ctx, int batches, int batch_size) {
    auto c = std::unique_ptr<DatabaseContext>(this->CreateContext(10000, 100, ctx));

    // for random but consistent results
    srand(0);
    Stopwatch sw;

    sw.Start();

    for (int i = 0; i < batches; i++) {
      int time = rand() % batch_size + 1;
      WriteToDatabase(c->GetDb(), "usd_gbp", 1, batch_size, (timestamp_t)time);
    }

    sw.Stop();

    validate_read(c->GetDb(),
                  "usd_gbp",
                  batch_size * batches,
                  data_point_t::kMinTimestamp,
                  data_point_t::kMaxTimestamp);

    return sw;
  };

};

}
}

#endif //SHAKADB_STORAGE_PERFORMANCE_TESTS_H