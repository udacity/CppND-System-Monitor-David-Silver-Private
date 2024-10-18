#include "linux_parser.h"

#include <dirent.h>
#include <unistd.h>

#include <cmath>
#include <filesystem>
#include <set>
#include <string>
#include <vector>

using std::stof;
using std::string;
using std::to_string;
using std::vector;

namespace fs = std::filesystem;

// DONE: An example of how to read data from the filesystem
string LinuxParser::OperatingSystem() {
  string line;
  string key;
  string value;
  std::ifstream filestream(kOSPath);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::replace(line.begin(), line.end(), ' ', '_');
      std::replace(line.begin(), line.end(), '=', ' ');
      std::replace(line.begin(), line.end(), '"', ' ');
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "PRETTY_NAME") {
          std::replace(value.begin(), value.end(), '_', ' ');
          return value;
        }
      }
    }
  }
  return value;
}

// DONE: An example of how to read data from the filesystem
string LinuxParser::Kernel() {
  string os, version, kernel;
  string line;
  std::ifstream stream(kProcDirectory + kVersionFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::replace(line.begin(), line.end(), ' ', '_');
    std::istringstream linestream(line);
    linestream >> os >> version >> kernel;
  }
  return kernel;
}

// BONUS: Update this to use std::filesystem
vector<int> LinuxParser::Pids() {
  std::set<int> pids_as_set;
  const string &proc_dir = LinuxParser::kProcDirectory;

  auto is_convertible = [](const std::string str) -> bool {
    for (int i = 0; i < str.length(); i++) {
      if (!isdigit(str[i])) return false;
    }
    return true;
  };

  if (fs::exists(proc_dir)) {
    for (auto const &entry : fs::directory_iterator(proc_dir)) {
      auto path = entry.path();
      auto relative = path.lexically_relative(proc_dir);
      if (fs::is_directory(path) && is_convertible(relative)) {
        int pid = std::stoi(relative);
        pids_as_set.insert(pid);
      }
    }
  }
  vector<int> pids{pids_as_set.begin(), pids_as_set.end()};
  return pids;
}

// TODO: Read and return the system memory utilization
float LinuxParser::MemoryUtilization() {
  string key, value, line;
  float value_mem_t{0}, value_mem_f{0};
  std::ifstream stream(kProcDirectory + kMeminfoFilename);
  if (stream.is_open()) {
    while (std::getline(stream, line)) {
      std::replace(line.begin(), line.end(), ':', ' ');
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "MemTotal") value_mem_t = std::stof(value);
        if (key == "MemFree") value_mem_f = std::stof(value);
      }
    }
  }
  return value_mem_t - value_mem_f;
}

// TODO: Read and return the system uptime
long LinuxParser::UpTime() {
  string up, idle;
  string line;
  float uptime{0};
  std::ifstream stream(kProcDirectory + kUptimeFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> up >> idle;
    if (up.length()) uptime = std::stof(up);
  }
  return static_cast<long>(std::floor(uptime));
};

// TODO: Read and return the number of jiffies for the system
long LinuxParser::Jiffies() { return 0; }

// TODO: Read and return the number of active jiffies for a PID
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::ActiveJiffies(int pid [[maybe_unused]]) { return 0; }

// TODO: Read and return the number of active jiffies for the system
long LinuxParser::ActiveJiffies() { return 0; }

// TODO: Read and return the number of idle jiffies for the system
long LinuxParser::IdleJiffies() { return 0; }

// TODO: Read and return CPU utilization
vector<string> LinuxParser::CpuUtilization() { return {}; }

// TODO: Read and return the total number of processes
int LinuxParser::TotalProcesses() {
  string key, value, line;
  int processes;
  std::ifstream stream(kProcDirectory + kStatFilename);
  if (stream.is_open()) {
    while (std::getline(stream, line)) {
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "processes") processes = std::stoi(value);
        break;
      }
    }
  }
  return processes;
};

// TODO: Read and return the number of running processes
int LinuxParser::RunningProcesses() { return LinuxParser::Pids().size(); };

// TODO: Read and return the command associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Command(int pid) {
  string cmd;
  auto pids = LinuxParser::Pids();
  auto p_active = std::find(pids.begin(), pids.end(), pid);
  if (p_active != pids.end()) {
    string line;
    std::ifstream stream{kProcDirectory + "/" + std::to_string(pid) +
                         kCmdlineFilename};
    if (stream.is_open()) {
      std::getline(stream, line);
      std::istringstream linestream(line);
      linestream >> cmd;
    }
  }
  return cmd;
};

// TODO: Read and return the memory used by a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Ram(int pid [[maybe_unused]]) { return string(); }

// TODO: Read and return the user ID associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Uid(int pid [[maybe_unused]]) { return string(); }

// TODO: Read and return the user associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::User(int pid [[maybe_unused]]) { return string(); }

// TODO: Read and return the uptime of a process
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::UpTime(int pid [[maybe_unused]]) { return 0; }
