/****************************************************************
*****************************************************************
    _/    _/  _/_/_/  _/       Numerical Simulation Laboratory
   _/_/  _/ _/       _/       Physics Department
  _/  _/_/    _/    _/       Universita' degli Studi di Milano
 _/    _/       _/ _/       Prof. D.E. Galli
_/    _/  _/_/_/  _/_/_/_/ email: Davide.Galli@unimi.it
*****************************************************************
*****************************************************************/

#include <iostream>
#include <cmath>
#include <fstream>
#include <string>
#include "random.h"

using namespace std;
 
int main (int argc, char *argv[]){

   Random rnd;
   int seed[4];
   int p1, p2;
   ifstream Primes("Primes");
   if (Primes.is_open()){
      Primes >> p1 >> p2 ;
   } else cerr << "PROBLEM: Unable to open Primes" << endl;
   Primes.close();

   ifstream input("seed.in");
   string property;
   if (input.is_open()){
      while ( !input.eof() ){
         input >> property;
         if( property == "RANDOMSEED" ){
            input >> seed[0] >> seed[1] >> seed[2] >> seed[3];
            rnd.SetRandom(seed,p1,p2);
         }
      }
      input.close();
   } else cerr << "PROBLEM: Unable to open seed.in" << endl;

  

   int M=100000;
   int N=100;
   int L=int(M/N);
   double *block = new double[L] ;
   double sum=0.;

   double *mean = new double[N] ;   
   double *mean2 = new double[N] ;
   double *meanprog = new double[N] ;   
   double *meanprog2 = new double[N] ;
   double *err = new double[N] ;


   for(int t=0; t<N; t++){
	   for(int i=0; i<L; i++){
	      block[i]=rnd.Rannyu();
	      sum+=pow(block[i]-0.5, 2);
	   }
	   mean[t]=sum/double(L);
	   mean2[t]=mean[t]*mean[t];
	   sum=0.;
	   
	   meanprog[t]	= 0;
	   meanprog2[t]	= 0;
	   
	   if(t!=0){
		for(int j=0; j<t+1;j++){
			meanprog2[t]+=mean2[j];
			meanprog[t]+=mean[j];
		} 
	   meanprog[t]/=double(t+1);
	   meanprog2[t]/=double(t+1);

	   err[t]=sqrt(abs((meanprog2[t]-(meanprog[t]*meanprog[t])))/double(t));

	   }else{
			meanprog[t]=mean[t];
	   }

   }	   

   err[0]=0.;
   for(int i=0; i<6; i++){
      cout<<mean[i]<<endl;
      cout<<mean2[i]<<endl;
      cout<<endl;

   } 
  
   ofstream o;
   o.open("output1.out");
   err[0]=0.;
   for(int t=0; t<N; t++){
	o<<t*N<<" "<<meanprog[t]-(1./12.)<<" "<<err[t]<<endl;
   }
   
   o.close();
   delete block;
   delete mean;
   delete mean2;
   delete meanprog;
   delete meanprog2;
   delete err;
   /*
   for(int i=0; i<20; i++){
      cout << block[i] << endl;
   }*/

   rnd.SaveSeed();
   return 0;
}

/****************************************************************
*****************************************************************
    _/    _/  _/_/_/  _/       Numerical Simulation Laboratory
   _/_/  _/ _/       _/       Physics Department
  _/  _/_/    _/    _/       Universita' degli Studi di Milano
 _/    _/       _/ _/       Prof. D.E. Galli
_/    _/  _/_/_/  _/_/_/_/ email: Davide.Galli@unimi.it
*****************************************************************
*****************************************************************/
