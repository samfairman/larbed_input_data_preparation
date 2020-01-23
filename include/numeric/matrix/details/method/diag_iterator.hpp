#ifndef DF9H4KLJAHFDO94YSFAKJDH948YAFLKJVCMJNBAOYUH84897YAFKLJH498YAFKUJHSAFDI9Y
#define DF9H4KLJAHFDO94YSFAKJDH948YAFLKJVCMJNBAOYUH84897YAFKLJH498YAFKUJHSAFDI9Y

#include <iterator>
#include <memory>

namespace numeric
{
    template<typename Matrix, typename Type, typename Allocator>
    struct matrix_diag_iterator
    {
        typedef Matrix                                                              zen_type;
        typedef std::allocator_traits<Allocator>                                    allocator_trait_type;
        typedef typename allocator_trait_type::size_type                            size_type;
        typedef typename allocator_trait_type::difference_type                      difference_type;
        typedef typename allocator_trait_type::pointer                              pointer;
        typedef typename allocator_trait_type::const_pointer                        const_pointer;
        
        typedef stride_iterator<pointer>                                            diag_iterator;
        typedef stride_iterator<const_pointer>                                      const_diag_iterator;
        typedef std::reverse_iterator<diag_iterator>                                reverse_diag_iterator;
        typedef std::reverse_iterator<const_diag_iterator>                          const_reverse_diag_iterator;

        typedef diag_iterator                                                       upper_diag_iterator;
        typedef reverse_diag_iterator                                               reverse_upper_diag_iterator;
        typedef const_diag_iterator                                                 const_upper_diag_iterator;
        typedef const_reverse_diag_iterator                                         const_reverse_upper_diag_iterator;

        typedef diag_iterator                                                       lower_diag_iterator;
        typedef reverse_diag_iterator                                               reverse_lower_diag_iterator;
        typedef const_diag_iterator                                                 const_lower_diag_iterator;
        typedef const_reverse_diag_iterator                                         const_reverse_lower_diag_iterator;

        diag_iterator upper_diag_begin( const size_type index )
        {
            zen_type& zen = static_cast<zen_type&>( *this );
            return diag_iterator( zen.begin() + index, zen.col() + 1 );
        }

        diag_iterator upper_diag_end( const size_type index )
        {
            zen_type& zen = static_cast<zen_type&>( *this );
            size_type depth = zen.col() - index;

            if ( zen.row() < depth )
            { depth = zen.row(); }

            return diag_iterator( upper_diag_begin( index ) + depth );
        }

        const_diag_iterator upper_diag_begin( const size_type index ) const
        {
            zen_type const& zen = static_cast<zen_type const&>( *this );
            return const_diag_iterator( zen.begin() + index, zen.col() + 1 );
        }

        const_diag_iterator upper_diag_end( const size_type index ) const
        {
            zen_type const& zen = static_cast<zen_type const&>( *this );
            size_type depth = zen.col() - index;

            if ( zen.row() < depth )
            { depth = zen.row(); }

            return upper_diag_begin( index ) + depth;
        }

        const_diag_iterator upper_diag_cbegin( const size_type index ) const
        {
            zen_type const& zen = static_cast<zen_type const&>( *this );
            return const_diag_iterator( zen.cbegin() + index, zen.col() + 1 );
        }

        const_diag_iterator upper_diag_cend( const size_type index ) const
        {
            zen_type const& zen = static_cast<zen_type const&>( *this );
            size_type depth = zen.col() - index;

            if ( zen.row() < depth )
            { depth = zen.row(); }

            return upper_diag_cbegin( index ) + depth;
        }

        reverse_upper_diag_iterator
        upper_diag_rbegin( const size_type index = 0 )
        {
            return reverse_upper_diag_iterator( upper_diag_end( index ) );
        }

        reverse_upper_diag_iterator
        upper_diag_rend( const size_type index = 0 )
        {
            return reverse_upper_diag_iterator( upper_diag_begin( index ) );
        }

        const_reverse_upper_diag_iterator
        upper_diag_rbegin( const size_type index = 0 ) const
        {
            return const_reverse_upper_diag_iterator( upper_diag_end( index ) );
        }

        const_reverse_upper_diag_iterator
        upper_diag_rend( const size_type index = 0 ) const
        {
            return const_reverse_upper_diag_iterator( upper_diag_begin( index ) );
        }

        const_reverse_upper_diag_iterator
        upper_diag_crbegin( const size_type index = 0 ) const
        {
            return const_reverse_upper_diag_iterator( upper_diag_end( index ) );
        }

        const_reverse_upper_diag_iterator
        upper_diag_crend( const size_type index = 0 ) const
        {
            return const_reverse_upper_diag_iterator( upper_diag_begin( index ) );
        }


        diag_iterator lower_diag_begin( const size_type index )
        {
            zen_type& zen = static_cast<zen_type&>( *this );
            return diag_iterator( zen.begin() + index * zen.col(), zen.col() + 1 );
        }

