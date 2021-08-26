#include <iostream>
#include <cstdlib>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <fstream>
#include <math.h>

using namespace std;

int N = 40;
int iterMax = 1000000;
double demE = 0;
double totE = 20;
double delE;
double partVNext;

//create a function that outputs data into a .txt file
void SaveIntoFile(double demon[]){
    ofstream outputFile;
    outputFile.open("vel_programdata.txt");
        for(int count=0; count < iterMax; count++){
            outputFile << demon[count] << endl;
            }
    outputFile.close();
}


//returns random double
double rand_float(double a, double b) {
    return ((double)rand() / RAND_MAX) * (b - a) + a;
}


int main(){
        double partV[N];
        double demon[iterMax];
        //the seed is different each time for random number
        srand(time(0));
        
        //start with same v
        for(int countV=0; countV < N+1; countV++){
            partV[countV]= float((sqrt(2*totE))/(sqrt(N)));
        }
    
        //reach equilibrium
        for (int countIter=0; countIter < iterMax; countIter++){
            for (int countPart = 0; countPart<N; countPart++){
                SaveIntoFile(demon);
                int indPart = rand()%N;  // good
                double dV = rand_float(-2, 2); //good
                partVNext = partV[indPart] + dV; //good
                delE = 0.5*((partVNext*partVNext) - (partV[indPart]*partV[indPart])); //good
                
                //accept change if the change is negative, give to demon
                if (delE < 0){
                    demE = demE - delE;
                    partV[indPart] = partVNext;
                    totE = totE + delE;
                    //cout << demE << endl;
                    demon[countPart] = demE;
                    //cout << totE<< endl;
                }
                if(0 < delE){
                    // accept positive change only if demon has that energy available
                    if (delE <= demE){
                        demE = demE - delE;
                        partV[indPart] = partVNext;
                        totE = totE + delE;
                        //cout << demE << endl;
                        demon[countPart] = demE;
                       //cout << totE << endl;
                    }
                }
            }
        }
        
        //this is just to check that the equilibrium energy makes sense
        double sumVel = 0;
        for (int count = 0; count < N; count++){
            sumVel = sumVel + partV[count];
        }
    
        cout << "avgVel: " << sumVel/N << "\n" << "demE: " << demE << "\n" << "totE per part: " << totE/N << endl ;
        double kinT = (sumVel/N)*(sumVel/N)/(1.380649e-23);
        cout << "kinT " << kinT << endl;
    cout << "Ed/kinT: " << demE / kinT;
        for(int i=0; i<N; i++){
            cout << partV[i] << endl;
        }

    return 0;
}
