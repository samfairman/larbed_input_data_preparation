#ifndef ATWOTPDAWYOKXSTUPANIOIGTEQSETASNUEGRGPCPEGYRSNHXDEIUQDDLYSHCJMXHTHLFYGNQW
#define ATWOTPDAWYOKXSTUPANIOIGTEQSETASNUEGRGPCPEGYRSNHXDEIUQDDLYSHCJMXHTHLFYGNQW

#include <numeric/matrix/details/matrix.hpp>

#include <algorithm>
#include <cstddef>
#include <cassert>
#include <cmath>

namespace numeric
{
    //solving   Ax = b      -- A is an upper triangular matrix
    //
    //return
    //          0    --     success
    //          1    --     failed
    template<typename Type, typename Allocator>
    int
    backward_substitution( const matrix<type, Allocator>&           A,  //A[n][n] is an upper triangular matrix
                           matrix<Type, Allocator>&                 x,  //x[n]
                           const matrix<Type, Allocator>&           b ) //b[n]
    {
        typedef matrix_type<Type, Allocator>       matrix_type;
        typedef typename matrix_type::value_type    value_type;
        typedef typename matrix_type::size_type     size_type;

        assert( A.row() == A.col() );
        assert( A.row() == b.row() );
        assert( b.col() == 1 );
        size_type const n = A.row();

        //initialize x
        matrix_type x_ { n, 1 };
        std::fill( x_.begin(), x_.end(), value_type( 0 ) );

        for ( size_type i = 0; i != n; ++i )
        {
            size_type const r = n - 1 - i;
            value_type sum = std::inner_product( x_.rbegin(), x_.rbegin() + i, A.row_rbegin( r ), value_type( 0 ) );
            x_[r][0] = ( b[r][0] - sum ) / A[r][r];
            if ( std::isinf( x_[r][0] ) || std::isnan( x_[r][0] ) )
                return 1;
        }

        x.swap( x_ );

        return 0;
    }

}//namespace numeric

#endif//ATWOTPDAWYOKXSTUPANIOIGTEQSETASNUEGRGPCPEGYRSNHXDEIUQDDLYSHCJMXHTHLFYGNQW

