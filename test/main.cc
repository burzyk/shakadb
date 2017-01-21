#include <cstdio>
#include <functional>
#include <test/framework/test-context.h>
#include <test/framework/test-runner.h>
#include <src/utils/directory.h>
#include "database-tests.h"

#define TEST(test_case) result = runner.RunTest("" #test_case "", test_case);

int main() {
  std::string dir("/Users/pburzynski/apollo-test/data/test-stuff");
  apollo::Directory::CreateDirectory(dir);
  apollo::test::TestRunner runner(dir);
  int result = 0;

  printf("==================== Running tests ====================\n");

  TEST(apollo::test::simple_database_initialization_test);
  TEST(apollo::test::basic_database_write_and_read_all);
  TEST(apollo::test::write_database_in_one_big_batch);
  TEST(apollo::test::write_database_in_multiple_small_batches);
  TEST(apollo::test::database_multi_write_and_read_all);

  runner.PrintSummary();
  printf("==================== Tests finished ===================\n");

  return result;
}