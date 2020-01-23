#ifndef BULRPQBRTODEMSCGQXQVLKIQQIKXDIYDIPTPTXDPOMVDNAIOOMIMDMSWMUWAVDOEYQHIEBWCI
#define BULRPQBRTODEMSCGQXQVLKIQQIKXDIYDIPTPTXDPOMVDNAIOOMIMDMSWMUWAVDOEYQHIEBWCI

#include <device/complex.hpp>

#include <math_functions.h>

namespace device
{
    
    template< typename Type > struct pow;

    template<> struct pow<float>
    {
        typedef float value_type;

        __device__ __host__
        value_type operator()( const value_type x, const value_type y ) const
        {
            return ::powf(x, y);
        }
    };//struct pow<float>

    template<> struct pow<double>
    {
        typedef double value_type;

        __device__ __host__
        value_type operator()( const value_type x, const value_type y ) const
        {
            return ::pow(x, y);
        }
    };//struct pow<double>

    template< typename Type >
    struct pow< device::complex<Type> >
    {
        typedef device::complex<Type> value_type;

        __device__ __host__
        value_type operator()( const value_type x, const value_type y ) const
        {
            //to be implemented
            return value_type(0,0);
        }
    };//struct pow<complex<...> >

}//namespace device

#endif//BULRPQBRTODEMSCGQXQVLKIQQIKXDIYDIPTPTXDPOMVDNAIOOMIMDMSWMUWAVDOEYQHIEBWCI
