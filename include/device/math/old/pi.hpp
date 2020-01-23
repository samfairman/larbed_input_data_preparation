#ifndef _PI_HPP_INCLUDED_SDPOFINJ49P8ASFLKJ49PHIASFDJHI498HASFDLJHIOFSDFSAOJHI4F
#define _PI_HPP_INCLUDED_SDPOFINJ49P8ASFLKJ49PHIASFDJHI498HASFDLJHIOFSDFSAOJHI4F

namespace device
{
    template<typename Type>
    struct pi
    {
        typedef Type value_type;

        __host__ __device__
        value_type operator()() const 
        {
            return static_cast<value_type>(3.141592653589793238462643383279502884L);
        }

    };//struct pi

}//namespace device

#endif//_PI_HPP_INCLUDED_SDPOFINJ49P8ASFLKJ49PHIASFDJHI498HASFDLJHIOFSDFSAOJHI4F

