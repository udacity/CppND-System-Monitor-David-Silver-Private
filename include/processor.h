#include <utility>
#include <string>
#include <stdexcept>

#ifndef PROCESSOR_H
#define PROCESSOR_H

using namespace std;

class Processor {
 public:
  Processor(string cpuStatsFilePath) : cpu_stats_file_path_(std::move(cpuStatsFilePath)) {
    if (this->cpu_stats_file_path_.empty()) {throw runtime_error("processor's statistics file path must not be empty"); }
  }
  float Utilization();
  bool operator==(Processor b) const;

 private:
  const string cpu_stats_file_path_;
};

#endif