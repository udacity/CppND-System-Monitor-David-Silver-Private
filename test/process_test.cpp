#include "gtest/gtest.h"
#include "../include/linux_system.h"
#include "../include/linux_parser.h"
#include "../include/processor.h"
#include "../include/process.h"

#include <algorithm>
#include <string>
#include <filesystem>
#include <unistd.h>

using std::string;
using std::filesystem::path;

const path kTestDir("test");
const path kTestDataDir("testdata");
const path kTestDataDirPath = std::filesystem::current_path() / kTestDir / kTestDataDir;
const path kOSVersionFilePath = kTestDataDirPath / path("fake_os_release");
const path kkernelInfoFilePath = kTestDataDirPath / path("fake_proc_version");
const path kEtcPasswdFilePath = kTestDataDirPath / path("fake_etc_passwd");
const path kMemInfoFilePath = kTestDataDirPath / path("fake_meminfo");
const path kStatsFilePath = kTestDataDirPath / path("fake_stat");
const path kUptimeFilePath = kTestDataDirPath / path("fake_uptime");
const path kRecentMemInfoFilePath = kTestDataDirPath / path("recent_meminfo");
const path kRecentStatsFilePath = kTestDataDirPath / path("recent_stat");
const path kRecentUptimeFilePath = kTestDataDirPath / path("recent_uptime");

class ProcTest : public testing::Test {
 protected:
 LinuxSystem system_{kTestDataDirPath.generic_string(), kTestDataDirPath.generic_string(), kMemInfoFilePath.generic_string(), kOSVersionFilePath.generic_string(), kTestDataDirPath.generic_string(), kStatsFilePath.generic_string(), kUptimeFilePath.generic_string(), kkernelInfoFilePath.generic_string(), kEtcPasswdFilePath.generic_string()};
 LinuxSystem recent_system_{kTestDataDirPath.generic_string(), kTestDataDirPath.generic_string(), kRecentMemInfoFilePath.generic_string(), kOSVersionFilePath.generic_string(), kTestDataDirPath.generic_string(), kRecentStatsFilePath.generic_string(), kRecentUptimeFilePath.generic_string(), kkernelInfoFilePath.generic_string(), kEtcPasswdFilePath.generic_string()};
 Process p1_{recent_system_, 1, "root", "/sbin/init", kTestDataDirPath};
 Process p75_{system_, 75, "root", "snapfuse /var/lib/snapd/snaps/bare_5.snap /snap/bare/5 -o ro,nodev,allow_other,suid ", kTestDataDirPath};
 Process p78_{recent_system_, 78, "root", "snapfuse /var/lib/snapd/snaps/bare_5.snap /snap/bare/5 -o ro,nodev,allow_other,suid ", kTestDataDirPath};
 Process p103_{system_, 103, "foo", "/usr/lib/chromium-browser/chromium-browser --type=zygote --ppapi-flash-path=/usr/lib/adobe-fl", kTestDataDirPath};
 const float cpuHertz = float(sysconf(_SC_CLK_TCK));
};

TEST_F(ProcTest, Proc1PIDTest) {
 EXPECT_EQ(p1_.Pid(), 1);
}

TEST_F(ProcTest, Proc75PIDTest) {
 EXPECT_EQ(p75_.Pid(), 75);
}

TEST_F(ProcTest, Proc103PIDTest) {
 EXPECT_EQ(p103_.Pid(), 103);
}

TEST_F(ProcTest, Proc1UserTest) {
 EXPECT_EQ(p1_.User(), "root");
}

TEST_F(ProcTest, Proc75UserTest) {
 EXPECT_EQ(p75_.User(), "root");
}

TEST_F(ProcTest, Proc103UserTest) {
 EXPECT_EQ(p103_.User(), "foo");
}

TEST_F(ProcTest, Proc1CpuUtilizationTest) {
 const float total = float(285) + float(39) + float(78) + float(24);
 const float elapsed = float(552) - (float(76) / cpuHertz);
 const float expected = (total / cpuHertz) / elapsed;
 EXPECT_FLOAT_EQ(p1_.CpuUtilization(), expected);
}

TEST_F(ProcTest, Proc75CpuUtilizationTest) {
 const float total = float(0) + float(0) + float(0) + float(0);
 const float elapsed = float(12198) - (float(217) / cpuHertz);
 const float expected = (total / cpuHertz) / elapsed;
 EXPECT_FLOAT_EQ(p75_.CpuUtilization(), expected);
}

TEST_F(ProcTest, Proc78CpuUtilizationTest) {
 const float total = float(56) + float(4) + float(0) + float(0);
 const float elapsed = float(552) - (float(164) / cpuHertz);
 const float expected = (total / cpuHertz) / elapsed;
 EXPECT_FLOAT_EQ(p78_.CpuUtilization(), expected);
}

TEST_F(ProcTest, Proc103CpuUtilizationTest) {
 const float total = float(3) + float(48) + float(91213) + float(12278);
 const float elapsed = float(12198) - (float(3570) / cpuHertz);
 const float expected = (total / cpuHertz) / elapsed;
 EXPECT_FLOAT_EQ(p103_.CpuUtilization(), expected);
}

TEST_F(ProcTest, Proc1RamTest) {
 EXPECT_EQ(p1_.Ram(), "165");
}

TEST_F(ProcTest, Proc75RamTest) {
 EXPECT_EQ(p75_.Ram(), "4");
}

TEST_F(ProcTest, Proc78RamTest) {
 EXPECT_EQ(p78_.Ram(), "4");
}

TEST_F(ProcTest, Proc103RamTest) {
 EXPECT_EQ(p103_.Ram(), "457");
}

TEST_F(ProcTest, LessThanTest1) {
 EXPECT_TRUE(p78_ < p1_);
}

TEST_F(ProcTest, LessThanTest2) {
 EXPECT_TRUE(p78_ < p103_);
}

TEST_F(ProcTest, LessThanTest3) {
 EXPECT_TRUE(p1_ < p103_);
}

TEST_F(ProcTest, LessThanTest4) {
 EXPECT_TRUE(p75_ < p78_);
}

TEST_F(ProcTest, SortTest) {
 vector<Process> procs{p1_, p103_, p78_, p75_};
 // std::sort(procs.begin(), procs.end());
 EXPECT_EQ(procs[0], p103_);
 EXPECT_EQ(procs[1], p1_);
 EXPECT_EQ(procs[2], p75_);
 EXPECT_EQ(procs[3], p78_);
}