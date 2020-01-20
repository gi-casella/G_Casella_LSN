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

    int M=100;
    int N=10000;
    double *bin = new double[M] ;
    int *counter = new int[M] ;

    for ( int n=0; n<M; n++ ){
    	bin[n]		= 0.;
		counter[n]	= 0;
    }
   	
   	
    for ( int n=0; n<M; n++ ){
   		bin[n]=0.01*(n+1);	
    }
    double alpha;
    double chi2 = 0.;
    
  
    ofstream Out;
    Out.open("output1.out");
      
	for ( int T=0; T<100; T++ ){
		for ( int i=0; i<N; i++){
			alpha = rnd.Rannyu();
			for ( int n=0; n<M; n++ ){
				if(n==0){
					if(alpha<bin[n])counter[n]++;				
				} else {
					if(alpha<bin[n] && alpha>bin[n-1])counter[n]++;
				}
			}			
			
		}
		for ( int n=0; n<M; n++ ){
				double num = ( double(counter[ n ]) - double( N   )/double(M)  );
				double den = double( N  )/double(M) ; 
				chi2+= num*num/den;
				counter[ n ] = 0;
			}
			Out<<T<<" "<<chi2<<endl;
			cout<<T<<" "<<chi2<<endl;
			chi2 = 0.;	
		
			
	}
   
	Out.close();   

    delete bin;
    delete counter;

 
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
	return;
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
