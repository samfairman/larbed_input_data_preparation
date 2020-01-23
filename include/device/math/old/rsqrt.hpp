#ifndef _RSQRT_HPP_INCLUDED_SDFIONASOIUH43OHUASFLKAJSHF948YASLFIUHASOFIUH98R4FKJ
#define _RSQRT_HPP_INCLUDED_SDFIONASOIUH43OHUASFLKAJSHF948YASLFIUHASOFIUH98R4FKJ

#include <device/typedef.hpp> //for uint32_t and uint64_t

namespace device
{

    //reverse square root
    //Matthew Robertson (2012-04-24). "A Brief History of InvSqrt". UNBSJ.

    /*
    __device__ __forceinline__
    float rsqrt( const float x )
    {
        float const x2      = x * 0.5;
        float ans           = x;
        device::uint32_t i  = *( device::uint32_t * ) &ans;
        i                   = 0x5f375a86 - ( i >> 1 );
        ans                 = *( float * ) &i;
        ans                *= 1.5 - ( x2 * ans * ans );
        return ans;
    }

    __device__ __forceinline__
    double rsqrt( const double x )
    {
        const double x2     = x * 0.5;
        double ans          = x;
        device::uint64_t i  = *( device::uint64_t * ) &ans;
        i                   = 0x5fe6eb50c7b537a9 - ( i >> 1 );
        ans                 = *( double * ) &i;
        ans                *= 1.5 - ( x2 * ans * ans );
        return ans;
    }
    */

    template<typename Type>
    struct rsqrt;

    template<>
    struct rsqrt<float>
    {
        typedef float value_type;

        __device__ __host__
        value_type operator()( const value_type x ) const
        {
            float const x2      = x * 0.5;
            float ans           = x;
            device::uint32_t i  = *( device::uint32_t * ) &ans;
            i                   = 0x5f375a86 - ( i >> 1 );
            ans                 = *( float * ) &i;
            ans                *= 1.5 - ( x2 * ans * ans );
            return ans;
        }
    
    };//struct rsqrt<float>

    template<>
    struct rsqrt<double>
    {
        typedef double value_type;

        __device__ __host__
        value_type operator()( const value_type x ) const 
        {
            const double x2     = x * 0.5;
            double ans          = x;
            device::uint64_t i  = *( device::uint64_t * ) &ans;
            i                   = 0x5fe6eb50c7b537a9 - ( i >> 1 );
            ans                 = *( double * ) &i;
            ans                *= 1.5 - ( x2 * ans * ans );
            return ans;
        }
    
    };//struct rsqrt<double>

}//namespace device

#endif//_RSQRT_HPP_INCLUDED_SDFIONASOIUH43OHUASFLKAJSHF948YASLFIUHASOFIUH98R4FKJ

