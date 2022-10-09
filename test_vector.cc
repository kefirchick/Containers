#include <gtest/gtest.h>

#include "s21_vector.h"
#include "vector"

TEST(vector, test_001_push_back) {
  s21::vector<int> myVector01;
  myVector01.push_back(11);
  int expectation = 11;
  ASSERT_TRUE(myVector01[0] == expectation);
}

TEST(vector, test_002_create) {
  s21::vector<int> myVector01 = {11, 12};
  int expectation = 12;
  ASSERT_TRUE(myVector01[1] == expectation);
}

TEST(vector, test_003_move) {
  s21::vector<int> myVector01(1);           // 0
  myVector01.push_back(11);                 // 0 11
  s21::vector<int> myVector02{myVector01};  // 0 11
  myVector02.push_back(12);                 // 0 11 12
  myVector01 = std::move(myVector02);       // 0 11 12
  int expectation = 12;
  ASSERT_TRUE(myVector01[2] == expectation);
}

TEST(vector, test_004_empty) {
  s21::vector<int> myVector01 = {11, 12};
  bool expectation = false;
  ASSERT_TRUE(myVector01.empty() == expectation);
}

TEST(vector, test_005_empty) {
  s21::vector<int> myVector01;
  bool expectation = true;
  ASSERT_TRUE(myVector01.empty() == expectation);
}

TEST(vector, test_006_max_size_char) {
  std::vector<char> stdVector01;
  s21::vector<char> myVector01;
  ASSERT_TRUE(myVector01.max_size() == stdVector01.max_size());
}

TEST(vector, test_007_max_size_int) {
  std::vector<int> stdVector01;
  s21::vector<int> myVector01;
  ASSERT_TRUE(myVector01.max_size() == stdVector01.max_size());
}

TEST(vector, test_008_max_size_double) {
  std::vector<double> stdVector01;
  s21::vector<double> myVector01;
  ASSERT_TRUE(myVector01.max_size() == stdVector01.max_size());
}

TEST(vector, test_009_capacity) {
  s21::vector<double> myVector01;
  size_t expectation = 1;
  ASSERT_TRUE(myVector01.capacity() == expectation);
}

TEST(vector, test_010_capacity) {
  s21::vector<double> myVector01(100);
  size_t expectation = 100;
  ASSERT_TRUE(myVector01.capacity() == expectation);
}

TEST(vector, test_011_capacity) {
  s21::vector<double> myVector01 = {11, 12};
  size_t expectation = 2;
  ASSERT_TRUE(myVector01.capacity() == expectation);
}

TEST(vector, test_012_push_back) {
  s21::vector<double> myVector01;
  for (int i = 0; i < 3; i++) {
    myVector01.push_back(i);
  }
  myVector01.shrink_to_fit();
  size_t expectation = 3;
  ASSERT_TRUE(myVector01.capacity() == expectation);
}

TEST(vector, test_013_insert) {
  s21::vector<int> myVector01 = {11, 12};
  myVector01.insert(myVector01.begin() + 1, 14);
  int expectation = 14;
  ASSERT_TRUE(myVector01[1] == expectation);
}

TEST(vector, test_014_erase) {
  s21::vector<int> myVector01 = {11, 12, 13};
  myVector01.erase(myVector01.begin() + 1);
  int expectation = 13;
  ASSERT_TRUE(myVector01[1] == expectation);
}

TEST(vector, test_015_swap) {
  s21::vector<int> myVector01 = {11, 11};
  s21::vector<int> myVector02 = {12, 12, 12};
  myVector01.swap(myVector02);
  int expectation = 12;
  ASSERT_TRUE(myVector01[2] == expectation);
}

TEST(vector, test_016_equal) {
  s21::vector<int> myVector01 = {11, 12};
  s21::vector<int> myVector02;
  myVector02 = myVector01;
  int expectation = 12;
  ASSERT_TRUE(myVector02[1] == expectation);
}

TEST(vector, test_017_list_emplace) {
  std::vector<int> stdVector;
  stdVector.push_back(11);
  stdVector.push_back(12);
  stdVector.emplace(stdVector.begin(), 13);
  s21::vector<int> myVector;
  myVector.push_back(11);
  myVector.push_back(12);
  myVector.emplace(myVector.begin(), 13);
  ASSERT_TRUE(myVector.front() == stdVector.front());
  ASSERT_TRUE(myVector.size() == stdVector.size());
}

TEST(vector, test_018_emplace_back) {
  s21::vector<int> first_vector;
  first_vector.push_back(11);
  first_vector.push_back(12);
  first_vector.emplace_back(13, 14);
  ASSERT_TRUE(first_vector.back() == 14);
  ASSERT_TRUE(first_vector.size() == 4);
}