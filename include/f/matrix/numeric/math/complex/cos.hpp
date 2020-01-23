#ifndef KXPJBLDYDXHKWNJCHKXBTSRVLYHVVFJJMENBGXOGWLPPTDGUPHVBDMRALLUYFFKWBUUGSFUMT
#define KXPJBLDYDXHKWNJCHKXBTSRVLYHVVFJJMENBGXOGWLPPTDGUPHVBDMRALLUYFFKWBUUGSFUMT

#include <f/matrix/impl/matrix_impl.hpp>
#include <f/algorithm/for_each.hpp>

#include <cstddef>
#include <complex>

namespace f
{

    template<typename T, std::size_t D, typename A>
    const matrix<std::complex<T>,D, A> cos( const matrix<std::complex<T>,D,A>& m )
    {
        matrix<std::complex<T>,D,A> ans( m.row(), m.col() );

        std::for_each( m.begin(), m.end(), ans.begin(), []( const std::complex<T>& c, std::complex<T>& r ) { r = std::cos(c); } );

        return ans;
    }

}//namespace f

#endif//KXPJBLDYDXHKWNJCHKXBTSRVLYHVVFJJMENBGXOGWLPPTDGUPHVBDMRALLUYFFKWBUUGSFUMT

