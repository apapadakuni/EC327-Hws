// Copyright 2017 Isa Mustafa isas@bu.edu
// Copyright 2017 Andreas Papadakis apapadak@bu.edu
// stringtesters original

#include <iostream>
#include <string>
using std::string;
using std::cout;
using std::cin;



// for(int j=0; j<=9; j++){
// if(num[i]==j || num[0]=='0'){
//  error=false;
// } else error=true;
//break;
//}


bool is_palindrome(string num, bool & error) {

  error = false;

  if (num.size() == 0) {
    error = true;
    return false;
  } else {
    if (num[0] == '0') {
      error = true;
      return false;
    } else {
      if (num.size() > 1) {
        for(int i = 0; i < num.size(); i++) {
          int check = ('0' <= num[i] && num[i] <= '9');
          if (check == 0) {
            error = true;
            return false;
          }
        }
      }
    }
}

    if (num.size() == 1) {
      return true;
    } else if(num.size() % 2 == 0) {
      for(int k = 0; k <= ((num.size() / 2) - 1); k++) {
        if (num[k] != num[(num.size() - k - 1)]) {
          return false;
        } 
      }
    } else if (num.size() % 2 == 1) {
      for(int k = 0; k <= (num.size() / 2 - 1.5); k++) {
        if (num[k] != num[(num.size() - k - 1)]) {
          return false;
        } 
      }
    }
    return true;
  }



bool is_word(string s) {
  int cap;
  int i = 1;
  int check = 0;
  int rest;
  int j = 0;
  int allcaps;
  int alllower;

  if (s.size() > 0) {
    cap = 'A' <= s[0] && s[0] <= 'Z';
    while (i < s.size()) {
      rest = 'a' <= s[i] && s[i] <= 'z';
      if (rest == 0) {
        break;
      }
      i = i + 1;
    }
    while (j < s.size()) {
      allcaps = 'A' <= s[j] && s[j] <= 'Z';
      if (allcaps == 0) {
        break;
      }
      j = j + 1;
    }
    j = 0;

    while (j < s.size()) {
      alllower = 'a' <= s[j] && s[j] <= 'z';
      if (alllower == 0) {
        break;
      }
      j = j + 1;
    }
  }

  if (s.size() == 0) {
    return 0;
  } else if ((rest && cap) || allcaps || alllower) {
    return 1;
  }
}

// leave this line and everything below as is
int main() {
  cout << std::boolalpha;

  if (not is_word("test")) cout << "we1\n";
  if (not is_word("Test")) cout << "we2\n";
  if (not is_word("TEST")) cout << "we3\n";
  if (not is_word("thisisaword")) cout << "we4\n";

  if (is_word("123")) cout << "we5\n";
  if (is_word("")) cout << "we6\n";
  if (is_word("abc123abc")) cout << "we7\n";
  if (is_word("tEst")) cout << "we8\n";
  if (is_word("tEst")) cout << "we9\n";
  if (is_word("TESTer")) cout << "we10\n";

  bool error;

  if (not is_palindrome("12321", error) or error) cout << "pe1\n";
  if (not is_palindrome("9009", error) or error) cout  << "pe2\n";
  if (not is_palindrome("9", error) or error)  cout << "pe3\n";
  if (not is_palindrome("123456777654321", error) or error) cout << "pe4\n";

  if (is_palindrome("abcba", error) or not error) cout << "pe5\n";
  if (is_palindrome("12321 a", error) or not error) cout << "pe6\n";
  if (is_palindrome("0012100", error) or not error) cout << "pe7\n";

  if (is_palindrome("123", error) or error) cout << "pe8\n";
  if (is_palindrome("123211", error) or error) cout << "pe9\n";

  cout << "Test Other Words. Ctrl-D to exit.\n";

  string s;
  bool pal;
  while (cin >> s) {
    pal = is_palindrome(s, error);
    cout << s << " " << pal << " " << error << " " << is_word(s) << '\n';
  }

  return 0;
}
