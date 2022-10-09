#include <gtest/gtest.h>

#include "array"
#include "s21_array.h"

TEST(array, test_001_create_copy_move_at) {
  std::array<int, 2> stdArray01 = {11, 12};
  std::array<int, 2> stdArray02 = std::move(stdArray01);
  std::array<int, 2> stdArray03(stdArray02);
  s21::array<int, 2> myArray01 = {11, 12};
  s21::array<int, 2> myArray02 = std::move(myArray01);
  s21::array<int, 2> myArray03(myArray01);
  ASSERT_TRUE(myArray03.at(0) == stdArray03.at(0) &&
              myArray03.at(1) == stdArray03.at(1));
}

TEST(array, test_002_front) {
  std::array<int, 3> stdArray01 = {11, 12, 13};
  s21::array<int, 3> myArray01 = {11, 12, 13};
  ASSERT_TRUE(myArray01.front() == stdArray01.front());
}

TEST(array, test_003_back) {
  std::array<int, 3> stdArray01 = {11, 12, 13};
  s21::array<int, 3> myArray01 = {11, 12, 13};
  ASSERT_TRUE(myArray01.back() == stdArray01.back());
}

TEST(array, test_004_data) {
  std::array<int, 3> stdArray01 = {11, 12, 13};
  s21::array<int, 3> myArray01 = {11, 12, 13};
  ASSERT_TRUE(*myArray01.data() == *stdArray01.data());
}

TEST(array, test_005_begin) {
  std::array<int, 3> stdArray01 = {11, 12, 13};
  s21::array<int, 3> myArray01 = {11, 12, 13};
  ASSERT_TRUE(*myArray01.begin() == *stdArray01.begin());
}

TEST(array, test_006_end) {
  std::array<int, 3> stdArray01 = {11, 12, 13};
  s21::array<int, 3> myArray01 = {11, 12, 13};
  ASSERT_TRUE(*(myArray01.end() - 1) == *(stdArray01.end() - 1));
}

TEST(array, test_007_empty) {
  std::array<int, 3> stdArray01 = {11, 12, 13};
  s21::array<int, 3> myArray01 = {11, 12, 13};
  ASSERT_TRUE(myArray01.empty() == stdArray01.empty());
}

TEST(array, test_008_size) {
  std::array<int, 3> stdArray01 = {11, 12, 13};
  s21::array<int, 3> myArray01 = {11, 12, 13};
  ASSERT_TRUE(myArray01.size() == stdArray01.size());
}

TEST(array, test_009_max_size) {
  std::array<int, 3> stdArray01 = {11, 12, 13};
  s21::array<int, 3> myArray01 = {11, 12, 13};
  ASSERT_TRUE(myArray01.max_size() == stdArray01.max_size());
}

TEST(array, test_010_swap) {
  std::array<int, 3> stdArray01 = {11, 12, 13};
  std::array<int, 3> stdArray02 = {14, 15, 16};
  stdArray01.swap(stdArray02);
  s21::array<int, 3> myArray01 = {11, 12, 13};
  s21::array<int, 3> myArray02 = {14, 15, 16};
  myArray01.swap(myArray02);
  ASSERT_TRUE(stdArray01[0] == myArray01[0]);
}

TEST(array, test_011_fill) {
  std::array<int, 3> stdArray01;
  stdArray01.fill(11);
  s21::array<int, 3> myArray01;
  myArray01.fill(11);
  ASSERT_TRUE(myArray01[0] == stdArray01[0]);
}