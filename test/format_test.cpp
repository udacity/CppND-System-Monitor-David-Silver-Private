#include "gtest/gtest.h"
#include "../include/format.h"

TEST(FormatTest, CorrectlyFormatsDataOnlySeconds) {
  EXPECT_EQ(Format::ElapsedTime(10), "00:00:10");
}
