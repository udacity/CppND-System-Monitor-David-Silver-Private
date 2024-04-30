#ifndef PROCESS_H
#define PROCESS_H

#include <unistd.h>

#include <chrono>
#include <ctime>
#include <filesystem>
#include <string>
#include <unordered_map>

#include "system.h"

const std::chrono::duration<int, std::milli> kUpdateInterval(500);
const float kCPUHertz = float(sysconf(_SC_CLK_TCK));

/*
Basic class for Process representation
It contains relevant attributes as shown below
*/
class Process {
 public:
  Process(System* system, const int pid, const std::string user,
          const std::string command, const std::filesystem::path pathRoot);
  int Pid();
  std::string User();
  std::string Command();
  float CpuUtilization();
  std::string Ram();
  long int UpTime();
  bool operator<(Process const& a) const;
  bool operator>(Process const& a) const;
  bool operator==(Process b) const;

 private:
  System* system_;
  int pid_;
  std::string user_;
  std::string cmd_;
  std::filesystem::path fs_path_root_;
  std::filesystem::path proc_stats_file_path_;
  long int uptime_{0};
  float cpu_utilization_{0};
  float previous_cpu_utilization_{0};
  std::chrono::time_point<std::chrono::system_clock> stats_last_updated_;
  void UpdateStats();
};

#endif