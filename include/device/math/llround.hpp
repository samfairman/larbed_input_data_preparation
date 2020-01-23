#ifndef TTHNWUOIOBEPTNOQCHIJYHYRXTYEVHSGASHERLWYILIRFPDSTVPXTJDMSNGRDDLOSSHCIXNJM
#define TTHNWUOIOBEPTNOQCHIJYHYRXTYEVHSGASHERLWYILIRFPDSTVPXTJDMSNGRDDLOSSHCIXNJM

#include <device/complex.hpp>

#include <math_functions.h>

namespace device
{
    
    template< typename Type > struct llround;

    template<> struct llround<float>
    {
        typedef float value_type;

        __device__ __host__
        value_type operator()( const value_type x ) const
        {
            return ::llroundf(x);
        }
    };//struct llround<float>

    template<> struct llround<double>
    {
        typedef double value_type;

        __device__ __host__
        value_type operator()( const value_type x ) const
        {
            return ::llround(x);
        }
    };//struct llround<double>

    template< typename Type >
    struct llround< device::complex<Type> >
    {
        typedef device::complex<Type> value_type;

        __device__ __host__
        value_type operator()( const value_type x ) const
        {
            //to be implemented
            return value_type(0,0);
        }
    };//struct llround<complex<...> >

}//namespace device

#endif//TTHNWUOIOBEPTNOQCHIJYHYRXTYEVHSGASHERLWYILIRFPDSTVPXTJDMSNGRDDLOSSHCIXNJM
