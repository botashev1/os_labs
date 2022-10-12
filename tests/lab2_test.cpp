#include <gtest/gtest.h>

#include <array>
#include <memory>
#include <parent.h>
#include <vector>


TEST(FirstLabTests, SimpleTest) {

    constexpr int inputSize = 4;

    std::array< std::vector<std::string>, inputSize> input = {
            (std::vector<std::string>){
                    "abcabc",
                    "qwerty qwerty",
                    "A n O t H e R             TeSt",
                    "oNe1 Two2  thr3ee   5fiVe     Ei8ght        13thiRTEEN             ...",
                    "2 + 2 = 4",
                    "0123456789 abcdefghijklmnopqrstuvwxyz"
            },
            {
                    "second test",
                    "1234567890/.,'][",
                    ".            .             .                         ...............",
                    "!?+-*/_;",
            },
            {
                "",
                "                  "
            },
            {
                "AAAAAAAAAAAAAAAAAAAAAAAAAAAAA"
            }
    };

    std::array< std::vector<std::string>, inputSize> expectedOutput = {
            (std::vector<std::string>){
                    "ABCABC",
                    "QWERTY QWERTY",
                    "A N O T H E R TEST",
                    "ONE1 TWO2 THR3EE 5FIVE EI8GHT 13THIRTEEN ...",
                    "2 + 2 = 4",
                    "0123456789 ABCDEFGHIJKLMNOPQRSTUVWXYZ"
            },
            {
                    "SECOND TEST",
                    "1234567890/.,'][",
                    ". . . ...............",
                    "!?+-*/_;",
            },
            {
                    "",
                    " ",
            },
            {
                    "AAAAAAAAAAAAAAAAAAAAAAAAAAAAA"
            }
    };


    for (int i = 0; i < inputSize; i++) {
        auto result = ParentRoutine(getenv("child1"), getenv("child2"), input[i]);
        EXPECT_EQ(result, expectedOutput[i]);
    }
}