        diag_iterator lower_diag_end( const size_type index )
        {
            zen_type& zen = static_cast<zen_type&>( *this );
            size_type depth = zen.row() - index;

            if ( zen.col() < depth )
            { depth = zen.col(); }

            return lower_diag_begin( index ) + depth;
        }

        const_diag_iterator lower_diag_begin( const size_type index ) const
        {
            zen_type const& zen = static_cast<zen_type const&>( *this );
            return const_diag_iterator( zen.begin() + index * zen.col(), zen.col() + 1 );
        }

        const_diag_iterator lower_diag_end( const size_type index ) const
        {
            zen_type const& zen = static_cast<zen_type const&>( *this );
            size_type depth = zen.row() - index;

            if ( zen.col() < depth )
            { depth = zen.col(); }

            return lower_diag_begin( index ) + depth;
        }

        const_diag_iterator lower_diag_cbegin( const size_type index ) const
        {
            zen_type const& zen = static_cast<zen_type const&>( *this );
            return const_diag_iterator( zen.begin() + index * zen.col(), zen.col() + 1 );
        }

        const_diag_iterator lower_diag_cend( const size_type index ) const
        {
            zen_type const& zen = static_cast<zen_type const&>( *this );
            size_type depth = zen.row() - index;

            if ( zen.col() < depth )
            { depth = zen.col(); }

            return lower_diag_begin( index ) + depth;
        }

        reverse_lower_diag_iterator lower_diag_rbegin( const size_type index = 0 )
        {
            return reverse_lower_diag_iterator( lower_diag_end( index ) );
        }

        reverse_lower_diag_iterator lower_diag_rend( const size_type index = 0 )
        {
            return reverse_lower_diag_iterator( lower_diag_begin( index ) );
        }

        const_reverse_lower_diag_iterator lower_diag_rbegin( const size_type index = 0 ) const
        {
            return const_reverse_lower_diag_iterator( lower_diag_end( index ) );
        }

        const_reverse_lower_diag_iterator lower_diag_rend( const size_type index = 0 ) const
        {
            return const_reverse_lower_diag_iterator( lower_diag_begin( index ) );
        }

        const_reverse_lower_diag_iterator lower_diag_crbegin( const size_type index = 0 ) const
        {
            return const_reverse_lower_diag_iterator( lower_diag_end( index ) );
        }

        const_reverse_lower_diag_iterator lower_diag_crend( const size_type index = 0 ) const
        {
            return const_reverse_lower_diag_iterator( lower_diag_begin( index ) );
        }

        diag_iterator diag_begin( const difference_type index = 0 )
        {
            if ( index > 0 ) { return upper_diag_begin( index ); }

            return lower_diag_begin( -index );
        }

        diag_iterator diag_end( const difference_type index = 0 )
        {
            if ( index > 0 ) { return upper_diag_end( index ); }

            return lower_diag_end( -index );
        }

        const_diag_iterator diag_begin( const difference_type index = 0 ) const
        {
            if ( index > 0 ) { return upper_diag_begin( index ); }

            return lower_diag_begin( -index );
        }

        const_diag_iterator diag_end( const difference_type index = 0 ) const
        {
            if ( index > 0 ) { return upper_diag_end( index ); }

            return lower_diag_end( -index );
        }

        const_diag_iterator diag_cbegin( const difference_type index = 0 ) const
        {
            if ( index > 0 ) { return upper_diag_cbegin( index ); }

            return lower_diag_cbegin( -index );
        }

        const_diag_iterator diag_cend( const difference_type index = 0 ) const
        {
            if ( index > 0 ) { return upper_diag_cend( index ); }

            return lower_diag_cend( -index );
        }


        reverse_diag_iterator diag_rbegin( const difference_type index = 0 )
        {
            if ( index > 0 ) { return upper_diag_rbegin( index ); }

            return lower_diag_rbegin( -index );
        }

        reverse_diag_iterator diag_rend( const difference_type index = 0 )
        {
            if ( index > 0 ) { return upper_diag_rend( index ); }

            return lower_diag_rend( -index );
        }

        const_reverse_diag_iterator diag_rbegin( const difference_type index = 0 ) const
        {
            if ( index > 0 ) { return upper_diag_rbegin( index ); }

            return lower_diag_rbegin( -index );
        }

        const_reverse_diag_iterator diag_rend( const difference_type index = 0 ) const
        {
            if ( index > 0 ) { return upper_diag_rend( index ); }

            return lower_diag_rend( -index );
        }

        const_reverse_diag_iterator diag_crbegin( const difference_type index = 0 ) const
        {
            if ( index > 0 ) { return upper_diag_crbegin( index ); }

            return lower_diag_crbegin( -index );
        }

        const_reverse_diag_iterator diag_crend( const difference_type index = 0 ) const
        {
            if ( index > 0 ) { return upper_diag_crend( index ); }

            return lower_diag_crend( -index );
        }

    };//struct matrix_diag_iterator

}//namespace numeric

#endif//DF9H4KLJAHFDO94YSFAKJDH948YAFLKJVCMJNBAOYUH84897YAFKLJH498YAFKUJHSAFDI9Y

