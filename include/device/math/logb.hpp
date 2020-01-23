#ifndef TAIUUFVEHBKAPXEBGHXLHIAJJHJCNCTTPESVEDUAMLGHWJNVTBJOGGPYKECYBRJHNXTHBTNJM
#define TAIUUFVEHBKAPXEBGHXLHIAJJHJCNCTTPESVEDUAMLGHWJNVTBJOGGPYKECYBRJHNXTHBTNJM

#include <device/complex.hpp>

#include <math_functions.h>

namespace device
{
    
    template< typename Type > struct logb;

    template<> struct logb<float>
    {
        typedef float value_type;

        __device__ __host__
        value_type operator()( const value_type x ) const
        {
            return ::logbf(x);
        }
    };//struct logb<float>

    template<> struct logb<double>
    {
        typedef double value_type;

        __device__ __host__
        value_type operator()( const value_type x ) const
        {
            return ::logb(x);
        }
    };//struct logb<double>

    template< typename Type >
    struct logb< device::complex<Type> >
    {
        typedef device::complex<Type> value_type;

        __device__ __host__
        value_type operator()( const value_type x ) const
        {
            //to be implemented
            return value_type(0,0);
        }
    };//struct logb<complex<...> >

}//namespace device

#endif//TAIUUFVEHBKAPXEBGHXLHIAJJHJCNCTTPESVEDUAMLGHWJNVTBJOGGPYKECYBRJHNXTHBTNJM
