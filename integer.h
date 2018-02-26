// Copyright 2017 Andreas Papadakis apapadak@bu.edu
// Copyright 2017 Boxi Huang huangbo@bu.edu
// Copyright 2017 Hayato Nakamura hayaton@bu.edu



#ifndef INTEGER_H
#define INTEGER_H
#include <string>
#include <iostream>
#include <vector>

using std::string;
using std::stoi;
using std::ostream;
using std::to_string;
using std::cout;
using std::endl;
using std::vector;

class Integer {
 public:
  string value;
  bool neg;
  Integer() {
    value = '0';
  }
  Integer(string text) {
    int i = 0;

    if (text[0] == '-') {
      neg = true;
      int count = 0;
      for (int i = 1; i < text.size() - 1; i++) {
        if (text[i] == '0') {
          count = count + 1;
        } else if (text[i] != '0') {
          break;
        }
        text.erase(1, count);
      }
      if (text[1] == '0') {
        text.erase(0, 1);
      }

      //i = 1;
      //text.erase(0, 1);
    } else {
      int count = 0;
      for (int i = 0; i < text.size() - 1; i++) {
        if (text[i] == '0') {
          count = count + 1;
        } else if (text[i] != '0') {
          break;

        }
        text.erase(0, count);
      }
    }

    string supbo = text;


    // int count = 0;

    // for (int k = i ; i < (supbo.size() - 1); i++) {

    //   if (supbo[i] == '0') {
    //     count = count + 1;
    //   } else if (supbo[i] != '0') {
    //     break;
    //   }
    // }

    // supbo.erase(0, count);
    // if (neg == true) {
    //   supbo.insert(0, 1, '-');
    // }


    this->value = supbo;
  }
  Integer(int value) {
    string x = to_string(value);
    if (x[0] == '-') {
      neg = true;
    }
    this->value = x;
  }

  friend bool operator==(const Integer& left, const Integer& right);
  friend bool operator!=(const Integer& left, const Integer& right);
  friend bool operator<(const Integer& left, const Integer& right);

  explicit operator bool() const {
    if (this->value[0] == '0') {
      return false;
    } else if (this->value[0] == '-') {
      if (this->value[1] == '0') {
        return false;
      }
      return true;
    } else {
      return true;
    }
  }
  Integer operator++();
  Integer operator++(int);

