#include <iostream>
#include <fstream>
#include <cmath>
#include <cstdlib>
#include "random.h"
#include "econoph.h"

using namespace std;


Econoph :: Econoph (double s0, double K, double r, double vty, double T){
   _s0=s0;
   _K=K;
   _r=r;
   _vty=vty; 
   _T=T;
   _t=.0;
   _s_now=s0;
   
   
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

}

Econoph :: Econoph(){}

Econoph :: ~Econoph(){}


double Econoph :: Price_Direct(){
     
  _s_now *=exp((_r-0.5*_vty*_vty)*_T+(_vty*rnd.Gauss(.0,_T)));
  
  return _s_now;
}
 	
double Econoph :: Price_step(double t){
  
  _s_now*=exp((_r-0.5*_vty*_vty)*(t)+_vty*rnd.Gauss(.0,1.)*sqrt(t));
  _t+=t;
  return _s_now;
}

double Econoph :: d1() {
  double d;
  d=(log(_s0/_K)+_r+0.5*_vty*_vty*(_T))/(_vty*sqrt(_T));
  return d;
}

double Econoph :: d2() {
  double d;
  d=d1()-_vty*sqrt(_T);
  return d;
}

double Econoph :: Euro_call() {
  double C;
  C=_s0*N(d1()) - _K*exp(-_r*(_T))*(N(d2()));
  return C;
}

double Econoph :: Euro_put() {
  double C;
  C=_s0*(0.5*(1+erf( d1()/ sqrt(2.) ) )-1.) - _K*exp(-_r*(_T))*(0.5*(1+erf( d2()/ sqrt(2.) ) )-1.);
  return C;
}
 
  /*double Price_step(double t);
  double d1();
  double d2();
  double Euro_call();
  double Euro_put();
*/
