#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>
#include <iostream>

using namespace std;

#define SLOW
#define N 200000000
double A[N];
double sum; 

double clock_now() {
    struct timeval now;
    gettimeofday(&now, NULL);
    return (double)now.tv_sec + (double)now.tv_usec/1.0e6;
};

struct Timer {
  double Begin, Finish;
  double Total_OS;
  double elapsedTime_OS;

  Timer() {
    Total_OS  = 0.0;
    elapsedTime_OS  = 0;
  }
  
  void Start() {
    elapsedTime_OS  = -1; 
    Begin  = clock_now();
  }
  
  void Reset() {    
    elapsedTime_OS  = 0;
    Total_OS  = 0 ; 
  }
  
  void Stop() {
    //check the best practices guide for details of timings.
    Finish = clock_now();
    elapsedTime_OS  = (Finish - Begin);
    Total_OS  += (elapsedTime_OS) ;
  }

  ~Timer() {
  }
};

void init() {
  for (int i=0; i< N; i++) {
    A[i] = i*6.09;
 }
}

void slow() {
  for (int i=0; i< N; i++) {
    A[i] = A[i] + 6.09;
  }
}

void fast() { 
  for (int i=0; i< N; i++) {
    sum +=  A[i];
  }  
}
 
void fast_slow_fused() {
  for (int i=0; i< N; i++) {
    A[i] = A[i] + 6.09;
    sum +=  A[i];
  }  
}

int main(int argsc, char** args) {
  Timer timer;
  int option = atoi(args[1]);
  timer.Start();
  switch (option) {
    case 1: 
      cout << "slow";
      slow();
      break;
    case 2:
      cout << "fast";
      fast();
      break;
    case 3:
      cout << "slow then fast";
      slow();
      fast();
      break;
    case 4:
      cout << "fast then slow";
      fast();
      slow();
      break;
    case 5:
      cout << "fast_slow_fused";
      fast_slow_fused();
      break;
  }
  timer.Stop();
  cout << endl;
  cout << "Time spent: " << timer.elapsedTime_OS << endl;
}