  Integer operator--();
  Integer operator--(int);

};
Integer add(const Integer& one, const Integer& two) {
  if (one.neg == false && two.neg == false) {
    bool overflow = false;
    int indexone = one.value.size() - 1;
    int indexval = two.value.size() - 1;
    int index;
    string first = one.value;
    string second = two.value;
    int stringsize;



    if (first.size() > second.size()) {

      string text(first.size(), '0');
      for (int k = second.size() - 1; k > -1; k--) {
        //cout << k << " " << text <<"\n";
        text[first.size() - 1 - k] = second[second.size() - 1 - k];

      }

      //cout << text << "\n";

      index = indexone;
      stringsize = first.size();
      second = text;

    } else if (second.size() > first.size()) {
      string text(second.size(), '0');

      for (int j = first.size() - 1; j > -1; j--) {
        text[second.size() - 1 - j] = first[first.size() - j - 1];
      }
      index = indexval;
      stringsize = second.size();
      first = text;

    } else if (second.size() == first.size()) {
      index = indexval;
      stringsize = first.size();
    }
    //cout << first << " " << second << "\n";

    string adding(stringsize + 1, '0');
    index = stringsize - 1;
    //cout << adding << "\n";

    while (index >= 0) {
      //cout << index << "\n";
      if (overflow == false) {
        char addition  = first[index] + second[index] - '0';
        if (addition > '9') {
          overflow = true;
          addition = addition - '9'  + '0' - 1;
        }
        adding[index + 1] = addition;
      } else if (overflow == true) {
        char addition  = first[index] + second[index] - '0' + 1;
        if (addition > '9') {
          overflow = true;
          addition = addition - '9'  + '0' - 1;
        } else overflow = false;
        adding[index + 1] = addition;
      }
      index = index - 1;
      //cout << adding << "\n";

    }
    if (overflow == true) {
      adding [0] = '1';
    } else adding.erase(0, 1);
    Integer result(adding);
    return result;
  }
  // else if (one.neg == false && two.neg == true){
  // 	Integer result = subtract(one,two);
  // 	return result;
  // }
  // else if (one.neg == true && two.neg == false){
  // 	Integer result = subtract(two,one);
  // 	return result;
  // }
  else if (one.neg == true && two.neg == true) {
    string str1 = one.value;
    string str2 = two.value;
    str1.erase(0, 1);
    str2.erase(0, 1);


    Integer left(str1);
    Integer right(str2);

    bool overflow = false;
    int indexone = left.value.size() - 1;
    int indexval = right.value.size() - 1;
    int index;
    string first = left.value;
    string second = right.value;
    int stringsize;



    if (first.size() > second.size()) {

      string text(first.size(), '0');
      for (int k = second.size() - 1; k > -1; k--) {
        //cout << k << " " << text <<"\n";
        text[first.size() - 1 - k] = second[second.size() - 1 - k];

      }

      //cout << text << "\n";

      index = indexone;
      stringsize = first.size();
      second = text;

    } else if (second.size() > first.size()) {
      string text(second.size(), '0');

      for (int j = first.size() - 1; j > -1; j--) {
        text[second.size() - 1 - j] = first[first.size() - j - 1];
      }
      index = indexval;
      stringsize = second.size();
      first = text;

    } else if (second.size() == first.size()) {
      index = indexval;
      stringsize = first.size();
    }
    //cout << first << " " << second << "\n";

    string adding(stringsize + 1, '0');
    index = stringsize - 1;
    //cout << adding << "\n";

    while (index >= 0) {
      //cout << index << "\n";
      if (overflow == false) {
        char addition  = first[index] + second[index] - '0';
        if (addition > '9') {
          overflow = true;
          addition = addition - '9'  + '0' - 1;
        }
        adding[index + 1] = addition;
      } else if (overflow == true) {
        char addition  = first[index] + second[index] - '0' + 1;
        if (addition > '9') {
          overflow = true;
          addition = addition - '9'  + '0' - 1;
        } else overflow = false;
        adding[index + 1] = addition;
      }
      index = index - 1;
      //cout << adding << "\n";

    }
    if (overflow == true) {
      adding [0] = '1';
    } else adding.erase(0, 1);

    //string negadding(adding.)
    adding.insert(0, 1, '-');
    Integer result(adding);
    return result;

  }

}

