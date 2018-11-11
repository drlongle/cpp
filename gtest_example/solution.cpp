
#include <iostream>
#include <string>

#include <gtest/gtest.h>
#include <gmock/gmock.h>

using namespace std;

bool string_to_int(const string& num_in_string, int64_t& num)
{
    bool res;
    size_t processed_chars;
    num = stol(num_in_string, &processed_chars);

    if (processed_chars < num_in_string.size()) {
        res = false;
	num = 0;
    } else
        res = true;

    return res;
}

// Simple test
TEST(BasicTestCase, BasicTest)
{
    int64_t num;
    bool res = string_to_int("22", num);
    ASSERT_TRUE(res);
    ASSERT_EQ(num, 22);
}


struct TestParameters
{
    string num_in_string;
    int64_t num;
    bool res;
};

class ConversionTest : public ::testing::TestWithParam<TestParameters>
{

};

// Test with parameters
TEST_P(ConversionTest, StringToInt)
{
    struct TestParameters params = GetParam();
    bool res;
    int64_t num;
    res = string_to_int(params.num_in_string, num);
    ASSERT_EQ(res, params.res);
    ASSERT_EQ(num, params.num);
}


INSTANTIATE_TEST_CASE_P(Default, ConversionTest,
        ::testing::Values(
	TestParameters{"1", 1, true},
        TestParameters{"1000", 1000, true},
        TestParameters{"123a", 0, false}
));


int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}

