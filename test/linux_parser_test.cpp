#include <string>
#include <filesystem>
#include <iostream>

#include "gtest/gtest.h"
#include "../include/linux_parser.h"

using std::string;

TEST(OperatingSystemTest, LinuxOSTest) {
  std::filesystem::path file("fake_os_release");
  std::filesystem::path test_dir("test");
  std::filesystem::path test_data_dir("testdata");
  std::filesystem::path os_data_path = std::filesystem::current_path() / test_dir / test_data_dir / file;
  std::cout << "test data path: " << os_data_path << "\n";
  EXPECT_EQ(LinuxParser::OperatingSystem(os_data_path), "Ubuntu 22.04.4 LTS");
}