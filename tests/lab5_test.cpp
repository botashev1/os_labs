#include <fstream>
#include <gtest/gtest.h>
#include <string>
#include <dlfcn.h>
#include <signature.h>


TEST(Lab5Test, DynamicTest) {

    const std::vector <std::string> FUNC_NAME = {"primeCount", "sort"};

    std::vector < std::vector <int> > input1 = {{1, 10}, {1, 100}, {107, 107}, {100, 105}};

    std::vector < std::vector <int> > input2 = {
            {3, 2, 1, 4, 5},
            {100, -1, 0},
            {1, 1, 1, 1, 1},
            {1000000},
            {-1919, -66666, -789}
    };

    std::vector <int> output1 = {4, 25, 1, 2};

    std::vector < std::vector <int> > output2= {
            {1, 2, 3, 4, 5},
            {-1, 0, 100},
            {1, 1, 1, 1, 1},
            {1000000},
            {-66666, -1919, -789}
    };


    int (*primeCountOne)(int a, int b);
    std::vector <int> (*sortOne)(std::vector <int>array, int low, int high);
    void* handleOne = dlopen(getenv("PATH_TO_libd1_dynamic.so"), RTLD_LAZY);
    ASSERT_NE(handleOne, nullptr);


    int (*primeCountTwo)(int a, int b);
    std::vector <int>(*sortTwo)(std::vector <int>array, int low, int high);
    void* handleTwo = dlopen(getenv("PATH_TO_libd2_dynamic.so"), RTLD_LAZY);
    ASSERT_NE(handleTwo, nullptr);


    primeCountOne = ((int (*)(int, int)) dlsym(handleOne, FUNC_NAME[0].c_str()));
    primeCountTwo = ((int (*)(int, int)) dlsym(handleTwo, FUNC_NAME[0].c_str()));
    sortOne = (std::vector <int>(*)(std::vector <int>, int, int))dlsym(handleOne, FUNC_NAME[1].c_str());
    sortTwo = (std::vector <int>(*)(std::vector <int>, int, int))dlsym(handleTwo, FUNC_NAME[1].c_str());


    for (size_t i = 0; i < input1.size(); i++) {
        auto primeCountOutOne = primeCountOne(input1[i][0], input1[i][1]);
        auto primeCountOutTwo = primeCountTwo(input1[i][0], input1[i][1]);
        EXPECT_EQ(primeCountOutOne, output1[i]);
        EXPECT_EQ(primeCountOutTwo, output1[i]);
    }

    for (size_t i = 0; i < input2.size(); i++) {
        auto sortOutOne = sortOne(input2[i], 0, (int)input2[i].size());
        auto sortOutTwo = sortTwo(input2[i], 0, (int)input2[i].size() - 1);


        for (int j = 0; j < output2[i].size(); j++){
            EXPECT_EQ(sortOutOne[j], output2[i][j]);
            EXPECT_EQ(sortOutTwo[j], output2[i][j]);
        }
    }
}

TEST(Lab5Test, StaticOneTest) {

    std::vector < std::vector <int> > input1 = {{1, 10}, {1, 100}, {107, 107}, {100, 105}};

    std::vector < std::vector <int> > input2 = {
            {3, 2, 1, 4, 5},
            {100, -1, 0},
            {1, 1, 1, 1, 1},
            {1000000},
            {-1919, -66666, -789}
    };

    std::vector <int> output1 = {4, 25, 1, 2};

    std::vector < std::vector <int> > output2= {
            {1, 2, 3, 4, 5},
            {-1, 0, 100},
            {1, 1, 1, 1, 1},
            {1000000},
            {-66666, -1919, -789}
    };

    for (int i = 0; i < input1.size(); i++) {
        auto primeCountOut = primeCount(input1[i][0], input1[i][1]);
        EXPECT_EQ(primeCountOut, output1[i]);
    }

    for (size_t i = 0; i < input2.size(); i++) {
        auto sortOut = sort(input2[i], 0, (int)input2[i].size());

        for (int j = 0; j < output2[i].size(); j++){
            EXPECT_EQ(sortOut[j], output2[i][j]);
        }
    }
}