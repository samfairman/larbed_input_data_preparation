#ifndef _SWAP_HPP_INCLUDED_OISNDFOUH3498AHUSFDNKJ48AFSUB489UHAFIKHU48GASHFIUYG4F
#define _SWAP_HPP_INCLUDED_OISNDFOUH3498AHUSFDNKJ48AFSUB489UHAFIKHU48GASHFIUYG4F

namespace device
{
    template<typename T>
    void swap( T& lhs, T& rhs)
    {
        const T tmp( lhs );
        lhs = rhs;
        rhs = tmp;
    }
}//namespace device

#endif//_SWAP_HPP_INCLUDED_OISNDFOUH3498AHUSFDNKJ48AFSUB489UHAFIKHU48GASHFIUYG4F

