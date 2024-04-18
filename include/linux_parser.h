#ifndef SYSTEM_PARSER_H
#define SYSTEM_PARSER_H

#include <fstream>
#include <regex>
#include <string>
#include <filesystem>

namespace LinuxParser {
// Paths
const std::string kProcDirectory{"/proc/"};
const std::string kCmdlineFilename{"/cmdline"};
const std::string kCpuinfoFilename{"/cpuinfo"};
const std::string kStatusFilename{"/status"};
const std::string kStatFilename{"/stat"};
const std::string kUptimeFilename{"/uptime"};
const std::string kMeminfoFilename{"/meminfo"};
const std::string kVersionFilename{"/version"};
const std::string kOSPath{"/etc/os-release"};
const std::string kPasswordPath{"/etc/passwd"};

const std::string kTotalProcsKey{"processes"};
const std::string kNumRunningProcsKey{"procs_running"};
const std::string kMemTotalKey{"MemTotal:"};
const std::string kMemFreeKey{"MemFree:"};

// System
float MemoryUtilization(const std::filesystem::path &filePath);
long UpTime(const std::filesystem::path &filePath);
std::vector<int> Pids(const std::string &dirPath);
int TotalProcesses(const std::filesystem::path &filePath);
int RunningProcesses(const std::filesystem::path &filePath);
std::string OperatingSystem(const std::filesystem::path &filePath);
std::string Kernel(const std::filesystem::path &filePath);

// CPU
enum CPUStates {
  kUser_ = 0,
  kNice_,
  kSystem_,
  kIdle_,
  kIOwait_,
  kIRQ_,
  kSoftIRQ_,
  kSteal_,
  kGuest_,
  kGuestNice_
};
std::vector<std::string> CpuUtilization();
long Jiffies();
long ActiveJiffies();
long ActiveJiffies(int pid);
long IdleJiffies();

// Processes
std::string Command(int pid);
std::string Ram(int pid);
std::string Uid(int pid);
std::string User(int pid);
long int UpTime(int pid);
};  // namespace LinuxParser

#endif