#include <iostream>

#include "./googletest/googletest/include/gtest/gtest.h"

long eliminate_unset_bits(std::string number);

TEST(SUCCEED, Random_1) {
    ASSERT_EQ(eliminate_unset_bits("0101011110101"), 255);
}

TEST(SUCCEED, Random_2) { ASSERT_EQ(eliminate_unset_bits("01100000100"), 7); }

TEST(SUCCEED, Random_3) {
    ASSERT_EQ(eliminate_unset_bits("100101111001"), 127);
}

TEST(SUCCEED, Only_zeroes) { ASSERT_EQ(eliminate_unset_bits("0000"), 0); }

TEST(SUCCEED, Only_ones) { ASSERT_EQ(eliminate_unset_bits("1111"), 15); }

TEST(SUCCEED, Empty_string) { ASSERT_EQ(eliminate_unset_bits(""), -1); }

TEST(SUCCEED, Wrong_digits) { ASSERT_EQ(eliminate_unset_bits("10122212"), -1); }

TEST(SUCCEED, Wrong_digits_only) { ASSERT_EQ(eliminate_unset_bits("777"), -1); }

TEST(SUCCEED, Letters) { ASSERT_EQ(eliminate_unset_bits("101aaa1a"), -1); }

TEST(SUCCEED, Letters_only) { ASSERT_EQ(eliminate_unset_bits("aaa"), -1); }

TEST(SUCCEED, Whitespaces) { ASSERT_EQ(eliminate_unset_bits("101 11  1"), -1); }

TEST(SUCCEED, Whitespaces_only) { ASSERT_EQ(eliminate_unset_bits("   "), -1); }

TEST(SUCCEED, Long_overflow) {
    ASSERT_EQ(eliminate_unset_bits("111111111111111111111111111111111111"), -1);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}