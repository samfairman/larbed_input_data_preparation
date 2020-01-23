#ifndef _SWAP_HPP_IONCLUDED_SDFPOJNASFDLKJFSDAPONASDFLKJASDF9P8HJ4LKJASHFDKLJASDH
#define _SWAP_HPP_IONCLUDED_SDFPOJNASFDLKJFSDAPONASDFLKJASDF9P8HJ4LKJASHFDKLJASDH

#include <utility>

namespace numeric
{
    template< typename Matrix, typename Type, typename Allocator >
    struct matrix_swap
    {
        typedef Matrix                                      zen_type;
        typedef std::allocator_traits<Allocator>            allocator_trait_type;

        void swap( zen_type& other)
        {
            auto& zen = static_cast<zen_type&>(*this);
            std::swap( zen.row_, other.row_ );
            std::swap( zen.col_, other.col_ );
            std::swap( zen.alloc_, other.alloc_ );
            std::swap( zen.data_, other.data_ );
        }
    };//struct matrix_swap
}//namespace numeric

#endif//_SWAP_HPP_IONCLUDED_SDFPOJNASFDLKJFSDAPONASDFLKJASDF9P8HJ4LKJASHFDKLJASDH

