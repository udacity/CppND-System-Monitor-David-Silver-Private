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

Unit unitFromString(std::string unitName) {
    std::transform(unitName.begin(), unitName.end(), unitName.begin(), tolower);
    if (unitName == "kb") {
        return Unit::kb;
    } else if (unitName == "mb") {
        return Unit::mb;
    } else if (unitName == "gb") {
        return Unit::gb;
    } else {
        throw std::invalid_argument("unit must a supported value");
    }
}

class Utilization {
  public: 
    Utilization(Unit unit, long amount) : unit_(unit), amount_(amount) {
        if (amount < 0) {
            throw std::invalid_argument("unit must not be a negative value");
        }
    }
    std::string ToMbString() {
        switch (this->unit_)
        {
        case Unit::kb:
            return std::to_string(int(this->amount_ * 0.001));
            break;
        case Unit::mb:
            return std::to_string(this->amount_);
            break;
        case Unit::gb:
            return std::to_string(this->amount_ * 1000);
            break;
        default:
            throw std::runtime_error("missing implementation for the unit type");
            break;
        }
    }
  private:
    Unit unit_;
    long amount_;
};

}; // namespace SystemMemory

#endif