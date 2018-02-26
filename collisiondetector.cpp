// Copyright 2017 Andreas Papadakis apapadak@bu.edu
// Copyright 2017 Hayato Nakamura hayaton@bu.edu

#include <iostream>
#include <string>
#include <vector>
#include <math.h>
#include <algorithm>

using namespace std;
class Vehicle {
 public:
  string id;
  double rx, ry; // starting position
  double vx, vy; // velocity
  bool still_alive = true;

  Vehicle(string text, double xpos, double ypos, double xvel, double yvel) {
    this -> id = text;
    this -> rx = xpos;
    this -> ry = ypos;
    this -> vx = xvel;
    this -> vy = yvel;
  }
// Vehicle(bool alive){
// 	this --> still_alive = alive;
// }
};



class Collision {
 public:
  string vehicle1, vehicle2;
  double time;

  Collision(string one, string two, double timecollided) {
    vehicle1 = one;
    vehicle2 = two;
    time = timecollided;
  }

  friend bool operator<(const Collision& left, const Collision& right);



};

bool operator<(const Collision& left, const Collision& right) {
  if (left.time < right.time) {
    return true;
  } else return false;
}




vector<Vehicle> vehicles;
vector<Collision> collisions; // collisions of all vehicles (dead?)
vector<Collision> real_collisions; // collisions of previously alive vehicles




//std::sort


int main() {
//collisiondetector <random10.coordinates >random10.results;
  string s;
  double rx;
  double ry;
  double vx;
  double vy;
  vector <Vehicle> Cars;
  vector <Collision> crash;



  while (cin >> s >> rx >> ry >> vx >> vy) {
    Vehicle temp(s, rx, ry, vx, vy);
    Cars.push_back(temp);
  }

//cout << Cars.size()<<endl;

  double ax;
  double bx;
  double ay;
  double by;


  for (int i = 0; i < Cars.size(); i++) {

    for (int j = i + 1; j < Cars.size(); j++) {
      //cout<<i <<": " << j << endl;
      ax = Cars[i].rx - Cars[j].rx;
      bx = Cars[i].vx - Cars[j].vx;
      ay = Cars[i].ry - Cars[j].ry;
      by = Cars[i].vy - Cars[j].vy;

      double a = bx * bx + by * by;
      double b = 2 * ax * bx + 2 * ay * by;
      double c = ax * ax + ay * ay - 100;
      double D = b * b - 4 * a * c;


      if (D >= 0) {
        double time1 = (-b + sqrt(D)) / (2 * a);
        double time2 = (-b - sqrt(D)) / (2 * a);
        double time;
        if ((time1 > 0) || (time2 > 0)) {
          if ((time1 > time2) && (time2 > 0)) {
            time = time2;
          } else if ((time2 > time1) && (time1 > 0)) {
            time = time1;
          } else if ((time2 == time1) && (time1 > 0)) {
            time = time2;
          }
          Collision tempcrash(Cars[i].id, Cars[j].id, time);
          crash.push_back(tempcrash);
          // Cars[i].still_alive = false;
          // Cars[j].still_alive = false;

          // if (Cars[i].still_alive==true && Cars[j].still_alive==true){

          // 	Collision tempcrash(Cars[i].id, Cars[j].id, time);
          // 	crash.push_back(tempcrash);
          // 	Cars[i].still_alive = false;
          // 	Cars[j].still_alive = false;
          // 	//cout << time << ": " << Cars[i].id << " colides with " << Cars[j].id << endl;
          // }


        }

        //cout << "collision\n";
      }

    }
  }


// (myvector.begin(), myvector.end(), myobject);

  sort(crash.begin(), crash.end()); //sort all crashes by time

  vector <Collision> obj = crash;
// crash = correct(crash);
  for (int k = 0; k < obj.size(); k++) {
    //vector <Collision> dead;
    for (int rest = obj.size() - 1; rest > k; rest--) {
      //cout << k <<" " << rest <<"size" << obj.size()<< endl;
      bool check1 = ((obj[k].vehicle1 == obj[rest].vehicle1) || (obj[k].vehicle1 == obj[rest].vehicle2)); //checking for left hand size vehile
      if  (check1 == true)	{ //cout << rest << endl;
        obj.erase(obj.begin() + rest); //dead.push_back(rest) //saves index of the ones we want to dlt;
        //dead.push_back(rest);
        //break;
      }
      bool check2 = ((obj[k].vehicle2 == obj[rest].vehicle1) || (obj[k].vehicle2 == obj[rest].vehicle2));
      if  (check2 == true)	{ //cout << rest << endl;
        obj.erase(obj.begin() + rest); //dead.push_back(rest) //saves index of the ones we want to dlt;
        //dead.push_back(rest);
        //break;
      }

// cout << k <<" " << rest <<"size" << obj.size()<< endl;
    }
  }

  crash = obj;

// for (int j=0; j<crash.size();j++){
// 	vector <int> dead = correct (crash, j);
// 	for (int in = dead.size()-1; in>-1;in--){
// 		crash.erase(crash.begin()+dead[in]);
// 	}
// }
//get the index of the overlapping
// dead.pop_back();/



// for (int in = dead.size()-1; in>-1; in--){

// 	crash.erase(crash.begin()+dead[in]); //removes the ones that are actually alive

// }


  for (int i = 0; i < Cars.size(); i++) {
    for (int j = 0; j < crash.size(); j++) {
      if ((Cars[i].id == crash[j].vehicle1) || (Cars[i].id == crash[j].vehicle2)) {
        Cars[i].still_alive = false; //removes from cars the dead ones
      }
    }
  }


  cout.precision(8);
//Final output:
  cout << "there are " << Cars.size() << " vehicles\n";
  cout << "collision report\n";
  if (crash.size() == 0) {
    cout << "none\n";
  } else {
    for (int i = 0; i < crash.size(); i++) {
      cout << "at " << crash[i].time << " " << crash[i].vehicle1 << " collided with " << crash[i].vehicle2 << endl;
    }
  }
  cout << "the remaining vehicles are\n";
  if (2 * crash.size() == (Cars.size())) {
    //cout << crash.size() << Cars.size()/2;
    cout << "none\n";
  } else {
    for (int k = 0; k < Cars.size(); k++) {
      if (Cars[k].still_alive == true) {
        cout << Cars[k].id << " " << Cars[k].rx << " " << Cars[k].ry << " " << Cars[k].vx << " " << Cars[k].vy << endl;
      }
    }
  }


}



