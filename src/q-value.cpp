#include <fstream>
#include "actions.h"

double Q[336][336];

double getQ(int state, int action) {
  return Q[state][action];
}

double policy(int current) {
    double maxValue = -99999;
    int maxNext = -1; // For testing cause not all Q's have values yet
    for (int i = 0; i < LENGTH; i++) {
        int nextState = *(actions[current]+i);

        if(nextState != -1) {
            double value = getQ(current,nextState);
            printf("%f\n", value);
            if(value != 0) {
            if (value > maxValue) {
                maxValue = value;
                maxNext = nextState;
            } 
        }
        }
    }
    return maxValue;
}

void printPolicy() {
  std::ofstream pFile ("values.txt");

  if(pFile.is_open()) {
      for (int i=0; i < 336; i++) {
          int current = i;
          double next =  policy(current);
          pFile << next << "\n";
          printf("State %d Value %f\n",current,next);
      }    
    } 
    pFile.close();      
}



int main() {

  double q = 0.0;
  std::ifstream qFile ("q.txt");
  if(qFile.is_open()) {
    for(int i=0; i<336; i++) {
      for(int j=0; j<336; j++) {
        qFile>>q;
        Q[i][j] = q; //read Q in
        printf("%f\n", q);
      }
    }
  }

  printPolicy();
}