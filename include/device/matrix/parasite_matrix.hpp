#ifndef RFVJDXQTYYOQCDEBDSWTLMXTADCPFRBDWLJRPUSRHUKOVOGXWCYJGBFNIKAKHVAGQSGNHOTFV
#define RFVJDXQTYYOQCDEBDSWTLMXTADCPFRBDWLJRPUSRHUKOVOGXWCYJGBFNIKAKHVAGQSGNHOTFV

#include <device/typedef.hpp>

namespace device
{
    template< typename T >
    struct parasite_matrix
    {
        typedef T               value_type;
        typedef size_t          size_type;

        value_type*             data_; 
        size_type               row_;
        size_type               col_;

        __device__
        parasite_matrix( value_type* data, size_type const row, size_type const col ) : data_( data ), row_( row ), col_( col ) {}

        value_type 
        __device__
        operator()( size_type row, size_type col ) const 
        {
            if ( row < row_ && col < col_ ) 
                return data_[row * col_ + col]; 
            return value_type(0);
        }

        value_type&
        __device__
        operator()( size_type row, size_type col )
        {
            return data_[row * col_ + col]; 
        }
    };

}//namespace device

#endif//RFVJDXQTYYOQCDEBDSWTLMXTADCPFRBDWLJRPUSRHUKOVOGXWCYJGBFNIKAKHVAGQSGNHOTFV
