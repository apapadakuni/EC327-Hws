// Copyright 2017 <Copyright Andreas Papadakis>, apapadak@bu.edu

#include <iostream>
using std::cout;


int main() {
  int counter = 0;
  int k = 1;
  int i = 1;
  int thous;
  int ones;
  int tens;
  int huns;
  int yo;
  int yo2;





  while (counter < 888) {
    i = k;
    while (i < 10000) {
      thous = (i - (i % 1000)) / 1000;
      yo = i % 1000;
      huns = (yo - (yo % 100)) / 100;
      yo2 = yo % 100;
      tens = (yo2 - (yo2 % 10)) / 10;
      ones = i % 10;
      i = ones * ones + tens * tens + huns * huns + thous * thous;
      if (i == 1) {
        counter = counter + 1;
        cout << k << "\n";
        break;
      }
      if (i == 4) {
        break;
      }
    }
    k = k + 1;
  }
  return 0;
}
