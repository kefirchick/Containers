#include <gtest/gtest.h>

#include "s21_map.h"

TEST(map, insert_pair_test) {
  s21::map<int, int> s;
  auto result = s.insert(std::pair<int, int>(1, 10));
  EXPECT_EQ(10, *(result.first));
  EXPECT_EQ(true, result.second);
  result = s.insert(2, 20);
  EXPECT_EQ(20, *(result.first));
  EXPECT_EQ(true, result.second);
  result = s.insert_or_assign(3, 30);
  EXPECT_EQ(30, *(result.first));
  EXPECT_EQ(true, result.second);
  auto it = s.begin();
  EXPECT_EQ(10, *it);
  it = s.end();
  EXPECT_EQ(30, *it);
  result = s.insert(std::pair<int, int>(3, 30));
  EXPECT_EQ(false, result.second);
}

TEST(map, iterator_inc_test) {
  s21::map<int, int> s;
  s.insert(std::pair<int, int>(1, 10));
  s.insert(std::pair<int, int>(3, 30));
  s.insert(std::pair<int, int>(2, 20));
  auto it = s.begin();
  EXPECT_EQ(10, *it);
  ++it;
  EXPECT_EQ(20, *it);
  ++it;
  EXPECT_EQ(30, *it);
  EXPECT_ANY_THROW(++it);
}

TEST(map, iterator_dec_test) {
  s21::map<int, int> s;
  s.insert(std::pair<int, int>(1, 10));
  s.insert(std::pair<int, int>(3, 30));
  s.insert(std::pair<int, int>(2, 20));
  auto it = s.end();
  EXPECT_EQ(30, *it);
  --it;
  EXPECT_EQ(20, *it);
  --it;
  EXPECT_EQ(10, *it);
  EXPECT_ANY_THROW(--it);
}

TEST(map, misc_test) {
  s21::map<int, int> s;
  EXPECT_EQ(true, s.empty());
  EXPECT_EQ(0, s.size());
  s.insert(std::pair<int, int>(1, 10));
  s.insert(std::pair<int, int>(3, 30));
  s.insert(std::pair<int, int>(2, 20));
  EXPECT_EQ(false, s.empty());
  EXPECT_EQ(3, s.size());
  EXPECT_EQ(2147483647, s.max_size());
}

TEST(map, erase_test) {
  s21::map<int, int> s{{1, 10}, {3, 30}, {2, 20}};
  auto it = s.end();
  s.erase(it);
  it = s.begin();
  EXPECT_EQ(10, *it);
  it = s.end();
  EXPECT_EQ(20, *it);
  s.erase(it);
  it = s.end();
  EXPECT_EQ(10, *it);
  it = s.begin();
  EXPECT_EQ(10, *it);
  s.erase(it);
  EXPECT_ANY_THROW(s.erase(it));
}

TEST(map, contains_test) {
  s21::map<int, int> s{{1, 10}, {3, 30}, {2, 20}};
  EXPECT_EQ(true, s.contains(3));
  EXPECT_EQ(false, s.contains(4));
}

TEST(map, copy_constructor_test) {
  s21::map<int, int> s1{{1, 10}, {3, 30}, {2, 20}};
  s21::map<int, int> s2(s1);
  auto it = s2.begin();
  EXPECT_EQ(10, *it);
  ++it;
  EXPECT_EQ(20, *it);
  ++it;
  EXPECT_EQ(30, *it);
}

TEST(map, merge_test) {
  s21::map<int, int> s1{{1, 10}, {3, 30}};
  s21::map<int, int> s2{{2, 20}, {4, 40}};
  s1.merge(s2);
  auto it = s1.begin();
  EXPECT_EQ(10, *it);
  ++it;
  EXPECT_EQ(20, *it);
  ++it;
  EXPECT_EQ(30, *it);
  ++it;
  EXPECT_EQ(40, *it);
}

TEST(map, clear_test) {
  s21::map<int, int> s{{1, 10}, {3, 30}, {2, 20}};
  s.clear();
  EXPECT_EQ(true, s.empty());
  EXPECT_ANY_THROW(s.begin());
}

TEST(map, move_constructor_test) {
  s21::map<int, int> s1{{1, 10}, {3, 30}, {2, 20}};
  s21::map<int, int> s2(std::move(s1));
  auto it = s2.begin();
  EXPECT_EQ(10, *it);
  ++it;
  EXPECT_EQ(20, *it);
  ++it;
  EXPECT_EQ(30, *it);
}

TEST(map, swap_test) {
  s21::map<int, int> s1{{1, 10}, {3, 30}};
  s21::map<int, int> s2{{2, 20}, {4, 40}};
  s1.swap(s2);
  auto it = s2.begin();
  EXPECT_EQ(10, *it);
  ++it;
  EXPECT_EQ(30, *it);
  it = s1.begin();
  EXPECT_EQ(20, *it);
  ++it;
  EXPECT_EQ(40, *it);
}

TEST(map, access_test) {
  s21::map<int, int> s{{1, 10}, {3, 30}, {2, 20}};
  EXPECT_EQ(30, s[3]);
  s[3] = 40;
  EXPECT_EQ(40, s.at(3));
  s.insert_or_assign(3, 30);
  EXPECT_EQ(30, s[3]);
}
