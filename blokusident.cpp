// Copyright 2017 Andreas Papadakis apapadak@bu.edu
// Copyright 2017 Isa Mustafa isas@bu.edu
// Copyright 2017 Boxi Huang huangbo@bu.edu
// Copyright 2017 Hayato Nakamura hayaton@bu.edu

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <math.h>
using std:: string;
using std:: ifstream;
using std:: ofstream;
using std:: cin;
using std:: cout;
using std:: vector;
using namespace std;





vector<string> shift(vector<string> block, int size) {


  int invalid = 1;
  int maxrow = size;
  int maxcol = size;
  int minrow = 100;
  int mincol;


  for (int row = 0; row < size; row++) {
    for (int col = 0; col < size; col++) {

      if (block[row][col] == '*' && minrow == 100) {
        minrow = row;
        mincol = col;
        maxcol = col;
      }
      if (block[row][col] == '*') {
        maxrow = row;

      }
      if (block[row][col] == '*' && (col < mincol)) {
        mincol = col;
      }
      if (block[row][col] == '*' && (col > maxcol)) {
        maxcol = col;
      }
    }
  }
  string newrow(size, '.');



  vector<string> out(size, newrow);



  for (int outrow = 0; outrow <= (maxrow - minrow); outrow++) {
    for (int outcol = 0; outcol <= (maxcol - mincol); outcol++) {
      out[outrow][outcol] =  block[outrow + minrow][outcol + mincol];
    }
  }


  return out;
}




vector<string> rot90(vector<string> isolated) {
  string newrow(isolated.size(), '.');
  vector<string> newvector(isolated.size(), newrow);

  for (int i = 0; i < isolated.size(); i++) {
    for(int j = 0; j < isolated[i].size(); j++) {

      newvector[i][j] = isolated[j][isolated.size() - 1 - i];
    }
  }
  return newvector;
}

vector<string> rot180(vector<string> isolated) {
  string newrow(isolated.size(), '.');
  vector<string> newvector(isolated.size(), newrow);
  string newrow2(isolated.size(), '.');
  vector<string> newvector2(isolated.size(), newrow);

  for (int i = 0; i < isolated.size(); i++) {
    for(int j = 0; j < isolated[i].size(); j++) {

      newvector[i][j] = isolated[j][isolated.size() - i];
    }
  }
  for (int i = 0; i < newvector.size(); i++) {
    for(int j = 0; j < newvector[i].size(); j++) {

      newvector2[i][j] = newvector[j][newvector.size() - i];
    }
  }
  return newvector2;
}

vector<string> rot270(vector<string> isolated) {
  string newrow(isolated.size(), '.');
  vector<string> newvector(isolated.size(), newrow);
  string newrow2(isolated.size(), '.');
  vector<string> newvector2(isolated.size(), newrow);
  string newrow3(isolated.size(), '.');
  vector<string> newvector3(isolated.size(), newrow);

  for (int i = 0; i < isolated.size(); i++) {
    for(int j = 0; j < isolated[i].size(); j++) {

      newvector[i][j] = isolated[j][isolated.size() - i];
    }
  }
  for (int i = 0; i < newvector.size(); i++) {
    for(int j = 0; j < newvector[i].size(); j++) {

      newvector2[i][j] = newvector[j][newvector.size() - i];
    }
  }
  for (int i = 0; i < newvector2.size(); i++) {
    for(int j = 0; j < newvector2[i].size(); j++) {

      newvector3[i][j] = newvector2[j][newvector2.size() - i];
    }
  }
  return newvector3;
}


vector<string> flipud(vector<string> isolated) {
  string newrow(isolated.size(), '.');
  vector<string> newvector(isolated.size(), newrow);

  for (int i = 0; i < floor(isolated.size() / 2); i++) {
    for(int j = 0; j < isolated[i].size(); j++) {

      newvector[i][j] = isolated[i][isolated.size() - j];
    }
  }
  return newvector;
}

vector<string> fliplr(vector<string> isolated) {
  string newrow(isolated.size(), '.');
  vector<string> newvector(isolated.size(), newrow);

  for (int i = 0; i < isolated.size(); i++) {
    for(int j = 0; j < floor(isolated.size() / 2); j++) {

      newvector[i][j] = isolated[isolated.size() - i][j];
    }
  }
  return newvector;
}