Integer subtract(const Integer& one, const Integer& two) {
  string left = one.value;
  string right = two.value;
  string x = left;
  string y = right;

  if (x[0] == '-') {
    x.erase(0, 1);
  }

  if (y[0] == '-') {
    y.erase(0, 1);
  }

  bool xisbigger = 0;

  if (x.size() > y.size()) {
    xisbigger = 1;
  } else if (x.size() < y.size()) {
    xisbigger = 0;
  } else if (x.size() == y.size()) {
    for (int i = 0; i < x.size(); i++) {
      if (x[i] < y[i]) {
        xisbigger = 0;
        break;
      }
      if (x[i] > y[i]) {
        xisbigger = 1;
        break;
      }
    }
    string result(1, '0');
    //cout << result << endl;
  }
  if (xisbigger == 1) {
    string text(x.size(), '0');
    for (int k = y.size() - 1; k > -1; k--) {
      //cout << k << " " << text <<"\n";
      text[x.size() - 1 - k] = y[y.size() - 1 - k];
    }
    y = text;
  } else if (xisbigger == 0) {
    string text(y.size(), '0');
    for (int k = x.size() - 1; k > -1; k--) {
      //cout << k << " " << text <<"\n";
      text[y.size() - 1 - k] = x[x.size() - 1 - k];
    }
    x = text;

  }





  if (left[0] == '-' && right[0] == '-') { //both negative so - - (-)
    int stringsize = x.size();
    string xdecoy = x;
    string ydecoy = y;
    if (xisbigger == 0) {
      string temp = y;
      y = x;
      x =  temp;
    }
    //cout << x << endl;
    //cout << y << endl;
    string adding(stringsize, '0');
    int index = stringsize - 1;
    int overflow = false;
    //cout << adding << "\n";
    //cout << index << endl;
    while (index >= 0) {
      //cout << index << "\n";
      if (overflow == false) {
        char addition  = x[index] - y[index] + '0';
        //cout << addition << endl;
        if (addition < '0') {
          //cout <<"wrong"; // wrong;
          overflow = true;
          addition = addition + '9'  - '0' + 1;
        }
        adding[index] = addition;
      } else if (overflow == true) {
        char addition  = x[index] - y[index] + '0' - 1;
        if (addition < '0') {
          overflow = true;
          addition = addition + '9'  - '0' + 1;
        } else overflow = false;
        adding[index] = addition;
      }
      index = index - 1;
      //cout << adding << "\n";

    }
    if (xisbigger == 1) {
      adding.insert(0, 1, '-');
    }
    Integer result2(adding);
    return result2;
    //	cout << adding << endl;

    //Integer result(adding);
    //return result;
  }

  else if (left[0] != '-' && right[0] != '-') {
    int stringsize = x.size();
    string xdecoy = x;
    string ydecoy = y;
    if (xisbigger == 0) {
      string temp = y;
      y = x;
      x =  temp;
    }
    //cout << x << endl;
    //cout << y << endl;
    string adding(stringsize, '0');
    int index = stringsize - 1;
    int overflow = false;
    //cout << adding << "\n";
    //cout << index << endl;
    while (index >= 0) {
      //cout << index << "\n";
      if (overflow == false) {
        char addition  = x[index] - y[index] + '0';
        //cout << addition << endl;
        if (addition < '0') {
          //cout <<"wrong"; // wrong;
          overflow = true;
          addition = addition + '9'  - '0' + 1;
        }
        adding[index] = addition;
      } else if (overflow == true) {
        char addition  = x[index] - y[index] + '0' - 1;
        if (addition < '0') {
          overflow = true;
          addition = addition + '9'  - '0' + 1;
        } else overflow = false;
        adding[index] = addition;
      }
      index = index - 1;
      //cout << adding << "\n";

    }
    if (xisbigger == 0) {
      adding.insert(0, 1, '-');
    }
    Integer result2(adding);
    return result2;


  }
  if (left[0] != '-' && right[0] == '-') {
    Integer xsub(x);
    Integer ysub(y);
    Integer result1 = add(xsub, ysub);
    return result1;
  }

  if (left[0] == '-' && right[0] != '-') {
    //string result1 = add(left,y);
    Integer xsub(x);
    Integer ysub(y);
    Integer result1 = add(xsub, ysub);
    string punk = result1.value;
    punk.insert(0, 1, '-');
    Integer result2(punk);
    return result2;
  }





}



// Multiply Function

int getC(int num) {
  int carry = 0;
  if(num >= 10) {
    while(num != 0) {
      carry = num % 10;
      num = num / 10;
    }
  } else carry = 0;
  return carry;
}

int num(char a) {
  return int(a) - 48;
}

