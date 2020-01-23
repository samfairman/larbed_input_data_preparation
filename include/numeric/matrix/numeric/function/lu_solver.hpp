#ifndef QIHEFKDXCOOPHGFKKMFFIJNHGWOLQMDMSARUYFTHURJFJRCNNKIXYMBEPGMKLWEUSWFCWMIVX
#define QIHEFKDXCOOPHGFKKMFFIJNHGWOLQMDMSARUYFTHURJFJRCNNKIXYMBEPGMKLWEUSWFCWMIVX

#include <numeric/matrix/details/matrix.hpp>
#include <numeric/matrix/numeric/function/lu_decomposition.hpp>
#include <numeric/matrix/numeric/function/forward_substitution.hpp>
#include <numeric/matrix/numeric/function/backward_substitution.hpp>

#include <algorithm>
#include <cstddef>
#include <cassert>
#include <cmath>

namespace numeric
{
    //solving   Ax = b      -- using lu/forward_substitution/backward_substitution method
    //
    //return
    //          0    --     success
    //          1    --     failed
    template< typename Type, typename Allocator >
    int
    lu_solver( const matrix<Type, Allocator>&           A,
               matrix<Type, Allocator>&                 x,
               const matrix<Type, Allocator>&           b 
             )
    {
        typedef matrix<Type, Allocator>                 matrix_type;

        assert( A.row() == A.col() );
        assert( A.row() == b.row() );
        assert( b.col() == 1 );

        matrix_type L, U, Y;

        if ( lu_decomposition( A, L, U ) || forward_substitution( L, Y, b ) || backward_substitution( U, x, Y ) ) 
            return 1;

        return 0;
    }

}//namespace numeric

#endif//QIHEFKDXCOOPHGFKKMFFIJNHGWOLQMDMSARUYFTHURJFJRCNNKIXYMBEPGMKLWEUSWFCWMIVX

