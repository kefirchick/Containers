#ifndef SRC_S21_MAP_H_
#define SRC_S21_MAP_H_

#include <cstdio>
#include <iostream>
#include <limits>

#include "s21_vector.h"

namespace s21 {

template <typename Key, typename T>
class map {
 public:
  using key_type = Key;
  using mapped_type = T;
  using value_type = std::pair<const key_type, mapped_type>;
  using reference = T &;
  using const_iterator = const class iterator;
  using const_reference = const T &;
  using size_type = size_t;

  class node {
   public:
    node *left, *right, *parent;
    key_type key;
    mapped_type val;

    node() : left(nullptr), right(nullptr), parent(nullptr) {}

    node(node *p, value_type v)
        : left(nullptr),
          right(nullptr),
          parent(p),
          key(v.first),
          val(v.second) {
      if (!p) return;
      if (p->key > v.first) {
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
  };

  class iterator {
   public:
    node *ptr;

    iterator() : ptr(nullptr) {}

    mapped_type operator*() {
      if (!ptr) throw std::out_of_range("ERROR: map is empty");
      return ptr->val;
    }

    iterator operator++() {
      if (!ptr) throw std::out_of_range("ERROR: map is empty");
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
      throw std::out_of_range("ERROR: end of map");
      return *this;
    }

    iterator operator--() {
      if (!ptr) throw std::out_of_range("ERROR: map is empty");
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
      throw std::out_of_range("ERROR: begin of map");
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
      if (current->key > value.first) {
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

  void add_nodes(const map &s) {
    if (!s._root) return;
    iterator it1 = s.begin();
    iterator it2 = s.end();
    while (true) {
      insert(std::make_pair(it1.ptr->key, it1.ptr->val));
      if (it1.ptr->key == it2.ptr->key) break;
      ++it1;
    }
  }

  iterator find(const key_type &key) {
    iterator it1 = begin();
    iterator it2 = end();
    while (it1.ptr->key != it2.ptr->key) {
      if (it1.ptr->key == key) return it1;
      ++it1;
    }
    return it1;
  }

 public:
  map() : _size(0), _root(nullptr) {}

  explicit map(std::initializer_list<value_type> const &list) : map() {
    for (auto element : list) {
      insert(element);
    }
  }

  map(const map &s) : _size(0), _root(nullptr) { add_nodes(s); }

  map(map &&s) : _size(0), _root(nullptr) {
    add_nodes(s);
    s.clear();
  }

  ~map() { clear(); }

  map &operator=(const map &s) {
    clear();
    _size = 0;
    add_nodes(s);
    return *this;
  }

  map operator=(map &&s) {
    clear();
    _size = 0;
    add_nodes(s);
    s.clear();
    return *this;
  }

  mapped_type &operator[](const key_type &key) {
    if (!_root) throw std::out_of_range("ERROR: map is empty");
    if (!contains(key)) throw std::out_of_range("ERROR: no such key");
    return find(key).ptr->val;
  }

  mapped_type &at(const Key &key) { return (*this)[key]; }

  iterator begin() const {
    if (!_root) throw std::out_of_range("ERROR: map is empty");
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
    if (!_root) throw std::out_of_range("ERROR: map is empty");
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

  size_type max_size() { return std::numeric_limits<mapped_type>::max(); }

  void clear() {
    while (_root) {
      iterator it = begin();
      erase(it);
    }
  }

  std::pair<iterator, bool> insert(const value_type &value) {
    if (contains(value.first)) return std::make_pair(end(), false);
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

  std::pair<iterator, bool> insert(const Key &key, const T &obj) {
    return insert(std::make_pair(key, obj));
  }

  std::pair<iterator, bool> insert_or_assign(const Key &key, const T &obj) {
    if (contains(key)) {
      iterator it = find(key);
      it.ptr->val = obj;
      return std::make_pair(it, true);
    } else {
      return insert(std::make_pair(key, obj));
    }
  }

  void erase(iterator it) {
    if (!_root) throw std::out_of_range("ERROR: map is empty");
    node *temp = it.ptr;
    if (temp->left && temp->right) {
      ++it;
      temp->val = *it;
    }
    erase_node(temp);
    delete temp;
    --_size;
  }

  void merge(map &other) {
    add_nodes(other);
    other.clear();
  };

  bool contains(const Key &key) {
    if (!_root) return false;
    iterator it = find(key);
    return it.ptr->key == key;
  }

  void swap(map &other) {
    map<key_type, mapped_type> temp(other);
    other = *this;
    *this = temp;
  }

  template <typename... Args>
  s21::vector<std::pair<iterator, bool>> emplace(Args &&...args) {
    s21::vector<value_type> values{args...};
    s21::vector<std::pair<iterator, bool>> result;
    for (auto value : values) result.push_back(insert(value));
    return result;
  }
};
}  // namespace s21

#endif  //  SRC_S21_MAP_H_
