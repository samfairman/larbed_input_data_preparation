#ifndef KTUEOAQXDWQXYRBAVUVYQPKXSXQUOSMSNXXEMPWRFKREWPSABUDFXUHQFVGKNAALRGGUTKGVS
#define KTUEOAQXDWQXYRBAVUVYQPKXSXQUOSMSNXXEMPWRFKREWPSABUDFXUHQFVGKNAALRGGUTKGVS

#include <device/complex.hpp>

#include <math_functions.h>

namespace device
{
    
    template< typename Type > struct atan2;

    template<> struct atan2<float>
    {
        typedef float value_type;

        __device__ __host__
        value_type operator()( const value_type x, const value_type y ) const
        {
            return ::atan2f(x, y);
        }
    };//struct atan2<float>

    template<> struct atan2<double>
    {
        typedef double value_type;

        __device__ __host__
        value_type operator()( const value_type x, const value_type y ) const
        {
            return ::atan2(x, y);
        }
    };//struct atan2<double>

    template< typename Type >
    struct atan2< device::complex<Type> >
    {
        typedef device::complex<Type> value_type;

        __device__ __host__
        value_type operator()( const value_type x, const value_type y ) const
        {
            //to be implemented
            return value_type(0,0);
        }
    };//struct atan2<complex<...> >

}//namespace device

#endif//KTUEOAQXDWQXYRBAVUVYQPKXSXQUOSMSNXXEMPWRFKREWPSABUDFXUHQFVGKNAALRGGUTKGVS
