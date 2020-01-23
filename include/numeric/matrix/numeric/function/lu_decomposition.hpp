#ifndef RUYVLXDHOJVRMONDWXCMNAOUIKTVSXXQEIQNMYQJRYBHORNPWSSMNRSBPQFWLEPFQVQEAVOHB
#define RUYVLXDHOJVRMONDWXCMNAOUIKTVSXXQEIQNMYQJRYBHORNPWSSMNRSBPQFWLEPFQVQEAVOHB

#include <numeric/matrix/details/matrix.hpp>

#include <cstddef>
#include <cassert>
#include <algorithm>
#include <cmath>

namespace numeric
{

    // LU decomposition
    // return
    //          0       --       success
    //          1       --       failed
    template<typename Type, typename Allocator>
    int lu_decomposition( const matrix<Type, Allocator>& A, matrix<Type, Allocator>& L, matrix<Type, Allocator>& U )
    {
        assert( A.row() == A.col() );

        const std::size_t n = A.row();

        matrix<Type, Allocator> L_ { n, n };
        matrix<Type, Allocator> U_ { n, n };

        std::fill( L_.diag_begin(), L_.diag_end(), Type{ 1 } );

        for ( std::size_t j = 0; j < n; ++j )
        {
            for ( std::size_t i = 0; i < j + 1; ++i )
                U_[i][j] = A[i][j] - std::inner_product( L_.row_begin( i ), L_.row_begin( i ) + i, U_.col_begin( j ), Type{0} );

            for ( std::size_t i = j + 1; i < n; ++i )
            {
                L_[i][j] = ( A[i][j] - std::inner_product( L_.row_begin( i ), L_.row_begin( i ) + j, U_.col_begin( j ), Type{0} ) ) / U_[j][j];

                if ( std::isinf( L_[i][j] ) || std::isnan( L_[i][j] ) )
                    return 1;
            }
        }

        L.swap( L_ );
        U.swap( U_ );

        return 0;
    }

}//namespace numeric

#endif//RUYVLXDHOJVRMONDWXCMNAOUIKTVSXXQEIQNMYQJRYBHORNPWSSMNRSBPQFWLEPFQVQEAVOHB

