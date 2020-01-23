#ifndef _BIND1ST_HPP_INCLUDED_SDOIASFO9HU49A8UFHKJSHDBFASFJNBVIUHFD87H4KJHASF873
#define _BIND1ST_HPP_INCLUDED_SDOIASFO9HU49A8UFHKJSHDBFASFJNBVIUHFD87H4KJHASF873

#include <device/functional/unary_function.hpp>

namespace device
{
    template< typename Operation >
    struct binder1st
    : public unary_function<typename Operation::second_argument_type, typename Operation::result_type>
    {   
    protected:
      Operation op; 
      typename Operation::first_argument_type value;
    public:
      __device__ __host__
      binder1st(const Operation& f, const typename Operation::first_argument_type& v) : op(f), value(v) 
      {}

      __device__ __host__
      typename Operation::result_type
      operator()(const typename Operation::second_argument_type& v) const
      { 
          return op(value, v); 
      }
/*
      __device__
      typename Operation::result_type
      operator()(typename Operation::second_argument_type& v) const
      { 
          return op(value, v); 
      }

      __device__
      typename Operation::result_type
      operator()(typename Operation::second_argument_type v) const
      { 
          return op(value, v); 
      }
*/
    };//struct binder1st

    template <class Operation, class Value_Type>
    __device__ __host__
    inline binder1st<Operation>
    bind1st(const Operation& f, const Value_Type& v)
    {   
      typedef typename Operation::first_argument_type first_argument_type;
      return binder1st<Operation>(f, first_argument_type(v));
    }

}//namespace device

#endif//_BIND1ST_HPP_INCLUDED_SDOIASFO9HU49A8UFHKJSHDBFASFJNBVIUHFD87H4KJHASF873

