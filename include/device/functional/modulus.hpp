#ifndef _MODULUS_HPP_INCLUDED_DFSPHI9498HAFILSDJKAW98HU34OILJKASFD9OHU348JALKSFF
#define _MODULUS_HPP_INCLUDED_DFSPHI9498HAFILSDJKAW98HU34OILJKASFD9OHU348JALKSFF 

#include <device/functional/binary_function.hpp>

namespace device
{
    template<typename Value_Type>
    struct modulus : device::binary_function<Value_Type, Value_Type, Value_Type>
    {
        __device__ __host__
        Value_Type operator ()( const Value_Type& a, const Value_Type& b ) const 
        {
            return a%b; 
        }
    };//struct modulus 

}//namespace device

#endif//_MODULUS_HPP_INCLUDED_DFSPHI9498HAFILSDJKAW98HU34OILJKASFD9OHU348JALKSFF 

