#ifndef _COPYSIGN_HPP_INCLUDED_FSOIJ349OHUAFSDLKJH4908AHFUDSLK4UH89A7FH487HF874Y
#define _COPYSIGN_HPP_INCLUDED_FSOIJ349OHUAFSDLKJH4908AHFUDSLK4UH89A7FH487HF874Y

#include <device/math/sgn.hpp>

namespace device
{
    /*
    template<typename Type> __device__
    Type copysign( const Type& x, const Type& y )
    {
        const Type s = device::sgn( y );
        return s * x;
    }
    */

    template<typename Type>
    struct copysign
    {
        typedef Type value_type;

        __host__ __device__
        value_type operator()( const value_type& x, const value_type& y ) const
        {
            const value_type s = device::sgn<value_type>()( y );
            return s * x;
        }
    
    };//struct copysign 

}

#endif//_COPYSIGN_HPP_INCLUDED_FSOIJ349OHUAFSDLKJH4908AHFUDSLK4UH89A7FH487HF874Y

