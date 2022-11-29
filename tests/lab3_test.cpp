#include <gtest/gtest.h>

#include <lab3.h>
#include <utils.h>
#include <cmath>


const double TEST_EPS = 1e-14;

TEST(ThirdLabTests, GetRandomNumberCorrectResults) {
    EXPECT_LE(abs(GetRandomNumber(0)), 0 + TEST_EPS);

    EXPECT_LE(abs(GetRandomNumber(1)), 1 + TEST_EPS);

    EXPECT_LE(abs(GetRandomNumber(1000000)), 1000000 + TEST_EPS);

    EXPECT_LE(abs(GetRandomNumber(99999.999)), 99999.999 + TEST_EPS);

    EXPECT_LE(abs(GetRandomNumber(0.0001)), 0.0001 + TEST_EPS);

    EXPECT_LE(abs(GetRandomNumber(7)), 7 + TEST_EPS);

    EXPECT_LE(abs(GetRandomNumber(123.4567)), 123.4567 + TEST_EPS);
}


TEST(ThirdLabTests, InCircleCorrectResults) {
    EXPECT_EQ(InCircle(1, 0, 1), true);
    EXPECT_EQ(InCircle(0, 1, 1), true);
    EXPECT_EQ(InCircle(-1, 0, 1), true);
    EXPECT_EQ(InCircle(0, -1, 1), true);
    EXPECT_EQ(InCircle(1, 1, 1), false);
    EXPECT_EQ(InCircle(-1, -1, 1), false);
    EXPECT_EQ(InCircle(99999, -99999, 1), false);
    EXPECT_EQ(InCircle(-99999, 99999, 1), false);

    EXPECT_EQ(InCircle(0, 0, 0.1), true);
    EXPECT_EQ(InCircle(-0.000001, -0.000001, 0.1), true);
    EXPECT_EQ(InCircle(-0.1, -0.1, 0.000001), false);

    EXPECT_EQ(InCircle(3, 4, 5), true);
    EXPECT_EQ(InCircle(3.00001, 4.00000001, 5), false);

    EXPECT_EQ(InCircle(1234.5678, 9876.54321, 99999999), true);
}

//TEST(ThirdLabTest, PerfomanceTest) {
//    EXPECT_GE(singleThread, multiThread);
//}