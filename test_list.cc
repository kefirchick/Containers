#include <gtest/gtest.h>

#include "list"
#include "s21_list.h"

TEST(list, test_001_begin) {
  std::list<int> std_list;
  for (int j = 11; j < 15; ++j) {
    std_list.push_front(j);
  }
  s21::list<int> the_list;
  for (int i = 11; i < 15; ++i) {
    the_list.push_front(i);
  }
  ASSERT_TRUE(*the_list.begin() == *std_list.begin());
}

TEST(list, test_003_front) {
  std::list<int> std_list;
  for (int j = 11; j < 15; ++j) {
    std_list.push_front(j);
  }
  s21::list<int> the_list;
  for (int i = 11; i < 15; ++i) {
    the_list.push_front(i);
  }
  ASSERT_TRUE(the_list.front() == std_list.front());
}

TEST(list, test_004_back) {
  std::list<int> std_list;
  for (int j = 11; j < 15; ++j) {
    std_list.push_front(j);
  }
  s21::list<int> the_list;
  for (int i = 11; i < 15; ++i) {
    the_list.push_front(i);
  }
  ASSERT_TRUE(the_list.back() == std_list.back());
}

TEST(list, test_005_empty) {
  s21::list<int> the_list;
  ASSERT_TRUE(the_list.empty() == true);
}

TEST(list, test_006_empty) {
  s21::list<int> the_list;
  for (int i = 11; i < 15; ++i) {
    the_list.push_front(i);
  }
  ASSERT_TRUE(the_list.empty() == false);
}

TEST(list, test_007_size) {
  s21::list<int> the_list(4);
  size_t size = the_list.size();
  size_t expectation = 4;
  ASSERT_TRUE(size == expectation);
}

TEST(list, test_008_max_size) {
  std::list<int> std_list;
  size_t expectation = std_list.max_size();
  s21::list<int> the_list;
  size_t ans = the_list.max_size();
  ASSERT_TRUE(ans == expectation);
}

TEST(list, test_009_clear) {
  s21::list<int> the_list;
  for (int i = 11; i < 15; ++i) {
    the_list.push_front(i);
  }
  the_list.clear();
  ASSERT_TRUE(the_list.size() == 0);
}

TEST(list, test_010_insert) {
  std::list<int> std_list;
  for (int j = 11; j < 15; ++j) {
    std_list.push_back(j);
  }
  auto std_it = std_list.begin();
  std_list.insert(++std_it, 99);
  s21::list<int> the_list;
  for (int j = 11; j < 15; ++j) {
    the_list.push_back(j);
  }
  auto the_it = the_list.begin();
  the_list.insert(++the_it, 99);
  ASSERT_TRUE(the_list.size() == std_list.size());
}

TEST(list, test_011_erase) {
  std::list<int> std_list;
  for (int j = 11; j < 15; ++j) {
    std_list.push_back(j);
  }
  auto std_it = std_list.begin();
  std_list.erase(++std_it);
  s21::list<int> the_list;
  for (int j = 11; j < 15; ++j) {
    the_list.push_back(j);
  }
  auto the_it = the_list.begin();
  the_list.erase(++the_it);
  ASSERT_TRUE(the_list.size() == std_list.size());
}

TEST(list, test_012_push_back) {
  std::list<int> std_list;
  for (int j = 11; j < 15; ++j) {
    std_list.push_back(j);
  }
  s21::list<int> the_list;
  for (int j = 11; j < 15; ++j) {
    the_list.push_back(j);
  }
  ASSERT_TRUE(the_list.size() == std_list.size());
}

TEST(list, test_013_pop_back) {
  std::list<int> std_list;
  for (int j = 11; j < 15; ++j) {
    std_list.push_back(j);
  }
  std_list.pop_back();
  s21::list<int> the_list;
  for (int j = 11; j < 15; ++j) {
    the_list.push_back(j);
  }
  the_list.pop_back();
  ASSERT_TRUE(the_list.size() == std_list.size());
}

TEST(list, test_014_push_front) {
  std::list<int> std_list;
  for (int j = 11; j < 15; ++j) {
    std_list.push_front(j);
  }
  s21::list<int> the_list;
  for (int j = 11; j < 15; ++j) {
    the_list.push_front(j);
  }
  ASSERT_TRUE(the_list.size() == std_list.size());
}

TEST(list, test_015_pop_front) {
  std::list<int> std_list;
  for (int j = 11; j < 15; ++j) {
    std_list.push_back(j);
  }
  std_list.pop_front();
  s21::list<int> the_list;
  for (int i = 11; i < 15; ++i) {
    the_list.push_front(i);
  }
  the_list.pop_front();
  ASSERT_TRUE(the_list.size() == std_list.size());
}

TEST(list, test_016_swap) {
  std::list<int> std_first_list;
  for (int j = 11; j < 15; ++j) {
    std_first_list.push_back(j);
  }
  std::list<int> std_second_list;
  for (int i = 14; i < 19; ++i) {
    std_second_list.push_back(i);
  }
  std_first_list.swap(std_second_list);

  s21::list<int> first_list;
  for (int j = 11; j < 15; ++j) {
    first_list.push_back(j);
  }
  s21::list<int> second_list;
  for (int i = 14; i < 19; ++i) {
    second_list.push_back(i);
  }
  first_list.swap(second_list);
  ASSERT_TRUE(first_list.size() == std_first_list.size());
}

