#ifndef TBRFPGQYCSRIFTGXXJMCKXAINRAVNPNENFEKATDFMBNKVFUYRRUXEKQONMAEFWVWFPUTXADYR
#define TBRFPGQYCSRIFTGXXJMCKXAINRAVNPNENFEKATDFMBNKVFUYRRUXEKQONMAEFWVWFPUTXADYR

#include <numeric/matrix/details/matrix.hpp>

#include <algorithm>
#include <cstddef>
#include <cassert>
#include <cmath>

namespace numeric
{
    //solving   Ax = b      -- A is a lower triangular matrix
    //
    //return
    //          0    --     success
    //          1    --     failed
    template<typename Type, typename Allocator>
    int
    forward_substitution( const matrix<Type, Allocator>&           A,  //A[n][n] is a lower triangular matrix
                          matrix<Type, Allocator>&                 x,  //x[n][1]
                          const matrix<Type, Allocator>&           b ) //b[n][1]
    {
        typedef matrix<Type, Allocator>          matrix_type;
        typedef typename matrix_type::value_type value_type;
        typedef typename matrix_type::size_type  size_type;

        assert( A.row() == A.col() );
        assert( A.row() == b.row() );
        assert( b.col() == 1 );
        size_type const n = A.row();

        matrix_type x_ { n, 1 };

        //initialize x_
        std::fill( x_.begin(), x_.end(), value_type( 0 ) );

        for ( size_type i = 0; i != n; ++i )
        {
            value_type sum = std::inner_product( x_.begin(), x_.begin() + i, A.row_begin( i ), value_type( 0 ) );
            x_[i][0] = ( b[i][0] - sum ) / A[i][i];
            if ( std::isinf( x_[i][0] ) || std::isnan( x_[i][0] ) )
                return 1;
        }

        x.swap( x_ );

        return 0;
    }

}//namespace numeric

#endif//TBRFPGQYCSRIFTGXXJMCKXAINRAVNPNENFEKATDFMBNKVFUYRRUXEKQONMAEFWVWFPUTXADYR

