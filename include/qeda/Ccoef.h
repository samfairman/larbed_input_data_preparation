// file Ccoef.h: contains functions for computing generic C-q-coefficients
#ifndef _CQCOEF_H
#define _CQCOEF_H

#include <iterator>
#include <string>
#include <ctime>
#include <vector>
#include <algorithm>    // std::sort
#include <qeda/DataTypes.h>

inline ftype rpow(ftype arg,int r) {
	return (r==0) ? 1.0 : ((r==1) ? arg : ((r==2) ? arg*arg : pow(arg,r)));
}

static void insSort(std::vector<ftype> v,std::vector<ftype> vp, int n) {
  int i,j;
  ftype temp;
  for (i = 1; i <= n; i++) {
    temp = v[i];
    for (j = i-1; j >= 0 && v[j] > temp; j--) v[j+1] = v[j];
    v[j+1] = temp;
  }
}

// The D-coefficient is calculated recursively 
// initially, s = dk-j.
double drec(int s,double Bk,std::vector<double> bArray,int l) {
  double D=0; 
  int r;
  if (s==0) return 1.0;
  for (r=0;r<l;r++) D+=drec(s-1,Bk,bArray,r+1)/(Bk-bArray[r]);
  return D;
}

/******************************************************************
 * the Cqcoef function: calculates the C(q,n,l1,...,m) coefficients
 * central function to this program!
 * 
 * bArray = the array holding all the beams, except the last one,
 *          which is always g_Nmid = 0
 *          we must have allocated at least q+1 elements for bArray
 * q      = bCount = length of bArray (because we did not count the last beam).
 * T      = pi*thickness/k_n 
 ******************************************************************/

static complex_type Cqcoef(std::vector <ftype> bArray, int q, std::complex<double> T) {
  std::complex<double> Cq,c,Tbk;   /* complex data type compatible with FORTRAN */
  int k,dk,j,r,s;
  double bk,c1,eps = 1e-12;
  static std::vector<double> oArray;
  static std::vector<double> bpArray;
  static std::vector<double> fact;
  static int maxLength = 0;  /* keeps track of length of arrays */


  Cq = std::complex<double>(0.0,0.0); 
  // bArray[q] = 0;
  // bArray.sort();

   if (q+1 > maxLength) {  /* adjust length of arrays dynamicaly */
	  maxLength = q+1;      /* if longer ones are needed          */
	  oArray.resize(maxLength);
	  bpArray.resize(maxLength);
	  fact.resize(maxLength+1);
	  for (fact[0]=1,j=1;j<=maxLength;j++) fact[j] = fact[j-1]*j;
  }
  // insSort(bArray,bpArray, q);
  for (r=0;r<=q;r++) bpArray[r] = (double)bArray[r];
  std::sort(bpArray.begin(), bpArray.begin()+q+1);
  k=0;
  while (k <= q) {
    bk = bpArray[k];
	Tbk = T*bk;
    for (dk=0;dk<q-k;dk++) if(fabs(bk-bpArray[dk+k+1])>eps) break;
	// oArray must contain all elements, except for the current one:
    for (r=0;r<k;r++) oArray[r] = bpArray[r];
    for (r+=dk+1;r<=q;r++) oArray[r-dk-1] = bpArray[r];
    for (j=0;j<=dk;j++) {
      // c = complex_type(cos(T*bk),sin(T*bk));
	  c=exp(Tbk);
	  for (s=0;s<q-j;s++) {
		//if (r%2) c -= complex_type(0.0,rpow(T*bk,r)/fact[r]*(1-(((r>>1)%2)<<1)));
       	//else c -= rpow(T*bk,r)/fact[r]*(1-(((r>>1)%2)<<1));
		  c -= pow(Tbk,s)/fact[s];
	  }
      for (c1 = 1.0,r=0;r<q-dk;r++) c1 *= (bk-oArray[r]);
	  if (abs(c1) < eps) c1 = (c1 < 0.0) ? -eps : eps;  // this is a safety guard to avoid excessively large coefficients
	  c /= c1;
      // c1  = drec(dk-j,bk,oArray,q-dk)*(1-(((dk-((j+1)>>1))%2)<<1))/;            /* D-coefficient */
      // c1 *= rpow(T,j);
	  //if (j%2) Cq += c*complex_type(0.0,c1);
      //else Cq += c*c1;
	  if (dk == q) Cq += (dk == j) ? c*pow(T,j)/fact[j] : 0.0f; // fully degenerate
	  else Cq += c*pow(T,j)*pow(-1.0,dk-j)*drec(dk-j,bk,oArray,q-dk)/fact[j];
    }
    k += dk+1;
  }

  return Cq;
}

#endif // _CQCOEF_H