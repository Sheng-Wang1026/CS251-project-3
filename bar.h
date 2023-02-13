// bar.h
// TO DO:  add header comment here.  Also add function header comments below.

#include "myrandom.h" // used in autograder, do not remove
#include <iostream>
#include <string>
using namespace std;

//
// Bar
//
class Bar {
private:
  // Private member variables for a Bar object
  // TO DO:  Define private member variables for this class
  // NOTE: You should not be allocating memory on the heap for this class.
  string Name;
  int Value;
  string Category;

public:
  // default constructor:
  Bar() {

    // TO DO:  Write this constructor.
    this->Name = "";
    this->Value = 0;
    this->Category = "";
  }

  //
  // a second constructor:
  //
  // Parameter passed in constructor Bar object.
  //
  Bar(string name, int value, string category) {

    // TO DO:  Write this constructor.
    this->Name = name;
    this->Value = value;
    this->Category = category;
  }

  // destructor:
  virtual ~Bar() {

    // TO DO:  Write this destructor or leave empty if not needed.
  }

  // create a new function to set data in Bar.
  void setData(string name, int value, string category) {
    this->Name = name;
    this->Value = value;
    this->Category = category;
  }

  // getName:
  string getName() {

    // TO DO:  Write this function.

    return Name; // TO DO:  update this, it is only here so code compiles.
  }

  // getValue:
  int getValue() {

    // TO DO:  Write this function.

    return Value; // TO DO:  update this, it is only here so code compiles.
  }

  // getCategory:
  string getCategory() {

    // TO DO:  Write this function.

    return Category; // TO DO:  update this, it is only here so code compiles.
  }

  // operators
  // TO DO:  Write these operators.  This allows you to compare two Bar
  // objects.  Comparison should be based on the Bar's value.  For example:
  bool operator<(const Bar &other) const {
    if (this->Value < other.Value) {
      return true;
    }
    return false;
  }

  bool operator<=(const Bar &other) const {
    if (this->Value <= other.Value) {
      return true;
    }
    return false;
  }

  bool operator>(const Bar &other) const {
    if (this->Value > other.Value) {
      return true;
    }
    return false;
  }

  bool operator>=(const Bar &other) const {
    if (this->Value >= other.Value) {
      return true;
    }
    return false;
  }
};
