#include <string>
#include <filesystem>
#include <iostream>

#include "gtest/gtest.h"
#include "../include/linux_parser.h"

using std::string;

const std::filesystem::path kTestDir("test");
const std::filesystem::path kTestDataDir("testdata");

TEST(OperatingSystemTest, LinuxOSTest) {
  std::filesystem::path file("fake_os_release");
  std::filesystem::path os_data_path = std::filesystem::current_path() / kTestDir / kTestDataDir / file;
  EXPECT_EQ(LinuxParser::OperatingSystem(os_data_path), "Ubuntu 22.04.4 LTS");
}

TEST(KernelTest, LinuxOSTest) {
  std::filesystem::path file("fake_proc_version");
  std::filesystem::path kernel_data_path = std::filesystem::current_path() / kTestDir / kTestDataDir / file;
  EXPECT_EQ(LinuxParser::Kernel(kernel_data_path), "5.15.146.1-microsoft-standard-WSL2");
}

TEST(NumberOfProcessesTest, LinuxOSTest) {
  std::filesystem::path file("fake_stat");
  std::filesystem::path stat_data_path = std::filesystem::current_path() / kTestDir / kTestDataDir / file;
  EXPECT_EQ(LinuxParser::RunningProcesses(stat_data_path), 2);
}

TEST(TotalNumberOfProcessesTest, LinuxOSTest) {
  std::filesystem::path file("fake_stat");
  std::filesystem::path stat_data_path = std::filesystem::current_path() / kTestDir / kTestDataDir / file;
  EXPECT_EQ(LinuxParser::TotalProcesses(stat_data_path), 29904);
}

TEST(UptimeTest, LinuxOSTest) {
  std::filesystem::path file("fake_uptime");
  std::filesystem::path stat_data_path = std::filesystem::current_path() / kTestDir / kTestDataDir / file;
  EXPECT_EQ(LinuxParser::UpTime(stat_data_path), 12198);
}