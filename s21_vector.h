#ifndef SRC_S21_VECTOR_H_
#define SRC_S21_VECTOR_H_

#include <cmath>
#include <cstdio>
#include <iostream>

namespace s21 {

template <typename T>
class vector {
 private:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using iterator = T *;
  using const_iterator = const T *;
  using size_type = size_t;

  size_t capacity_;
  size_t size_ = 1;
  T *ptr_;

 public:
  vector() : capacity_(1) {
    size_ = 0;
    ptr_ = new T[capacity_]();
  }

  vector(size_type n) {
    size_ = n;
    capacity_ = size_;
    ptr_ = new T[capacity_]();
  }

  vector(std::initializer_list<value_type> const list) {
    size_ = 0;
    capacity_ = size_ + 1;
    ptr_ = new T[capacity_]();
    for (auto i : list) {
      ptr_[size_++] = i;
      capacity_ = size_;
    }
  }

  vector(const vector &v) : capacity_(v.capacity_), ptr_(v.ptr_) {
    size_ = v.size_;
  }

  vector(vector &&v) : capacity_(v.capacity_), ptr_(v.ptr_) {
    size_ = v.size_;
    v.ptr_ = nullptr;
    v.size_ = 0;
  }

  ~vector() {
    delete[] ptr_;
    size_ = capacity_ = 0;
    ptr_ = nullptr;
  }

  void operator=(const vector &v) {
    if (&v == this)
      throw std::out_of_range("ERROR: Cannot copy a vector to itself");
    delete[] ptr_;
    size_ = v.size_;
    capacity_ = v.capacity_;
    ptr_ = new T[capacity_]();
    this->data_copy(v);
  }

  void operator=(vector &&v) {
    // std::cout << "---===MOVE===---" << std::endl;
    if (&v == this)
      throw std::out_of_range("ERROR: Cannot move a vector to itself");
    // delete[] ptr_;
    // ptr_ = v.ptr_;
    // size_ = v.size_;
    // capacity_ = v.capacity_;
    clear();
    size_ = v.size_;
    capacity_ = v.capacity_;
    ptr_ = new T[capacity_]();
    this->data_copy(v);
    // v.clear();
    // v.size_ = v.capacity_ = 0;
    // v.ptr_ = nullptr;
  }

  reference at(size_type pos) {
    if (pos > size_ - 1)
      throw std::out_of_range(
          "ERROR: terminate called after throwing an instance of "
          "'S21::out_of_range'");
    return ptr_[pos];
  }

  reference operator[](size_type pos) {
    if (pos > size_ - 1)
      throw std::out_of_range(
          "ERROR: terminate called after throwing an instance of "
          "'S21::out_of_range'");
    return ptr_[pos];
  }

  const_reference front() { return ptr_[0]; }

  const_reference back() { return ptr_[size_ - 1]; }

  iterator data() { return &ptr_[0]; }

  iterator begin() { return &ptr_[0]; }

  iterator end() { return &ptr_[size_]; }

  bool empty() {
    bool answer = false;
    if (size_ == 0) answer = true;
    return answer;
  }

  size_type size() { return size_; }

  size_type max_size() {
    size_type n = pow(2, 63) / sizeof(T);
    n--;
    return n;
  }

  void reserve(size_type newCapacity) {
    T *p = ptr_;
    ptr_ = new T[newCapacity]();
    for (size_type i = 0; i < size_; i++) ptr_[i] = p[i];
    capacity_ = newCapacity;
    delete[] p;
    p = nullptr;
  }

  size_type capacity() { return capacity_; }

  void shrink_to_fit() {
    if (capacity_ == size_) return;
    reserve(size_);
  }

  void clear() {
    if (size_ == 0) return;
    for (size_t i = 0; i < size_; i++) {
      ptr_[i] = 0;
    }
    size_ = capacity_ = 0;
  }

  iterator insert(iterator pos, const_reference value) {
    iterator it = pos;
    T *p = ptr_;
    if (size_ >= capacity_ - 1) capacity_ = capacity_ * 2;
    delete[] ptr_;
    ptr_ = new T[capacity_]();
    size_++;
    for (size_type i = 0, j = 0; i < size_; i++, j++) {
      if (pos == &p[i]) {
        ptr_[j] = value;
        it = &ptr_[j];
        j++;
      }
      ptr_[j] = p[i];
    }
    return it;
  }

  void erase(iterator pos) {
    T *p = ptr_;
    delete[] ptr_;
    ptr_ = new T[capacity_ * 2]();
    size_--;
    for (size_type i = 0, j = 0; i < size_; i++, j++) {
      if (pos == &p[i]) i++;
      ptr_[j] = p[i];
    }
  }

  void push_back(T data) {
    if (size_ == capacity_) reserve(2 * capacity_);
    ptr_[size_++] = data;
  }

  void pop_back() { ptr_[size_--] = 0; }

  void swap(vector &other) {
    T *p = ptr_;
    size_type psize_ = size_;
    size_type pcapacity_ = capacity_;
    ptr_ = other.ptr_;
    size_ = other.size_;
    capacity_ = other.capacity_;
    other.size_ = psize_;
    other.capacity_ = pcapacity_;
    other.ptr_ = p;
    // delete[] p;
    // p = nullptr;
    // std::cout << "---===SWAP===---" << std::endl;
  }

  void data_copy(const vector &V) {
    for (size_type i = 0; i < V.size_; i++) ptr_[i] = V.ptr_[i];
  }

  template <typename... Args>
  iterator emplace(const_iterator pos, Args &&...args) {
    vector<T> temp({args...});
    iterator it = (T *)pos;
    for (int i = temp.size() - 1; i >= 0; --i) it = insert(it, temp[i]);
    return it;
  }

  template <class... Args>
  void emplace_back(Args &&...args) {
    std::initializer_list<T> arg{args...};
    for (auto &val : arg) push_back(val);
  }
};
}  // namespace s21
#endif  //  SRC_S21_VECTOR_H_
