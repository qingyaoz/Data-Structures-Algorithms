// stats.cpp
// Project UID 5366c7e2b77742d5b2142097e51561a5

#include "stats.h"
#include <cassert>
#include <vector>
#include "p1_library.h"
#include <cmath>    //for modf

using namespace std;

vector<vector<double> > summarize(vector<double> v) {
  sort(v);
  vector<vector<double> > result;
  vector<double> temp;
  temp.push_back(v[0]);
  temp.push_back(1);
  result.push_back(temp);
  for (size_t i = 1; i < v.size(); ++i) {
    if (v[i] == result.back()[0]){
      result.back()[1]++;
    } else {
      temp[0] = v[i];
      temp[1] = 1;
      result.push_back(temp);
    }
  }
  return result;
}

int count(vector<double> v) {
  return v.size();
}

double sum(vector<double> v) {
  double sum_ = 0;
  for (double element : v){
    sum_ += element;
  }
  return sum_;
}

double mean(vector<double> v) {
  return sum(v)/v.size();
}

double median(vector<double> v) {
  sort(v);
  if (v.size()%2 == 1) {
    return v[v.size() / 2]; // index starts from 0
  } else {
    return (v[v.size() / 2 - 1] + v[v.size() / 2])/2;
  }
}

double mode(vector<double> v) {
  vector<vector<double> > summary = summarize(v);
  double max_num = 0;
  double max = 0;
  for (vector<double> &element : summary) { // faster?
    if (element[1] > max_num) {
      max_num = element[1];
      max = element[0];
    }
  }
  return max;
}

double min(vector<double> v) {
  sort(v);
  return v[0];
}

double max(vector<double> v) {
  sort(v);
  return v[v.size() - 1];
}

double stdev(vector<double> v) {
  double mean_ = mean(v);
  double temp = 0;
  for (double element : v) {
    temp += pow(element - mean_, 2);
  }
  return sqrt(temp/(v.size()-1));
}

double percentile(vector<double> v, double p) {
  sort(v);
  if (p == 1) {
    return v.back();
  } 
  double rank = p * (v.size() - 1) + 1;
  double intpart;
  double fractpart;
  fractpart = modf(rank, &intpart);
  double result = v[intpart-1] + fractpart * (v[intpart] - v[intpart-1]); // - 1 for index
  return result;
}