#include <unistd.h>
#include <cctype>
#include <sstream>
#include <string>
#include <vector>
#include <chrono>
#include <ctime>

#include "process.h"
#include "linux_parser.h"

using std::string;
using std::to_string;
using std::vector;

int Process::Pid() { return this->pid_; }

// TODO: Return this process's CPU utilization
float Process::CpuUtilization() {
    UpdateStats();
    this->cpu_utilization_;
}

// TODO: Return the command that generated this process
string Process::Command() { return this->cmd_; }

// TODO: Return this process's memory utilization
string Process::Ram() { return string(); }

// TODO: Return the user (name) that generated this process
string Process::User() { return this->user_; }

// TODO: Return the age of this process (in seconds)
long int Process::UpTime() {
    UpdateStats();
    return this->uptime_;
}

// TODO: Overload the "less than" comparison operator for Process objects
// REMOVE: [[maybe_unused]] once you define the function
bool Process::operator<(Process const& a) const {
    this->cpu_utilization_ < a.cpu_utilization_;
}

void Process::UpdateStats() {
    const std::chrono::time_point now = std::chrono::system_clock::now();
    const std::chrono::time_point nextUpdate = stats_last_updated_ + kUpdateInterval;
    if (now < nextUpdate) {
        return;
    }
    this->stats_last_updated_ = now;
    const auto stats = LinuxParser::Stats(this->proc_stats_file_path_);
    const auto systemUpTime = this->system_.UpTime();
    const long procStartTime = std::stol(stats[LinuxParser::kStarttimeStatIndex]);
    const long procUpTime = std::stol(stats[LinuxParser::kUtimeStatIndex]);
    const long procSTime = std::stol(stats[LinuxParser::kStimeStatIndex]);
    const long procCUTime = std::stol(stats[LinuxParser::kCutimeStatIndex]);
    const long procCSTime = std::stol(stats[LinuxParser::kCstimeStatIndex]);
    const auto cpuHertz = sysconf(_SC_CLK_TCK);
    const long procTotalTime = procUpTime + procSTime + procCUTime + procCSTime;
    const long procElapsedTime = systemUpTime - (procStartTime / cpuHertz);
    this->uptime_ = procElapsedTime;
    this->cpu_utilization_ = 100 * ((procTotalTime / cpuHertz) / procElapsedTime);
}