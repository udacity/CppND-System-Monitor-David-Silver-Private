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
  std::filesystem::path os_data_path = std::filesystem::current_path() / kTestDir / kTestDataDir / file;
  EXPECT_EQ(LinuxParser::Kernel(os_data_path), "5.15.146.1-microsoft-standard-WSL2");
}