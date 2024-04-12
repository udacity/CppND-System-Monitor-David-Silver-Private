#include <utility>
#include <string>
#include <stdexcept>

#ifndef PROCESSOR_H
#define PROCESSOR_H

using namespace std;

class Processor {
 public:
  Processor(string infoFilePath) : info_file_path_(std::move(infoFilePath)) {
    if (infoFilePath.empty()) {throw  runtime_error("processor's information file path must not be empty"); }
  }
  float Utilization();  // TODO: See src/processor.cpp

 private:
  string info_file_path_;
};

#endif