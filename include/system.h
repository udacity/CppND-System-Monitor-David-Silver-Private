#ifndef SYSTEM_H
#define SYSTEM_H

#include <string>
#include <vector>

#include "process.h"
#include "processor.h"

class System {
 public:
  virtual Processor& Cpu() = 0;                   // TODO: See src/system.cpp
  virtual std::vector<Process>& Processes() = 0;  // TODO: See src/system.cpp
  virtual float MemoryUtilization() = 0;          // TODO: See src/system.cpp
  virtual long UpTime() = 0;                      // TODO: See src/system.cpp
  virtual int TotalProcesses() = 0;               // TODO: See src/system.cpp
  virtual int RunningProcesses() = 0;             // TODO: See src/system.cpp
  virtual std::string Kernel() = 0;               // TODO: See src/system.cpp
  virtual std::string OperatingSystem() = 0;      // TODO: See src/system.cpp

  // TODO: Define any necessary private members
 protected:
  Processor cpu_;
  std::vector<Process> processes_ = {};
};

#endif