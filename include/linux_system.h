#ifndef MONITOR_LINUX_SYSTEM_H
#define MONITOR_LINUX_SYSTEM_H

#include "system.h"
using std::string;

class LinuxSystem : protected System {
 public:
  // The default constructor uses the standard location for the Linux system files, using the constants defined in the linux_parser.h header file.
  LinuxSystem();
  // Constructor for specifying alternative files for providing system information. Useful for unit testing the implementation logic.
  LinuxSystem(string cpuInfoFilePath, string memInfoFilePath, string osVersionFilePath, string statusFilePath, string statsFilePath, string uptimeFilePath);
 private:
  string cpu_info_file_path_;
  string status_file_path_;
  string mem_info_file_path_;
  string stats_file_path_;
  string uptime_file_path_;
  string os_version_file_path_;
};

#endif  // MONITOR_LINUX_SYSTEM_H
