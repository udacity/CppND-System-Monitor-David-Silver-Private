#ifndef PROCESS_H
#define PROCESS_H

#include <string>
#include <unordered_map>
#include <filesystem>

/*
Basic class for Process representation
It contains relevant attributes as shown below
*/
class Process {
 public:
  Process(const int pid, const std::string user, const std::string command, const std::filesystem::path pathRoot) : pid_(pid), user_(user), cmd_(command), fs_path_root_(pathRoot) {}
  int Pid();                               // TODO: See src/process.cpp
  std::string User();                      // TODO: See src/process.cpp
  std::string Command();                   // TODO: See src/process.cpp
  float CpuUtilization();                  // TODO: See src/process.cpp
  std::string Ram();                       // TODO: See src/process.cpp
  long int UpTime();                       // TODO: See src/process.cpp
  bool operator<(Process const& a) const;  // TODO: See src/process.cpp

 private:
  const int pid_;
  const std::string user_;
  const std::string cmd_;
  const std::filesystem::path fs_path_root_;
};

#endif