#ifndef PROCESS_H
#define PROCESS_H

#include <string>

using std::string;

class Process {
 public:
  Process(int);
  int Pid() const;                   // DONE: See src/process.cpp
  string User() const;               // DONE: See src/process.cpp
  string Command() const;            // DONE: See src/process.cpp
  float CpuUtilization();            // DONE: See src/process.cpp
  string Ram();                      // DONE: See src/process.cpp
  long int UpTime();                 // DONE: See src/process.cpp
  bool operator<(Process const& a);  // DONE: See src/process.cpp

  // DONE: Declare any necessary private members
 private:
  int pid_;
  string user_;
  string command_;
};

#endif