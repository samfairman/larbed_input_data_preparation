#ifndef SI3IKLAFJLKVLAKJFD0498UALFDJKALKJASLKSDJALFDSJKSDALKJSDAF0984USALFKJVCLK
#define SI3IKLAFJLKVLAKJFD0498UALFDJKALKJASLKSDJALFDSJKSDALKJSDAF0984USALFKJVCLK

#include <numeric/matrix/details/utility/stride_iterator.hpp>

#include <memory>

namespace numeric
{
    template<typename Matrix, typename Type, typename Allocator>
    struct matrix_col_iterator
    {
        typedef Matrix                                                          zen_type;
        typedef std::allocator_traits<Allocator>                                allocator_trait_type;
        typedef typename allocator_trait_type::size_type                        size_type;
        typedef typename allocator_trait_type::value_type                       value_type;
        typedef typename allocator_trait_type::pointer                          pointer;
        typedef typename allocator_trait_type::const_pointer                    const_pointer;
        typedef stride_iterator<pointer>                                        col_iterator;
        typedef stride_iterator<const_pointer>                                  const_col_iterator;
        typedef std::reverse_iterator<col_iterator>                             reverse_col_iterator;
        typedef std::reverse_iterator<const_col_iterator>                       const_reverse_col_iterator;

        col_iterator col_begin( const size_type index )
        {
            zen_type& zen = static_cast<zen_type&>( *this );
            return col_iterator( zen.begin() + index, zen.col() );
        }

        col_iterator col_end( const size_type index )
        {
            zen_type& zen = static_cast<zen_type&>( *this );
            return col_begin( index ) + zen.row();
        }

        const_col_iterator col_begin( const size_type index ) const
        {
            zen_type const& zen = static_cast<zen_type const&>( *this );
            return const_col_iterator( zen.begin() + index, zen.col() );
        }

        const_col_iterator col_end( const size_type index ) const
        {
            zen_type const& zen = static_cast<zen_type const&>( *this );
            return col_begin( index ) + zen.row();
        }

        const_col_iterator col_cbegin( const size_type index ) const
        {
            zen_type const& zen = static_cast<zen_type const&>( *this );
            return const_col_iterator( zen.begin() + index, zen.col() );
        }

        const_col_iterator col_cend( const size_type index ) const
        {
            zen_type const& zen = static_cast<zen_type const&>( *this );
            return col_begin( index ) + zen.row();
        }

        reverse_col_iterator col_rbegin( const size_type index = 0 )
        {
            return reverse_col_iterator( col_end( index ) );
        }

        reverse_col_iterator col_rend( const size_type index = 0 )
        {
            return reverse_col_iterator( col_begin( index ) );
        }

        const_reverse_col_iterator col_rbegin( const size_type index = 0 ) const
        {
            return const_reverse_col_iterator( col_end( index ) );
        }

        const_reverse_col_iterator col_rend( const size_type index = 0 ) const
        {
            return const_reverse_col_iterator( col_begin( index ) );
        }

        const_reverse_col_iterator col_crbegin( const size_type index = 0 ) const
        {
            return const_reverse_col_iterator( col_end( index ) );
        }

        const_reverse_col_iterator col_crend( const size_type index = 0 ) const
        {
            return const_reverse_col_iterator( col_begin( index ) );
        }

    };//struct matrix_col_iterator

}//namespace numeric

#endif//SI3IKLAFJLKVLAKJFD0498UALFDJKALKJASLKSDJALFDSJKSDALKJSDAF0984USALFKJVCLK

