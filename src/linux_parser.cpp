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

bool process_is_active(const int &pid) {
  auto pids = LinuxParser::Pids();
  auto p_active = std::find(pids.begin(), pids.end(), pid);
  return p_active != pids.end();
};

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

// BONUS: Update this to use std::filesystem [DONE]
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

// DONE: Read and return the system memory utilization
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

// DONE: Read and return the system uptime
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

// DONE: Read and return the number of jiffies for the system
long LinuxParser::Jiffies() {
  long active = LinuxParser::ActiveJiffies();
  long idle = LinuxParser::IdleJiffies();
  return active + idle;
}

// DONE: Read and return the number of active jiffies for a PID
long LinuxParser::ActiveJiffies(int pid) {
  long p_active_jiffies{0};
  if (process_is_active(pid)) {
    std::ifstream file_stream{kProcDirectory + "/" + std::to_string(pid) +
                              kStatFilename};
    if (file_stream.is_open()) {
      string line;
      string unused_token;
      long utime, stime, cutime, cstime;

      std::getline(file_stream, line);
      std::istringstream linestream(line);

      for (int i = 0; i < 13; i++) {
        linestream >> unused_token;
      }

      linestream >> utime >> stime >> cutime >> cstime;
      p_active_jiffies = utime + stime + cutime + cstime;
    }
  }
  return p_active_jiffies;
}

// DONE: Read and return the number of active jiffies for the system
long LinuxParser::ActiveJiffies() {
  std::ifstream file_stream{kProcDirectory + kStatFilename};
  if (file_stream.is_open()) {
    string line, user, nice, system, idle, iowait, irq, softirq, steal;
    std::getline(file_stream, line);
    std::istringstream linestream(line);
    linestream >> user >> nice >> system >> idle >> iowait >> irq >> softirq >>
        steal;
    return std::stol(user) + std::stol(nice) + std::stol(system) +
           std::stol(irq) + std::stol(softirq) + std::stol(steal);
  }
};

// DONE: Read and return the number of idle jiffies for the system
long LinuxParser::IdleJiffies() {
  std::ifstream file_stream{kProcDirectory + kStatFilename};
  if (file_stream.is_open()) {
    string line, unused_token, idle, iowait;
    std::getline(file_stream, line);
    std::istringstream linestream(line);
    for (int i = 0; i < 3; i++) {
      linestream >> unused_token;
    }
    linestream >> idle >> iowait;
    return std::stol(idle) + std::stol(iowait);
  }
}
// TODO: Read and return CPU utilization
vector<string> LinuxParser::CpuUtilization() {
  vector<string> cpus;
  long non_idle = LinuxParser::ActiveJiffies();
  long idle = LinuxParser::IdleJiffies();
  long usage = non_idle / (non_idle + idle);
  cpus.push_back(std::to_string(usage) + "%");
  return cpus;
}

// DONE: Read and return the total number of processes
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

// DONE: Read and return the number of running processes
int LinuxParser::RunningProcesses() {
  string key, value, line;
  int running_processes;
  std::ifstream stream(kProcDirectory + kStatFilename);
  if (stream.is_open()) {
    while (std::getline(stream, line)) {
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "procs_running") running_processes = std::stoi(value);
        break;
      }
    }
  }
  return running_processes;
};

// DONE: Read and return the command associated with a process
string LinuxParser::Command(int pid) {
  string cmd;
  if (process_is_active(pid)) {
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

// DONE: Read and return the memory used by a process
string LinuxParser::Ram(int pid) {
  string ram{"0 MB"};
  if (process_is_active(pid)) {
    std::ifstream stream(kProcDirectory + "/" + std::to_string(pid) +
                         kStatusFilename);
    if (stream.is_open()) {
      string line, key, value;
      while (std::getline(stream, line)) {
        std::replace(line.begin(), line.end(), ':', ' ');
        std::istringstream linestream(line);
        while (linestream >> key >> value) {
          if (key == "VmSize") {
            auto ram_in_mb = std::stof(value) / 100;
            return std::to_string(ram_in_mb) + " MB";
          }
        }
      }
    }
  }
  return ram;
}

// DONE: Read and return the user ID associated with a process
string LinuxParser::Uid(int pid) {
  string uid{""};
  if (process_is_active(pid)) {
    std::ifstream stream(kProcDirectory + "/" + std::to_string(pid) +
                         kStatusFilename);
    if (stream.is_open()) {
      string line, key, value;
      while (std::getline(stream, line)) {
        std::replace(line.begin(), line.end(), ':', ' ');
        std::istringstream linestream(line);
        while (linestream >> key >> value) {
          if (key == "Uid") {
            uid = value;
            break;
          }
        }
      }
    }
  }
  return uid;
}

// DONE: Read and return the user associated with a process
string LinuxParser::User(int pid) {
  string username{""};
  if (process_is_active(pid)) {
    string uid = LinuxParser::Uid(pid);
    std::ifstream stream{kPasswordPath};
    if (stream.is_open() && uid.length()) {
      string line, user_name, x_pass, userid;
      while (std::getline(stream, line)) {
        std::replace(line.begin(), line.end(), ':', ' ');
        std::istringstream linestream(line);
        while (linestream >> user_name >> x_pass >> userid) {
          if (userid == uid) {
            username = user_name;
            break;
          }
        }
      }
    }
  }
  return username;
}

// TODO: Read and return the uptime of a process
long LinuxParser::UpTime(int pid) {
  long process_uptime{0};
  if (process_is_active(pid)) {
    std::ifstream file_stream{kProcDirectory + "/" + std::to_string(pid) +
                              kStatFilename};
    if (file_stream.is_open()) {
      string line, value;
      if (std::getline(file_stream, line)) {
        std::istringstream sstream(line);
        vector<string> fields;

        for (string field; sstream >> field;) {
          fields.push_back(field);
        }

        if (fields.size() >= 22) process_uptime = std::stof(fields[21]);
      }
    }
  }

  return process_uptime / sysconf(_SC_CLK_TCK);
}