string multiply(string a, string b) {
  string ret;
  int alength = a.length();
  int blength = b.length();
  int ROW = blength;
  int COL = alength + blength + 2;
  int mat[blength][COL];
  for(int i = 0; i < blength; ++i) {
    for(int j = 0; j < COL; ++j) {
      mat[i][j] = 0;
    }
  }
  int carry = 0, n, x = alength - 1, y = blength - 1;
  for(int i = 0; i < blength; ++i) {
    x = alength - 1;
    carry = 0;
    for(int j = (COL - 1) - i; j >= 0; --j) {
      if((x >= 0) && (y >= 0))  {
        n = (num(a[x]) * num(b[y])) + carry;
        mat[i][j] = n % 10;
        carry = getC(n);
      } else if((x >= -1) && (y >= -1)) {
        mat[i][j] = carry;
      }
      x = x - 1;
    }
    y = y - 1;
  }

  carry = 0;
  int sum_arr[COL];
  for(int i = 0; i < COL; ++i) sum_arr[i] = 0;
  for(int i = 0; i < blength; ++i) {
    for(int j = COL - 1; j >= 0; --j) {
      sum_arr[j] += (mat[i][j]);
    }
  }
  int temp;
  for(int i = COL - 1; i >= 0; --i) {
    sum_arr[i] += carry;
    temp = sum_arr[i];
    sum_arr[i] = sum_arr[i] % 10;
    carry = getC(temp);
  }

  for(int i = 0; i < COL; ++i) {
    ret.push_back(char(sum_arr[i] + 48));
  }

  while(ret[0] == '0') {
    ret = ret.substr(1, ret.length() - 1);
  }
  return ret;
}

//Division function
string div(string one, string two) {
  int s1 = one.size();
  int s2 = two.size();
  string quotient;
  vector<int> dividend (s1, 0);
  for (int i = 0; i < s1; i++) {
    dividend[i] = one[i] - '0';
  }
  int dvsr = stoi(two);

  int rem = 0;
  for (int j = 0; j < s1; j++) {
    int dvnd = rem * 10 + dividend[j];
    int d = 0;
    while (dvnd / dvsr == 0) {
      quotient.push_back('0');
      d++;
      dvnd = dvnd * 10 + dividend[j + d];
    }
    int value = dvnd / dvsr;
    quotient.push_back((char)value + '0');
    rem = dvnd % dvsr;
    j += d;
  }
  quotient.erase(0, std::min(quotient.find_first_not_of('0'), quotient.size() - 1));
  return quotient;
}

string mod(string one, string two) {

  int s1 = one.size();
  int s2 = two.size();
  vector<int> dividend (s1, 0);
  for (int i = 0; i < s1; i++) {
    dividend[i] = one[i] - '0';
  }
  int dvsr = stoi(two);
  int rem = 0;
  for (int j = 0; j < s1; j++) {
    int dvnd = rem * 10 + dividend[j];
    int d = 0;
    while (dvnd / dvsr == 0) {
      d++;
      dvnd = dvnd * 10 + dividend[j + d];
    }
    int value = dvnd / dvsr;
    rem = dvnd % dvsr;
    j += d;
  }
  string r = std::to_string(rem);
  return r;
  if (s1 < s2) {
    return one;
  }
}

Integer operator+(const Integer& left, const Integer& right) {
  Integer result = add(left, right);
  return result;
}

Integer operator+=(const Integer& var, const Integer& adden) {
  Integer result = add(var, adden);
  return 	result;
}

Integer operator-(const Integer& left, const Integer& right) {
  Integer result = subtract(left, right);
  return result;

}

Integer operator-=(const Integer& left, const Integer& right) {
  Integer result = subtract(left, right);
  return result;
}





Integer Integer::operator++() {
  // Pre (++i)


  Integer one(1);
  *this = add(*this, one);
  return *this;
}

Integer Integer::operator++(int) { //i++
  Integer one(1);
  Integer temp = add(*this, one);
  return Integer(temp);
}

Integer Integer::operator--() {
  // Pre (++i)
  Integer one(1);
  *this = subtract(*this, one);
  return *this;
}

Integer Integer::operator--(int) {
  // Post (i++)
  Integer one(1);
  Integer temp = subtract(*this, one);
  return Integer(temp);
}

