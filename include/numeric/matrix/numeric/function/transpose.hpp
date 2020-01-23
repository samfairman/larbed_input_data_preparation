#ifndef RNKLWHUEWBTEXXTOTKFNGDIBJNWCEOAUQLACDXOYIBVMRTGHJXVAKEGVVXKUEVPXSSILGYIMB
#define RNKLWHUEWBTEXXTOTKFNGDIBJNWCEOAUQLACDXOYIBVMRTGHJXVAKEGVVXKUEVPXSSILGYIMB

#include <numeric/matrix/details/matrix.hpp>

#include <cstddef>

namespace numeric
{

    template< typename Type, typename Allocator >
    void transpose( matrix<Type, Allocator> const& A, matrix<Type, Allocator>& A_T )
    {
        A_T.resize( A.col(), A.row() );
        for ( std::size_t r = 0; r != A.row(); ++r )
            std::copy( A.row_begin(r), A.row_end(r), A_T.col_begin(r) );
    }

    template< typename Type, typename Allocator >
    matrix<Type, Allocator> const transpose( matrix<Type, Allocator> const& A )
    {
        matrix<Type, Allocator> A_T{ A.col(), A.row() };
        transpose( A, A_T );
        return A_T;
    }

}//namespace numeric

#endif//RNKLWHUEWBTEXXTOTKFNGDIBJNWCEOAUQLACDXOYIBVMRTGHJXVAKEGVVXKUEVPXSSILGYIMB

