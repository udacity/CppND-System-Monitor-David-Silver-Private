#include "gtest/gtest.h"
#include "../include/format.h"

TEST(FormatTest, CorrectlyFormatsDataOnlySeconds) {
  EXPECT_EQ("", "00:00:10");
}
