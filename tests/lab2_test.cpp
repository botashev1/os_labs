#include <gtest/gtest.h>

#include <array>
#include <memory>
#include <parent.h>


TEST(FirstLabTests, SimpleTest) {

    constexpr int inputSize = 6;

    std::array<std::string, inputSize> input = {
            "abcabc",
            "qwerty qwerty",
            "A n O t H e R             TeSt",
            "oNe1 Two2  thr3ee   5fiVe     Ei8ght        13thiRTEEN             ...",
            "2 + 2 = 4",
            "0123456789 abcdefghijklmnopqrstuvwxyz"
    };

    std::array<std::string, inputSize> expectedOutput = {
            "ABCABC",
            "QWERTY QWERTY",
            "A N O T H E R TEST",
            "ONE1 TWO2 THR3EE 5FIVE EI8GHT 13THIRTEEN ...",
            "2 + 2 = 4",
            "0123456789 ABCDEFGHIJKLMNOPQRSTUVWXYZ"
    };


    for (int i = 0; i < inputSize; i++) {
        std::string result = ParentRoutine(getenv("child1"), getenv("child2"), input[i]);
        EXPECT_EQ(result, expectedOutput[i]);
    }
}