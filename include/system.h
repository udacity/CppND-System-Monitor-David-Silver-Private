#ifndef SYSTEM_H
#define SYSTEM_H

#include <string>
#include <utility>
#include <vector>

#include "process.h"
#include "processor.h"

using namespace std;

class System {
 public:
  System(Processor cpu) : cpu_(std::move(cpu)) {}
  virtual Processor& Cpu() = 0;
  virtual vector<Process>& Processes() = 0;
  virtual float MemoryUtilization() = 0;
  virtual long UpTime() = 0;
  virtual int TotalProcesses() = 0;
  virtual int RunningProcesses() = 0;
  virtual string Kernel() = 0;
  virtual string OperatingSystem() = 0;

 protected:
  Processor cpu_;
  vector<Process> processes_ = {};

  string osName_{""};
};

#endif