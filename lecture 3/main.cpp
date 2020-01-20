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
#include "econoph.h"



using namespace std;
 

int main (int argc, char *argv[]){

   Econoph mark (100., 100., 0.1, 0.25, 1.);
   int M=10000 ;
   int N=100 ;
   int B=100;
   double *price_C = new double[M];
   double *price_P = new double[M];
   
   double *ave_= new double[N];
   double *ave2_= new double[N];
  

   
	//1 step evolved market generation, with filling of arrays of price of the call and put options

   for(int i=0; i<M; i++){
	   price_C[i]=max( 0. ,exp(-0.1)*(mark.Price_Direct()-100.));
	   mark.Start();
	   price_P[i]=max( 0. ,exp(-0.1)*(100.-mark.Price_Direct()));
	   mark.Start();
	}
	
	


	cout<<"call: "<<mark.Euro_call()<<endl;
	cout<<"put: "<<mark.Euro_put()<<endl;


	//producing the data for different Block size
	//direct call
	
	double sum=0;
	double sum2=0;
	
	ofstream Output_;
   	Output_.open("Direct_call.out");
	for(int b=0; b<N; b++){
		ave_[b]=0;
		for(int t=0; t<B; t++){
			ave_[b]+=price_C[B*b+t];
		}
		ave_[b]/=double(B);
		ave2_[b]=ave_[b]*ave_[b];
		sum+=ave_[b];
		sum2+=ave2_[b];		

	Output_<< b <<" "<< sum/double(b+1) <<" "<<sqrt(( sum2/double(b+1) - pow( sum/double(b+1), 2 ) )/double(b+1))<<endl;
	}
	
	
	Output_.close();
	
	//direct put
	
	
	sum=0.;
	sum2=0.;
	
	
   	Output_.open("Direct_put.out");
	for(int b=0; b<N; b++){
		ave_[b]=0;
		for(int t=0; t<B; t++){
			ave_[b]+=price_P[B*b+t];
		}
		ave_[b]/=double(B);
		ave2_[b]=ave_[b]*ave_[b];
		sum+=ave_[b];
		sum2+=ave2_[b];		

		Output_<< b <<" "<< sum/double(b+1) <<" "<<sqrt(( sum2/double(b+1) - pow( sum/double(b+1), 2 ) )/double(b+1))<<endl;
	}
	
	Output_.close();

	


	//100 step evolved market simulation
	double price;
	
	for(int i=0; i<M; i++){
		for(int s=0; s<99; s++){
			price=mark.Price_step(0.01);
		}
	   price_C[i]=max( 0. , exp(-0.1)*(price-100.));
	   price_P[i]=max( 0. , exp(-0.1)*(100.-price));
	   mark.Start();
	}


	//discretized (step-by-step) call
	sum=0.;
	sum2=0.;

	
   	Output_.open("Step_call.out");
	sum=0.;
	sum2=0.;	
	for(int b=0; b<N; b++){
		ave_[b]=0;
		for(int t=0; t<B; t++){
				ave_[b]+=price_C[B*b+t];
		}
		ave_[b]/=double(B);
		ave2_[b]=ave_[b]*ave_[b];
		sum+=ave_[b];
		sum2+=ave2_[b];		

		Output_<< b <<" "<< sum/double(b+1) <<" "<<sqrt(( sum2/double(b+1) - pow( sum/double(b+1), 2 ) )/double(b+1))<<endl;
	}
	
	Output_.close();

	


	//discretized (step-by-step) put
	sum=0.;
	sum2=0.;
		
	
   	Output_.open("Step_put.out");
   	
	for(int b=0; b<N; b++){
		ave_[b]=0;
		for(int t=0; t<B; t++){
			ave_[b]+=price_P[B*b+t];
		}
		ave_[b]/=double(B);
		ave2_[b]=ave_[b]*ave_[b];
		sum+=ave_[b];
		sum2+=ave2_[b];		

		Output_<< b <<" "<< sum/double(b+1) <<" "<<sqrt(( sum2/double(b+1) - pow( sum/double(b+1), 2 ) )/double(b+1))<<endl;
	}
	
	Output_.close();
	

	delete price_C;
	delete price_P;
	delete ave_;
	delete ave2_;
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
