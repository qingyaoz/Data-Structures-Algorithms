// main.cpp
// Project UID 5366c7e2b77742d5b2142097e51561a5

#include "stats.h"
#include "p1_library.h"
#include <iostream>
#include <fstream>
# include <sstream>
using namespace std;

int main() {

  char filename[32];
  char column[32];
  vector<double> temp;
  string skip;
  cout << "enter a filename\n";
  cin >> filename;
  //FILE *fp = fopen(filename, "r");
  ifstream file(filename);
  string data;
  vector<string> lines;

  cout << "enter a column name" << endl;
  cin >> column;
  cout << "reading column " << column << " from " << filename << endl;

  temp = extract_column(filename,column);
  // for (double element : temp) {
  //   cout << element << endl;
  // }


  cout << "Summary (value: frequency)" << endl;
  for (vector<double> i : summarize(temp)) {
    cout << i[0] << ": " << i[1] << endl;
  }

  cout << endl;
  double stedv_= stdev(temp);

  cout << "count = " << count(temp) << endl;


  cout << "sum = " << sum(temp) << endl;
  cout << "mean = " << mean(temp) << endl;
  cout << "stdev = " << stedv_ << endl;
  cout << "median = " << median(temp) << endl;
  cout << "mode = " << mode(temp) << endl;
  cout << "min = " << min(temp) << endl;
  cout << "max = " << max(temp) << endl;
  cout << "  0th percentile = " << percentile(temp, 0) << endl;
  cout << " 25th percentile = " << percentile(temp, 0.25) << endl;
  cout << " 50th percentile = " << percentile(temp, 0.5) << endl;
  cout << " 75th percentile = " << percentile(temp, 0.75) << endl;
  cout << "100th percentile = " << percentile(temp, 1) << endl;
}

