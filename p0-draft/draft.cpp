#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

struct Node {
  char datum;
  Node *next;
};

bool is_capital(char c) {
  return c <= 'Z' && c >= 'A';
}



void takes_an_integer(int x) {} 

// make draft.exe
// ./draft.exe
int main() {
  size_t x;
  cin >> x; takes_an_integer(x);
  
}
