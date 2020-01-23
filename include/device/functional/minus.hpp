#ifndef _MINUS_HPP_INCLUDED_SFOIH39048HAKSFJAIOSUH438OHAFLKUHAS87G43OIUAHFKJSHF
#define _MINUS_HPP_INCLUDED_SFOIH39048HAKSFJAIOSUH438OHAFLKUHAS87G43OIUAHFKJSHF 

#include <device/functional/binary_function.hpp>

namespace device
{
    template<typename Value_Type>
    struct minus : device::binary_function<Value_Type, Value_Type, Value_Type>
    {
        __device__ __host__
        Value_Type operator ()( const Value_Type& a, const Value_Type& b ) const 
        {
            return a-b; 
        }
    };//struct minus

}//namespace device

#endif//_MINUS_HPP_INCLUDED_SFOIH39048HAKSFJAIOSUH438OHAFLKUHAS87G43OIUAHFKJSHF 

