#ifndef _MULTIPLIES_HPP_INCLUDED_OPFDINSLKASJNSADKJBNVKJBSADFIUAJFO8U34HKJAFHSDF
#define _MULTIPLIES_HPP_INCLUDED_OPFDINSLKASJNSADKJBNVKJBSADFIUAJFO8U34HKJAFHSDF 

#include <device/functional/binary_function.hpp>

namespace device
{
    template<typename Value_Type>
    struct multiplies : device::binary_function<Value_Type, Value_Type, Value_Type>
    {
        __device__ __host__
        Value_Type operator ()( const Value_Type& a, const Value_Type& b ) const 
        {
            return a*b; 
        }
    };//struct multiplies 

}//namespace device

#endif//_MULTIPLIES_HPP_INCLUDED_OPFDINSLKASJNSADKJBNVKJBSADFIUAJFO8U34HKJAFHSDF 

