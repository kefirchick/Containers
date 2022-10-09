#ifndef SRC_S21_QUEUE_H_
#define SRC_S21_QUEUE_H_

#include <cstdio>
#include <iostream>

#include "s21_vector.h"

namespace s21 {

template <typename T>
class queue {
 private:
  struct node {
    node *p;
    T val;
  };

  size_t _size;
  node *_head, *_tail;

  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using size_type = size_t;

 private:
  void clear_queue() {
    while (_head) {
      pop();
    }
  }

  void reverse_copy(const queue &src) {
    if (!src._tail) return;
    clear_queue();
    node element = *src._tail;
    push(element.val);
    while (element.p) {
      element = *element.p;
      push(element.val);
    }
  }

 public:
  queue() : _size(0), _head(nullptr), _tail(nullptr) {}

  explicit queue(std::initializer_list<value_type> const &list) : queue() {
    for (auto element : list) {
      push(element);
    }
  }

  queue(const queue &other) : queue() { *this = other; }

  queue(queue &&other) : queue() { *this = std::move(other); }

  ~queue() { clear_queue(); }

  const_reference front() {
    if (!_head) throw std::out_of_range("ERROR: Queue is empty");
    return _head->val;
  }

  const_reference back() {
    if (!_tail) throw std::out_of_range("ERROR: Queue is empty");
    return _tail->val;
  }

  bool empty() { return !_size; }

  size_type size() { return _size; }

  void push(const_reference value) {
    node *temp = new node;
    _size++;
    temp->val = value;
    temp->p = _tail;
    _tail = temp;
    if (_size == 1) _head = temp;
  }

  void pop() {
    if (!_head) throw std::out_of_range("ERROR: Stack is empty");
    delete _head;
    _size--;
    if (_size == 0) {
      _head = nullptr;
      _tail = nullptr;
      return;
    }
    _head = _tail;
    for (size_type i = 1; i < _size; ++i) {
      _head = _head->p;
    }
    _head->p = nullptr;
  }

  void swap(queue &other) {
    queue temp = *this;
    *this = other;
    other = temp;
  }

  queue &operator=(const queue &other) {
    if (!other._head || this == &other) return *this;
    clear_queue();
    _size = 0;
    queue temp;
    temp.reverse_copy(other);
    reverse_copy(temp);
    return *this;
  }

  queue &operator=(queue &&other) {
    if (!other._head || this == &other) return *this;
    clear_queue();
    _size = 0;
    queue temp;
    temp.reverse_copy(other);
    reverse_copy(temp);
    other.clear_queue();
    return *this;
  }

  template <typename... Args>
  void emplace_back(Args &&...args) {
    s21::vector<value_type> values{args...};
    for (auto value : values) push(value);
  }
};
}  // namespace s21

#endif  //  SRC_S21_QUEUE_H_
