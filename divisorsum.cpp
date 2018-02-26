// Copyright 2017 <Copyright Andreas Papadakis>, apapadak@bu.edu

#include <iostream>
using std::cout;


int main() {
  int i;
  i = 2;

  int j;
  j = 2;

  int k;
  k = 1;

  while (i <= 888) {
    cout << i << ": ";
    cout << "1 ";
    while (j < i) {
      if (i % j == 0) {
        cout << "+ " << j << " ";
        k = k + j;
      }
      j = j + 1;
    }
    cout << "= " << k << "\n";
    j = 2;
    k = 1;
    i = i + 1;
  }
}
