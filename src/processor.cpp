#include "processor.h"

#include <string>
#include <vector>

#include "linux_parser.h"

float Processor::Utilization() {
  return (float)LinuxParser::ActiveJiffies(this->cpu_stats_file_path_) /
         (float)LinuxParser::Jiffies(this->cpu_stats_file_path_);
}

bool Processor::operator==(Processor b) const {
  return this->cpu_stats_file_path_ == b.cpu_stats_file_path_;
}