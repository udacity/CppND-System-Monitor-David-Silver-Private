#include "gtest/gtest.h"
#include "../include/system_memory.h"

#include <stdexcept>

TEST(UnitFromStringTest, WorksAsExpected) {
    EXPECT_EQ(SystemMemory::Unit::kb, SystemMemory::UnitFromString("KB"));
    EXPECT_EQ(SystemMemory::Unit::kb, SystemMemory::UnitFromString("kB"));
    EXPECT_EQ(SystemMemory::Unit::kb, SystemMemory::UnitFromString("Kb"));
    EXPECT_EQ(SystemMemory::Unit::kb, SystemMemory::UnitFromString("kb"));
    EXPECT_EQ(SystemMemory::Unit::mb, SystemMemory::UnitFromString("MB"));
    EXPECT_EQ(SystemMemory::Unit::mb, SystemMemory::UnitFromString("mB"));
    EXPECT_EQ(SystemMemory::Unit::mb, SystemMemory::UnitFromString("Mb"));
    EXPECT_EQ(SystemMemory::Unit::mb, SystemMemory::UnitFromString("mb"));
    EXPECT_EQ(SystemMemory::Unit::gb, SystemMemory::UnitFromString("GB"));
    EXPECT_EQ(SystemMemory::Unit::gb, SystemMemory::UnitFromString("gB"));
    EXPECT_EQ(SystemMemory::Unit::gb, SystemMemory::UnitFromString("Gb"));
    EXPECT_EQ(SystemMemory::Unit::gb, SystemMemory::UnitFromString("gb"));
}

TEST(UnitFromStringTest, HandlesBadInput) {
    ASSERT_THROW(SystemMemory::UnitFromString("invalid"), std::invalid_argument);
}

TEST(UtilizationTest, HandlesBadInput) {
    ASSERT_THROW(SystemMemory::Utilization(SystemMemory::Unit::kb, -1), std::invalid_argument);
}

TEST(UtilizationTest, ToMbString) {
    EXPECT_EQ(SystemMemory::Utilization(SystemMemory::Unit::kb, 231264).ToMbString(), "231");
    EXPECT_EQ(SystemMemory::Utilization(SystemMemory::Unit::mb, 30104).ToMbString(), "30104");
    EXPECT_EQ(SystemMemory::Utilization(SystemMemory::Unit::gb, 4).ToMbString(), "4000");
}