#ifndef _STATIC_MATRIX_HPP_INCLUDED_SDFPIONJH498YASFLKJH4978AHSFDLKJH498YSAFDKJH
#define _STATIC_MATRIX_HPP_INCLUDED_SDFPIONJH498YASFLKJH4978AHSFDLKJH498YSAFDKJH

#include <device/matrix/static_matrix/static_matrix_1_1.hpp>
#include <device/matrix/static_matrix/static_matrix_2_2.hpp>
#include <device/matrix/static_matrix/static_matrix_m_m.hpp>
#include <device/matrix/static_matrix/static_matrix_m_n.hpp>
#include <device/typedef.hpp>

#include <numeric>
#include <algorithm>
#include <iostream>

namespace device
{

    template<typename T, device::size_t M, device::size_t N, device::size_t L>
    device::static_matrix<T,M,L> const operator * ( const device::static_matrix<T,M,N>& lhs, const device::static_matrix<T,N,L>& rhs )
    {
        device::static_matrix<T,M,L> ans;

        for ( device::size_t i = 0; i != M; ++i )
            for ( device::size_t j = 0; j != L; ++j )
                ans[i][j] = std::inner_product( lhs.row_begin(i), lhs.row_end(i), rhs.col_begin(j), T() );

        return ans;
    }

    template<typename T, device::size_t M, device::size_t N>
    device::static_matrix<T,M,N> const operator / ( const device::static_matrix<T,M,N>& lhs, const device::static_matrix<T,N,N>& rhs )
    {
        return lhs * rhs.inverse();
    }

    template<typename T, device::size_t M, device::size_t N>
    std::ostream& operator << ( std::ostream& lhs, const device::static_matrix<T,M,N>& rhs )
    {
        for ( device::size_t r = 0; r != M; ++r )
        {
            std::copy( rhs.row_begin(r), rhs.row_end(r), std::ostream_iterator<T>(lhs, "\t" ) );
            lhs << "\n";
        }
        return lhs;
    }

}//namespace device

#endif//_STATIC_MATRIX_HPP_INCLUDED_SDFPIONJH498YASFLKJH4978AHSFDLKJH498YSAFDKJH

