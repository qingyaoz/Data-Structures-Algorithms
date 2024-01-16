// Project UID af1f95f547e44c8ea88730dfb185559d

#include <cassert>

#include "Matrix.h"
#include "Matrix_test_helpers.h"
#include "unit_test_framework.h"

using namespace std;


// Here's a free test for you! Model yours after this one.
// Test functions have no interface and thus no RMEs, but
// add a comment like the one here to say what it is testing.
// -----
// Fills a 3x5 Matrix with a value and checks
// that Matrix_at returns that value for each element.
TEST(test_fill_basic) {
  Matrix *mat = new Matrix; // create a Matrix in dynamic memory

  const int width = 3;
  const int height = 5;
  const int value = 42;
  Matrix_init(mat, 3, 5);
  Matrix_fill(mat, value);

  for(int r = 0; r < height; ++r){
    for(int c = 0; c < width; ++c){
      ASSERT_EQUAL(*Matrix_at(mat, r, c), value);
    }
  }
  Matrix_print(mat, cout);

  delete mat; // delete the Matrix
}

// ADD YOUR TESTS HERE
// You are encouraged to use any functions from Matrix_test_helpers.h as needed.
// test init
TEST(test_init_basic) {
  Matrix *mat = new Matrix;

  const int width = 3;
  const int height = 5;
  Matrix_init(mat, 3, 5);
  assert(Matrix_width(mat) == width);
  assert(Matrix_height(mat) == height);

  delete mat; // delete the Matrix
}

TEST(test_init_one) {
  Matrix *mat = new Matrix;

  const int width = 1;
  const int height = 1;
  Matrix_init(mat, 1, 1);
  assert(Matrix_width(mat) == width);
  assert(Matrix_height(mat) == height);

  delete mat; // delete the Matrix
}

TEST(test_basic_wh) {
  Matrix *mat = new Matrix;

  const int width = 3;
  const int height = 5;
  const int value = 10;
  Matrix_init(mat, width, height);
  Matrix_fill(mat, value);

  assert(Matrix_width(mat) == 3);
  assert(Matrix_height(mat) == 5);

  delete mat; // delete the Matrix
}

TEST(test_basic_fill_wh_one) {
  Matrix *mat = new Matrix;
  const int value = 10; 
  const int width = 1;
  const int height = 1;

  Matrix_init(mat, width, height);
  Matrix_fill(mat, value);

  assert(Matrix_width(mat) == 1);
  assert(Matrix_height(mat) == 1);

  for(int r = 0; r < height; ++r){
    for(int c = 0; c < width; ++c){
      ASSERT_EQUAL(*Matrix_at(mat, r, c), value);
    }
  }

  delete mat; // delete the Matrix
}

TEST(test_basic_rowcol) {
  Matrix *mat = new Matrix;

  const int value = 10;
  Matrix_init(mat, 3, 5);
  Matrix_fill(mat, value);
  assert(Matrix_row(mat, Matrix_at(mat, 2, 1)) == 2);
  assert(Matrix_column(mat, Matrix_at(mat, 3, 1)) == 1);
  delete mat; // delete the Matrix
}

TEST(test_rowcol_one) {
  Matrix *mat = new Matrix;

  const int value = 10;
  Matrix_init(mat, 1, 1);
  Matrix_fill(mat, value);
  assert(Matrix_row(mat, Matrix_at(mat, 0, 0)) == 0);
  assert(Matrix_column(mat, Matrix_at(mat, 0, 0)) == 0);
  delete mat; // delete the Matrix
}

TEST(test_basic_at) {
  Matrix *mat = new Matrix;

  const int value = 10;
  Matrix_init(mat, 3, 5);
  Matrix_fill(mat, value);

  *Matrix_at(mat, 2, 1) = 2;
  *Matrix_at(mat, 3, 1) = 0;

  ostringstream actual;
  Matrix_print(mat, actual);

  ostringstream expected;
  expected << "3 5\n"
           << "10 10 10 \n"
           << "10 10 10 \n"
           << "10 2 10 \n"
           << "10 0 10 \n"
           << "10 10 10 \n";
  ASSERT_EQUAL(expected.str(), actual.str());

  delete mat; // delete the Matrix
}

TEST(test_at_one) {
  Matrix *mat = new Matrix;

  const int value = 10;
  Matrix_init(mat, 1, 1);
  Matrix_fill(mat, value);
  *Matrix_at(mat, 0, 0) = 2;

  ostringstream expected;
  expected << "1 1\n"
           << "2 \n";
  ostringstream actual;
  Matrix_print(mat, actual);

  ASSERT_EQUAL(expected.str(), actual.str());

  delete mat; // delete the Matrix
}

TEST(test_basic_border) {
  Matrix *mat = new Matrix;

  const int value = 10;
  Matrix_init(mat, 5, 4);
  Matrix_fill(mat, value);
  Matrix_fill_border(mat, 22);
  
  ostringstream actual;
  Matrix_print(mat, actual);

  ostringstream expected;
  expected << "5 4\n"
           << "22 22 22 22 22 \n"
           << "22 10 10 10 22 \n"
           << "22 10 10 10 22 \n"
           << "22 22 22 22 22 \n";
  ASSERT_EQUAL(expected.str(), actual.str());
  
  assert(Matrix_max(mat) == 22);
  assert(Matrix_column_of_min_value_in_row(mat, 2, 0, 5) == 1);
  assert(Matrix_column_of_min_value_in_row(mat, 2, 1, 3) == 1);
  assert(Matrix_column_of_min_value_in_row(mat, 2, 4, 5) == 4);
  assert(Matrix_min_value_in_row(mat, 2, 0, 5) == 10);
  delete mat; // delete the Matrix
}

