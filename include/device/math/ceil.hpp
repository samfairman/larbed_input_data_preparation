#ifndef KPVLPGWLCMEXKUBIXXRABCQWTSMIPXYPNBYVBHRQKPSNDRWXKUIRNTNTCTLTEPSKCNEWRIKAN
#define KPVLPGWLCMEXKUBIXXRABCQWTSMIPXYPNBYVBHRQKPSNDRWXKUIRNTNTCTLTEPSKCNEWRIKAN

#include <device/complex.hpp>

#include <math_functions.h>

namespace device
{
    
    template< typename Type > struct ceil;

    template<> struct ceil<float>
    {
        typedef float value_type;

        __device__ __host__
        value_type operator()( const value_type x ) const
        {
            return ::ceilf(x);
        }
    };//struct ceil<float>

    template<> struct ceil<double>
    {
        typedef double value_type;

        __device__ __host__
        value_type operator()( const value_type x ) const
        {
            return ::ceil(x);
        }
    };//struct ceil<double>

    template< typename Type >
    struct ceil< device::complex<Type> >
    {
        typedef device::complex<Type> value_type;

        __device__ __host__
        value_type operator()( const value_type x ) const
        {
            //to be implemented
            return value_type(0,0);
        }
    };//struct ceil<complex<...> >

}//namespace device

#endif//KPVLPGWLCMEXKUBIXXRABCQWTSMIPXYPNBYVBHRQKPSNDRWXKUIRNTNTCTLTEPSKCNEWRIKAN
