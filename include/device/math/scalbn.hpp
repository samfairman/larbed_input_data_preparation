#ifndef FDGKIVTPVQGBQMMXXUKYMVJIJVNWRMPOJTJTNJDYPKHUVDMMPQUBOSXQSLBOHKLVBVSUPJLKE
#define FDGKIVTPVQGBQMMXXUKYMVJIJVNWRMPOJTJTNJDYPKHUVDMMPQUBOSXQSLBOHKLVBVSUPJLKE

#include <device/complex.hpp>

#include <math_functions.h>

namespace device
{
    
    template< typename Type > struct scalbn;

    template<> struct scalbn<float>
    {
        typedef float value_type;

        __device__ __host__
        value_type operator()( const value_type x, const value_type y ) const
        {
            return ::scalbnf(x, y);
        }
    };//struct scalbn<float>

    template<> struct scalbn<double>
    {
        typedef double value_type;

        __device__ __host__
        value_type operator()( const value_type x, const value_type y ) const
        {
            return ::scalbn(x, y);
        }
    };//struct scalbn<double>

    template< typename Type >
    struct scalbn< device::complex<Type> >
    {
        typedef device::complex<Type> value_type;

        __device__ __host__
        value_type operator()( const value_type x, const value_type y ) const
        {
            //to be implemented
            return value_type(0,0);
        }
    };//struct scalbn<complex<...> >

}//namespace device

#endif//FDGKIVTPVQGBQMMXXUKYMVJIJVNWRMPOJTJTNJDYPKHUVDMMPQUBOSXQSLBOHKLVBVSUPJLKE
