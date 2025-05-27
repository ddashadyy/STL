#include <gtest/gtest.h>

#include "../containers/array.hpp"  

TEST(ArrayTest, DefaultConstructor) {
    ownstl::array<int, 5> arr;
    EXPECT_EQ(arr.size(), 5);
    EXPECT_FALSE(arr.empty());
}

TEST(ArrayTest, InitializerListConstructor) {
    ownstl::array<int, 3> arr = {1, 2, 3};
    EXPECT_EQ(arr[0], 1);
    EXPECT_EQ(arr[1], 2);
    EXPECT_EQ(arr[2], 3);
}

TEST(ArrayTest, AtMethod) {
    ownstl::array<int, 3> arr = {10, 20, 30};
    EXPECT_EQ(arr.at(0), 10);
    EXPECT_EQ(arr.at(1), 20);
    EXPECT_EQ(arr.at(2), 30);
    EXPECT_THROW(arr.at(3), std::out_of_range);
}

TEST(ArrayTest, SubscriptOperator) {
    ownstl::array<std::string, 2> arr = {"hello", "world"};
    EXPECT_EQ(arr[0], "hello");
    EXPECT_EQ(arr[1], "world");
    arr[1] = "test";
    EXPECT_EQ(arr[1], "test");
}

TEST(ArrayTest, FrontBackMethods) {
    ownstl::array<int, 4> arr = {5, 10, 15, 20};
    EXPECT_EQ(arr.front(), 5);
    EXPECT_EQ(arr.back(), 20);
}

TEST(ArrayTest, DataMethod) {
    ownstl::array<int, 3> arr = {100, 200, 300};
    int* ptr = arr.data();
    EXPECT_EQ(*ptr, 100);
    EXPECT_EQ(*(ptr + 1), 200);
}

TEST(ArrayTest, Iterators) {
    ownstl::array<int, 5> arr = {1, 2, 3, 4, 5};
    
    int sum = 0;
    for (auto it = arr.begin(); it != arr.end(); ++it) {
        sum += *it;
    }
    EXPECT_EQ(sum, 15);

    sum = 0;
    for (auto it = arr.rbegin(); it != arr.rend(); ++it) {
        sum += *it;
    }
    EXPECT_EQ(sum, 15);
}

TEST(ArrayTest, SizeMethods) {
    ownstl::array<double, 0> empty_arr;
    EXPECT_TRUE(empty_arr.empty());
    EXPECT_EQ(empty_arr.size(), 0);
    
    ownstl::array<char, 255> large_arr;
    EXPECT_EQ(large_arr.size(), 255);
    EXPECT_GT(large_arr.max_size(), 0);
}

TEST(ArrayTest, FillMethod) {
    ownstl::array<int, 4> arr;
    arr.fill(42);
    for (auto val : arr) {
        EXPECT_EQ(val, 42);
    }
}

TEST(ArrayTest, SwapMethod) {
    ownstl::array<int, 3> arr1 = {1, 2, 3};
    ownstl::array<int, 3> arr2 = {4, 5, 6};
    
    arr1.swap(arr2);
    
    EXPECT_EQ(arr1[0], 4);
    EXPECT_EQ(arr1[1], 5);
    EXPECT_EQ(arr1[2], 6);
    
    EXPECT_EQ(arr2[0], 1);
    EXPECT_EQ(arr2[1], 2);
    EXPECT_EQ(arr2[2], 3);
}

TEST(ArrayTest, ConstMethods) {
    const ownstl::array<int, 2> arr = {7, 8};
    EXPECT_EQ(arr.at(0), 7);
    EXPECT_EQ(arr[1], 8);
    EXPECT_EQ(arr.front(), 7);
    EXPECT_EQ(arr.back(), 8);
    EXPECT_NE(arr.data(), nullptr);
    
    auto it = arr.begin();
    EXPECT_EQ(*it, 7);
}

TEST(ArrayTest, MoveSemantics) {
    ownstl::array<std::string, 2> arr1 = {"a", "b"};
    ownstl::array<std::string, 2> arr2 = std::move(arr1);
    
    EXPECT_EQ(arr2[0], "a");
    EXPECT_EQ(arr2[1], "b");
}


int main(int argc, char** argv) 
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}