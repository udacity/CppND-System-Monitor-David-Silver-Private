#ifndef MONITOR_LINUX_SYSTEM_H
#define MONITOR_LINUX_SYSTEM_H

#include "system.h"
using std::string;

class LinuxSystem : public System {
 public:
  // The default constructor uses the standard location for the Linux system files, using the constants defined in the linux_parser.h header file.
  LinuxSystem();
  // Constructor for specifying alternative files for providing system information. Useful for unit testing the implementation logic.
  LinuxSystem(string cpuInfoFilePath, string memInfoFilePath, string osVersionFilePath, string statusFilePath, string statsFilePath, string uptimeFilePath, string kernelInfoFilePath);
  Processor& Cpu() override;
  std::vector<Process>& Processes() override;
  float MemoryUtilization() override;
  long UpTime() override;
  int TotalProcesses() override;
  int RunningProcesses() override;
  std::string Kernel() override;
  std::string OperatingSystem() override;
 private:
  string cpu_info_file_path_;
  string status_file_path_;
  string mem_info_file_path_;
  string stats_file_path_;
  string uptime_file_path_;
  string os_version_file_path_;
  string kernel_info_file_path_;
};

#endif  // MONITOR_LINUX_SYSTEM_H
