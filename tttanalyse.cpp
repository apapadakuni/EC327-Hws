// Copyright 2017 Andreas Papadakis apapadak@bu.edu

#include <iostream>
#include <fstream>
#include <string>
using std:: string;
using std:: ifstream;
using std:: ofstream;

char whowon(string line) {
  int i = 0;
  char xwon = 'b';
  char owon = 'b';
  char out;
  while (i < 7) {
    if ((line[i] == line[i + 1]) &&
        (line[i + 1] == line[i + 2]) && (line[i] == 'x')) {
      xwon = 'x';
    }
    if ((line[i] == line[i + 1]) &&
        (line[i + 1] == line[i + 2]) && (line[i] == 'o')) {
      owon = 'o';
    }
    i = i + 3;
  }

  i = 0;

  while (i < 3) {
    if ((line[i] == line[i + 3]) &&
        (line[i + 3] == line[i + 6]) && (line[i + 3] == 'x')) {
      xwon = 'x';
    }
    if ((line[i] == line[i + 3]) &&
        (line[i + 3] == line[i + 6]) && (line[i + 3] == 'o')) {
      owon = 'o';
    }
    i = i + 1;
  }

  if ((line[0] == line[4]) && (line[4] == line[8]) && (line[4] == 'x')) {
    xwon = 'x';
  }
  if ((line[0] == line[4]) && (line[4] == line[8]) && (line[4] == 'o')) {
    owon = 'o';
  }
  if (line[2] == line[4] && line[4] == line[6] && (line[2] == 'x')) {
    xwon = 'x';
  }
  if (line[2] == line[4] && line[4] == line[6] && (line[2] == 'o')) {
    owon = 'o';
  }
  if ((xwon == 'x') && (owon == 'o')) {
    out = 'i';
  } else if ((xwon == 'x') && (owon == 'b')) {
    out = xwon;
  } else if ((xwon == 'b') && (owon == 'o')) {
    out = owon;
  } else if ((xwon == 'b') && (owon == 'b')) {
    out = 'n';
  }
  return out;
}




int main() {
  char ans;
  int i = 0;
  int countx = 0;
  int counto = 0;
  int countspace = 0;
  char won = 'b';
  int valid;
  string line;

  ifstream readfile("tictactoeboards.txt");
  ofstream writfile("tttstatus.txt");
  if (readfile.is_open()) {
    while ( getline(readfile, line) ) {
      while (i < line.size()) {
        if (line[i] == 'x') {
          countx = countx + 1;
        }
        if (line[i] == 'o') {
          counto = counto + 1;
        }
        if (line[i] == '#') {
          countspace = countspace + 1;
        }
        i = i + 1;
      }
      won = whowon(line);

      valid = ((countx == counto) || (countx == (counto + 1)));

      if (valid == 1) {
        if ((countx == (counto + 1)) && (won == 'x')) {
          ans = 'x';
        } else if ((countx == counto) && (won == 'o')) {
          ans = 'o';
        } else if ((won == 'n') && (countspace == 0)) {
          ans = 't';
        } else if ((won == 'n') && (countspace > 0)) {
          ans = 'c';
        } else {
          ans = 'i';
        }
      } else if (valid == 0) {
        ans = 'i';
      }


      writfile << line << " " << ans << "\n";
      i = 0;
      countx = 0;
      counto = 0;
      countspace = 0;
    }
    readfile.close();
  }
  return 0;
}
