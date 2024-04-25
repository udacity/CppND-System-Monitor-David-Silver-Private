#include "gtest/gtest.h"
#include "../include/processor.h"
#include "../include/linux_parser.h"

#include <filesystem>

const std::filesystem::path kTestDir("test");
const std::filesystem::path kTestDataDir("testdata");
const std::filesystem::path kTestDataDirPath = std::filesystem::current_path() / kTestDir / kTestDataDir;

TEST(CPUUtilizationTest, FakeStatTest) {
  std::filesystem::path file("fake_stat");
  std::filesystem::path stat_data_path = kTestDataDirPath / file;
  const float expected = 0.001203349;
  Processor p{stat_data_path.generic_string()};
  const float actual = p.Utilization();
  EXPECT_FLOAT_EQ(actual, expected);
}

TEST(CPUUtilizationTest, FakeCPUStatTest) {
  std::filesystem::path file("fake_cpu_stat");
  std::filesystem::path stat_data_path = kTestDataDirPath / file;
  const float expected = 0.08594523;
  Processor p{stat_data_path.generic_string()};
  const float actual = p.Utilization();
  EXPECT_FLOAT_EQ(actual, expected);
}
