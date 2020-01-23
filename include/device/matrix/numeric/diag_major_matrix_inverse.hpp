#ifndef _DIAG_MAJOR_MATRIX_INVERSE_HPP_INCLUDED_FDPOSIJASDLK498HASFDLIUH498UHFSD
#define _DIAG_MAJOR_MATRIX_INVERSE_HPP_INCLUDED_FDPOSIJASDLK498HASFDLIUH498UHFSD

#include <device/complex.hpp>
#include <device/functional.hpp>
#include <device/matrix.hpp>
#include <device/matrix/numeric/gemm.hpp>
#include <device/math/inverse.hpp>
#include <device/math/abs.hpp>
#include <device/vector.hpp>
#include <device/algorithm/copy.hpp>
#include <device/algorithm/transform.hpp>
#include <device/numeric/accumulate.hpp>

namespace device
{
    namespace diag_misc_space_sd9ij4398yuasf89yasfdiouh498yfsdf9h4fdef
    {
        template< typename T >
        struct fix_complex_value_type
        {
            typedef T value_type;
        };

        template< typename T >
        struct fix_complex_value_type<device::complex<T> >
        {
            typedef T value_type;
        };

    }//namespace diag_misc_space_sd9ij4398yuasf89yasfdiouh498yfsdf9h4fdef 


    template<typename T>
    const matrix<T> diag_major_matrix_inverse( const matrix<T>& A )
    {
        typedef typename diag_misc_space_sd9ij4398yuasf89yasfdiouh498yfsdf9h4fdef::fix_complex_value_type<T> ::value_type value_type;
        const value_type eps( 1.0e-8 );
        size_t n = A.row();
        //const value_type EPS = eps * n;
        device::matrix<T> A_( n, n, T(0) );
        device::matrix<T> A__( n, n );
        device::transform( A.diag_begin(), A.diag_end(), A_.diag_begin(), device::inverse<T>() );

        device::vector<value_type> x(n);

        for(;;)
        {
            //A_ *= ( 2 * eye<T>(n,n) - A_*A );
            device::gemm( A__, A_, A ); // A__ = A_ * A;

            {   //here we check if A__ is close to I
                // x = abs( A__[i][i] )
                device::transform( A__.diag_begin(), A__.diag_end(), x.begin(), device::abs<T>() );
                // sum_A_ii 
                const value_type sum_A_ii = device::accumulate( x.begin(), x.end(), value_type(0) );
                // x = x^2
                device::transform( x.begin(), x.end(), x.begin(), x.begin(), device::multiplies<value_type>() );
                // sum_A_ii_2
                const value_type sum_A_ii_2 = device::accumulate( x.begin(), x.end(), value_type(0) );
                const value_type rate = sum_A_ii / sqrt<value_type>()(n*sum_A_ii_2) + eps;
                if ( rate >= value_type(1) ) return  A_;
            }

            device::transform( A__.begin(), A__.end(), A__.begin(), device::negate<T>() ); // A__ = -A__
            device::transform( A__.diag_begin(), A__.diag_end(), A__.diag_begin(), device::bind1st( device::plus<T>(), T(2) ) ); // A__ = A__ + 2I
            A_ *= A__;// A_ = A_ * ( 2I - A_*A )
        }
    }

}//namespace device

#endif//_DIAG_MAJOR_MATRIX_INVERSE_HPP_INCLUDED_FDPOSIJASDLK498HASFDLIUH498UHFSD

