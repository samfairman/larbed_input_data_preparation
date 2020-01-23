#ifndef _NEGATE_HPP_INCLUDED_SPF9I4398AFLIUH3498YHASFKLJHASDJKVNAF98HU43JHFSD987
#define _NEGATE_HPP_INCLUDED_SPF9I4398AFLIUH3498YHASFKLJHASDJKVNAF98HU43JHFSD987

#include <device/functional/unary_function.hpp>

namespace device
{

    template<typename Value_Type>
    struct negate : device::unary_function<Value_Type, Value_Type>
    {
        __device__ __host__
        Value_Type operator ()( const Value_Type& v ) const 
        {
            return -v;
        }
    };//struct negate

}//namespace device

#endif//_NEGATE_HPP_INCLUDED_SPF9I4398AFLIUH3498YHASFKLJHASDJKVNAF98HU43JHFSD987

