/* stats_tests.cpp
 *
 * Unit tests for the simple statistics library
 * Project UID 5366c7e2b77742d5b2142097e51561a5
 *
 * EECS 280 Project 1
 *
 * Protip #1: Write tests for the functions BEFORE you implement them!  For
 * example, write tests for median() first, and then write median().  It sounds
 * like a pain, but it helps make sure that you are never under the illusion
 * that your code works when it's actually full of bugs.
 *
 * Protip #2: Instead of putting all your tests in main(),  put each test case
 * in a function!
 */


#include "stats.h"
#include <iostream>
#include <cassert>
#include <vector>
#include <cmath>
using namespace std;

void test_sum_small_data_set();
void test_summarize_gen();
void test_count_gen();
void test_count_0();
void test_sum_gen();
void test_mean_gen();
void test_median_odd();
void test_median_even();
void test_mode_single();
void test_mode_cf1();
void test_mode_cf2();
void test_min_gen();
void test_max_gen();
void test_stdev_gen();
void test_percentile_gen1();
void test_percentile_gen2();
void test_percentile_cf();
void test_percentile_neg();
// Add prototypes for you test functions here.

int main() {
  // test_sum_small_data_set();
  // // Call your test functions here
  test_summarize_gen();
  test_count_gen();
  test_count_0();
  test_sum_gen();
  test_mean_gen();
  test_median_odd();
  test_median_even();
  test_mode_single();
  test_mode_cf1();
  test_mode_cf2();
  test_min_gen();
  test_max_gen();
  test_stdev_gen();
  test_percentile_gen1();
  test_percentile_gen2();
  test_percentile_cf();
  test_percentile_neg();
  return 0;
}

void test_sum_small_data_set() {
  cout << "test_sum_small_data_set" << endl;

  vector<double> data;
  data.push_back(1);
  data.push_back(2);
  data.push_back(3);

  assert(sum(data) == 6);

  cout << "PASS!" << endl;
}

// Add the test function implementations here.
void test_summarize_gen(){
  cout << "test_summarize_gen" << endl;

  vector<double> data;
  data.push_back(5);
  data.push_back(10);
  data.push_back(7);
  data.push_back(5);
  data.push_back(7);

  vector<vector<double>> result = summarize(data);
  assert(result[0][0] == 5);
  assert(result[0][1] == 2);
  assert(result[1][0] == 7);
  assert(result[1][1] == 2);
  assert(result[2][0] == 10);
  assert(result[2][1] == 1);

  cout << "PASS!" << endl;
}

void test_count_gen(){
  cout << "test_count_gen" << endl;

  vector<double> data;
  data.push_back(4);
  data.push_back(4);
  data.push_back(4);
  data.push_back(4);
  data.push_back(4);

  assert(count(data) == 5);

  cout << "PASS!" << endl;
}

void test_count_0(){
  cout << "test_count_0" << endl;

  vector<double> data;

  assert(count(data) == 0);

  cout << "PASS!" << endl;
}

void test_sum_gen(){
  cout << "test_sum_gen" << endl;

  vector<double> data;
  data.push_back(2.1);
  data.push_back(-1);
  data.push_back(0);

  assert(sum(data) == 1.1);

  cout << "PASS!" << endl;
}

void test_mean_gen(){
  cout << "test_mean_gen" << endl;

  vector<double> data;
  data.push_back(0);
  data.push_back(6);
  data.push_back(1.5);

  assert(mean(data) == 2.5);

  cout << "PASS!" << endl;
}

void test_median_odd(){
  cout << "test_median_odd" << endl;

  vector<double> data;
  data.push_back(4);
  data.push_back(1);
  data.push_back(9);

  assert(median(data) == 4);

  cout << "PASS!" << endl;
}

void test_median_even(){
  cout << "test_median_even" << endl;

  vector<double> data;
  data.push_back(8);
  data.push_back(3);
  data.push_back(4.5);
  data.push_back(7);

  assert(median(data) == 5.75);

  cout << "PASS!" << endl;
}

void test_mode_single(){
  cout << "test_mode_single" << endl;

  vector<double> data;
  data.push_back(2.5);
  data.push_back(1.1);
  data.push_back(7);

  assert(mode(data) == 1.1);

  cout << "PASS!" << endl;
}

void test_mode_cf1(){
  cout << "test_mode_cf1" << endl;

  vector<double> data;
  data.push_back(3);
  data.push_back(-1);
  data.push_back(-1);
  data.push_back(-1);
  data.push_back(3);

  assert(mode(data) == -1);

  cout << "PASS!" << endl;
}

void test_mode_cf2(){
  cout << "test_mode_cf2" << endl;

  vector<double> data;
  data.push_back(2);
  data.push_back(2);
  data.push_back(1);
  data.push_back(1);

  assert(mode(data) == 1);

  cout << "PASS!" << endl;
}


void test_min_gen(){
  cout << "test_min_gen" << endl;

  vector<double> data;
  data.push_back(2);
  data.push_back(0);
  data.push_back(1);

  assert(min(data) == 0);

  cout << "PASS!" << endl;
}

void test_max_gen(){
  cout << "test_max_gen" << endl;

  vector<double> data;
  data.push_back(2);
  data.push_back(0);
  data.push_back(1);

  assert(max(data) == 2);

  cout << "PASS!" << endl;
}


void test_stdev_gen(){
  cout << "test_stdev_gen" << endl;

  vector<double> data;
  data.push_back(0);
  data.push_back(-4);
  data.push_back(4);

  assert(stdev(data) == 4);

  cout << "PASS!" << endl;
}

void test_percentile_gen1(){
  cout << "test_percentile_gen1" << endl;

  vector<double> data;
  data.push_back(15);
  data.push_back(20);
  data.push_back(35);
  data.push_back(40);
  data.push_back(50);

  assert(percentile(data,0.4) == 29);

  cout << "PASS!" << endl;
}

void test_percentile_gen2(){
  cout << "test_percentile_gen2" << endl;

  vector<double> data;
  data.push_back(2);
  data.push_back(1);
  data.push_back(5);
  data.push_back(4);
  data.push_back(3);

  assert(percentile(data,0.25) == 2);
  assert(percentile(data,0.6) == 3.4);
  assert(percentile(data,0) == 1);
  assert(percentile(data,1) == 5);

  cout << "PASS!" << endl;
}

void test_percentile_cf(){
  cout << "test_percentile_cf" << endl;

  vector<double> data;
  data.push_back(2);
  data.push_back(2);
  data.push_back(2);

  assert(percentile(data,0.25) == 2);
  assert(percentile(data,0.6) == 2);
  assert(percentile(data,0) == 2);
  assert(percentile(data,1) == 2);

  cout << "PASS!" << endl;
}

void test_percentile_neg(){
  cout << "test_percentile_neg" << endl;

  vector<double> data;
  data.push_back(-2);
  data.push_back(2);
  data.push_back(-5);
  data.push_back(2);
  data.push_back(2);

  assert(percentile(data,0.25) == -2);
  // double test = percentile(data,0.3);
  // cout << test << "  " << (test == -1.2) << endl;
  // assert(percentile(data,0.3) == -1.2);
  assert(abs(percentile(data,0.3) - (-1.2)) < 0.00001);
  assert(percentile(data,0) == -5);
  assert(percentile(data,0.9) == 2);

  cout << "PASS!" << endl;
}

