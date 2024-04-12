#include "linux_system.h"
#include "linux_parser.h"
#include "process.h"

using namespace std;

LinuxSystem::LinuxSystem() {
  this->cpu_info_file_path_ = LinuxParser::kProcDirectory + LinuxParser::kCpuinfoFilename;
  this->mem_info_file_path_ = LinuxParser::kProcDirectory + LinuxParser::kMeminfoFilename;
  this->os_version_file_path_ = LinuxParser::kOSPath;
  this->status_file_path_ = LinuxParser::kProcDirectory + LinuxParser::kStatusFilename;
  this->stats_file_path_ =  LinuxParser::kProcDirectory + LinuxParser::kStatFilename;
  this->uptime_file_path_ = LinuxParser::kProcDirectory + LinuxParser::kUptimeFilename;

  this->cpu_ = Processor(this->cpu_info_file_path_);
}

LinuxSystem::LinuxSystem(string cpuInfoFilePath, string memInfoFilePath, string osVersionFilePath, string statusFilePath, string statsFilePath, string uptimeFilePath) {
  this->cpu_info_file_path_ = cpuInfoFilePath;
  this->mem_info_file_path_ = memInfoFilePath;
  this->os_version_file_path_ = osVersionFilePath;
  this->status_file_path_ = statusFilePath;
  this->stats_file_path_ =  statsFilePath;
  this->uptime_file_path_ = uptimeFilePath;

  this->cpu_ = Processor(this->cpu_info_file_path_);
}

// TODO: Return the system's CPU
Processor& System::Cpu() { return cpu_; }

// TODO: Return a container composed of the system's processes
vector<Process>& System::Processes() { return processes_; }

// TODO: Return the system's kernel identifier (string)
std::string System::Kernel() { return string(); }

// TODO: Return the system's memory utilization
float System::MemoryUtilization() { return 0.0; }

// TODO: Return the operating system name
std::string System::OperatingSystem() { return string(); }

// TODO: Return the number of processes actively running on the system
int System::RunningProcesses() { return 0; }

// TODO: Return the total number of processes on the system
int System::TotalProcesses() { return 0; }

// TODO: Return the number of seconds since the system started running
long int System::UpTime() { return 0; }