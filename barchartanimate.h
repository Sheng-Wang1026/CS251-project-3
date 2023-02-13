// barchartanimate.h
// TO DO:  add header comment here.  Also add function header comments below.

#include "barchart.h"
#include "myrandom.h" // used in autograder, do not remove
#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <unistd.h>
#include <vector>

using namespace std;

//
// BarChartAnimate
//
class BarChartAnimate {
private:
  //
  // Private member variables for the abstraction.
  // This implementation uses a low-level C array, bars, to store a list of
  // BarCharts.  As a result, you must also keep track of the number of
  // elements stored (size) and the capacity of the array (capacity).
  // This IS dynamic array, so it must expand automatically, as needed.
  //
  BarChart *barcharts; // pointer to a C-style array
  int size;
  int capacity;
  map<string, string> colorMap;
  string title;
  string xlabel;
  string source;

public:
  // a parameterized constructor:
  // Like the ourvector, the barcharts C-array should be constructed here
  // with a capacity of 4.
  BarChartAnimate(string title, string xlabel, string source) {

    // TO DO:  Write this constructor.
    barcharts = new BarChart[4];
    size = 0;
    capacity = 4;
    this->title = title;
    this->xlabel = xlabel;
    this->source = source;
  }

  //
  // destructor:
  //
  // Called automatically by C++ to free the memory associated
  // by BarChartAnimate.
  //
  virtual ~BarChartAnimate() {

    // TO DO:  Write this destructor.
    delete[] barcharts;

    barcharts = nullptr;
  }

  void setColor(string category, map<string, string> &Map, int &colorIndex) {
    if (!Map.count(category)) {
      Map[category] = COLORS[colorIndex];
      colorIndex++;
      if (colorIndex == 7) {
        colorIndex = 0;
      }
    }
  }

  // addFrame:
  // adds a new BarChart to the BarChartAnimate object from the file stream.
  // if the barcharts has run out of space, double the capacity (see
  // ourvector.h for how to double the capacity).
  // See application.cpp and handout for pre and post conditions.
  void addFrame(ifstream &file) {

    if (size == capacity) {
      int newCapacity = capacity * 2;
      BarChart *newBC = new BarChart[newCapacity];

      for (int i = 0; i < size; i++) {
        newBC[i] = barcharts[i];
      }

      delete[] barcharts;
      barcharts = newBC;
      capacity = newCapacity;
    }

    string frame, name, country, category;
    string value;
    int colorIndex = 0;

    // TO DO:  Write this constructor.
    string temp;
    getline(file, temp);
    // cout << temp;
    int S;
    file >> S;
    BarChart bc(S);
    // cout << S;
    for (int i = 0; i < S; i++) {
      getline(file, frame, ',');
      if (frame != "") {
        getline(file, name, ',');
        getline(file, country, ',');
        getline(file, value, ',');
        getline(file, category, '\n');

        setColor(category, colorMap, colorIndex);

        bc.addBar(name, stoi(value), category);
        bc.setFrame(frame);
      }
    }

    // bc.graph(cout,this->colorMap, S);
    barcharts[size] = bc;
    if (frame != "") {
      size++;
    }
    // cout << barcharts[0].getFrame() << endl;
  }

  // animate:
  // this function plays each frame stored in barcharts.  In order to see the
  // animation in the terminal, you must pause between each frame.  To do so,
  // type:  usleep(3 * microsecond);
  // Additionally, in order for each frame to print in the same spot in the
  // terminal (at the bottom), you will need to type: output << CLEARCONSOLE;
  // in between each frame.
  void animate(ostream &output, int top, int endIter) {
    unsigned int microsecond = 50000;

    // TO DO:  Write this functio
    if (endIter == -1) {
      endIter = this->size;
    }
    for (int i = 0; i < endIter; i++) {
      usleep(3 * microsecond);
      output << CLEARCONSOLE;
      output << BLACK << title << endl;
      output << BLACK << source << endl;
      barcharts[i].graph(output, this->colorMap, top);
      output << BLACK << xlabel << endl;
      output << BLACK << "Frame: " << barcharts[i].getFrame() << endl;
    }
  }

  //
  // Public member function.
  // Returns the size of the BarChartAnimate object.
  //
  int getSize() {

    return this->size; // TO DO:  update this, it is only here so code compiles.
  }

  //
  // Public member function.
  // Returns BarChart element in BarChartAnimate.
  // This gives public access to BarChart stored in the BarChartAnimate.
  // If i is out of bounds, throw an out_of_range error message:
  // "BarChartAnimate: i out of bounds"
  //
  BarChart &operator[](int i) {

    // TO DO:  Write this function.

    return barcharts[i]; // TO DO:  update this, it is only here so code
                         // compiles.
  }
};
