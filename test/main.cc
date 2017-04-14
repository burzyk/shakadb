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
#include <cstdio>
#include <functional>

#include "test/framework/test-context.h"
#include "test/framework/test-runner.h"
#include "src/utils/allocator.h"
#include "src/utils/disk.h"
#include "test/tests/base-database-tests.h"
#include "test/tests/database-basic-tests.h"

#define RUN_TESTS
//#define RUN_PERF_TESTS

#ifdef RUN_TESTS
#define TEST(clazz, test_case) result |= runner.RunTest(\
      "" #clazz "_" #test_case "", \
      [&clazz](shakadb::test::TestContext ctx) -> void { clazz.test_case(ctx); });
#else
#define TEST(clazz, test_case)
#endif

#ifdef RUN_PERF_TESTS
#define TEST_PERF(clazz, test_case) result |= runner.RunPerfTest(\
      "" #clazz "_" #test_case "", \
      [&clazz](shakadb::test::TestContext ctx) -> shakadb::Stopwatch { return clazz.test_case(ctx); });
#else
#define TEST_PERF(clazz, test_case)
#endif

int main() {
  std::string dir("/Users/pburzynski/shakadb-test/data/test-stuff");
  sdb_directory_create(dir.c_str());
  shakadb::test::TestRunner runner(dir);
  int result = 0;

  printf("==================== Running tests ====================\n");

  auto database_basic = shakadb::test::DatabaseBasicTests();
  TEST(database_basic, simple_database_initialization_test);
  TEST(database_basic, basic_database_write_and_read_all);
  TEST(database_basic, write_database_in_one_big_batch);
  TEST(database_basic, write_database_in_multiple_small_batches);
  TEST(database_basic, database_write_history);
  TEST(database_basic, database_write_close_and_write_more);
  TEST(database_basic, database_multi_write_and_read_all);
  TEST(database_basic, database_continuous_write);
  TEST(database_basic, database_continuous_write_with_pickup);
  TEST(database_basic, database_write_batch_size_equal_to_page_capacity);
  TEST(database_basic, database_write_batch_size_greater_than_page_capacity);
  TEST(database_basic, database_write_replace);
  TEST(database_basic, database_read_inside_single_chunk);
  TEST(database_basic, database_read_span_two_chunks);
  TEST(database_basic, database_read_span_three_chunks);
  TEST(database_basic, database_read_chunk_edges);
  TEST(database_basic, database_read_duplicated_values);
  TEST(database_basic, database_read_with_limit);
  TEST(database_basic, database_truncate);
  TEST(database_basic, database_truncate_multiple);
  TEST(database_basic, database_truncate_write_again);

  runner.PrintSummary();
  printf("==================== Tests finished ===================\n");

  return result;
}
