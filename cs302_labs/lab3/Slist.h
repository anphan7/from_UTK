#ifndef SLIST_H
#define SLIST_H

// include header file(s) needed

#include "Slist.h"
#include <iostream>
#include <cstring>
#include <algorithm>
#include <iomanip>
#include <fstream>
#include <string>
#include <vector>
#include <iterator>
using namespace std;

// qsort_r3: randomly chosen pivot, 3-way partition {<},{=},{>}

// template <typename T>
template <class T>
class slist
{
private:
  struct node
  {
    node()
    {
      data = T();
      next = NULL;
    }
    node(const T &key) { data = key; next = NULL; } // add node(const T &key) { write this }
    bool operator<(const T &rhs) const // add overloaded operator< code
    {
      return data < rhs.data;
    }
    T data;
    node *next;
  };

private:
  class sptr
  {
    public:
      sptr(node *_ptr = NULL)
      {
        ptr = _ptr;
      }
      bool operator<(const node &rhs) const { return *ptr < *rhs.ptr; }
      operator node *() const { return ptr; }

    private:
      node *ptr;
  }; // add class sptr { write this for node data }

public:
  class iterator
  {
  public:
    iterator() { p = NULL; }
    T &operator*() { return p->data; }
    iterator &operator++()
    {
      p = p->next;
      return *this;
    }
    bool operator!=(const iterator &rhs) const { return p != rhs.p; }

  private:
    iterator(node *n_p) { p = n_p; }
    node *p;

    friend class slist<T>;
  };

public:
  slist();
  ~slist();

  void push_back(const T &);
  void sort(const string &);

  iterator begin() { return iterator(head->next); }
  iterator end() { return iterator(NULL); }

private:
  node *head;
  node *tail;
  int count = 0; // not include in the skeleton program
};

template <typename T>
slist<T>::slist()
{
  head = new node();
  tail = head;
}

template <typename T>
slist<T>::~slist()
{
  while (head->next != NULL)
  {
    node *p = head->next;
    head->next = p->next;
    delete p;
  }
  delete head;

  head = NULL;
  tail = NULL;
}

template <typename T>
void slist<T>::push_back(const T &din)
{
  tail->next = new node(din);
  tail = tail->next;
}

template <typename T>
void slist<T>::sort(const string &algname)
{
  // determine number of list elements
  int count_size = 0;
  node *current = head; // current = p;
  int i;
  iterator it (begin());
  for (; it != end(); ++it)
  {
    count_size++;
  }
  cout << count_size << endl; // number count on the list which is 352 on repeat1.txt

  // set up smart pointer array called Ap
  vector<sptr> Ap (count_size);  // Allocate Ap pointers of count . Ap.size() here 352
  for (i = 0; current -> next != NULL; current = current -> next , i++)                 // Initialize the individual smart pointers to point to the list node
  {
    Ap[i] = current -> next;
  }
  if (algname.compare("-quicksort") == 0)
  {
    std::sort (Ap.begin(), Ap.end() );
  }
  // if quicksort, apply std::sort(...)
  // if mergesort, apply std::stable_sort(...)
  // if qsort_r3, apply qsort_r3(...)
  // use sorted Ap array to relink list
}

#endif // SLIST_H