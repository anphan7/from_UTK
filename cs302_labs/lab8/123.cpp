#include <iostream>
using namespace std;

class base {
  public:
    virtual void print() { cout << "base class" << endl; }
};
class derived : public base {
  public:
    void print() { cout << "derived class" << endl; }
};
int main() {
  base *ptr;
  derived der;
  ptr = &der;
  
  ptr->print();
}