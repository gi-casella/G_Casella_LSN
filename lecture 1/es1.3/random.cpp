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
#include <fstream>
#include <cmath>
#include <cstdlib>
#include "random.h"

using namespace std;

Random :: Random(){}

Random :: ~Random(){}

void Random :: SaveSeed(){
   ofstream WriteSeed;
   WriteSeed.open("seed.out");
   if (WriteSeed.is_open()){
      WriteSeed << l1 << " " << l2 << " " << l3 << " " << l4 << endl;;
   } else cerr << "PROBLEM: Unable to open random.out" << endl;
  WriteSeed.close();
  return;
}

double Random :: Gauss(double mean, double sigma) {
   double s=Rannyu();
   double t=Rannyu();
   double x=sqrt(-2.*log(1.-s))*cos(2.*M_PI*t);
   return mean + x * sigma;
}

double Random:: Expon(double lambda){
   double x=Rannyu();
   return -(1./lambda)*log(1-x);
}

double Random:: nExpon(double lambda, int n){
   double x, sum=0;
   for (int t=0;t<n; t++){
      x=Rannyu();
      sum+=-(1./lambda)*log(1-x);
      
   }
   return sum/double (n);
}

double Random:: nLorenz(double mu, double lambda, int n){
   double x, sum=0;
   for (int t=0;t<n; t++){
      x=Rannyu();
      sum+=mu+lambda*tan(M_PI*Rannyu()-(M_PI/2.)); 
   }
   return sum/double( n);
}

double Random:: Lorenz(double mu, double lambda){
   double x=(M_PI*Rannyu()-M_PI/2.);
   return mu+lambda*tan(x);
}

double Random :: nRannyu(int n){
	double sum=0.;
	for (int t=0; t<n; t++){
	  sum+=Rannyu();
	}
	return sum/double (n);
}

double Random :: Rannyu(double min, double max){
   return min+(max-min)*Rannyu();
}

double Random :: Rannyu(void){
  const double twom12=0.000244140625;
  int i1,i2,i3,i4;
  double r;

  i1 = l1*m4 + l2*m3 + l3*m2 + l4*m1 + n1;
  i2 = l2*m4 + l3*m3 + l4*m2 + n2;
  i3 = l3*m4 + l4*m3 + n3;
  i4 = l4*m4 + n4;
  l4 = i4%4096;
  i3 = i3 + i4/4096;
  l3 = i3%4096;
  i2 = i2 + i3/4096;
  l2 = i2%4096;
  l1 = (i1 + i2/4096)%4096;
  r=twom12*(l1+twom12*(l2+twom12*(l3+twom12*(l4))));

  return r;
}

void Random :: SetRandom(int * s, int p1, int p2){
  m1 = 502;
  m2 = 1521;
  m3 = 4071;
  m4 = 2107;
  l1 = s[0]%4096;
  l2 = s[1]%4096;
  l3 = s[2]%4096;
  l4 = s[3]%4096;
  l4 = 2*(l4/2)+1;
  n1 = 0;
  n2 = 0;
  n3 = p1;
  n4 = p2;

  return;
}

double	Random:: randang(void){
	

	double theta=M_PI/360;
	double x=Rannyu(-1., 1.) ;
	double y=Rannyu(-1., 1.) ;
	double r= sqrt((x*x)+(y*y));

	if(r<=1.){
		if(y>0.){
			theta=acos(x/r);
		}else{
			theta=2*M_PI-acos(x/r);
		}			
	}else{
		while(r>=1.){
			x=Rannyu(-1., 1.);
			y=Rannyu(-1., 1.) ;
			r= sqrt(x*x+y*y);
			
		}
		if(y>0.){
			theta=acos(x/r);
		}else{
			theta=2*M_PI-acos(x/r);
		}			
	}

	return theta;		
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
