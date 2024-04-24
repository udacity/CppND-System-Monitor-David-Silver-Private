#include "gtest/gtest.h"
#include "../include/processor.h"
#include "../include/linux_parser.h"

#include <filesystem>

TEST(UtilizationTest, FakeStatTest) {
  std::filesystem::path file("fake_stat");
  std::filesystem::path stat_data_path = kTestDataDirPath / file;
  const float expected = 0.001203349;
  const float actual = LinuxParser::ActiveJiffies(stat_data_path);
  EXPECT_EQ(actual, expected);
}

TEST(UtilizationTest, FakeCPUStatTest) {
  std::filesystem::path file("fake_cpu_stat");
  std::filesystem::path stat_data_path = kTestDataDirPath / file;
  const float expected = 0.08594523;
  const float actual = LinuxParser::ActiveJiffies(stat_data_path);
  EXPECT_FLOAT_EQ(actual, expected);
}
