#ifndef FCNIRWEKRUUERRIXGSNFMDBIHCJYGQUFAHGGUTGCFKNQAMVVCCQPWNIACFCKCKDPOKQAQUBJQ
#define FCNIRWEKRUUERRIXGSNFMDBIHCJYGQUFAHGGUTGCFKNQAMVVCCQPWNIACFCKCKDPOKQAQUBJQ

#include <memory>
#include <cassert>

namespace numeric
{
    template<typename Matrix, typename Type, typename Allocator>
    struct matrix_minus_operator
    {
        typedef Matrix                                                          zen_type;
        typedef std::allocator_traits<Allocator>                                allocator_trait_type;
        typedef typename allocator_trait_type::value_type                       value_type;
        typedef typename allocator_trait_type::size_type                        size_type;
        typedef typename allocator_trait_type::pointer                          pointer;
        typedef typename allocator_trait_type::const_pointer                    const_pointer;
        typedef pointer                                                         iterator;
        typedef const_pointer                                                   const_iterator;

        friend 
        zen_type operator - ( zen_type const& lhs, zen_type const& rhs )
        {
            assert( lhs.row() == rhs.row() );
            assert( lhs.col() == rhs.col() );
            zen_type ans{ lhs };
            for ( size_type r = 0; r != lhs.row(); ++r )
                for ( size_type c = 0; c != lhs.col(); ++c )
                    ans[r][c] -= rhs[r][c];
            return ans;
        }

        friend 
        zen_type operator - ( zen_type && lhs, zen_type const& rhs )
        {
            assert( lhs.row() == rhs.row() );
            assert( lhs.col() == rhs.col() );
            zen_type ans{ lhs };
            for ( size_type r = 0; r != lhs.row(); ++r )
                for ( size_type c = 0; c != lhs.col(); ++c )
                    ans[r][c] -= rhs[r][c];
            return ans;
        }

        friend 
        zen_type operator - ( zen_type const& lhs, zen_type&& rhs )
        {
            return ( - rhs ) + lhs;
        }

        friend 
        zen_type operator - ( zen_type&& lhs, zen_type&& rhs )
        {
            assert( lhs.row() == rhs.row() );
            assert( lhs.col() == rhs.col() );
            zen_type ans{ lhs };
            for ( size_type r = 0; r != lhs.row(); ++r )
                for ( size_type c = 0; c != lhs.col(); ++c )
                    ans[r][c] -= rhs[r][c];
            return ans;
        }

        friend 
        zen_type operator - ( zen_type const& lhs, value_type const& rhs )
        {
            assert( lhs.row() == rhs.row() );
            assert( lhs.col() == rhs.col() );

            zen_type ans{ lhs };

            std::for_each( ans.diag_begin(), ans.diag_end(), [&rhs](value_type& x){ x -= rhs; } );

            return ans;
        }

        friend 
        zen_type operator - ( zen_type&& lhs, value_type const& rhs )
        {
            assert( lhs.row() == rhs.row() );
            assert( lhs.col() == rhs.col() );

            zen_type ans{ lhs };

            std::for_each( ans.diag_begin(), ans.diag_end(), [&rhs](value_type& x){ x -= rhs; } );

            return ans;
        }

        friend 
        zen_type operator - ( value_type const& lhs, zen_type const& rhs )
        {
            return ( - rhs ) + lhs;
        }

        friend 
        zen_type operator - ( value_type const& lhs, zen_type&& rhs )
        {
            return ( - rhs ) + lhs;
        }

    };//struct

}//namespace numeric

#endif//FCNIRWEKRUUERRIXGSNFMDBIHCJYGQUFAHGGUTGCFKNQAMVVCCQPWNIACFCKCKDPOKQAQUBJQ

