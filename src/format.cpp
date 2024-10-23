#include "format.h"

#include <sstream>
#include <string>

using std::string;

// DONE: Complete this helper function
// INPUT: Long int measuring seconds
// OUTPUT: HH:MM:SS
string Format::ElapsedTime(long seconds) {
  long hours = seconds / 3600;
  long minutes = (seconds % 3600) / 60;
  long secs = seconds % 3600 % 60;
  std::ostringstream formatted_time{};
  string s_hours =
      hours <= 9 ? "0" + std::to_string(hours) : std::to_string(hours);
  string s_minutes =
      minutes <= 9 ? "0" + std::to_string(minutes) : std::to_string(minutes);
  string s_seconds =
      secs <= 9 ? "0" + std::to_string(secs) : std::to_string(secs);
  formatted_time << s_hours << ":" << s_minutes << ":" << s_seconds;
  return formatted_time.str();
};