Integer operator*(const Integer& i, const Integer& j) {
  string a = i.value;
  string b = j.value;

  if((a == "0") or (b == "0")) {
    Integer answer2(0);
    return answer2;
  } else if ((a[0] == '-') and (b[0] != '-')) {
    a[0] = '0';
    string answer = "-" + multiply(a, b);
    Integer answer2(answer);
    return answer2;
  } else if ((a[0] != '-') and (b[0] == '-')) {
    b[0] = '0';
    string answer = "-" + multiply(a, b);
    Integer answer2(answer);
    return answer2;
  } else if ((a[0] == '-') and (b[0] == '-')) {
    a[0] = '0';
    b[0] = '0';
    string answer = multiply(a, b);
    Integer answer2(answer);
    return answer2;
  } else {
    string answer = multiply(a, b);
    Integer answer2(answer);
    return answer2;
  }
}

Integer operator*=(const Integer& i, const Integer& j) {
  string a = i.value;
  string b = j.value;

  if((a == "0") or (b == "0")) {
    Integer answer2(0);
    return answer2;
  } else if ((a[0] == '-') and (b[0] != '-')) {
    a[0] = '0';
    string answer = "-" + multiply(a, b);
    Integer answer2(answer);
    return answer2;
  } else if ((a[0] != '-') and (b[0] == '-')) {
    b[0] = '0';
    string answer = "-" + multiply(a, b);
    Integer answer2(answer);
    return answer2;
  } else if ((a[0] == '-') and (b[0] == '-')) {
    a[0] = '0';
    b[0] = '0';
    string answer = multiply(a, b);
    Integer answer2(answer);
    return answer2;
  } else {
    string answer = multiply(a, b);
    Integer answer2(answer);
    return answer2;
  }
}

Integer operator*(const Integer& i, const int j) {
  return (i * Integer(j));
}

Integer operator*(int i, const Integer& j ) {
  return (Integer(i) * j);
}

// Integer operator*=(const Integer& i, const int j) {
//   return (i * Integer(j));
// }

// Integer operator*=(int i, const Integer& j ) {
//   return (Integer(i) * j);
// }


// bool isneg(string str) {
//   if(str[0] == '-')
//     return true;
//   else
//     return false;
// }

Integer operator/(const Integer one, const Integer two) {
  string str1 = one.value;
  string str2 = two.value;
  string final;
  int flag = 0;
  string zero = "0";

  if (str1.size() < str2.size()) {
    return Integer(zero);
  }
  if(str1[0] == '-') {
    str1.erase(str1.begin());
    flag = flag + 1;
  }
  if(str2[0] == '-') {
    str2.erase(str2.begin());
    flag = flag + 1;
  }

  final = div(str1, str2);
  if (flag == 1) {
    final.insert(0, "-");
  }
  Integer ans(final);
  return ans;
}

Integer operator/=(const Integer one, const Integer two) {
  string str1 = one.value;
  string str2 = two.value;
  string final;
  int flag = 0;
  string zero = "0";

  if (str1.size() < str2.size()) {
    return Integer(zero);
  }
  if(str1[0] == '-') {
    str1.erase(str1.begin());
    flag = flag + 1;
  }
  if(str2[0] == '-') {
    str2.erase(str2.begin());
    flag = flag + 1;
  }

  final = div(str1, str2);
  if (flag == 1) {
    final.insert(0, "-");
  }
  Integer ans(final);
  return ans;
}

Integer operator%(const Integer one, const Integer two) {
  string str1 = one.value;
  string str2 = two.value;
  string final;
  int flag = 0;
  if (str1.size() < str2.size()) {
    return Integer(str1);
  }
  if(str1[0] == '-') {
    str1.erase(str1.begin());
    flag = flag + 1;
  }
  if(str2[0] == '-') {
    str2.erase(str2.begin());
    flag = flag + 1;
  }
  final = mod(str1, str2);
  Integer ans(final);
  return ans;
}

