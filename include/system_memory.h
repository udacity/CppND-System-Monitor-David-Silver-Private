#ifndef SYSTEM_MEMORY_H
#define SYSTEM_MEMORY_H

#include <algorithm>
#include <string>
#include <stdexcept>

namespace SystemMemory {

enum class Unit {
  kb,
  mb,
  gb
};

Unit UnitFromString(std::string unitName);

class Utilization {
  public: 
    Utilization(Unit unit, long amount);
    std::string ToMbString();
  private:
    Unit unit_;
    long amount_;
};

}; // namespace SystemMemory

#endif