#ifndef _BIND2ND_HPP_INCLUDED_DSOFUIASLKJ3489HUAFSDIJLK4879HUAIFJDSKHF987Y3IUHFF
#define _BIND2ND_HPP_INCLUDED_DSOFUIASLKJ3489HUAFSDIJLK4879HUAIFJDSKHF987Y3IUHFF

#include <device/functional/unary_function.hpp>

namespace device
{

    template <class Operation>
    struct binder2nd : public unary_function<typename Operation::first_argument_type, typename Operation::result_type>
    {
      Operation op;
      typename Operation::second_argument_type value;

      __device__ __host__
      binder2nd(const Operation& f, const typename Operation::second_argument_type& v) : op(f), value(v) {}

      __device__ __host__
      typename Operation::result_type
      operator()(const typename Operation::first_argument_type& v) const
      { 
          return op(v, value); 
      }
/*
      __device__
      typename Operation::result_type
      operator()(typename Operation::first_argument_type& v) const
      { 
          return op(v, value); 
      }

      __device__
      typename Operation::result_type
      operator()(typename Operation::first_argument_type v) const
      { 
          return op(v, value); 
      }
*/
    };

    template <class Operation, class Value_Type>
    __device__ __host__
    inline binder2nd<Operation>
    bind2nd(const Operation& f, const Value_Type& v)
    {
      typedef typename Operation::second_argument_type second_argument_type;
      return binder2nd<Operation>(f, second_argument_type(v));
    }
}//namespace device 

#endif//_BIND2ND_HPP_INCLUDED_DSOFUIASLKJ3489HUAFSDIJLK4879HUAIFJDSKHF987Y3IUHFF

