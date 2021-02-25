#ifndef SLIST_H
#define SLIST_H

// include header file(s) needed

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
    node(const T &key)
    {
      data = key;
      next = NULL;
    }                                     // add node(const T &key) { write this }
    bool operator<(const node &rhs) const // add overloaded operator< code
    {
      if (data < rhs.data)
        return true;
      else
        return false;
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
    bool operator<(const sptr &rhs) const { return *ptr < *rhs.ptr; }
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
  node *current = head; // tracking the pointer
  iterator it(begin());
  for (; it != end(); ++it) // loop through the size of the list
  {
    count_size++; // size of the list
  }

  // set up smart pointer array called Ap
  vector<sptr> Ap(count_size); // Allocate Ap pointers of count . Ap.size() here 351

  for (int i = 0; current->next != NULL; i++) // Initialize the individual smart pointers to point to the list node
  {
    Ap[i] = current->next;
    current = current->next;              // moving on to the next node
  }
  if (algname.compare("-quicksort") == 0)     // option with quicksort
  {
    std::sort(Ap.begin(), Ap.end());          // std::sort()
  }
  else if (algname.compare("-mergesort") == 0)  // option with mergesort
  {
    std::stable_sort(Ap.begin(), Ap.end());     // std::stable_sort()
  }
 
  //---------Relink the node ----------------------
  current = head;                             // start from head node

  for (int i = 0; i < count_size; i++)        // relink each node start from 0
  {
    current->next = Ap[i];          // connet from the vector to node
    current = Ap[i];
  }
  current->next = NULL;           // at the end of node, set it to NULL
  tail = current;                 
}

// use sorted Ap array to relink list

#endif // SLIST_H