TEST(test_basic_min) {
  Matrix *mat = new Matrix;

  const int value = 9;
  Matrix_init(mat, 7, 5);
  Matrix_fill(mat, value);
  Matrix_fill_border(mat, 5);
  *Matrix_at(mat, 1, 3) = 0;
  *Matrix_at(mat, 2, 1) = 4;
  *Matrix_at(mat, 2, 4) = 3;
  *Matrix_at(mat, 2, 6) = 1;
 
  ostringstream actual;
  Matrix_print(mat, actual);

  ostringstream expected;
  expected << "7 5\n"
           << "5 5 5 5 5 5 5 \n"
           << "5 9 9 0 9 9 5 \n"
           << "5 4 9 9 3 9 1 \n"
           << "5 9 9 9 9 9 5 \n"
           << "5 5 5 5 5 5 5 \n";
  ASSERT_EQUAL(expected.str(), actual.str());

  assert(Matrix_max(mat) == 9);
  assert(Matrix_min_value_in_row(mat, 1, 0, 5) == 0);
  assert(Matrix_column_of_min_value_in_row(mat, 1, 0, 5) == 3);
  assert(Matrix_min_value_in_row(mat, 1, 1, 7) == 0);
  assert(Matrix_column_of_min_value_in_row(mat, 1, 1, 7) == 3);
  assert(Matrix_min_value_in_row(mat, 2, 1, 7) == 1);
  assert(Matrix_column_of_min_value_in_row(mat, 2, 1, 7) == 6);
  assert(Matrix_min_value_in_row(mat, 2, 1, 5) == 3);
  assert(Matrix_column_of_min_value_in_row(mat, 2, 1, 5) == 4);
  assert(Matrix_min_value_in_row(mat, 2, 0, 2) == 4);
  assert(Matrix_column_of_min_value_in_row(mat, 2, 0, 2) == 1);
  assert(Matrix_min_value_in_row(mat, 3, 1, 6) == 9);
  assert(Matrix_column_of_min_value_in_row(mat, 3, 1, 6) == 1);
  assert(Matrix_min_value_in_row(mat, 4, 0, 7) == 5);
  assert(Matrix_column_of_min_value_in_row(mat, 4, 0, 7) == 0);
  
  delete mat; // delete the Matrix
}

TEST(test_min_one) {
  Matrix *mat = new Matrix;

  const int value = 0;
  Matrix_init(mat, 1, 1);
  Matrix_fill(mat, value);

  ostringstream expected;
  expected << "1 1\n"
           << "0 \n";
  ostringstream actual;
  Matrix_print(mat, actual);

  ASSERT_EQUAL(expected.str(), actual.str());

  assert(Matrix_min_value_in_row(mat, 0, 0, 1) == 0);
  assert(Matrix_column_of_min_value_in_row(mat, 0, 0, 1) == 0);

  delete mat; // delete the Matrix
}

TEST(test_matrix_print) {
  Matrix *mat = new Matrix;
  Matrix_init(mat, 1, 1);

  *Matrix_at(mat, 0, 0) = 42;
  ostringstream expected;
  expected << "1 1\n"
           << "42 \n";
  ostringstream actual;
  Matrix_print(mat, actual);
  ASSERT_EQUAL(expected.str(), actual.str());

  delete mat;
}

TEST(test_border_one) {
  Matrix *mat = new Matrix;
  Matrix_init(mat, 1, 1);
  *Matrix_at(mat, 0, 0) = 42;
  Matrix_fill_border(mat, 10);

  ostringstream expected;
  expected << "1 1\n"
           << "10 \n";

  ostringstream actual;
  Matrix_print(mat, actual);
  ASSERT_EQUAL(expected.str(), actual.str());

  delete mat;
}

TEST(test_border_two) {
  Matrix *mat = new Matrix;
  Matrix_init(mat, 2, 2);
  Matrix_fill(mat, 42);
  Matrix_fill_border(mat, 10);

  ostringstream expected;
  expected << "2 2\n"
           << "10 10 \n"
           << "10 10 \n";

  ostringstream actual;
  Matrix_print(mat, actual);
  ASSERT_EQUAL(expected.str(), actual.str());
  delete mat;
}

TEST(test_border_three) {
  Matrix *mat = new Matrix;
  Matrix_init(mat, 3, 3);
  Matrix_fill(mat, 42);
  Matrix_fill_border(mat, 10);

  ostringstream expected;
  expected << "3 3\n"
           << "10 10 10 \n"
           << "10 42 10 \n"
           << "10 10 10 \n";
  
  ostringstream actual;
  Matrix_print(mat, actual);
  ASSERT_EQUAL(expected.str(), actual.str());

  delete mat;
}

TEST(test_matrix_basic) {
  Matrix *mat = new Matrix;
  Matrix_init(mat, 5, 5);
  Matrix_fill(mat, 0);

  int *ptr = Matrix_at(mat, 2, 3);
  assert(Matrix_row(mat, ptr) == 2);
  assert(Matrix_column(mat, ptr) == 3);

  delete mat;
}
// NOTE: The unit test framework tutorial in Lab 2 originally
// had a semicolon after TEST_MAIN(). Although including and
// excluding the semicolon are both correct according to the c++
// standard, the version of g++ we are using reports a warning
// when there is a semicolon. Therefore do NOT add a semicolon
// after TEST_MAIN()
TEST_MAIN() // Do NOT put a semicolon here
