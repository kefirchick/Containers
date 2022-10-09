#include <gtest/gtest.h>

#include "s21_stack.h"

TEST(stack, push_pop_top_test) {
  s21::stack<int> s;
  EXPECT_ANY_THROW(s.top());
  EXPECT_ANY_THROW(s.pop());
  s.push(1);
  s.push(2);
  EXPECT_EQ(2, s.top());
  EXPECT_EQ(2, s.size());
  EXPECT_EQ(false, s.empty());
  s.pop();
  EXPECT_EQ(1, s.top());
  s.pop();
  EXPECT_ANY_THROW(s.top());
  EXPECT_ANY_THROW(s.pop());
  EXPECT_EQ(true, s.empty());
}

TEST(stack, initialize_test) {
  s21::stack<int> s({1, 2, 3, 4, 5});
  EXPECT_EQ(5, s.top());
}

TEST(stack, copy_test) {
  s21::stack<int> s1({1, 2, 3, 4, 5});
  s21::stack<int> s2(s1);
  EXPECT_EQ(5, s2.top());
}

TEST(stack, move_test) {
  s21::stack<int> s1({1, 2, 3, 4, 5});
  s21::stack<int> s2(std::move(s1));
  EXPECT_EQ(5, s2.top());
}

TEST(stack, swap_test) {
  s21::stack<int> s1({1, 2, 3, 4, 5});
  s21::stack<int> s2({5, 4, 3, 2, 1});
  s1.swap(s2);
  EXPECT_EQ(1, s1.top());
  EXPECT_EQ(5, s2.top());
}

TEST(stack, emplace_test) {
  s21::stack<int> s;
  s.emplace_front(1, 2, 3);
  EXPECT_EQ(3, s.top());
}