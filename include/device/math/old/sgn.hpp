#ifndef _SGN_HPP_INCLUDED_DS9HIJ43LKJNASFD98HU4KLJASNFD87H4KJBNV98UH4KJFSD98UH4F
#define _SGN_HPP_INCLUDED_DS9HIJ43LKJNASFD98HU4KLJASNFD87H4KJBNV98UH4KJFSD98UH4F

namespace device
{
/*
    template<typename Type> __device__
    Type sgn( const Type& value )
    {
        if ( value < Type(0) ) return Type(-1);
        if ( value > Type(0) ) return Type(1);
        return Type(0);
    }
*/
    template<typename Type>
    struct sgn
    {
        typedef Type value_type;

        __device__ __host__
        value_type operator()( const value_type& value ) const 
        {
            if ( value < Type(0) ) return Type(-1);
            if ( value > Type(0) ) return Type(1);
            return Type(0);
        }
    
    };//struct sgn

}//namespace device

#endif//_SGN_HPP_INCLUDED_DS9HIJ43LKJNASFD98HU4KLJASNFD87H4KJBNV98UH4KJFSD98UH4F