int invalid (vector <string> block, int size) {


  int numstars = 0;


  for (int row = 0; row < size; row++) {
    for (int col = 0; col < size; col++) {
      if (block[row][col] == '*') {
        numstars = numstars + 1;
      }
    }
  }
  if (numstars == 1) {
    return 1;
  }

  vector <int> rows((numstars), 0);
  vector <int> cols((numstars), 0);
//cout << rows;

  int i = 0;
  for (int row = 0; row < size; row++) {
    for (int col = 0; col < size; col++) {
      if (block[row][col] == '*') {
        rows[i] = row;
        cols[i] = col;
        //cout << rows[i] << " " << cols[i] <<"\n";
        i = i + 1;
      }
    }
  }

  int check = 0;
  for (int k = 0; k < (numstars - 1); k++) {
    for (int p = (k + 1); p < numstars; p++) {

      int checkrow = ((rows[k] == (rows[p] + 1)) || (rows[k] == (rows[p] - 1))) && (cols[k] == cols[p]);
      int checkcol = ((cols[k] == (cols[p] + 1)) || (cols[k] == (cols[p] - 1))) && (rows[k] == rows[p]);

      check = checkrow || checkcol;
      if (checkrow == 1) {
        break;
      }
      if (checkcol == 1) {
        break;
      }


    }
    if (check == 0) {
      return 1;
    }

  }

  return 0;
}




vector <int> identity(vector <string> file, int num) {


  int rows = file.size(); //REMEMBER IT IS THE SIZE, NOT THE FUCKING INDEX
  vector <int> out(5, 10000);

  vector <string> block;
  vector <string> nextblock;
  int outpos = 0;

  for (int i = 0; i < (rows - num - 1); i = i + num + 1) {
    //cout << "BLOCK1\n";
    for (int j = 0; j < num; j++) {
      block.push_back(file[i + j]); //block is the block we want to examine
//    cout << block[j] << "\n";
    }
    if (invalid(block, num) == 1) { // meaning the block is invalid
      out[outpos] = i; //put the value of the beginning row of the invalid box
      outpos = outpos + 1;
      //cout << "INVALID" << "\n";
    } else { //meaning the box is valid so we check for the rest

      for (int k = i + num + 1; k < rows; k = k + num + 1) { //this goes from where i is and picks then next four blocks
        // cout << "BLOCK2" <<"\n" ;
        for (int p = 0; p < num; p++ ) {
          nextblock.push_back(file[k + p]); //have now created the next block i want to compare
          //   cout <<  nextblock [p] << "\n";
        }
        //     block=shift(block, num);
        //nextblock = shift (nextblock, num);
        block = shift(block, num);
        // block = (rot90(block));
        //  for (int m=0; m<num; m++){
        //   cout << block[m] << "\n";
        // }


        // cout << "block1 \n";
        // for (int m=0; m<num; m++){
        //   cout << block[m] << "\n";
        // }
        // //cout << block[3];
        // cout << "block2 \n";
        // for (int m=0; m<num; m++){
        //   cout << nextblock[m] << "\n";
        // }


        bool equalrot = (block == shift(rot90(nextblock), num)) or (block == shift(rot270(nextblock), num)) or (block == shift(rot180(nextblock), num)); //rotations
        bool equalfld = (block == shift(nextblock, num)) or (block == shift(flipud(nextblock), num)) or (block == shift(flipud(rot270(nextblock)), num)); // or (block == shift(fliplr(nextblock), num)) ;
        bool equal = equalrot or equalfld; // meaning block and nextblock are equal at some point
        //cout << equal << "\n";
        if (equal == 1) {
          out[outpos] = k; //put the value of the row from nextblock has been taken from the file
          outpos = outpos + 1;
        }

        nextblock.clear(); //deleting nextblock, so the newblock is created in nextblock

      }
    }
    block.clear();
  }



  return out;


}




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

vector <string> dlt(vector <string> file, vector <int> dltnum, int size) {

  int pos = 0;

  for (int i = 4; i >= 0; i = i - 1) {

    pos = dltnum[i];
    if (pos != 10000) {
      file.erase(file.begin() + pos, file.begin() + pos + size + 1);
    }
  }



  return file;
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
    vector <string> notime;
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
          notime.push_back(lineyo);
        }
        myfile.close();
      }
      vector <int> nope = identity(notime, num);
      notime = dlt(notime, nope, num);
      for (int k = 0; k < notime.size(); k++) {
        cout << notime[k] << "\n";
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
      vector <string> sms;
      if (myfile.is_open()) {
        while ( getline (myfile, lineyo2) ) {
          sms.push_back(lineyo2); //printing the lines we get to the output file
        }
        myfile.close();
      }
      vector <int> nope = identity (sms, num);
      sms = dlt(sms, nope, num);

      if (thefile.is_open()) {
        for(int less = 0; less < sms.size(); less++) {
          thefile << sms[less] << '\n';
        }
        thefile.close();
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
    vector <int> bob = identity(show, num);
    show = dlt(show, bob, num);


    while (j < show.size()) {
      cout << show[j] << "\n";
      j = j + 1;
    }




  }
}


