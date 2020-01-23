#ifndef HELPERFUNCTIONS_H
#define HELPERFUNCTIONS_H

#include <qeda/DataTypes.h>

////////////////////////////////////////////////////////////////////////////
// This file contains a few general functions that are used by QEDA.


template<typename T> bool isfinite(T arg)
{
    return arg == arg && 
           arg != std::numeric_limits<T>::infinity() &&
           arg != -std::numeric_limits<T>::infinity();
}

double dmax(double a,double b) {return (a > b) ? a : b;}

	// code for finding the vertex of a parabola (http://stackoverflow.com/questions/717762/how-to-calculate-the-vertex-of-a-parabola-given-three-points) :
	// This function solves:
	// A*x1^2+B*x1+C=y1
	// A*x2^2+B*x2+C=y2
	// A*x3^2+B*x3+C=y3
	// The vertex of this parabola will be at (xv,yv)
	void CalcParabolaVertex(double x1, double y1, double x2, double y2, double x3, double y3, double &xv, double &A)
	{
		double  denom = (x1 - x2) * (x1 - x3) * (x2 - x3);
		A     = (x3 * (y2 - y1) + x2 * (y1 - y3) + x1 * (y3 - y2)) / denom;
		double B     = (x3*x3 * (y1 - y2) + x2*x2 * (y3 - y1) + x1*x1 * (y2 - y3)) / denom;
		double C     = (x2 * x3 * (x2 - x3) * y1 + x3 * x1 * (x3 - x1) * y2 + x1 * x2 * (x1 - x2) * y3) / denom;
	
		// printf("A = %f\n",A);
		if (A > 0) xv = -B / (2*A);
		else xv = 0;
		if (xv < 0) xv = 0;
		// yv = C - B*B / (4*A);
	}	
#endif