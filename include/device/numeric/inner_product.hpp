#ifndef _INNER_PRODUCT_HPP_INCLUDED_SPOFIASLFDJKH4UH9AFLKJHSAFDKLJHSADIUJHFAFEFD
#define _INNER_PRODUCT_HPP_INCLUDED_SPOFIASLFDJKH4UH9AFLKJHSAFDKLJHSADIUJHFAFEFD

namespace device
{
    template<typename Iterator1, typename Iterator2, typename T>
    __device__ __host__
    T kernel_inner_product( Iterator1 first1, Iterator1 last1, Iterator2 first2, T init )
    {
        while ( first1 != last1 )
            init += (*first1++) * (*first2++);

        return init;
    }

}//namespace device

#endif//_INNER_PRODUCT_HPP_INCLUDED_SPOFIASLFDJKH4UH9AFLKJHSAFDKLJHSADIUJHFAFEFD

