#ifndef MDET_HPP_INCLUDED_SDOFJIWEOUIJASFLDKJSAFLJKASFOIJSAFDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDF
#define MDET_HPP_INCLUDED_SDOFJIWEOUIJASFLDKJSAFLJKASFOIJSAFDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDF

#include <f/matrix/matrix.hpp>

namespace feng
{

    template<typename T, std::size_t D, typename A>
    T const det( const matrix<T,D,A>& m )
    {
        return m.det();
    }

}//namespace feng

#endif//_DET_HPP_INCLUDED_SDOFJIWEOUIJASFLDKJSAFLJKASFOIJSAFDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDF
