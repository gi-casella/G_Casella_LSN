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
	int M = 10000;
	int N = 100;	
	int B = int (M/N);
	
	
	//uniform sampling
	double sum = 0.;
	double sum2 = 0.;
	double I = 0.;
	
	
	ofstream Out;
	Out.open( "uniform.out" );
	
	for( int b = 0; b<N; b++ ){
		for ( int t = 0; t<B; t++ ){
			I += f ( rnd.Rannyu() ) ;
		}
		I /= double(B);
		sum += I;
		sum2 += I*I;
		I = 0.;
		Out<< b+1 <<" "<<sum/double(b+1)<<" "<<sqrt( ( sum2/double(b+1) - pow(sum/double(b+1),2) )/double(b+1) )<<endl;
	}
	
	Out.close();


	//importance sampling
	sum = 0.;
	sum2 = 0.;

	Out.open( "importance.out" );

	for( int b = 0; b<N; b++ ){
		for ( int t = 0; t<B; t++ ){
			I += fp ( p() ) ;
		}
		I /= double(B);
		sum += I;
		sum2 += I*I;
		I = 0.;
		Out<< b+1 <<" "<<sum/double(b+1)<<" "<<sqrt( ( sum2/double(b+1) - pow(sum/double(b+1),2) )/double(b+1) )<<endl;
	}
	
	Out.close();

    rnd.SaveSeed();
    return 0;
}


//******************************************************************************************//
//******************************************************************************************//
//******************************************************************************************//


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
   return;
}


double f( double x ){
	return (M_PI/2)*cos(x*M_PI/2);
}


double fp( double x ){
	//return (M_PI/4)*cos(x*M_PI/2)/( 1 - x );
	 double num = (M_PI/2)*cos(x*M_PI/2);
	 double den = 1 + M_PI/4 -x*(M_PI/2);
	 return num / den; 
}


double p( void ){
	double rho = rnd.Rannyu();
	//return  ( 1 - sqrt ( 1 - rho ) );
	 return  ( M_PI/4 + 1 - sqrt( pow(M_PI/4 + 1,2) - M_PI*rho ) ) / ( M_PI/2 )   ; 
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
