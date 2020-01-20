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
#include "main.h"

using namespace std;
 
int main (int argc, char *argv[]){

   RandomStuff();
   L=0.5;
   int nthr=1000000;
   int N=100;
   int B=int(double(nthr)/double(N));
   int nhit=0;
   
   //cout<<"B= "<<B<<endl;
   
   ofstream Out;
   Out.open("output.out");
   
   
   double *pi=new  double [ N ];
   double *pi2=new  double [ N ];
   int Nhit = 0;
   double sum, sum2;
   
   sum=0.;
   sum2=0.;
   for(int b=0; b<N; b++ ){
   	  	for( int t=0; t<B; t++ ){
   	  		Nhit+=Throw();
   	  	}
   	  	pi[b]=(2.*L*double(B))/double(Nhit);
   	  	pi2[b]=pi[b]*pi[b];
   	  	sum+=pi[b];
   	  	sum2+=pi2[b];
   	  	Nhit = 0;
   	  	//if(b%50==0)cout<<b+1<<" "<<pi[b]<<" "<<sum/double(b+1)<<" "<< sum2/double(b+1) - pow(sum/double(b+1),2) <<endl;
	    Out<<b+1<<" "<<sum/double(b+1)<<" "<< sqrt(sum2/double(b+1) - pow(sum/double(b+1),2))/sqrt(double(b+1)) <<endl;
   	  }

   cout<<"Final value of Pi: "<<sum/double(N)<<" with uncertainty: "<<sqrt(sum2/double(N) - pow(sum/double(N),2))/sqrt(double(N))<<endl;
   Out.close();

   rnd.SaveSeed();
   return 0;
}


void RandomStuff(void){
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



int Throw(void){
	//the lines on the floor are d=1 apart, so if the int(x) of the head and the tail are equal, the needle isn't on a line.
	//the problem is to extract head and tail at the right distance: we extract the coordinates of 2 points, the second poin gets used to extract the slope of the line that passes through the two points.
	// a new second point is found on the line such that its distance from the first one is L.
	double x1, x2;
	double y1, y2;
	x1=rnd.Rannyu(2.,102.);
	y2=rnd.Rannyu(2.,102.);
	y1=rnd.Rannyu(2.,102.);
	x2=rnd.Rannyu(2.,102.);
	int hit=1;
	
	double m=(y2-y1)/(x2-x1);
	double dx = L/sqrt( 1 + m*m );
	x2=x1+dx;
	if(int(x1)==int(x2))hit=0;
	if(x1==x2)hit=1;


	return hit;
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
