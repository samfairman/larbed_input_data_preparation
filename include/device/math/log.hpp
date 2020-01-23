#ifndef HCLLQIECUSOFYFKBRIUDWHOKSLIPIVPJVALUSGRUDCMABIOMVGPLUEXXFLYVPWKAPLRXDCLFL
#define HCLLQIECUSOFYFKBRIUDWHOKSLIPIVPJVALUSGRUDCMABIOMVGPLUEXXFLYVPWKAPLRXDCLFL

#include <device/complex.hpp>

#include <math_functions.h>

namespace device
{
    
    template< typename Type > struct log;

    template<> struct log<float>
    {
        typedef float value_type;

        __device__ __host__
        value_type operator()( const value_type x ) const
        {
            return ::logf(x);
        }
    };//struct log<float>

    template<> struct log<double>
    {
        typedef double value_type;

        __device__ __host__
        value_type operator()( const value_type x ) const
        {
            return ::log(x);
        }
    };//struct log<double>

    template< typename Type >
    struct log< device::complex<Type> >
    {
        typedef device::complex<Type> value_type;

        __device__ __host__
        value_type operator()( const value_type x ) const
        {
            //to be implemented
            return value_type(0,0);
        }
    };//struct log<complex<...> >

}//namespace device

#endif//HCLLQIECUSOFYFKBRIUDWHOKSLIPIVPJVALUSGRUDCMABIOMVGPLUEXXFLYVPWKAPLRXDCLFL
