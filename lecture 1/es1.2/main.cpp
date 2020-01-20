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

  

   //int M=100000;
   int N=10000;
   //int L=int(M/N);
   //double *block = new double[L] ;
   double sum=0.;

   double *ex1 = new double[N] ;   
   double *ex2 = new double[N] ;
   double *ex10 = new double[N] ;
   double *ex100 = new double[N] ;
   double *lor1 = new double[N] ;   
   double *lor2 = new double[N] ;
   double *lor10 = new double[N] ;
   double *lor100 = new double[N] ;
   double *n1 = new double[N] ;   
   double *n2 = new double[N] ;
   double *n10 = new double[N] ;
   double *n100 = new double[N] ;

   for(int t=0; t<N; t++){
	ex1[t]= rnd.nExpon(1.,1);
	ex2[t]= rnd.nExpon(1.,2);
	ex10[t]= rnd.nExpon(1.,10);
	ex100[t]= rnd.nExpon(1.,100);
	lor1[t]= rnd.nLorenz(0., 1.,1);
	lor2[t]= rnd.nLorenz(0., 1.,2);
	lor10[t]= rnd.nLorenz(0., 1.,10);
	lor100[t]= rnd.nLorenz(0., 1.,100);
	n1[t]= rnd.nRannyu(1);
	n2[t]= rnd.nRannyu(2);
	n10[t]= rnd.nRannyu(10);
	n100[t]= rnd.nRannyu(100);
   }
 
   ofstream o;
   o.open("output1");
   
   for(int t=0; t<N; t++){
	o<<ex1[t]<<' '<<ex2[t]<<' '<<ex10[t]<<' '<<ex100[t]<<' '<<lor1[t]<<' '<<lor2[t]<<' '<<lor10[t]<<' '<<lor100[t]<<' '<<n1[t]<<' '<<n2[t]<<' '<<n10[t]<<' '<<n100[t]<<' '<<endl;
   }
   
   o.close();
   //delete block;
   delete ex1;
   delete ex2;
   delete ex10;
   delete ex100;
   delete lor1;
   delete lor2;
   delete lor10;
   delete lor100;
   delete n1;
   delete n2;
   delete n10;
   delete n100;
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
