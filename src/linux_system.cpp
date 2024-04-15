#include "linux_system.h"
#include "linux_parser.h"
#include "process.h"

using namespace std;

const string kDefaultProcessorInfoFilePath = LinuxParser::kProcDirectory + LinuxParser::kCpuinfoFilename;

LinuxSystem::LinuxSystem() : System(Processor(kDefaultProcessorInfoFilePath)) {
  this->cpu_info_file_path_ = kDefaultProcessorInfoFilePath;
  this->mem_info_file_path_ = LinuxParser::kProcDirectory + LinuxParser::kMeminfoFilename;
  this->os_version_file_path_ = LinuxParser::kOSPath;
  this->status_file_path_ = LinuxParser::kProcDirectory + LinuxParser::kStatusFilename;
  this->stats_file_path_ =  LinuxParser::kProcDirectory + LinuxParser::kStatFilename;
  this->uptime_file_path_ = LinuxParser::kProcDirectory + LinuxParser::kUptimeFilename;
}

LinuxSystem::LinuxSystem(string cpuInfoFilePath, string memInfoFilePath, string osVersionFilePath, string statusFilePath, string statsFilePath, string uptimeFilePath) : System(Processor(cpuInfoFilePath)) {
  this->cpu_info_file_path_ = cpuInfoFilePath;
  this->mem_info_file_path_ = memInfoFilePath;
  this->os_version_file_path_ = osVersionFilePath;
  this->status_file_path_ = statusFilePath;
  this->stats_file_path_ =  statsFilePath;
  this->uptime_file_path_ = uptimeFilePath;
}

Processor& LinuxSystem::Cpu() { return this->cpu_; }

// TODO: Return a container composed of the system's processes
vector<Process>& LinuxSystem::Processes() { return processes_; }

// TODO: Return the system's kernel identifier (string)
std::string LinuxSystem::Kernel() { return string(); }

// TODO: Return the system's memory utilization
float LinuxSystem::MemoryUtilization() { return 0.0; }

// TODO: Return the operating system name
std::string LinuxSystem::OperatingSystem() { return string(); }

// TODO: Return the number of processes actively running on the system
int LinuxSystem::RunningProcesses() { return 0; }

// TODO: Return the total number of processes on the system
int LinuxSystem::TotalProcesses() { return 0; }

// TODO: Return the number of seconds since the system started running
long int LinuxSystem::UpTime() { return 0; }