#include "gtest/gtest.h"
#include "../include/format.h"

TEST(FormatTest, CorrectlyFormatsDataOnlySeconds) {
  EXPECT_EQ(Format::ElapsedTime(10), "00:00:10");
  EXPECT_EQ(Format::ElapsedTime(1), "00:00:01");
  EXPECT_EQ(Format::ElapsedTime(0), "00:00:00");
  EXPECT_EQ(Format::ElapsedTime(59), "00:00:59");
}

TEST(FormatTest, CorrectlyFormatsDataMinutesAndSeconds) {
  EXPECT_EQ(Format::ElapsedTime(61), "00:01:01");
  EXPECT_EQ(Format::ElapsedTime(610), "00:10:10");
  EXPECT_EQ(Format::ElapsedTime(3540), "00:59:00");
  EXPECT_EQ(Format::ElapsedTime(3599), "00:59:59");
}

TEST(FormatTest, CorrectlyFormatsData) {
  EXPECT_EQ(Format::ElapsedTime(3600), "01:00:00");
  EXPECT_EQ(Format::ElapsedTime(3661), "01:01:01");
  EXPECT_EQ(Format::ElapsedTime(356400), "99:00:00");
}