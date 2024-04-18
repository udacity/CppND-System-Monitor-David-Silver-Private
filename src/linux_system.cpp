#include "linux_system.h"
#include "linux_parser.h"
#include "process.h"
#include <iostream>

using namespace std;

const string kDefaultProcessorInfoFilePath = LinuxParser::kProcDirectory + LinuxParser::kCpuinfoFilename;

LinuxSystem::LinuxSystem() : System(Processor(kDefaultProcessorInfoFilePath)) {
  this->cpu_info_file_path_ = kDefaultProcessorInfoFilePath;
  this->mem_info_file_path_ = LinuxParser::kProcDirectory + LinuxParser::kMeminfoFilename;
  this->os_version_file_path_ = LinuxParser::kOSPath;
  this->status_file_path_ = LinuxParser::kProcDirectory + LinuxParser::kStatusFilename;
  this->stats_file_path_ =  LinuxParser::kProcDirectory + LinuxParser::kStatFilename;
  this->uptime_file_path_ = LinuxParser::kProcDirectory + LinuxParser::kUptimeFilename;
  this->kernel_info_file_path_ = LinuxParser::kProcDirectory + LinuxParser::kVersionFilename;
  this->uid_map_ = LinuxParser::UserIdMap(LinuxParser::kPasswordPath);
}

LinuxSystem::LinuxSystem(string cpuInfoFilePath, string memInfoFilePath, string osVersionFilePath, string statusFilePath, string statsFilePath, string uptimeFilePath, string kernelInfoFilePath, string etcPasswdFilePath) : System(Processor(cpuInfoFilePath)) {
  this->cpu_info_file_path_ = cpuInfoFilePath;
  this->mem_info_file_path_ = memInfoFilePath;
  this->os_version_file_path_ = osVersionFilePath;
  this->status_file_path_ = statusFilePath;
  this->stats_file_path_ =  statsFilePath;
  this->uptime_file_path_ = uptimeFilePath;
  this->kernel_info_file_path_ = kernelInfoFilePath;
  this->uid_map_ = LinuxParser::UserIdMap(etcPasswdFilePath);
}

Processor& LinuxSystem::Cpu() { return this->cpu_; }

// TODO: Return a container composed of the system's processes
vector<Process>& LinuxSystem::Processes() { return processes_; }

std::string LinuxSystem::Kernel() {  
  if (! this->kernelName_.empty()) {
    return this->kernelName_;
  }
  this->kernelName_ = LinuxParser::Kernel(this->kernel_info_file_path_);
  return this->kernelName_;
}

float LinuxSystem::MemoryUtilization() {
  return LinuxParser::MemoryUtilization(this->mem_info_file_path_);
}

std::string LinuxSystem::OperatingSystem() {
  if (! this->osName_.empty()) {
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
  return LinuxParser::UpTime(this->uptime_file_path_);
}