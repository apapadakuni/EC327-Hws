// Copyright 2017 Andreas Papadakis apapadak@bu.edu
// Copyright 2017 Hayato Nakamura hayaton@bu.edu
// Copyright 2017 Boxi Huang huangbo@bu.edu
// Copyright 2017 Isa Mustafayev isas@bu.edu

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

vector <Collision> collides(vector <Vehicle> Cars){


  vector <Collision> crash;
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


        }

      }

    }
  }

  //DONE WITH COLLISIONS BETWEEN CARS

    for (int i =0; i< Cars.size();i++){

    
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
      if  (check1 == true)  { //cout << rest << endl;
        obj.erase(obj.begin() + rest); //dead.push_back(rest) //saves index of the ones we want to dlt;
        //dead.push_back(rest);
        //break;
      }
      bool check2 = ((obj[k].vehicle2 == obj[rest].vehicle1) || (obj[k].vehicle2 == obj[rest].vehicle2));
      if  (check2 == true)  { //cout << rest << endl;
        obj.erase(obj.begin() + rest); //dead.push_back(rest) //saves index of the ones we want to dlt;
        //dead.push_back(rest);
        //break;
      }


    }
  }

  crash = obj;
  return crash;


} //end of function COLLIDES


vector <Collision> walls (vector <Collision> crash, vector <Vehicle> Cars, double xbegin, double ybegin, double xend, double yend){

  for (int i = 0 ; i<Cars.size(); i++){
    double timexend = (xend-5-Cars[i].rx)/Cars[i].vx;
    double timexbegin = (xbegin+5-Cars[i].rx)/Cars[i].vx;
    if (timexend>0){
      Collision temporary(Cars[i].id, "XEND", timexend);
      crash.push_back(temporary);
    }
    if (timexbegin>0){
      Collision temporary(Cars[i].id, "XBEGIN", timexbegin);
      crash.push_back(temporary);
    }
    double timeyend = (yend-5-Cars[i].ry)/Cars[i].vy;
    double timeybegin = (ybegin+5-Cars[i].ry)/ Cars[i].vy;
     if (timeyend>0){
      Collision temporary(Cars[i].id, "YEND", timeyend);
      crash.push_back(temporary);
    }
    if (timeybegin>0){
      Collision temporary(Cars[i].id, "YBEGIN", timeybegin);
      crash.push_back(temporary);
    }


  }

return crash;


}





vector <Vehicle> change(vector <Vehicle> Cars, vector <Collision> crash, double time){
  for (int i = 0 ; i < Cars.size(); i++){
    Cars[i].rx = Cars[i].rx + time* Cars[i].vx;
    Cars[i].ry = Cars[i].ry + time *Cars[i].vy;
  } //now i have shifted all balls to their positions at time: time



  for (int sametime=0; sametime<crash.size(); sametime++){

    if (crash[sametime].time == time){

      //now checking if the collision is that with a wall, and making the direction opposite accordingly
      if ((crash[sametime].vehicle2 == "XBEGIN") || (crash[sametime].vehicle2 == "XEND")) {
        for (int k=0; k<Cars.size(); k++){ //finding which vehicle it is within the vector Cars
          if (crash[sametime].vehicle1 == Cars[k].id){
        //cout << Cars[k].vx << endl;
             Cars[k].vx = Cars[k].vx*(-1);
       // cout << Cars[k].vx << endl;
              break; //dont need to continue when it finds it
          }
        }
       
      }
    
  

  //return Cars; //done  

 

  //same thing but with y now
      else if ((crash[sametime].vehicle2 == "YBEGIN") || (crash[sametime].vehicle2 == "YEND")) {
        for (int k=0; k<Cars.size(); k++){
          if (crash[sametime].vehicle1 == Cars[k].id){
        // cout << Cars[k].vx << endl;
            Cars[k].vy = Cars[k].vy*(-1);
        // cout << Cars[k].vx << endl;
            break;
          }
        }
        //return Cars; //done    
      }
      else {
  //if here, then the collision has to be between vehicles

  int first=0;
  int second = 0;

  for (first = 0; first<Cars.size(); first++){
    if (crash[sametime].vehicle1 == Cars[first].id){
      break;
    }
  }//we have the index for our first vehicle

  for (second = 0; second< Cars.size(); second++){
    if (crash[sametime].vehicle2 == Cars[second].id){
      break;
    }
  } // we have the index of the second vehicle

  //making variables as shown in the equation to make it easier;
  double vx1 = Cars[first].vx;
  double vy1 = Cars[first].vy;
  double rx1 = Cars[first].rx;
  double ry1 = Cars[first].ry;

  double vx2 = Cars[second].vx;
  double vy2 = Cars[second].vy;
  double rx2 = Cars[second].rx;
  double ry2 = Cars[second].ry;


  double dot = (vx1 - vx2)*(rx1 - rx2) + (vy1 - vy2)*(ry1 - ry2);

  double magnitude = (rx1-rx2)*(rx1-rx2) + (ry1-ry2)*(ry1-ry2);

  Cars[first].vx = vx1 - dot/magnitude * (rx1-rx2);
  Cars[first].vy = vy1 - dot/magnitude * (ry1-ry2);

  Cars[second].vx = vx2 - dot/magnitude * (rx2-rx1);
  Cars[second].vy = vy2 - dot/magnitude * (ry2-ry1);
  }

  }
}//end of for loop going through crashes

  return Cars;

}



