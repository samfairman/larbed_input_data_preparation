#ifndef _IOSTREAM_HPP_INCLUDED_SDOPIJSAFLJ4P9AJIF0LJKSFDA9O4JUAFJKL409E8UJAFLKJ3
#define _IOSTREAM_HPP_INCLUDED_SDOPIJSAFLJ4P9AJIF0LJKSFDA9O4JUAFJKL409E8UJAFLKJ3

#include <iostream>

#include <device/typedef.hpp>
#include <device/complex.hpp>
#include <device/matrix.hpp>
#include <device/vector.hpp>
#include <device/utility/device_to_host.hpp>

namespace device
{
    template< typename T, typename A >
    std::ostream&  operator << ( std::ostream& os, const device::matrix<T,A>& mat )
    {
        const device::size_t r = mat.row();
        const device::size_t c = mat.col();

        T* arr = new T[r*c];
        device::device_to_host( mat.begin(), mat.end(), arr );

        for ( device::size_t r_ = 0; r_ != r; ++ r_ )
        {
            for ( device::size_t c_ = 0; c_ != c; ++c_ )
            {
               os << *(arr+r_*c+c_) << "\t"; 
            }
            os << "\n";
        }

        delete[] arr;

        return os;
    }

    template< typename T, typename A >
    std::ostream&  operator << ( std::ostream& os, const device::vector<T,A>& vec )
    {
        const device::size_t s = vec.size();

        T* arr = new T[s];

        device::device_to_host( vec.begin(), vec.end(), arr );

        for ( device::size_t s_ = 0; s_ != s; ++s_ )
           os << *(arr+s_) << "\t"; 

        os << "\n";

        delete[] arr;

        return os;
    }
    
    template< typename T >
    std::ostream& operator << ( std::ostream& os, const device::complex<T>& c )
    {
        os << "(" << c.real() << ", " << c.imag() << ")";
        return os;
    }

}//namespace device

#endif//_IOSTREAM_HPP_INCLUDED_SDOPIJSAFLJ4P9AJIF0LJKSFDA9O4JUAFJKL409E8UJAFLKJ3

