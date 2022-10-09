#ifndef SRC_S21_ARRAY_H_
#define SRC_S21_ARRAY_H_

#include <cmath>
#include <cstdio>
#include <iostream>

namespace s21 {

template <typename T, unsigned int S>
class array {
 private:
  typedef T value_type;
  typedef T& reference;
  typedef const T& const_reference;
  typedef T* iterator;
  typedef const T* const_iterator;
  typedef size_t size_type;

  iterator ptr_;
  size_t size_ = 1;

 public:
  array() {
    if (S == 0) throw std::out_of_range("ERROR: Arrays size can`t be zerro");
    size_ = S;
    ptr_ = new T[size_];
  }

  array(std::initializer_list<value_type> const& items) : array() {
    size_type iter = 0;
    for (auto i : items) {
      ptr_[iter] = i;
      iter++;
    }
  }

  array(const array& a) : array() {
    size_ = a.size_;
    this->data_copy(a);
  }

  array(array&& a) : array() {
    size_ = a.size_;
    this->data_copy(a);
    delete[] ptr_;
    ptr_ = nullptr;
    size_ = 0;
  }

  ~array() {
    delete[] ptr_;
    ptr_ = nullptr;
    size_ = 0;
  }

  void operator=(array& a) {
    if (&a != this) {
      size_ = a.size_;
      ptr_ = a.ptr_;
      a.size_ = 0;
      delete[] a.ptr_;
    }
  }

  reference at(size_type pos) {
    if (pos > size_ - 1 || ptr_ == nullptr)
      throw std::out_of_range("ERROR: Out of range");
    return ptr_[pos];
  }

  reference operator[](size_type pos) { return ptr_[pos]; }

  const_reference front() { return ptr_[0]; }

  const_reference back() { return ptr_[size_ - 1]; }

  iterator data() { return ptr_; }

  iterator begin() { return &ptr_[0]; }

  iterator end() { return &ptr_[size_]; }

  bool empty() {
    bool answer = false;
    if (size_ == 0) answer = true;
    return answer;
  }

  size_type size() { return size_; }

  size_type max_size() { return size_; }

  void swap(array& other) {
    T* tmp = ptr_;
    ptr_ = other.ptr_;
    other.ptr_ = tmp;
    tmp = nullptr;
    delete[] tmp;
  }

  void fill(const_reference value) {
    for (size_type pos = 0; pos < size_; pos++) ptr_[pos] = value;
  }

  void data_copy(const array& a) {
    for (size_type i = 0; i < a.size_; i++) ptr_[i] = a.ptr_[i];
  }
};
}  // namespace s21

#endif  //  SRC_S21_ARRAY_H_
