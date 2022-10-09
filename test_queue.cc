#include <gtest/gtest.h>

#include "s21_queue.h"

TEST(queue, push_pop_front_back_test) {
  s21::queue<int> q;
  EXPECT_ANY_THROW(q.front());
  EXPECT_ANY_THROW(q.back());
  EXPECT_ANY_THROW(q.pop());
  q.push(1);
  q.push(2);
  EXPECT_EQ(1, q.front());
  EXPECT_EQ(2, q.back());
  EXPECT_EQ(false, q.empty());
  q.pop();
  EXPECT_EQ(2, q.front());
  EXPECT_EQ(2, q.back());
  q.pop();
  EXPECT_ANY_THROW(q.front());
  EXPECT_ANY_THROW(q.back());
  EXPECT_ANY_THROW(q.pop());
  EXPECT_EQ(true, q.empty());
}

TEST(queue, initialize_test) {
  s21::queue<int> q({1, 2, 3, 4, 5});
  EXPECT_EQ(1, q.front());
  EXPECT_EQ(5, q.back());
}

TEST(queue, copy_test) {
  s21::queue<int> q1({1, 2, 3, 4, 5});
  s21::queue<int> q2(q1);
  EXPECT_EQ(1, q2.front());
  EXPECT_EQ(5, q2.back());
}

TEST(queue, move_test) {
  s21::queue<int> q1({1, 2, 3, 4, 5});
  s21::queue<int> q2(std::move(q1));
  EXPECT_EQ(1, q2.front());
  EXPECT_EQ(5, q2.back());
}

TEST(queue, swap_test) {
  s21::queue<int> q1({1, 2, 3, 4, 5});
  s21::queue<int> q2({5, 4, 3, 2, 1});
  q2.swap(q1);
  EXPECT_EQ(5, q1.front());
  EXPECT_EQ(1, q1.back());
  EXPECT_EQ(1, q2.front());
  EXPECT_EQ(5, q2.back());
}

TEST(queue, emplace_test) {
  s21::queue<int> q;
  q.emplace_back(1, 2, 3);
  EXPECT_EQ(1, q.front());
  EXPECT_EQ(3, q.back());
}