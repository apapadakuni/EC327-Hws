// Copyright 2017 Andreas Papadakis apapadak@bu.edu
// Copyright 2017 Isa Mustafa isas@bu.edu
// Copyright 2017 Boxi Huang huangbo@bu.edu

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using std:: string;
using std:: ifstream;
using std:: ofstream;
using std:: cin;
using std:: cout;
using std:: vector;




int checkin(string file, int num) {
  ifstream ifs;
  ifs.open(file);
  string line;

  if (ifs.is_open()) {
    int rowcount = 0;
    int emptycount = 0;
    int check = 1;
    int nostar = 0;


    while (getline(ifs, line)) {


      for (int i = 0; i < line.size(); i++) {
        if (line[i] == '.') {
          nostar = nostar + 1;
        }

        if ((line[i] != '.' and line[i] != '*')) {
          return 1;
        }
      }

      if (line.size() != 0) {
        rowcount++;
      } else if (line.size() == 0) {
        emptycount++;
      }
      if (line.size() != num and line.size() != 0) {
        check = 0;
      }

      if (line.size() == 0) {
        if (nostar == (num * num)) {
          return 3;
        }
        nostar = 0;
      }
      //cout << emptycount << " " << rowcount << " "<< check <<"\n";
    }

    int morelines = (num * (emptycount) + emptycount);
    //cout << rowcount << " " << emptycount << " " << morelines  << "\n";
    if (((rowcount + emptycount) != morelines) or check == 0) {
      return 2;
    }


    ifs.close();
  }
  return 0;
}


int main(int argc, char const *argv[]) {

  int num = 5;
  string infile;
  string outfile;
  int inputresult;


  if (argc == 3) {
    num = std::stoi(argv[1]);
    infile = argv[2];
    inputresult = checkin(infile, num);
    //cout << inputresult << "\n"; // just checking
    if (inputresult == 2) {
      return 2;
    } else if (inputresult == 1) {
      return 1;
    } else if (inputresult == 3) {
      return 3;
    }

    else {    //this is for the case that the input file works with the user's 2 arguments, so print in terminal
      string lineyo;
      ifstream myfile (infile);
      if (myfile.is_open()) {
        while ( getline (myfile, lineyo) ) {
          cout << lineyo << '\n';
        }
        myfile.close();
      }
      return 0;
    }
  } //done with the case of "user enters one num and one input file"



  else if (argc > 3) {
    num = std::stoi(argv[1]);
    infile = argv[2];
    outfile = argv[3];
    inputresult = checkin(infile, num);
    if (inputresult == 2) {
      return 2;
    } else if (inputresult == 1) {
      return 1;
    } else {    //this is for the case that the input file works with the user's 2 arguments, so time to print to the output file
      string lineyo2;
      ifstream myfile (infile);
      ofstream thefile (outfile);
      if (myfile.is_open() && thefile.is_open()) {
        while ( getline (myfile, lineyo2) ) {
          thefile << lineyo2 << '\n'; //printing the lines we get to the output file
        }
        thefile.close();
        myfile.close();
      }
      return 0;
    }
  } //done with the case of "user enters every bit of info"
  else { //meaning the case of argc is 1 or 2
    int numline = 0;
    int alldots = 0;
    int count = 0;
    int sup = 0;
    vector <string> show;

    if (argc == 2) { //change the value of num if num is specified
      num = std::stoi(argv[1]);
    }
    string typed;

    while (getline (cin, typed)) {

      for (int i = 0; i < typed.size(); i++) {
        if (typed[i] == '.') {
          alldots = alldots + 1;
        }

        if ((typed[i] != '.' and typed[i] != '*')) {
          return 1;
        }
      }
      // if (typed.size() != num && numline != num) {
      //   return 2;
      // }
      int count = 0;

      if (typed.size() != 0) {
        numline = numline + 1;
      }

      count = numline;


      if (typed.size() == 0 && numline == num) {
        numline = 0;
      }
      if (typed.size() != num && typed.size() != 0) {
        return 2;
      }

      // cout << count << "\n";
      if (typed.size() == 0 && (count != num)) { //checking each line is the same size as num
        return 2;
      }
      //   else if (typed.size() == 0 && numline == num) {
      //     count = count + 1;
      // ;
      //     sup = numline;
      //     numline = 0;

      if (typed.size() == 0) {
        if (alldots == (num * num)) {
          return 3;
        }
        alldots = 0;
      }
      //   }

      show.push_back(typed);
      //cout << numline << "\n";
    }
    // // cout << show.size();
    //  if (sup != num) {
    //    return 2;
    //  }
    if (numline != num && numline != 0) {
      return 2;
    }

    int j = 0;
    while (j < show.size()) {
      cout << show[j] << "\n";
      j = j + 1;
    }




  }
}