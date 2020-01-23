#ifndef _BRACKET_OPERATOR_HPP_INCLUDED_SDFPOIJASFDLKJASLKSAJDSALDKJSADKLJH43098
#define _BRACKET_OPERATOR_HPP_INCLUDED_SDFPOIJASFDLKJASLKSAJDSALDKJSADKLJH43098

#include <memory>

namespace numeric
{
    template<typename Matrix, typename Type, typename Allocator>
    struct matrix_bracket_operator
    {
        typedef Matrix                                                          zen_type;
        typedef std::allocator_traits<Allocator>                                allocator_trait_type;
        typedef typename allocator_trait_type::size_type                        size_type;
        typedef typename allocator_trait_type::pointer                          pointer;
        typedef typename allocator_trait_type::const_pointer                    const_pointer;
        typedef pointer                                                         iterator;
        typedef const_pointer                                                   const_iterator;

        iterator operator[]( size_type index )
        {
            zen_type& zen = static_cast<zen_type&>( *this );
            return zen.row_begin(index);
        }

        const_iterator operator[]( size_type index ) const
        {
            zen_type const& zen = static_cast<zen_type const&>( *this );
            return zen.row_cbegin(index);
        }

    };//struct

}//namespace numeric

#endif//_BRACKET_OPERATOR_HPP_INCLUDED_SDFPOIJASFDLKJASLKSAJDSALDKJSADKLJH43098

