#ifndef PROCESS_H
#define PROCESS_H

#include <string>
#include <unordered_map>
#include <filesystem>
#include <chrono>
#include <ctime>

#include "linux_parser.h"
#include "system.h"

const std::chrono::duration<int, std::milli> kUpdateInterval(500);

/*
Basic class for Process representation
It contains relevant attributes as shown below
*/
class Process {
 public:
  Process(System& system, const int pid, const std::string user, const std::string command, const std::filesystem::path pathRoot) : system_(system), pid_(pid), user_(user), cmd_(command), fs_path_root_(pathRoot) {
    this->proc_stats_file_path_ = pathRoot / std::filesystem::path(std::to_string(pid)) / LinuxParser::kProcStatFilePath;
  }
  int Pid();                             
  std::string User();                    
  std::string Command();                 
  float CpuUtilization();                
  std::string Ram();                     
  long int UpTime();                     
  bool operator<(Process const& a) const;

 private:
  System& system_;
  const int pid_;
  const std::string user_;
  const std::string cmd_;
  const std::filesystem::path fs_path_root_;
  std::filesystem::path proc_stats_file_path_;
  long int uptime_{0};
  float cpu_utilization_{0};
  float previous_cpu_utilization_{0};
  std::chrono::time_point<std::chrono::system_clock> stats_last_updated_;
  void UpdateStats();
};

#endif