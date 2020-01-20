


class Econoph {

private:
  double _s0, _K, _r, _vty, _T, _s_now;
  Random rnd; 

protected:
  double _t;
public:
  // constructors
  Econoph();
  Econoph(double s0, double K, double r, double vty, double T);
  // destructor
  ~Econoph();
  double Price_Direct();
  double Price_step(double t);
  double d1();
  double N(double x){
  	x/=sqrt(2.);
  	return 0.5*(1+erf(x));
  }
  double d2();
  double Euro_call();
  double Euro_put();
  double Price_get(){return _s_now;}
  void Start(){
  	_s_now=_s0;
  	_t=0;
  	return;
  }
  
  
  
  // methods
  /*void SetRandom(int * , int, int);
  void SaveSeed();
  double Rannyu(void);
  double Rannyu(double min, double max);
  double Gauss(double mean, double sigma);
  double Expon(double lambda);
  double Lorenz(double mu, double lambda);
  double nExpon(double lambda, int n);
  double nRannyu(int n);
  double nLorenz(double mu, double lambda, int n);*/
};

