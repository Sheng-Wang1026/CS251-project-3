// barchart.h
// TO DO:  add header comment here.  Also add function header comments below.

#include "bar.h"
#include "myrandom.h" // used in autograder, do not remove
#include <algorithm>
#include <iostream>
#include <map>
#include <vector>

using namespace std;

// Constants used for bar chart animation.  You will primarily
// use these in barchartanimate.h, but you might find some useful here.
const string BOX = "\u29C8";
const string CLEARCONSOLE = "\033[2J";

// Color codes for Mimir (light mode)
const string RED("\033[1;36m");
const string PURPLE("\033[1;32m");
const string BLUE("\033[1;33m");
const string CYAN("\033[1;31m");
const string GREEN("\033[1;35m");
const string GOLD("\033[1;34m");
const string BLACK("\033[1;37m");
const string RESET("\033[0m");
const vector<string> COLORS = {RED, PURPLE, BLUE, CYAN, GREEN, GOLD, BLACK};

// Color codes for Codio (light/dark mode)
// const string CYAN("\033[1;36m");
// const string GREEN("\033[1;32m");
// const string GOLD("\033[1;33m");
// const string RED("\033[1;31m");
// const string PURPLE("\033[1;35m");
// const string BLUE("\033[1;34m");
// const string WHITE("\033[1;37m");
// const string RESET("\033[0m");
// const vector<string> COLORS = {CYAN, GREEN, GOLD, RED, PURPLE, BLUE, WHITE};

//
// BarChart
//
class BarChart {
private:
  //
  // Private member variables for the abstraction.
  // This implementation uses a low-level C array, bars, to store a list of
  // Bars.  As a result, you must also keep track of the number of elements
  // stored (size) and the capacity of the array (capacity).  This is not a
  // dynamic array, so it does not expand.
  //
  Bar *bars; // pointer to a C-style array
  int capacity;
  int size;
  string frame;

public:
  // default constructor:
  BarChart() {

    // TO DO:  Write this constructor.
    bars = nullptr;
    this->capacity = 0;
    this->size = 0;
    this->frame = "";
  }

  // parameterized constructor:
  // Parameter passed in determines memory allocated for bars.
  BarChart(int n) {

    // TO DO:  Write this constructor.
    bars = new Bar[n];
    this->capacity = n;
    this->size = 0;
    this->frame = "";
  }

  //
  // copy constructor:
  //
  // Called automatically by C++ to create an BarChart that contains
  // a copy of an existing BarChart.  Example: this occurs when passing
  // BarChart as a parameter by value.
  //
  BarChart(const BarChart &other) {

    // TO DO:  Write this constructor.
    bars = new Bar[other.capacity];
    for (int i = 0; i < other.capacity; i++) {
      this->bars[i].setData(other.bars[i].getName(), other.bars[i].getValue(),
                            other.bars[i].getCategory());
    }
    this->capacity = other.capacity;
    this->size = other.size;
    this->frame = other.frame;
  }
  //
  // copy operator=
  //
  // Called when you assign one BarChart into another, i.e. this = other;
  //
  BarChart &operator=(const BarChart &other) {

    delete[] this->bars;

    // TO DO:  Write this operator.
    this->bars = new Bar[other.capacity];
    for (int i = 0; i < other.capacity; i++) {
      this->bars[i].setData(other.bars[i].getName(), other.bars[i].getValue(),
                            other.bars[i].getCategory());
    }
    this->capacity = other.capacity;
    this->size = other.size;
    this->frame = other.frame;

    return *this; // TO DO:  update this, it is only here so code compiles.
  }

  // clear
  // frees memory and resets all private member variables to default values.
  void clear() {

    // TO DO:  Write this operator.
    delete[] bars;

    bars = nullptr;
    this->capacity = 0;
    this->size = 0;
    this->frame = "";
  }

  //
  // destructor:
  //
  // Called automatically by C++ to free the memory associated by the
  // BarChart.
  //
  virtual ~BarChart() {

    // TO DO:  Write this destructor.
    delete[] bars;
    bars = nullptr;
  }

  // setFrame
  void setFrame(string frame) {

    // TO DO:  Write this destructor.
    this->frame = frame;
  }

  // getFrame()
  // Returns the frame of the BarChart oboject.
  string getFrame() {

    // TO DO:  Write this function.

    return this
        ->frame; // TO DO:  update this, it is only here so code compiles.
  }

  // addBar
  // adds a Bar to the BarChart.
  // returns true if successful
  // returns false if there is not room
  bool addBar(string name, int value, string category) {

    // TO DO:  Write this function.
    if (this->size >= this->capacity) {
      return false;
    }

    else {
      Bar b(name, value, category);
      bars[size] = b;
      size++;
      return true; // TO DO:  update this, it is only here so code compiles.
    }
  }

  // getSize()
  // Returns the size (number of bars) of the BarChart object.
  int getSize() {

    // TO DO:  Write this function.

    return size; // TO DO:  update this, it is only here so code compiles.
  }

  // operator[]
  // Returns Bar element in BarChart.
  // This gives public access to Bars stored in the Barchart.
  // If i is out of bounds, throw an out_of_range error message:
  // "BarChart: i out of bounds"
  Bar &operator[](int i) {
    return this
        ->bars[i]; // TO DO:  update this, it is only here so code compiles.
  }

  // dump
  // Used for printing the BarChart object.
  // Recommended for debugging purposes.  output is any stream (cout,
  // file stream, or string stream).
  // Format:
  // "frame: 1
  // aname 5 category1
  // bname 4 category2
  // cname 3 category3" <-newline here
  void dump(ostream &output) {

    // TO DO:  Write this function.
    output << "frame: " << frame << endl;

    sort(bars, bars + size, greater<Bar>());

    for (int i = 0; i < size; i++) {
      output << bars[i].getName() << " " << bars[i].getValue() << " "
             << bars[i].getCategory() << endl;
    }
  }

  void checkColor(map<string, string> &colorMap, string key, string &color) {
    if (!colorMap.count(key)) {
      colorMap[key] = BLACK;
    }
    color = colorMap[key];
  }

  // graph
  // Used for printing out the bar.
  // output is any stream (cout, file stream, string stream)
  // colorMap maps category -> color
  // top is number of bars you'd like plotted on each frame (top 10? top 12?)
  void graph(ostream &output, map<string, string> &colorMap, int top) {
    int lenMax = 60; // this is number of BOXs that should be printed
                     // for the top bar (max value)

    // TO DO:  Write this function.

    sort(bars, bars + size, greater<Bar>());

    double Len;
    for (int i = 1; i < size; i++) {
      Len =
          (double(bars[i].getValue()) / double(bars[0].getValue())) * (lenMax);
      string barstr = "";
      for (int j = 0; j < floor(Len); j++) {
        barstr += BOX;
      }
      string color;
      checkColor(colorMap, bars[i].getCategory(), color);

      output << color << barstr << " " << bars[i].getName() << " "
             << bars[i].getValue() << endl;
    }
  }
};