Integer operator%=(const Integer one, const Integer two) {
  string str1 = one.value;
  string str2 = two.value;
  string final;
  int flag = 0;
  if (str1.size() < str2.size()) {
    return Integer(str1);
  }
  if(str1[0] == '-') {
    str1.erase(str1.begin());
    flag = flag + 1;
  }
  if(str2[0] == '-') {
    str2.erase(str2.begin());
    flag = flag + 1;
  }
  final = mod(str1, str2);
  Integer ans(final);
  return ans;
}


bool operator==(const Integer& left, const Integer& right) {
  if (left.value == right.value) return true;
  return false;
}


bool operator!=(const Integer& left, const Integer& right) {
  if (left.value != right.value)  return true;
  return false;
}

bool operator>(const Integer& left, const Integer& right) {
  string a = left.value;
  string b = right.value;

  if ((a[0] == '-') and (b[0] != '-')) {
    return false;
  } else if ((a[0] != '-') and (b[0] == '-')) {
    return true;
  } else if ((a[0] == '-') and (b[0] == '-')) {
    if (a.length() < b.length()) return true;
    if (a.length() > b.length()) return false;
    if (a[1] < b[1]) return true;
    if (a[1] > b[1]) return false;
    if (a == b) return false;
    return true;
  } else {
    if (a.length() > b.length()) return true;
    if (a.length() < b.length()) {
      if (a < b) return false;
    }
    if (a[0] < b[0]) return false;
    if (a == b) return false;
    return true;
  }
}

bool operator>=(const Integer& left, const Integer& right) {
  string a = left.value;
  string b = right.value;

  if ((a[0] == '-') and (b[0] != '-')) {
    return false;
  } else if ((a[0] != '-') and (b[0] == '-')) {
    return true;
  } else if ((a[0] == '-') and (b[0] == '-')) {
    if (a.length() < b.length()) return true;
    if (a.length() > b.length()) return false;
    if (a[1] < b[1]) return true;
    if (a[1] > b[1]) return false;
    if (a == b) return true;
    return true;
  } else {
    if (a.length() > b.length()) return true;
    if (a.length() < b.length()) {
      if (a < b) return false;
    }
    if (a[0] < b[0]) return false;
    if (a == b) return true;
    return true;
  }
}

bool operator<(const Integer& left, const Integer& right) {
  string a = left.value;
  string b = right.value;
  if (a == b) {
    return false;
  }

  if ((a[0] == '-') and (b[0] != '-')) {
    return true;
  } else if ((a[0] != '-') and (b[0] == '-')) {
    return false;
  } else if ((a[0] == '-') and (b[0] == '-')) {
    if (a.length() > b.length()) return true;
    if (a.length() < b.length()) return false;
    if (a[0] < b[0]) return false;
    if (a == b) return false;
    return true;
  } else {
    if (a.length() < b.length()) return true;
    if (a.length() > b.length()) return false;
    if (a[0] > b[0]) return false;
    if (a == b) return true;
    return true;
  }
}



bool operator<=(const Integer& left, const Integer& right) {
  string a = left.value;
  string b = right.value;
  if (a == b) {
    return true;
  }

  if ((a[0] == '-') and (b[0] != '-')) {
    return true;
  } else if ((a[0] != '-') and (b[0] == '-')) {
    return false;
  } else if ((a[0] == '-') and (b[0] == '-')) {
    if (a.length() > b.length()) return true;
    if (a.length() < b.length()) return false;
    if (a[0] < b[0]) return false;
    if (a == b) return true;
    return true;
  } else {
    if (a.length() < b.length()) return true;
    if (a.length() > b.length()) return false;
    if (a[0] > b[0]) return false;
    if (a == b) return false;
    return true;
  }
}


ostream &operator << (ostream &output, const Integer& p) {
  return (output << p.value);
}

std::istream& operator>>(std::istream& is, Integer& i) {
  is >> i.value;
  return is;
}
#endif