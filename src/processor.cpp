#include "processor.h"
#include "linux_parser.h"

#include<vector>
#include<string>

float Processor::Utilization() {
   return LinuxParser::ActiveJiffies(this->cpu_stats_file_path_) / LinuxParser::Jiffies(this->cpu_stats_file_path_);
}