TEST(list, test_017_merge) {
  std::list<int> std_first_list;
  for (int j = 11; j < 14; ++j) {
    std_first_list.push_back(j);
  }
  std::list<int> std_second_list;
  for (int i = 14; i < 18; ++i) {
    std_second_list.push_back(i);
  }
  std_first_list.merge(std_second_list);
  s21::list<int> first_list;
  for (int j = 11; j < 14; ++j) {
    first_list.push_back(j);
  }
  s21::list<int> second_list;
  for (int i = 14; i < 18; ++i) {
    second_list.push_back(i);
  }
  first_list.merge(second_list);
  ASSERT_TRUE(first_list.size() == std_first_list.size());
}

TEST(list, test_018_splice) {
  std::list<int> std_first_list;
  for (int j = 11; j < 14; ++j) {
    std_first_list.push_back(j);
  }
  std::list<int> std_second_list;
  for (int i = 14; i < 16; ++i) {
    std_second_list.push_back(i);
  }
  auto std_it = std_first_list.begin();
  std_first_list.splice(std_it, std_second_list);
  s21::list<int> first_list;
  for (int j = 11; j < 14; ++j) {
    first_list.push_back(j);
  }
  s21::list<int> second_list;
  for (int i = 14; i < 16; ++i) {
    second_list.push_back(i);
  }
  auto it = first_list.begin();
  first_list.splice(it, second_list);
  ASSERT_TRUE(first_list.size() == std_first_list.size());
}

TEST(list, test_019_splice) {
  std::list<int> std_first_list;
  for (int j = 11; j < 14; ++j) {
    std_first_list.push_back(j);
  }
  std::list<int> std_second_list;
  for (int i = 14; i < 16; ++i) {
    std_second_list.push_back(i);
  }
  auto std_it = std_first_list.begin();
  std_first_list.splice(++std_it, std_second_list);
  s21::list<int> first_list;
  for (int j = 11; j < 14; ++j) {
    first_list.push_back(j);
  }
  s21::list<int> second_list;
  for (int i = 14; i < 16; ++i) {
    second_list.push_back(i);
  }
  auto it = first_list.begin();
  first_list.splice(++it, second_list);
  ASSERT_TRUE(first_list.size() == std_first_list.size());
}

TEST(list, test_020_reverse) {
  std::list<int> std_first_list;
  for (int j = 11; j < 14; ++j) {
    std_first_list.push_back(j);
  }
  std_first_list.reverse();
  s21::list<int> first_list;
  for (int j = 11; j < 14; ++j) {
    first_list.push_back(j);
  }
  first_list.reverse();
  ASSERT_TRUE(std_first_list.size() == first_list.size());
}

TEST(list, test_021_unique) {
  std::list<int> std_first_list;
  std_first_list.push_back(1);
  std_first_list.push_back(2);
  std_first_list.push_back(2);
  std_first_list.push_back(3);
  std_first_list.push_back(3);
  std_first_list.push_back(3);
  std_first_list.push_back(1);
  std_first_list.unique();
  s21::list<int> first_list;
  first_list.push_back(1);
  first_list.push_back(2);
  first_list.push_back(2);
  first_list.push_back(3);
  first_list.push_back(3);
  first_list.push_back(3);
  first_list.push_back(1);
  first_list.unique();
  ASSERT_TRUE(std_first_list.size() == first_list.size());
}

TEST(list, test_022_sort) {
  std::list<int> std_first_list;
  std_first_list.push_back(2);
  std_first_list.push_back(4);
  std_first_list.push_back(1);
  std_first_list.push_back(3);
  std_first_list.push_back(2);
  std_first_list.sort();
  s21::list<int> first_list;
  first_list.push_back(2);
  first_list.push_back(4);
  first_list.push_back(1);
  first_list.push_back(3);
  first_list.push_back(2);
  first_list.sort();
  ASSERT_TRUE(*std_first_list.begin() == *first_list.begin());
}

TEST(list, test_023_iterator) {
  std::list<int> std_first_list;
  std_first_list.push_back(2);
  std_first_list.push_back(4);
  std_first_list.push_back(1);
  std_first_list.push_back(3);
  std_first_list.push_back(2);
  std::list<int>::iterator std_list_iter = std_first_list.begin();
  s21::list<int> first_list;
  first_list.push_back(2);
  first_list.push_back(4);
  first_list.push_back(1);
  first_list.push_back(3);
  first_list.push_back(2);
  s21::list<int>::iterator list_iter = first_list.begin();
  ASSERT_TRUE(*std_list_iter == *list_iter);
}

TEST(list, test_024_list_emplace) {
  s21::list<int> first_list;
  first_list.push_back(11);
  first_list.push_back(12);
  auto it = first_list.begin();
  first_list.emplace(it, 13, 14);
  ASSERT_TRUE(first_list.front() == 14);
  ASSERT_TRUE(first_list.size() == 4);
}

TEST(list, test_025_emplace_back) {
  s21::list<int> first_list;
  first_list.push_back(11);
  first_list.push_back(12);
  first_list.emplace_back(13, 14);
  ASSERT_TRUE(first_list.back() == 14);
  ASSERT_TRUE(first_list.size() == 4);
}

TEST(list, test_026_emplace_front) {
  s21::list<int> first_list;
  first_list.push_back(11);
  first_list.push_back(12);
  first_list.emplace_front(13, 14);
  ASSERT_TRUE(first_list.front() == 14);
  ASSERT_TRUE(first_list.size() == 4);
}

TEST(list, test_027_move_constructor) {
  s21::list<int> first_list{1, 2, 3};
  s21::list<int> second_list(std::move(first_list));
  auto it = second_list.begin();
  EXPECT_EQ(1, *it);
  ++it;
  EXPECT_EQ(2, *it);
  ++it;
  EXPECT_EQ(3, *it);
}