vector <Vehicle> changepos(vector <Vehicle> Cars, double time){
   for (int i = 0 ; i < Cars.size(); i++){
    Cars[i].rx = Cars[i].rx + time* Cars[i].vx;
    Cars[i].ry = Cars[i].ry + time *Cars[i].vy;
  } 
  return Cars;
}





int main() {
//collisiondetector <random10.coordinates >random10.results;
  string s;
  double rx;
  double ry;
  double vx;
  double vy;
  vector <Vehicle> Cars;
  vector <Collision> crash;
  double dt;
  double totaltime;
  double xbegin;
  double xend;
  double ybegin;
  double yend;

  cin >> dt >> totaltime;
  cin >> xbegin >> ybegin >> xend >> yend;


  while (cin >> s >> rx >> ry >> vx >> vy) {
    Vehicle temp(s, rx, ry, vx, vy);
    Cars.push_back(temp);
   }


    crash = collides (Cars);
    crash = walls (crash, Cars, xbegin, ybegin, xend, yend);
    sort(crash.begin(), crash.end());


    

  double prevcrashtime=0;
  double crashtime = 0;
  cout << dt << " " << totaltime << endl;
  cout << xbegin << " " << ybegin << " " << xend << " " << yend << endl;
  
  for (double t=0; t<totaltime+1; t=t+dt) {
   // cout << "at " << crash[0].time << " " << crash[0].vehicle1 << " collided with " << crash[0].vehicle2 << endl;
     cout << "at " << t <<endl;
        for (int k=0; k<Cars.size(); k++){

 
        cout << Cars[k].id << " " << Cars[k].rx << " " << Cars[k].ry <<endl ; //<< " " << Cars[k].vx << " " << Cars[k].vy << endl;
 
    }
           cout << "\n";

    crash = collides (Cars);
    crash = walls (crash, Cars, xbegin, ybegin, xend, yend);
    sort(crash.begin(), crash.end());
    crashtime = crash[0].time;
    if (crash[0].time > dt){//here is the case that 
        Cars = changepos (Cars, dt);
     //   cout << "Crashtime: " << crashtime << " " << crash[0].time<<endl; 
    }
    else { // meaning that our initial value of the crashtime is less than the dt, an
      // crashtime = 0;
      while (0 < crashtime and crashtime <= dt) { //meaning when there is a crash time between the two reported times
     
         // cout << "Crashtime: " << crashtime << " " << crash[0].time<<endl; 
           // Cars = changepos (Cars, crashtime);
        // cout << Cars[0].vx << " " << Cars[1].vx<<endl ;
            Cars = change (Cars, crash, crashtime);
         //   Cars = changepos (Cars, crash[0].time);

      //      

           crash = collides (Cars);
           crash = walls (crash, Cars, xbegin, ybegin, xend, yend);
            sort(crash.begin(), crash.end());
         //   cout << crash[0].time << endl;

           crashtime = crash[0].time+crashtime;
     //    

       }
        // cout << "Crashtime: " << crashtime <<endl;

      //   here though crashtime is more than dt, so crash[0].time 
        double newtime = crashtime- crash[0].time;
        newtime = dt - newtime; //so now we do find the time interval between our last caluclated positions and dt
        Cars= changepos (Cars, newtime);
        crash = collides (Cars);
        crash = walls (crash, Cars, xbegin, ybegin, xend, yend);
        sort(crash.begin(), crash.end());
    }
        




  }




  crash = collides (Cars);
  crash = walls (crash, Cars, xbegin, ybegin, xend, yend);
  sort(crash.begin(), crash.end());


  // for (int i = 0; i < Cars.size(); i++) {
  //   for (int j = 0; j < crash.size(); j++) {
  //     if ((Cars[i].id == crash[j].vehicle1) || (Cars[i].id == crash[j].vehicle2)) {
  //       Cars[i].still_alive = false; //removes from cars the dead ones
  //     }
  //   }
  // }



// if (crash.size() == 0) {
//     cout << "none\n";
//   } else {
//     for (int i = 0; i < crash.size(); i++) {
//       cout << "at " << crash[i].time << " " << crash[i].vehicle1 << " collided with " << crash[i].vehicle2 << endl;
//     }
//   }



// cout << "the remaining vehicles are\n";
//   if (2 * crash.size() == (Cars.size())) {
//     //cout << crash.size() << Cars.size()/2;
//     cout << "none\n";
//   } else {
//     for (int k = 0; k < Cars.size(); k++) {
//       if (Cars[k].still_alive == true) {
//         cout << Cars[k].id << " " << Cars[k].rx << " " << Cars[k].ry << " " << Cars[k].vx << " " << Cars[k].vy << endl;
//       }
//     }





// }








}

