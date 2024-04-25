#include <cctype>
#include <sstream>
#include <string>
#include <vector>
#include <chrono>
#include <ctime>
#include <iostream>

#include "process.h"
#include "linux_parser.h"

using std::string;
using std::to_string;
using std::vector;

int Process::Pid() { return this->pid_; }

float Process::CpuUtilization() {
    UpdateStats();
    return this->cpu_utilization_;
}

string Process::Command() { return this->cmd_; }

string Process::Ram() {
    return LinuxParser::Ram(this->fs_path_root_, this->pid_);
}

string Process::User() { return this->user_; }

long int Process::UpTime() {
    UpdateStats();
    return this->uptime_;
}

bool Process::operator<(Process const& a) const {
    std::cout << "this uitilzation: " << this->cpu_utilization_ << "\n";
    std::cout << "that uitilzation: " << a.cpu_utilization_ << "\n";
    return this->cpu_utilization_ < a.cpu_utilization_;
}

void Process::UpdateStats() {
    /*const std::chrono::time_point now = std::chrono::system_clock::now();
    const std::chrono::time_point nextUpdate = stats_last_updated_ + kUpdateInterval;
    if (now < nextUpdate) {
        return;
    }
    this->stats_last_updated_ = now;
    */
    const auto stats = LinuxParser::Stats(this->proc_stats_file_path_);
    const long systemUpTime = this->system_.UpTime();
    const long procStartTime = std::stol(stats[LinuxParser::kStarttimeStatIndex]);
    const long procUpTime = std::stol(stats[LinuxParser::kUtimeStatIndex]);
    const long procSTime = std::stol(stats[LinuxParser::kStimeStatIndex]);
    const long procCUTime = std::stol(stats[LinuxParser::kCutimeStatIndex]);
    const long procCSTime = std::stol(stats[LinuxParser::kCstimeStatIndex]);
    const float procTotalTime = float(procUpTime + procSTime + procCUTime + procCSTime);
    const float procElapsedTime = float(systemUpTime) - (float(procStartTime) / kCPUHertz);
    this->uptime_ = (long int) procElapsedTime;
    this->cpu_utilization_ = (procTotalTime / kCPUHertz) / procElapsedTime;
}