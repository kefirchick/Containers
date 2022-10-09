#ifndef SRC_S21_MULTISET_H_
#define SRC_S21_MULTISET_H_

#include <cstdio>
#include <iostream>
#include <limits>

#include "s21_vector.h"

namespace s21 {

template <typename T>
class multiset {
 public:
  using key_type = T;
  using value_type = T;
  using reference = T &;
  using const_iterator = const class iterator;
  using const_reference = const T &;
  using size_type = size_t;

  class node {
   public:
    node *left, *right, *parent;
    value_type val;

    node() : left(nullptr), right(nullptr), parent(nullptr) {}

    node(node *p, value_type v)
        : left(nullptr), right(nullptr), parent(p), val(v) {
      if (!p) return;
      if (*p > v) {
        p->left = this;
      } else {
        p->right = this;
      }
    }

    bool left_child() {
      if (!parent) return false;
      return this == parent->left;
    }

    bool right_child() {
      if (!parent) return false;
      return this == parent->right;
    }

    bool operator>(value_type value) { return val > value; }

    bool operator<(value_type value) { return val < value; }
  };

  class iterator {
   public:
    node *ptr;

    iterator() : ptr(nullptr) {}

    value_type operator*() {
      if (!ptr) throw std::out_of_range("ERROR: multiset is empty");
      return ptr->val;
    }

    bool operator==(const iterator &other) {
      if (!ptr) throw std::out_of_range("ERROR: multiset is empty");
      return this->ptr->val == other.ptr->val;
    }

    bool operator!=(const iterator &other) {
      if (!ptr) throw std::out_of_range("ERROR: multiset is empty");
      return this->ptr->val != other.ptr->val;
    }

    iterator operator++() {
      if (!ptr) throw std::out_of_range("ERROR: multiset is empty");
      if (ptr->right) {
        ptr = ptr->right;
        while (ptr->left) ptr = ptr->left;
        return *this;
      }
      while (ptr->parent) {
        if (ptr->left_child()) {
          ptr = ptr->parent;
          return *this;
        }
        ptr = ptr->parent;
      }
      throw std::out_of_range("ERROR: end of multiset");
      return *this;
    }

    iterator operator--() {
      if (!ptr) throw std::out_of_range("ERROR: multiset is empty");
      if (ptr->left) {
        ptr = ptr->left;
        while (ptr->right) ptr = ptr->right;
        return *this;
      }
      while (ptr->parent) {
        if (ptr->right_child()) {
          ptr = ptr->parent;
          return *this;
        }
        ptr = ptr->parent;
      }
      throw std::out_of_range("ERROR: begin of multiset");
      return *this;
    }
  };

  size_type _size;
  node *_root;

 private:
  node *insert_node(const value_type &value) {
    node *current = _root;
    node *temp_parent = nullptr;
    while (current) {
      if (*current > value) {
        temp_parent = current;
        current = current->left;
      } else {
        temp_parent = current;
        current = current->right;
      }
    }
    current = new node(temp_parent, value);
    return current;
  }

  void erase_node(node *n) {
    node *temp = nullptr;
    if (n->left) temp = n->left;
    if (n->right) temp = n->right;
    if (temp) temp->parent = n->parent;
    if (n->left_child()) n->parent->left = temp;
    if (n->right_child()) n->parent->right = temp;
    if (n == _root) _root = temp;
    if (_size == 1) _root = nullptr;
    n->left = n->right = n->parent = nullptr;
  }

  void add_nodes(const multiset &s) {
    if (!s._root) return;
    iterator it1 = s.begin();
    iterator it2 = s.end();
    while (true) {
      insert(*it1);
      if (it1 == it2) break;
      ++it1;
    }
  }

 public:
  multiset() : _size(0), _root(nullptr) {}

  explicit multiset(std::initializer_list<value_type> const &list)
      : multiset() {
    for (auto element : list) {
      insert(element);
    }
  }

  multiset(const multiset &s) : _size(0), _root(nullptr) { add_nodes(s); }

  multiset(multiset &&s) : _size(0), _root(nullptr) {
    add_nodes(s);
    s.clear();
  }

  ~multiset() { clear(); }

  multiset &operator=(const multiset &s) {
    clear();
    _size = 0;
    add_nodes(s);
    return *this;
  }

  multiset operator=(multiset &&s) {
    clear();
    _size = 0;
    add_nodes(s);
    s.clear();
    return *this;
  }

  iterator begin() const {
    if (!_root) throw std::out_of_range("ERROR: multiset is empty");
    node *current = _root;
    while (current->left) {
      current = current->left;
      if (current == _root) break;
    }
    iterator it;
    it.ptr = current;
    return it;
  }

  iterator end() const {
    if (!_root) throw std::out_of_range("ERROR: multiset is empty");
    node *current = _root;
    while (current->right) {
      current = current->right;
    }
    iterator it;
    it.ptr = current;
    return it;
  }

  bool empty() { return !_size; }

  size_type size() const { return _size; }

  size_type max_size() { return std::numeric_limits<value_type>::max(); }

  void clear() {
    while (_root) {
      iterator it = begin();
      erase(it);
    }
  }

  std::pair<iterator, bool> insert(const value_type &value) {
    iterator it;
    if (!_root) {
      _root = new node(nullptr, value);
      it.ptr = _root;
    } else {
      it.ptr = insert_node(value);
    }
    ++_size;
    return std::make_pair(it, true);
  }

  void erase(iterator it) {
    if (!_root) throw std::out_of_range("ERROR: multiset is empty");
    node *temp = it.ptr;
    if (temp->left && temp->right) {
      ++it;
      temp->val = *it;
    }
    erase_node(temp);
    delete temp;
    --_size;
  }

  void merge(multiset &other) {
    add_nodes(other);
    other.clear();
  };

  iterator find(const value_type &key) {
    if (!_root) throw std::out_of_range("ERROR: multiset is empty");
    iterator it1 = begin();
    iterator it2 = end();
    while (it1 != it2) {
      if (*it1 == key) return it1;
      ++it1;
    }
    return it1;
  }

  bool contains(const value_type &key) {
    if (!_root) return false;
    iterator it = find(key);
    return *it == key;
  }

  void swap(multiset &other) {
    multiset<value_type> temp(other);
    other = *this;
    *this = temp;
  }

  template <typename... Args>
  s21::vector<std::pair<iterator, bool>> emplace(Args &&...args) {
    s21::vector<key_type> values{args...};
    s21::vector<std::pair<iterator, bool>> result;
    for (auto value : values) result.push_back(insert(value));
    return result;
  }
};
}  // namespace s21

#endif  //  SRC_S21_MULTISET_H_
