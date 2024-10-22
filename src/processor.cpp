#include "processor.h"

#include <sstream>
#include <string>

#include "linux_parser.h"

// DONE: Return the aggregate CPU utilization
float Processor::Utilization() {
  auto cpus = LinuxParser::CpuUtilization();
  std::istringstream cpu_info(cpus.size() > 0 ? cpus[0] : "0 %");
  std::string cpu_utilization;
  cpu_info >> cpu_utilization;
  return std::stof(cpu_utilization);
};