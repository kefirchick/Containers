#ifndef SRC_S21_LIST_H_
#define SRC_S21_LIST_H_

#include <cmath>
#include <cstdio>
#include <iostream>

namespace s21 {

template <typename T>
class list {
 private:
  class node {
   public:
    node() {}
    node(T node_val) : val(node_val) {}
    ~node() {}
    node* next;
    node* prev;
    T val;
  };

 public:
  class ListIterator {
    friend class list<T>;

   public:
    ListIterator() : the_node(0) {}
    ListIterator(node* dn) : the_node(dn) {}
    ListIterator(const ListIterator& it) : the_node(it.the_node) {}
    ListIterator& operator=(const ListIterator& it) {
      the_node = it.the_node;
      return *this;
    }

    bool operator==(const ListIterator& it) const {
      return (the_node == it.the_node);
    }

    bool operator!=(const ListIterator& it) const { return !(it == *this); }

    ListIterator& operator++() {
      if (the_node == 0) throw "incremented an empty iterator";
      if (the_node->next == 0) throw "tried to increment too far past the end";
      the_node = the_node->next;
      return *this;
    }

    ListIterator& operator--() {
      if (the_node == 0) throw "incremented an empty iterator";
      if (the_node->prev == 0) throw "tried to increment too far past the end";
      the_node = the_node->prev;
      return *this;
    }

    T& operator*() const {
      if (the_node == 0) throw "tried to dereference an empty iterator";
      return the_node->val;
    }

   private:
    node* the_node;
  };

 private:
  node* head;
  node* tail;
  ListIterator head_iterator;
  ListIterator tail_iterator;

  using value_type = T;
  using reference = T&;
  using const_reference = const T&;
  using size_type = std::size_t;
  size_t size_ = 1;

 public:
  using iterator = ListIterator;
  using const_iterator = const ListIterator;

  list() {
    head = tail = new node;
    tail->next = nullptr;
    tail->prev = nullptr;
    size_ = 0;
    head_iterator = iterator(head);
    tail_iterator = iterator(tail);
  }

  list(size_type n) {
    head = tail = new node;
    tail->next = nullptr;
    tail->prev = nullptr;
    head_iterator = iterator(head);
    tail_iterator = iterator(tail);
    for (size_type i = 0; i < n; i++) {
      node* node_to_add = new node();
      node_to_add->next = head;
      node_to_add->prev = nullptr;
      head->prev = node_to_add;
      head = node_to_add;
      head_iterator = iterator(head);
    }
    size_ = n;
  }

  list(std::initializer_list<value_type> const& items) : list() {
    size_ = 0;
    for (auto element : items) {
      push_back(element);
    }
  }

  list(const list& list) : list::list() {
    clear();
    node* current = list.head;
    data_copy(current);
  }

  list(list&& list) : list::list() {
    clear();
    node* current = list.head;
    data_copy(current);
    list.clear();
  }

  ~list() {
    node* node_to_delete = head;
    for (node* sn = head; sn != tail;) {
      sn = sn->next;
      delete node_to_delete;
      node_to_delete = sn;
    }

    delete node_to_delete;
  }

  const_reference front() {
    if (head_iterator == nullptr)
      throw std::out_of_range("ERROR: The list is empty");
    return *head_iterator;
  }

  const_reference back() {
    if (head_iterator == nullptr)
      throw std::out_of_range("ERROR: The list is empty");
    node* current = this->head;
    while (current->next->next != nullptr) {
      current = current->next;
    }
    return current->val;
  }

  iterator begin() { return head_iterator; }

  iterator end() { return tail_iterator; }

  bool empty() { return head->next == nullptr; }

  size_type size() { return size_; }

  size_type max_size() {
    size_type n = pow(2, 63) / (sizeof(T) + 20);
    n = n + 21;
    return n;
  }

  void clear() {
    if (head_iterator != nullptr) {
      while (size_) {
        pop_front();
      }
    }
  }

  iterator insert(iterator pos, const_reference value) {
    if (pos.the_node == head) {
      push_front(value);
    } else {
      node* previous = this->head;
      while (previous->next != pos.the_node) {
        previous = previous->next;
      }
      node* node_to_add = new node(value);
      node_to_add->next = previous->next;
      node_to_add->prev = previous;
      previous->next->prev = node_to_add;
      previous->next = node_to_add;
      ++size_;
    }
    return pos;
  }

  void erase(iterator pos) {
    if (pos.the_node == head) {
      pop_front();
    } else {
      node* tmp = pos.the_node;
      pos.the_node->prev->next = pos.the_node->next;
      pos.the_node->next->prev = pos.the_node->prev;
      delete tmp;
      --size_;
    }
  }

