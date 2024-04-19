#include <dirent.h>
#include <unistd.h>
#include <string>
#include <vector>
#include <filesystem>
#include <iostream>

#include "linux_parser.h"

using std::stof;
using std::string;
using std::to_string;
using std::vector;


/**
 *  @brief  Searches in an external file for a line starting with the specified value, and returns the associated value.
 *  @param  filePath  A reference to the path to the file to read data from.
 *  @param  key  The word to search the file for, at the start of the line in the file.
 *
 *  @returns The first matching token of type `Value` on the row that starts with the specified word.
 */
template <typename Key, typename Value>
Value FindValue(const std::filesystem::path &filePath, const Key &key) {
  Key currentKey;
  Value currentValue;
  string line;
  std::ifstream stream(filePath);
  if (stream.is_open()) {
    while (std::getline(stream, line)) {
      std::istringstream linestream(line);
      linestream >> currentKey >> currentValue;
      if (currentKey == key) {
        return currentValue;
      }
    }
  }
  return currentValue;
}

// DONE: An example of how to read data from the filesystem
string LinuxParser::OperatingSystem(const std::filesystem::path &filePath) {
  string line;
  string key;
  string value;
  std::ifstream filestream(filePath);
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
string LinuxParser::Kernel(const std::filesystem::path &filePath) {
  string os, version, kernel;
  string line;
  std::ifstream stream(filePath);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> os >> version >> kernel;
  }
  return kernel;
}

// BONUS: Update this to use std::filesystem
vector<int> LinuxParser::Pids(const std::string &dirPath) {
  vector<int> pids;
  DIR* directory = opendir(dirPath.c_str());
  struct dirent* file;
  while ((file = readdir(directory)) != nullptr) {
    // Is this a directory?
    if (file->d_type == DT_DIR) {
      // Is every character of the name a digit?
      string filename(file->d_name);
      if (std::all_of(filename.begin(), filename.end(), isdigit)) {
        int pid = stoi(filename);
        pids.push_back(pid);
      }
    }
  }
  closedir(directory);
  return pids;
}

float LinuxParser::MemoryUtilization(const std::filesystem::path &filePath) {
  float value, memTotal, memFree;
  string line, keyName;
  std::ifstream stream(filePath);
  if (stream.is_open()) {
    while (std::getline(stream, line)) {
      std::istringstream linestream(line);
      linestream >> keyName >> value;
      if (keyName == kMemTotalKey) {
        memTotal = value;
      } else if (keyName == kMemFreeKey) {
        memFree = value;
      }
    }
  }
  // The output, display expects the utilization percentage to not be multiplied by 100 e.g. 0.041 instead of 4.1.
  return (memTotal - memFree) / memTotal;
}

long LinuxParser::UpTime(const std::filesystem::path &filePath) {
  long upTime;
  string line;
  std::ifstream stream(filePath);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> upTime;
  }
  return upTime;
}

// TODO: Read and return the number of jiffies for the system
long LinuxParser::Jiffies() { return 0; }

// TODO: Read and return the number of active jiffies for a PID
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::ActiveJiffies(int pid[[maybe_unused]]) { return 0; }

// TODO: Read and return the number of active jiffies for the system
long LinuxParser::ActiveJiffies() { return 0; }

// TODO: Read and return the number of idle jiffies for the system
long LinuxParser::IdleJiffies() { return 0; }

// TODO: Read and return CPU utilization
vector<string> LinuxParser::CpuUtilization() { return {}; }

// TODO: Read and return the total number of processes
int LinuxParser::TotalProcesses(const std::filesystem::path &filePath) { 
  return FindValue<std::string, int>(filePath, kTotalProcsKey);
}

// TODO: Read and return the number of running processes
int LinuxParser::RunningProcesses(const std::filesystem::path &filePath) {
  return FindValue<std::string, int>(filePath, kNumRunningProcsKey);
}

string LinuxParser::Command(const std::filesystem::path &filePathRoot, int pid) {
  std::filesystem::path filePath = filePathRoot / std::filesystem::path(std::to_string(pid)) / kCmdlineFilePath;
  string line{""};
  std::ifstream stream(filePath);
  if (stream.is_open()) {
    std::getline(stream, line);
  }
  return line;
}

// TODO: Read and return the memory used by a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Ram(const std::filesystem::path &filePathRoot, int pid) { return string(); }

string LinuxParser::Uid(const std::filesystem::path &filePathRoot, int pid) { 
  std::filesystem::path filePath = filePathRoot / std::filesystem::path(std::to_string(pid)) / kUidFilePath;
  return FindValue<string, string>(filePath, kUidKey);
}

// TODO: Read and return the user associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::User(const std::filesystem::path &filePathRoot, int pid) { return string(); }

// TODO: Read and return the uptime of a process
// REMOVE: [[maybe_unused]] once you define the function
long int LinuxParser::UpTime(const std::filesystem::path &filePathRoot, int pid) { return 0; }

std::unordered_map<int, std::string>& LinuxParser::UserIdMap(const std::filesystem::path &filePath) {
  static std::unordered_map<int, std::string> uid_map;

  int id;
  string line, datum, userName;
  std::ifstream stream(filePath);
  if (stream.is_open()) {
    while (std::getline(stream, line)) {
      std::istringstream linestream(line);
      // Split the line stream on the ':' delimiter, storing the value in the `datum` variable.
      std::getline(linestream, datum, ':');
      userName = datum;
      // The second portion of the line is not what we need, so we ignore it.
      std::getline(linestream, datum, ':');
      std::getline(linestream, datum, ':');
      // The third portion of the line is the user's ID.
      id = std::stoi(datum);
      uid_map[id] = userName;
    }
  }

  return uid_map;
}