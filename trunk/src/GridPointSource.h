//-*-c++-*-
#ifndef GRID_POINT_SOURCE_H
#define GRID_POINT_SOURCE_H

#include <iostream>
#include <vector>
#include <string>
#include "TimeDep.h"
#include "Source.h"
#include "Sarray.h"
#include "Filter.h"

class GridPointSource
{
   friend std::ostream& operator<<(std::ostream& output, const GridPointSource& s);
public:

  GridPointSource(double frequency, double t0,
		  int i0, int j0, int k0, int g,
		  double Fx, double Fy, double Fz,
		  timeDep tDep, int ncyc, double* pars, int npar, int* ipars, int nipar,
		  double* jacobian=NULL, double* dddp=NULL, double* hess1=NULL,
		  double* hess2=NULL, double* hess3=NULL );

 ~GridPointSource();

  int m_i0,m_j0,m_k0; // grid point index
  int m_grid;

  void getFxyz( double t, double* fxyz ) const;
  void getFxyztt( double t, double* fxyz ) const;
  void getFxyz_notime( double* fxyz ) const;

  // evaluate time fcn: RENAME to evalTimeFunc
  double getTimeFunc(double t) const;
  double evalTimeFunc_t(double t) const;
  double evalTimeFunc_tt(double t) const;
  double evalTimeFunc_ttt(double t) const;
  double evalTimeFunc_tttt(double t) const;

  void limitFrequency(double max_freq);

  void add_to_gradient( std::vector<Sarray>& kappa, std::vector<Sarray> & eta,
			double t, double dt, double gradient[11], std::vector<double> & h,
			Sarray& Jac, bool topography_exists );
  void add_to_hessian( std::vector<Sarray> & kappa, std::vector<Sarray> & eta,
		       double t, double dt, double hessian[121], std::vector<double> & h );
  void set_derivative( int der, const double dir[11] );
  void set_noderivative( );
  void print_info() const;

   //// discretize a time function at each time step and change the time function to be "Discrete()"
   //  void discretizeTimeFuncAndFilter(double tStart, double dt, int nSteps, Filter *filter_ptr);

 private:

  GridPointSource();

  void initializeTimeFunction();
  double mForces[3];
   //  double mAmp;
  double mFreq, mT0;

  timeDep mTimeDependence;
   double (*mTimeFunc)(double f, double t,double* par, int npar, int* ipar, int nipar );
  double (*mTimeFunc_t)(double f, double t,double* par, int npar, int* ipar, int nipar );
  double (*mTimeFunc_tt)(double f, double t,double* par, int npar, int* ipar, int nipar );
  double (*mTimeFunc_ttt)(double f, double t,double* par, int npar, int* ipar, int nipar );
  double (*mTimeFunc_om)(double f, double t,double* par, int npar, int* ipar, int nipar );
  double (*mTimeFunc_omtt)(double f, double t,double* par, int npar, int* ipar, int nipar );
  double (*mTimeFunc_tttt)(double f, double t,double* par, int npar, int* ipar, int nipar );
  double (*mTimeFunc_tttom)(double f, double t,double* par, int npar, int* ipar, int nipar );
  double (*mTimeFunc_ttomom)(double f, double t,double* par, int npar, int* ipar, int nipar );
  double (*mTimeFunc_tom)(double f, double t,double* par, int npar, int* ipar, int nipar );
   double (*mTimeFunc_omom)(double f, double t,double* par, int npar, int* ipar, int nipar );

  double* mPar;
  int* mIpar; 
  int  mNpar, mNipar;

  int mNcyc;
   //  double m_min_exponent;
  int m_derivative;
  bool m_jacobian_known;
  double m_jacobian[27];
  bool m_hessian_known;
  double m_hesspos1[9], m_hesspos2[9], m_hesspos3[9], m_dddp[9]; 
  double m_dir[11];
};

#endif
