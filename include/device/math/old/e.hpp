#ifndef _E_HPP_INCLUDED_DSFPIOJ498AFLKJH49PIJAF0LJK4089UJSAFDKLJ489YASFKLJH498YH
#define _E_HPP_INCLUDED_DSFPIOJ498AFLKJH49PIJAF0LJK4089UJSAFDKLJ489YASFKLJH498YH

namespace device
{
    template<typename Type>
    struct e
    {
        typedef Type value_type;

        __host__ __device__
        value_type operator()() const 
        {
            return static_cast<value_type>(2.718281828459045235360287471352662498L);
        }
    };//struct e

}//namespace device

#endif//_E_HPP_INCLUDED_DSFPIOJ498AFLKJH49PIJAF0LJK4089UJSAFDKLJ489YASFKLJH498YH


