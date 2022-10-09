#ifndef SRC_S21_STACK_H_
#define SRC_S21_STACK_H_

#include <cstdio>
#include <iostream>
#include <vector>

namespace s21 {

template <typename T>
class stack {
 private:
  struct node {
    node *p;
    T val;
  };

  size_t _size;
  node *_head;

  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using size_type = size_t;

 private:
  void reverse_copy(const stack &src) {
    if (!src._head) return;
    node element = *src._head;
    push(element.val);
    while (element.p) {
      element = *element.p;
      push(element.val);
    }
  }

  void clear_stack() {
    while (_head) {
      pop();
    }
    _size = 0;
    _head = nullptr;
  }

 public:
  stack() : _size(0), _head(nullptr) {}

  explicit stack(std::initializer_list<value_type> const &list) : stack() {
    for (auto element : list) {
      push(element);
    }
  }

  stack(const stack &other) : stack() { *this = other; }

  stack(stack &&other) : stack() { *this = std::move(other); }

  ~stack() { clear_stack(); }

  const_reference top() {
    if (!_head) throw std::out_of_range("ERROR: Stack is empty");
    return _head->val;
  }

  bool empty() { return !_size; }

  size_type size() { return _size; }

  void push(const_reference value) {
    node *temp = new node;
    _size++;
    temp->val = value;
    temp->p = _head;
    _head = temp;
  }

  void pop() {
    if (!_head) throw std::out_of_range("ERROR: Stack is empty");
    node *temp = _head->p;
    delete _head;
    _size--;
    _head = (_size) ? temp : nullptr;
  }

  void swap(stack &other) {
    stack temp = *this;
    *this = other;
    other = temp;
  }

  stack &operator=(const stack &other) {
    if (!other._head || this == &other) return *this;
    clear_stack();
    stack temp;
    temp.reverse_copy(other);
    reverse_copy(temp);
    return *this;
  }

  stack &operator=(stack &&other) {
    if (!other._head || this == &other) return *this;
    clear_stack();
    stack temp;
    temp.reverse_copy(other);
    reverse_copy(temp);
    other.clear_stack();
    return *this;
  }

  template <typename... Args>
  void emplace_front(Args &&...args) {
    std::vector<value_type> values{args...};
    for (auto value : values) push(value);
  }
};
}  // namespace s21
#endif  //  SRC_S21_STACK_H_
