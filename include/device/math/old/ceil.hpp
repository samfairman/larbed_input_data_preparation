#ifndef _CEIL_HPP_INCLUDED_SDPOFIH4HU9ASLFDKJH498HASFDILUH438HU7AFDSIUHF98Y4FSDF
#define _CEIL_HPP_INCLUDED_SDPOFIH4HU9ASLFDKJH498HASFDILUH438HU7AFDSIUHF98Y4FSDF

#include <device/typedef.hpp>

namespace device
{
    /*
    template<typename Type> __device__
    Type ceil( cnost Type x )
    {
        return (device::intmax_t)(x) + (1 - (device::intmax_t)((device::intmax_t)((x) + 1) - (x)));
    }
    */

    template<typename Type>
    struct ceil
    {
        typedef Type value_type;

        __device__ __host__
        value_type operator()( const value_type x ) const 
        {
            return (device::intmax_t)(x) + (1 - (device::intmax_t)((device::intmax_t)((x) + 1) - (x)));
        }
    
    };

}//namespace device

#endif//_CEIL_HPP_INCLUDED_SDPOFIH4HU9ASLFDKJH498HASFDILUH438HU7AFDSIUHF98Y4FSDF

