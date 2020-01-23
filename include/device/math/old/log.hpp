#ifndef _LOG_HPP_INCLUDED_FDDSPIOSAF98Y39OU8AHF984YAIFUH498YAFSDIOUH498YSFADKUHF
#define _LOG_HPP_INCLUDED_FDDSPIOSAF98Y39OU8AHF984YAIFUH498YAFSDIOUH498YSFADKUHF

#include <device/math/pi.hpp>
#include <device/math/sqrt.hpp>

namespace device
{
    namespace log_impl_private_sdinsapoij4oijasfdo4uiafjh4098jiafjiafj
    {
        // Ref:
        // Practically Fast Multiple-Precision Evaluation of log(x)
        // Journal of Information Processing, Vol. 4, No. 4, 1982
        template<typename Type>
        __device__ __host__
        Type log_impl_( const Type q, const Type _2_p, const Type _2_p2 )
        {
            typedef Type value_type;
            value_type t0(q);
            value_type t3(q);
            value_type qnn(q);
            value_type q2(q*q);
            value_type q2n1(q2*q);
            
            for ( device::size_t i = 0; ; ++i )
            {
                qnn *= q2n1;
                if ( qnn <= _2_p ) break;

                t0 += (i&1) ? qnn : -qnn;
                q2n1 *= q2;
            }

            t0 = value_type(1) - t0 - t0;
            t3 = value_type(1) - t3 - t3;
            value_type A(1);
            value_type t0_t3( t0/t3 );
            value_type t0_t3_2( t0_t3 * t0_t3 );
            value_type B( sqrt<value_type>()((value_type(1)+t0_t3_2)*(value_type(1)-t0_t3_2)) );
            value_type ab(0);

            for (;;)
            {
                if ( A > _2_p2 + B ) break;
                
                ab = ( A + B ) / value_type(2);
                B = sqrt<value_type>()(A*B);
                A = ab;
            }

            A = ( A + B ) / value_type(2);

            return ( A * t3 * t3 ) / pi<value_type>()();
        }

        template<typename Type>
        __device__ __host__
        Type log_impl( const Type q, const Type _2_p, const Type _2_p2 )
        {
            typedef Type value_type;

            const value_type log_e_2 =  0.693147180559945309417232121458176568L; 
    
            value_type j(0);

            value_type q_(q);

            while ( q_ < value_type(0.01 ) )
            {
                q_ *= value_type(2);
                j -= value_type(1);
            }

            while ( q_ > value_type(0.1) )
            {
                q_ /= value_type(2);
                j += value_type(1);
            }

            return log_impl_( q_, _2_p, _2_p2 ) + j * log_e_2;
        }

    }//namespace log_impl_private_sdinsapoij4oijasfdo4uiafjh4098jiafjiafj 


    template< typename Type >
    struct log;

    template<>
    struct log<float>
    {
        typedef float value_type;

        __device__ __host__
        value_type operator()( const value_type q ) const 
        {
            return log_impl_private_sdinsapoij4oijasfdo4uiafjh4098jiafjiafj::
                   log_impl( q, value_type(1.1920928955078125E-7), value_type(3.4526698300124391E-4));
        }
    };//log<float>

    template<>
    struct log<double>
    {
        typedef double value_type;

        __device__ __host__
        value_type operator()( const value_type q ) const 
        {
            return log_impl_private_sdinsapoij4oijasfdo4uiafjh4098jiafjiafj::
                   log_impl( q, value_type(2.22044604925031308085E-16), value_type(1.490116119384765625E-8) );
        }
    };//log<double>

    // TODO: 
    //       complex specializaiton for log here
    template< typename T >
    struct log< device::complex<T> >; 


    template<typename Type>
    struct ln
    {
        typedef Type value_type;

        __device__ __host__
        value_type operator()( const value_type q ) const
        {
            return log<value_type>()(q);
        }
    };//struct ln



}//namespace device

#endif//_LOG_HPP_INCLUDED_FDDSPIOSAF98Y39OU8AHF984YAIFUH498YAFSDIOUH498YSFADKUHF

