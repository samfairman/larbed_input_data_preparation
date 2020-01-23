#ifndef UBUEXEXTMTTPHAHHKXVGFOXGCJWPJEPQBCWCGSWXIUEMXOHVURITXIYEARGVWFWNLXLUBRANC
#define UBUEXEXTMTTPHAHHKXVGFOXGCJWPJEPQBCWCGSWXIUEMXOHVURITXIYEARGVWFWNLXLUBRANC

#include <algorithm>
#include <cassert>

namespace numeric
{
    template< typename Matrix, typename Type, typename Allocator >
    struct matrix_fill_n
    {
        typedef Matrix                                                  zen_type;
        typedef std::allocator_traits<Allocator>                        allocator_trait_type;
        typedef typename std::allocator_traits<Allocator>::size_type    size_type;
        typedef typename std::allocator_traits<Allocator>::value_type   value_type;

        auto fill_n( size_type n, value_type x )
        {
            auto& zen = static_cast<zen_type&>(*this);
            assert( zen.size() >= n );
            return std::fill_n( zen.begin(), n, x );
        }

    };//struct matrix_fill_n

#if 0
    template< typename Matrix, typename Type >
    struct matrix_fill_n< Matrix, Type, cuda_allocator >
    {
        typedef Matrix                                                  zen_type;
        typedef std::allocator_traits<Allocator>                        allocator_trait_type;
        typedef typename std::allocator_traits<Allocator>::size_type    size_type;

    };//struct matrix_fill_n
#endif




}//namespace numeric

#endif//UBUEXEXTMTTPHAHHKXVGFOXGCJWPJEPQBCWCGSWXIUEMXOHVURITXIYEARGVWFWNLXLUBRANC

