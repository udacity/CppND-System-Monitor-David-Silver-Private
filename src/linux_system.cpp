#include "linux_system.h"

#include <algorithm>
#include <chrono>
#include <filesystem>
#include <iostream>

#include "linux_parser.h"
#include "process.h"

using namespace std;

LinuxSystem::LinuxSystem() : System(Processor(kDefaultProcessorStatsFilePath)) {
  this->procs_dir_path_ = LinuxParser::kProcDirectory;
  this->cpu_info_file_path_ =
      LinuxParser::kProcDirectory + LinuxParser::kCpuinfoFilename;
  this->mem_info_file_path_ =
      LinuxParser::kProcDirectory + LinuxParser::kMeminfoFilename;
  this->os_version_file_path_ = LinuxParser::kOSPath;
  this->status_file_path_ =
      LinuxParser::kProcDirectory + LinuxParser::kStatusFilename;
  this->stats_file_path_ =
      LinuxParser::kProcDirectory + LinuxParser::kStatFilename;
  this->uptime_file_path_ =
      LinuxParser::kProcDirectory + LinuxParser::kUptimeFilename;
  this->kernel_info_file_path_ =
      LinuxParser::kProcDirectory + LinuxParser::kVersionFilename;
  this->uid_map_ = LinuxParser::UserIdMap(LinuxParser::kPasswordPath);
}

LinuxSystem::LinuxSystem(string procs_dir_path, string cpuInfoFilePath,
                         string memInfoFilePath, string osVersionFilePath,
                         string statusFilePath, string statsFilePath,
                         string uptimeFilePath, string kernelInfoFilePath,
                         string etcPasswdFilePath)
    : System(Processor(statsFilePath)) {
  this->procs_dir_path_ = procs_dir_path;
  this->cpu_info_file_path_ = cpuInfoFilePath;
  this->mem_info_file_path_ = memInfoFilePath;
  this->os_version_file_path_ = osVersionFilePath;
  this->status_file_path_ = statusFilePath;
  this->stats_file_path_ = statsFilePath;
  this->uptime_file_path_ = uptimeFilePath;
  this->kernel_info_file_path_ = kernelInfoFilePath;
  this->uid_map_ = LinuxParser::UserIdMap(etcPasswdFilePath);
}

LinuxSystem::~LinuxSystem() {
  this->uid_map_.clear();
  this->proc_map_.clear();
  this->processes_.clear();
}

Processor& LinuxSystem::Cpu() { return this->cpu_; }

vector<Process>& LinuxSystem::Processes() {
  this->processes_.clear();
  const vector<int> currentPids = LinuxParser::Pids(this->procs_dir_path_);
  const filesystem::path procDirPath(this->procs_dir_path_);
  for (const int pid : currentPids) {
    const string uid = LinuxParser::Uid(this->procs_dir_path_, pid);
    const string cmd = LinuxParser::Command(this->procs_dir_path_, pid);
    const Process proc(this, pid, this->uid_map_[uid], cmd, procDirPath);
    processes_.push_back(proc);
  }
  std::sort(processes_.rbegin(), processes_.rend());
  return processes_;
}

std::string LinuxSystem::Kernel() {
  if (!this->kernelName_.empty()) {
    return this->kernelName_;
  }
  this->kernelName_ = LinuxParser::Kernel(this->kernel_info_file_path_);
  return this->kernelName_;
}

float LinuxSystem::MemoryUtilization() {
  return LinuxParser::MemoryUtilization(this->mem_info_file_path_);
}

std::string LinuxSystem::OperatingSystem() {
  if (!this->osName_.empty()) {
    return this->osName_;
  }
  this->osName_ = LinuxParser::OperatingSystem(this->os_version_file_path_);
  return this->osName_;
}

int LinuxSystem::RunningProcesses() {
  return LinuxParser::RunningProcesses(this->stats_file_path_);
}

int LinuxSystem::TotalProcesses() {
  return LinuxParser::TotalProcesses(this->stats_file_path_);
}

long LinuxSystem::UpTime() {
  const std::chrono::time_point now = std::chrono::system_clock::now();
  const std::chrono::time_point nextUpdate =
      uptime_last_updated_ + kUpdateInterval;
  if (now < nextUpdate) {
    return this->uptime_;
  }
  this->uptime_last_updated_ = now;
  this->uptime_ = LinuxParser::UpTime(this->uptime_file_path_);
  return this->uptime_;
}

void LinuxSystem::SortDescending(vector<Process>& processes) {
  std::sort(processes.begin(), processes.end(),
            [](const Process a, const Process b) { return a > b; });
}