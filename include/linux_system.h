#ifndef MONITOR_LINUX_SYSTEM_H
#define MONITOR_LINUX_SYSTEM_H

#include "system.h"
using std::string;

class LinuxSystem : public System {
 private:
  string cpu_info_file_path_;
  string status_file_path_;
  string stats_file_path_;
  string uptime_file_path_;
  string mem_info_file_path_;
  string os_version_file_path_;
};

#endif  // MONITOR_LINUX_SYSTEM_H
