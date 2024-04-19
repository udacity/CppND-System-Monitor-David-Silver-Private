#include <algorithm>
#include <string>
#include <stdexcept>

#include "system_memory.h"


SystemMemory::Unit SystemMemory::UnitFromString(std::string unitName) {
    std::transform(unitName.begin(), unitName.end(), unitName.begin(), tolower);
    if (unitName == "kb") {
        return SystemMemory::Unit::kb;
    } else if (unitName == "mb") {
        return SystemMemory::Unit::mb;
    } else if (unitName == "gb") {
        return SystemMemory::Unit::gb;
    } else {
        throw std::invalid_argument("unit must a supported value");
    }
}

SystemMemory::Utilization::Utilization(SystemMemory::Unit unit, long amount) : unit_(unit), amount_(amount) {
    if (amount < 0) {
        throw std::invalid_argument("unit must not be a negative value");
    }
}

std::string SystemMemory::Utilization::ToMbString() {
    switch (this->unit_)
    {
    case SystemMemory::Unit::kb:
        return std::to_string(int(this->amount_ * 0.001));
        break;
    case SystemMemory::Unit::mb:
        return std::to_string(this->amount_);
        break;
    case SystemMemory::Unit::gb:
        return std::to_string(this->amount_ * 1000);
        break;
    default:
        throw std::runtime_error("missing implementation for the unit type");
        break;
    }
}