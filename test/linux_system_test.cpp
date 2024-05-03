#include "gtest/gtest.h"
#include "../include/linux_system.h"
#include "../include/linux_parser.h"
#include "../include/processor.h"

#include <string>
#include <filesystem>

using std::string;
using std::filesystem::path;

const path kTestDir("test");
const path kTestDataDir("testdata");
const path kTestDataDirPath = std::filesystem::current_path() / kTestDir / kTestDataDir;
const path kMemInfoFilePath = kTestDataDirPath / path("recent_meminfo");
const path kOSVersionFilePath = kTestDataDirPath / path("fake_os_release");
const path kStatsFilePath = kTestDataDirPath / path("recent_stat");
const path kUptimeFilePath = kTestDataDirPath / path("recent_uptime");
const path kkernelInfoFilePath = kTestDataDirPath / path("fake_proc_version");
const path kEtcPasswdFilePath = kTestDataDirPath / path("fake_etc_passwd");

class LinuxSystemTest : public testing::Test {
 protected:
 LinuxSystem system_{kTestDataDirPath.generic_string(), kTestDataDirPath.generic_string(), kMemInfoFilePath.generic_string(), kOSVersionFilePath.generic_string(), kTestDataDirPath.generic_string(), kStatsFilePath.generic_string(), kUptimeFilePath.generic_string(), kkernelInfoFilePath.generic_string(), kEtcPasswdFilePath.generic_string()};
};

TEST_F(LinuxSystemTest, CpuTest) {
 const Processor& expected{kStatsFilePath.generic_string()};
 auto cpu = system_.Cpu();
 EXPECT_EQ(cpu, expected);
 EXPECT_FLOAT_EQ(cpu.Utilization(), 0.0038888463);
}

TEST_F(LinuxSystemTest, ProcessesTest) {
 const int expectedSize = 4;
 auto processes = system_.Processes();
 EXPECT_EQ(processes.size(), expectedSize);
 EXPECT_EQ(processes[0].Pid(), 103);
 EXPECT_EQ(processes[0].User(), "foo");
 EXPECT_EQ(processes[0].Command(), "/usr/lib/chromium-browser/chromium-browser --type=zygote --ppapi-flash-path=/usr/lib/adobe-fl");
}

TEST_F(LinuxSystemTest, MemoryUtilizationTest) {
  EXPECT_FLOAT_EQ(system_.MemoryUtilization(), 0.034009644);
}

TEST_F(LinuxSystemTest, UpTimeTest) {
  EXPECT_EQ(system_.UpTime(), 552);
}

TEST_F(LinuxSystemTest, TotalProcessesTest) {
  EXPECT_EQ(system_.TotalProcesses(), 3464);
}

TEST_F(LinuxSystemTest, RunningProcessesTest) {
  EXPECT_EQ(system_.RunningProcesses(), 1);
}

TEST_F(LinuxSystemTest, OSTest) {
  EXPECT_EQ(system_.OperatingSystem(), "Ubuntu 22.04.4 LTS");
}

TEST_F(LinuxSystemTest, KernelTest) {
  EXPECT_EQ(system_.Kernel(), "5.15.146.1-microsoft-standard-WSL2");
}