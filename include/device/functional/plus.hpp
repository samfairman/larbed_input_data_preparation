#ifndef _PLUS_HPP_INCLUDED_SDPOIHAS984YHLKAJSF498YALFJK379YIUAWEFJKAFSD984KJHAFS
#define _PLUS_HPP_INCLUDED_SDPOIHAS984YHLKAJSF498YALFJK379YIUAWEFJKAFSD984KJHAFS

#include <device/functional/binary_function.hpp>

namespace device
{
    template<typename Value_Type>
    struct plus : device::binary_function<Value_Type, Value_Type, Value_Type>
    {
        __device__ __host__
        Value_Type operator ()( const Value_Type& a, const Value_Type& b ) const 
        {
            return a+b; 
        }
    };//struct plus

}//namespace device

#endif//_PLUS_HPP_INCLUDED_SDPOIHAS984YHLKAJSF498YALFJK379YIUAWEFJKAFSD984KJHAFS

