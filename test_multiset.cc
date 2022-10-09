#include <gtest/gtest.h>

#include "s21_multiset.h"

TEST(multiset, insert_test) {
  s21::multiset<int> s;
  auto result = s.insert(1);
  EXPECT_EQ(1, *(result.first));
  EXPECT_EQ(true, result.second);
  result = s.insert(3);
  EXPECT_EQ(3, *(result.first));
  EXPECT_EQ(true, result.second);
  result = s.insert(2);
  EXPECT_EQ(2, *(result.first));
  EXPECT_EQ(true, result.second);
  auto it = s.begin();
  EXPECT_EQ(1, *it);
  it = s.end();
  EXPECT_EQ(3, *it);
}

TEST(multiset, iterator_inc_test) {
  s21::multiset<int> s;
  s.insert(1);
  s.insert(2);
  s.insert(2);
  auto it = s.begin();
  EXPECT_EQ(1, *it);
  ++it;
  EXPECT_EQ(2, *it);
  ++it;
  EXPECT_EQ(2, *it);
  EXPECT_ANY_THROW(++it);
}

TEST(multiset, iterator_dec_test) {
  s21::multiset<int> s;
  s.insert(1);
  s.insert(3);
  s.insert(2);
  auto it = s.end();
  EXPECT_EQ(3, *it);
  --it;
  EXPECT_EQ(2, *it);
  --it;
  EXPECT_EQ(1, *it);
  EXPECT_ANY_THROW(--it);
}

TEST(multiset, misc_test) {
  s21::multiset<int> s;
  EXPECT_EQ(true, s.empty());
  EXPECT_EQ(0, s.size());
  s.insert(1);
  s.insert(3);
  s.insert(2);
  EXPECT_EQ(false, s.empty());
  EXPECT_EQ(3, s.size());
  EXPECT_EQ(2147483647, s.max_size());
}

TEST(multiset, erase_test) {
  s21::multiset<int> s{1, 3, 2};
  auto it = s.end();
  s.erase(it);
  it = s.begin();
  EXPECT_EQ(1, *it);
  it = s.end();
  EXPECT_EQ(2, *it);
  s.erase(it);
  it = s.end();
  EXPECT_EQ(1, *it);
  it = s.begin();
  EXPECT_EQ(1, *it);
  s.erase(it);
  EXPECT_ANY_THROW(s.erase(it));
}

TEST(multiset, find_test) {
  s21::multiset<int> s;
  s.insert(1);
  s.insert(3);
  s.insert(2);
  auto it = s.find(3);
  EXPECT_EQ(3, *it);
  it = s.find(2);
  EXPECT_EQ(2, *it);
  it = s.find(1);
  EXPECT_EQ(1, *it);
}

TEST(multiset, contains_test) {
  s21::multiset<int> s;
  s.insert(1);
  s.insert(3);
  s.insert(2);
  s.contains(3);
  EXPECT_EQ(true, s.contains(3));
  EXPECT_EQ(false, s.contains(4));
}

TEST(multiset, copy_constructor_test) {
  s21::multiset<int> s1{1, 3, 2};
  s21::multiset<int> s2(s1);
  auto it = s2.begin();
  EXPECT_EQ(1, *it);
  ++it;
  EXPECT_EQ(2, *it);
  ++it;
  EXPECT_EQ(3, *it);
}

TEST(multiset, merge_test) {
  s21::multiset<int> s1{1, 3};
  s21::multiset<int> s2{2, 4};
  s1.merge(s2);
  auto it = s1.begin();
  EXPECT_EQ(1, *it);
  ++it;
  EXPECT_EQ(2, *it);
  ++it;
  EXPECT_EQ(3, *it);
  ++it;
  EXPECT_EQ(4, *it);
}

TEST(multiset, clear_test) {
  s21::multiset<int> s{1, 2, 3};
  s.clear();
  EXPECT_EQ(true, s.empty());
  EXPECT_ANY_THROW(s.begin());
}

TEST(multiset, move_constructor_test) {
  s21::multiset<int> s1{1, 2, 3};
  s21::multiset<int> s2(std::move(s1));
  auto it = s2.begin();
  EXPECT_EQ(1, *it);
  ++it;
  EXPECT_EQ(2, *it);
  ++it;
  EXPECT_EQ(3, *it);
}

TEST(multiset, swap_test) {
  s21::multiset<int> s1{1, 2, 3};
  s21::multiset<int> s2{4};
  s1.swap(s2);
  auto it = s2.begin();
  EXPECT_EQ(1, *it);
  ++it;
  EXPECT_EQ(2, *it);
  ++it;
  EXPECT_EQ(3, *it);
  it = s1.begin();
  EXPECT_EQ(4, *it);
}

TEST(multiset, emplace_test) {
  s21::multiset<int> s;
  auto v = s.emplace(1, 2, 3);
  EXPECT_EQ(1, *(v[0].first));
  EXPECT_EQ(2, *(v[1].first));
  EXPECT_EQ(3, *(v[2].first));
  auto it = s.begin();
  EXPECT_EQ(1, *it);
  ++it;
  EXPECT_EQ(2, *it);
  ++it;
  EXPECT_EQ(3, *it);
}