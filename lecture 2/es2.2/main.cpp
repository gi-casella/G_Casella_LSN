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
	
	Dwalk= new int [d];
	for (int i = 0; i < d ; i++)Dwalk[i]=0;
	
	int walks	= 10000;
	int Nblock	= 100;
	int B = int(walks/Nblock);
	int nstep	= 100;	
	
	double r_2=0;
	double r_4=0;
	double x2=0., y2=0., z2=0.;
	
	double sum = 0.;
	double sum2 = 0.;
	
	//the first part of this code measures the final position of the walks in the discreate and continuous case.
	//it was needed to find a good number of blocks
	
	ofstream Out;
	Out.open( "discrete.out" );
	
	for(int b = 0; b < Nblock; b++ ){
		for ( int t=0; t<B; t++ ){
			for(int step=0; step<nstep; step++){
				r_2=0;
				r_4=0;
				DiscreteMove();
			}
			x2=double( pow( Dwalk[0], 2 ) );
			y2=double( pow( Dwalk[1], 2 ) );
			z2=double( pow( Dwalk[2], 2 ) );
			r_2 += sqrt(double( x2 + y2 + z2 ));
			r_4 += double( x2 + y2 + z2 );
			for (int i = 0; i < d ; i++)Dwalk[i]=0;
		}
		sum  += r_2;
		sum2 += r_4;
		Out<<b+1<<" "<<sum/double(b+1)<<" "<<sqrt( (sum2/double(b+1) - pow(sum/double(b+1),2) )/double(b+1) )<<endl;		
	}
		
	Out.close();	
		
	sum = 0.;
	sum2 = 0.;	
	
	//continuous walk:
	
	Out.open( "continuous.out" );
	
	Cwalk= new double [d];
	for (int i = 0; i < d ; i++)Cwalk[i]=0.;
	
	for(int b = 0; b < Nblock; b++ ){
		for ( int t=0; t<B; t++ ){
			for(int step=0; step<nstep; step++){
				r_2=0;
				r_4=0;
				ContinuousMove();
			}
			x2 = pow( Cwalk[0], 2 );
			y2 = pow( Cwalk[1], 2 );
			z2 = pow( Cwalk[2], 2 );
			r_2 += sqrt(double( x2 + y2 + z2 ));
			r_4 += double( x2 + y2 + z2 );
			for (int i = 0; i < d ; i++)Cwalk[i]=0.;
		}
		sum  += r_2;
		sum2 += r_4;
		Out<<b+1<<" "<<sum/double(b+1)<<" "<<sqrt( (sum2/double(b+1) - pow(sum/double(b+1),2) )/double(b+1) )<<endl;		
	}
   
   Out.close();
   // this part of the code measures the average position for each step of the walks.
   
   
   double *r_     = new double [nstep];
   double *acc_r  = new double [nstep];
   double *acc_r2 = new double [nstep];
   
   for(int step=0; step<nstep; step++){
   		r_[step]     = 0.;
   		acc_r[step]  = 0.;
   		acc_r2[step] = 0.;
   }
   	
	
	for(int b = 0; b < Nblock; b++ ){
		for ( int t=0; t<B; t++ ){
			for (int i = 0; i < d ; i++)Dwalk[i]=0;
			for(int step=0; step<nstep; step++){
				DiscreteMove();
				x2=double( pow( Dwalk[0], 2 ) );
				y2=double( pow( Dwalk[1], 2 ) );
				z2=double( pow( Dwalk[2], 2 ) );
				r_[step] += sqrt(double( x2 + y2 + z2 ));
			}
			
		}
		for(int step=0; step<nstep; step++){
			acc_r[step]  += r_[step]/double(B);
			acc_r2[step] += pow( r_[step]/double(B), 2 );
			r_[step]=0.;
		}
	}
	
	
	Out.open( "discrete_step.out" );
	for(int step=0; step<nstep; step++){
		Out << step+1 << "  " << 	acc_r[step]/double(Nblock) << "  " << sqrt( acc_r2[step]/double(Nblock) -  pow(acc_r[step]/double(Nblock),2)  )/sqrt(double(Nblock))<<endl;
	}
	Out.close();	
   
   
   
   
   for(int step=0; step<nstep; step++){
   		r_[step]     = 0.;
   		acc_r[step]  = 0.;
   		acc_r2[step] = 0.;
   }
   	
	
	
	for(int b = 0; b < Nblock; b++ ){
		for ( int t=0; t<B; t++ ){
			for (int i = 0 ; i < d ; i++)Cwalk[i]=0.;
			for (int step=0; step<nstep; step++){
				ContinuousMove();
				x2= pow( Cwalk[0], 2 );
				y2= pow( Cwalk[1], 2 );
				z2= pow( Cwalk[2], 2 );
				r_[step] += sqrt(double( x2 + y2 + z2 ));
			}
		}
		for(int step=0; step<nstep; step++){
			acc_r [step] += r_[step]/double(B);
			acc_r2[step] += pow( r_[step]/double(B), 2 );
			r_[step]=0.;
		}
	}
	
	
	Out.open( "continuous_step.out" );
	for(int step=0; step<nstep; step++){
		Out << step+1 << "  " << 	acc_r[step]/double(Nblock) << "  " << sqrt( acc_r2[step]/double(Nblock) -  pow(acc_r[step]/double(Nblock),2)  )/sqrt(double(Nblock))<<endl;
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


void DiscreteMove(void){

	double a=rnd.Rannyu(0.,3.);
				
	//discrete random walk is like the throw of a dice where "1" means go forward in direction x,
	//"2" means go backward in direction x and so on..
				
	if(a<=0.5){
		Dwalk[0]++;
	}else if(a<=1.){
		Dwalk[0]--;
	}else if(a<=1.5){
		Dwalk[1]++;
	}else if(a<=2.){
		Dwalk[1]--;
	}else if(a<=2.5){
		Dwalk[2]++;
	}else if(a<=3.){
		Dwalk[2]--;
	}
	return;
}


void ContinuousMove(void){
	double theta, phi;
	theta= rnd.Rannyu(0., M_PI);
	phi  = rnd.Rannyu(0., M_PI*2);
	Cwalk[0]+=sin(theta)*cos(phi);
	Cwalk[1]+=sin(theta)*sin(phi);
	Cwalk[2]+=cos(theta);
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
