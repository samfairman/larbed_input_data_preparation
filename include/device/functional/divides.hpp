#ifndef _DIVIDES_HPP_INCLUDED_SFUH3KJAFSD98HU4O8EIJKASFDN4987UIHAJFKSD498UIHAFJD
#define _DIVIDES_HPP_INCLUDED_SFUH3KJAFSD98HU4O8EIJKASFDN4987UIHAJFKSD498UIHAFJD 

#include <device/functional/binary_function.hpp>

namespace device
{
    template<typename Value_Type>
    struct divides : device::binary_function<Value_Type, Value_Type, Value_Type>
    {
        __device__ __host__
        Value_Type operator ()( const Value_Type& a, const Value_Type& b ) const 
        {
            return a/b; 
        }
    };//struct divides

}//namespace device

#endif//_DIVIDES_HPP_INCLUDED_SFUH3KJAFSD98HU4O8EIJKASFDN4987UIHAJFKSD498UIHAFJD 

