#ifndef ASDIOUH4093UIUREOI0498790328457029348750934285DLKUFHKJHASDFKLJHAFDSKLJH
#define ASDIOUH4093UIUREOI0498790328457029348750934285DLKUFHKJHASDFKLJHAFDSKLJH

#include <memory>

namespace numeric
{
    template<typename Matrix, typename Type, typename Allocator>
    struct matrix_row_iterator
    {
        typedef Matrix                                                          zen_type;
        typedef std::allocator_traits<Allocator>                                allocator_trait_type;
        typedef typename allocator_trait_type::size_type                        size_type;
        typedef typename allocator_trait_type::value_type                       value_type;
        typedef typename allocator_trait_type::pointer                          pointer;
        typedef typename allocator_trait_type::const_pointer                    const_pointer;
        typedef pointer                                                         iterator;
        typedef std::reverse_iterator<iterator>                                 reverse_iterator;
        typedef const_pointer                                                   const_iterator;
        typedef std::reverse_iterator<const_pointer>                            const_reverse_iterator;

        iterator row_begin( const size_type index = 0 )
        {
            zen_type& zen = static_cast<zen_type&>( *this );
            return zen.begin() + index * zen.col();
        }

        iterator row_end( const size_type index = 0 )
        {
            zen_type& zen = static_cast<zen_type&>( *this );
            return row_begin( index ) + zen.col();
        }

        const_iterator row_begin( const size_type index = 0 ) const
        {
            zen_type const& zen = static_cast<zen_type const&>( *this );
            return zen.begin() + index * zen.col();
        }

        const_iterator row_end( const size_type index = 0 ) const
        {
            zen_type const& zen = static_cast<zen_type const&>( *this );
            return row_begin( index ) + zen.col();
        }

        const_iterator row_cbegin( const size_type index = 0 ) const
        {
            zen_type const& zen = static_cast<zen_type const&>( *this );
            return zen.begin() + index * zen.col();
        }

        const_iterator row_cend( const size_type index = 0 ) const
        {
            zen_type const& zen = static_cast<zen_type const&>( *this );
            return row_begin( index ) + zen.col();
        }

        reverse_iterator row_rbegin( const size_type index = 0 )
        {
            return reverse_iterator( row_end( index ) );
        }

        reverse_iterator row_rend( const size_type index = 0 )
        {
            return reverse_iterator( row_begin( index ) );
        }

        const_reverse_iterator row_rbegin( const size_type index = 0 ) const
        {
            return const_reverse_iterator( row_end( index ) );
        }

        const_reverse_iterator row_rend( const size_type index = 0 ) const
        {
            return const_reverse_iterator( row_begin( index ) );
        }

        const_reverse_iterator row_crbegin( const size_type index = 0 ) const
        {
            return const_reverse_iterator( row_end( index ) );
        }

        const_reverse_iterator row_crend( const size_type index = 0 ) const
        {
            return const_reverse_iterator( row_begin( index ) );
        }

    };//struct

}//namespace numeric

#endif//ASDIOUH4093UIUREOI0498790328457029348750934285DLKUFHKJHASDFKLJHAFDSKLJH

