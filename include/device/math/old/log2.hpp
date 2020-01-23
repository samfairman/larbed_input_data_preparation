#ifndef _LOG2_HPP_INCLUDED_SFDPOIJ498AKFJ409U8ASFLKJH498YAFIOU4H98YASFKI4H89HF4F
#define _LOG2_HPP_INCLUDED_SFDPOIJ498AKFJ409U8ASFLKJH498YAFIOU4H98YASFKI4H89HF4F

#include <device/typedef.hpp>

namespace device
{
    template<typename T>
    struct log2;

    template<>
    struct log2<float>
    {
        typedef float value_type;

        __host__ __device__
        value_type operator()( value_type val ) const
        {
            device::int32_t* exp_ptr        = reinterpret_cast<device::int32_t*>( &val );
            device::int32_t x               = *exp_ptr;
            const device::int32_t log_2     = ( ( x >> 23 ) & 255 ) - 128;
            //for double, ((x>>52) & 2047) - 1024
            const float _1_3                = float(1) / float(3);
            x                              &= ~( 255 << 23 );
            x                              += 127 << 23;
            *exp_ptr                        = x;
            val                             = ( 2 - _1_3 * val ) * val - _1_3 - _1_3;
            return ( val + log_2 );
        }

    };//
}//namespace device

#endif//_LOG2_HPP_INCLUDED_SFDPOIJ498AKFJ409U8ASFLKJH498YAFIOU4H98YASFKI4H89HF4F

