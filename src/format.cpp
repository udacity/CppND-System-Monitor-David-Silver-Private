#include "format.h"

#include <chrono>
#include <cstdio>
#include <string>

using std::string;

/**
 *  @brief Helper function for displaying a duration.
 *  @param seconds duration measured in seconds
 *
 *  @returns the duration formatted as HH:MM:SS
 */
string Format::ElapsedTime(long seconds) {
  const std::chrono::seconds durationInSecs{seconds};
  const auto hrs =
      std::chrono::duration_cast<std::chrono::hours>(durationInSecs);
  const auto mins =
      std::chrono::duration_cast<std::chrono::minutes>(durationInSecs - hrs);
  const auto secs = std::chrono::duration_cast<std::chrono::seconds>(
      durationInSecs - hrs - mins);
  char output[9];
  std::sprintf(output, "%.2li:%.2li:%.2li", hrs.count(), mins.count(),
               secs.count());
  return output;
}