  void push_back(const_reference value) {
    if (head->next == nullptr) {
      push_front(value);
    } else {
      node* previous = this->head;
      while (previous->next->next != nullptr) previous = previous->next;
      node* node_to_add = new node(value);
      node_to_add->next = previous->next;
      node_to_add->prev = previous;
      previous->next = node_to_add;
      ++size_;
    }
  }

  void pop_back() {
    if (head->next != nullptr) {
      node* current = this->head;
      while (current->next->next != nullptr) current = current->next;
      current->prev->next = current->next;
      current->next->prev = current->prev;
      delete current;
      --size_;
    }
  }

  void push_front(const_reference value) {
    node* node_to_add = new node(value);
    node_to_add->next = head;
    node_to_add->prev = nullptr;
    head->prev = node_to_add;
    head = node_to_add;
    head_iterator = iterator(head);
    ++size_;
  }

  void pop_front() {
    if (head_iterator == nullptr)
      throw std::out_of_range("ERROR: The list is empty");
    node* tmp = head;
    head = tmp->next;
    tmp->next = nullptr;
    delete tmp;
    head_iterator = iterator(head);
    --size_;
  }

  void swap(list& other) {
    list<value_type> temp_list(*this);
    clear();
    data_copy(other.head);
    other.clear();
    other.data_copy(temp_list.head);
  }

  void merge(list& other) {
    data_copy(other.head);
    other.clear();
  }

  void splice(const_iterator pos, list& other) {
    if (pos.the_node == nullptr || pos.the_node->next == nullptr) {
      throw std::invalid_argument("Attempted a set to nullptr position");
    } else if (pos.the_node == head) {
      node* previous = other.head;
      while (previous->next->next != nullptr) {
        previous = previous->next;
      }
      for (size_type i = 0; i < other.size(); i++) {
        push_front(previous->val);
        previous = previous->prev;
      }
      other.clear();
    } else {
      node* previous = pos.the_node;
      node* node_to_insert = other.head;
      while (node_to_insert->next != nullptr) {
        insert(previous, node_to_insert->val);
        node_to_insert = node_to_insert->next;
      }
      other.clear();
    }
  }

  void reverse() {
    if (head_iterator == nullptr)
      throw std::out_of_range("ERROR: The list is empty");
    list<value_type> temp_list(*this);
    node* tmp_node = temp_list.head;
    clear();
    while (tmp_node->next != nullptr) {
      push_front(tmp_node->val);
      tmp_node = tmp_node->next;
    }
    temp_list.clear();
  }

  void unique() {
    node* current = head;
    while (current->next != nullptr) {
      if (current->val == current->next->val)
        while (current->val == current->next->val) erase(current->next);
      current = current->next;
    }
  }

  void sort() {
    node* tmp = head;
    while (tmp->next != nullptr) {
      node* current = tmp;
      node* min = tmp;
      while (current->next != nullptr) {
        if (current->val < min->val) min = current;
        current = current->next;
      }
      if (min != tmp) {
        min->prev->next = min->next;
        min->next->prev = min->prev;
        min->prev = tmp->prev;
        min->next = tmp;
        if (min->prev == nullptr) {
          head = min;
          head_iterator = iterator(head);
        } else {
          tmp->prev->next = min;
        }
        tmp->prev = min;
      } else {
        tmp = tmp->next;
      }
    }
  }

  void data_copy(node* list_iterator) {
    while (list_iterator->next != nullptr) {
      push_back(list_iterator->val);
      list_iterator = list_iterator->next;
    }
  }

  template <class... Args>
  iterator emplace(const_iterator pos, Args&&... args) {
    if ((sizeof...(args)) == 0) {
      value_type _empty = {};
      push_front(_empty);
    }
    std::initializer_list<T> arg{args...};
    for (auto& val : arg) push_front(val);
    return pos;
  }

  template <class... Args>
  void emplace_back(Args&&... args) {
    if ((sizeof...(args)) == 0) {
      value_type _empty = {};
      push_back(_empty);
    }
    std::initializer_list<T> arg{args...};
    for (auto& val : arg) push_back(val);
  }

  template <class... Args>
  void emplace_front(Args&&... args) {
    if ((sizeof...(args)) == 0) {
      value_type _empty = {};
      push_front(_empty);
    }
    std::initializer_list<T> arg{args...};
    for (auto& val : arg) push_front(val);
  }
};
}  // namespace s21

#endif  //  SRC_S21_VECTOR_H_