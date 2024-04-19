#include "gtest/gtest.h"
#include "../include/system_memory.h"

#include <stdexcept>

TEST(UnitFromStringTest, WorksAsExpected) {
    EXPECT_EQ(SystemMemory::Unit::kb, SystemMemory::unitFromString("KB"));
    EXPECT_EQ(SystemMemory::Unit::kb, SystemMemory::unitFromString("kB"));
    EXPECT_EQ(SystemMemory::Unit::kb, SystemMemory::unitFromString("Kb"));
    EXPECT_EQ(SystemMemory::Unit::kb, SystemMemory::unitFromString("kb"));
    EXPECT_EQ(SystemMemory::Unit::mb, SystemMemory::unitFromString("MB"));
    EXPECT_EQ(SystemMemory::Unit::mb, SystemMemory::unitFromString("mB"));
    EXPECT_EQ(SystemMemory::Unit::mb, SystemMemory::unitFromString("Mb"));
    EXPECT_EQ(SystemMemory::Unit::mb, SystemMemory::unitFromString("mb"));
    EXPECT_EQ(SystemMemory::Unit::gb, SystemMemory::unitFromString("GB"));
    EXPECT_EQ(SystemMemory::Unit::gb, SystemMemory::unitFromString("gB"));
    EXPECT_EQ(SystemMemory::Unit::gb, SystemMemory::unitFromString("Gb"));
    EXPECT_EQ(SystemMemory::Unit::gb, SystemMemory::unitFromString("gb"));
}

TEST(UnitFromStringTest, HandlesBadInput) {
    ASSERT_THROW(SystemMemory::unitFromString("invalid"), std::invalid_argument);
}

TEST(UtilizationTest, HandlesBadInput) {
    ASSERT_THROW(SystemMemory::Utilization(SystemMemory::Unit::kb, -1), std::invalid_argument);
}

TEST(UtilizationTest, ToMbString) {
    EXPECT_EQ(SystemMemory::Utilization(SystemMemory::Unit::kb, 231264).ToMbString(), "231");
    EXPECT_EQ(SystemMemory::Utilization(SystemMemory::Unit::mb, 30104).ToMbString(), "30104");
    EXPECT_EQ(SystemMemory::Utilization(SystemMemory::Unit::gb, 4).ToMbString(), "4000");
}