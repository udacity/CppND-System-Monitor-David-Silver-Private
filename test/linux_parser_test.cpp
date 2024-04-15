#include <string>

#include "gtest/gtest.h"
#include "../include/linux_parser.h"

using std::string;

TEST(OperatingSystemTest, LinuxOSTest) {
  EXPECT_EQ(LinuxParser::OperatingSystem("testdata/fake_os_release"), "Ubuntu 22.04.4 LTS");
}