#ifndef BKEGWWJHYSDGWOJBVKVLLWMUQJDDHRXVMCATVNNVEBSTLVHSAGSVPLOFWCFDAUSDNBNDCNTCJ
#define BKEGWWJHYSDGWOJBVKVLLWMUQJDDHRXVMCATVNNVEBSTLVHSAGSVPLOFWCFDAUSDNBNDCNTCJ

#include <device/complex.hpp>

#include <math_functions.h>

namespace device
{
    
    template< typename Type > struct exp2;

    template<> struct exp2<float>
    {
        typedef float value_type;

        __device__ __host__
        value_type operator()( const value_type x ) const
        {
            return ::exp2f(x);
        }
    };//struct exp2<float>

    template<> struct exp2<double>
    {
        typedef double value_type;

        __device__ __host__
        value_type operator()( const value_type x ) const
        {
            return ::exp2(x);
        }
    };//struct exp2<double>

    template< typename Type >
    struct exp2< device::complex<Type> >
    {
        typedef device::complex<Type> value_type;

        __device__ __host__
        value_type operator()( const value_type x ) const
        {
            //to be implemented
            return value_type(0,0);
        }
    };//struct exp2<complex<...> >

}//namespace device

#endif//BKEGWWJHYSDGWOJBVKVLLWMUQJDDHRXVMCATVNNVEBSTLVHSAGSVPLOFWCFDAUSDNBNDCNTCJ
