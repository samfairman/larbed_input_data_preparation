#ifndef _MAX_ELEMENT_HPP_INCLUDED_SDOPINJASDP98YUH4LKJFAHPOAHISFKLJ4H098UAFSOIJ4
#define _MAX_ELEMENT_HPP_INCLUDED_SDOPINJASDP98YUH4LKJFAHPOAHISFKLJ4H098UAFSOIJ4 

#include <device/algorithm/copy_n.hpp>
#include <device/config/threads_per_block.hpp>
#include <device/iterator.hpp>
#include <device/typedef.hpp>
#include <device/utility/cuda_assert.hpp>
#include <device/utility/device_to_host.hpp>
#include <device/limits.hpp>

namespace device
{

namespace max_element_impl_sfdoinasdflkjnasfdoijnsdfoijneouibafdkjbfdef
{

    template<typename T>
    __device__ __host__
    T __max( const T lhs, const T rhs )
    {
        if ( lhs > rhs ) return lhs;
        return rhs;
    }

    template<typename InputIterator, typename Distance, typename OutputIterator>
    __global__
    void _max_element_n( InputIterator g_idata, const Distance n, OutputIterator g_odata )
    {
        typedef typename device::iterator_traits<InputIterator>::value_type value_type;
        extern __shared__ value_type sdata[];

        const device::size_t tid = threadIdx.x;
        const device::size_t block_size = blockDim.x;
        const device::size_t gridSize = block_size * gridDim.x * 2;
        const device::int32_t n_is_pow_2 = !(n&(n-1));
        device::size_t i = blockIdx.x * block_size * 2 + threadIdx.x;

        value_type the_max =  device::numeric_limits<value_type>::min();

        while (i < n)
        {
            the_max = __max( *(g_idata+i), the_max );

            if (n_is_pow_2 || i + block_size < n) the_max = __max( the_max, *(g_idata+i+block_size) );

            i += gridSize;
        }

        sdata[tid] = the_max;
        __syncthreads();

        if (block_size >= 1024)
        {
            if (tid < 512)
                sdata[tid] = the_max = __max( the_max , sdata[tid + 512] )

            __syncthreads();
        }

        if (block_size >= 512)
        {
            if (tid < 256)
                sdata[tid] = the_max = __max( the_max, sdata[tid + 256] );

            __syncthreads();
        }

        if (block_size >= 256)
        {
            if (tid < 128)
                sdata[tid] = the_max = __max( the_max, sdata[tid + 128] );

            __syncthreads();
        }

        if (block_size >= 128)
        {
            if (tid <  64)
                sdata[tid] = the_max = __max( the_max, sdata[tid +  64] );

            __syncthreads();
        }

        if (tid < 32)
        {
            volatile value_type *smem = sdata;

            if (block_size >=  64)
                smem[tid] = the_max = __max( the_max, smem[tid + 32] );

            if (block_size >=  32)
                smem[tid] = the_max = __max( the_max, smem[tid + 16] );

            if (block_size >=  16)
                smem[tid] = the_max = __max( the_max, smem[tid +  8] );

            if (block_size >=   8)
                smem[tid] = the_max = __max( the_max, smem[tid +  4] );

            if (block_size >=   4)
                smem[tid] = the_max = __max( the_max, smem[tid +  2] );

            if (block_size >=   2)
                smem[tid] = the_max = __max( the_max, smem[tid +  1] );
        }

        if (tid == 0)
            *(g_odata+blockIdx.x) = sdata[0];
    }

    template<class InputIt, class T>
    T host_max_element(InputIt first, InputIt last, T value)
    {
        while ( first != last )
            value += *first++;

        return value;
    }

    template<typename Device_Iterator, typename T>
    T device_to_host_max_element( Device_Iterator d_first, Device_Iterator d_last, T value )
    {
        const device::size_t n = device::distance( d_first, d_last );

        if ( !!n )
        {
            T* h_first = new T[n];

            device::device_to_host( d_first, d_last, h_first );

            value = host_max_element( h_first, h_first+n, value );
            
            delete[] h_first;
        }

        return value;
    }

    template<typename InputIterator, typename Distance, typename T>
    T max_element_n( InputIterator g_idata_first, const Distance n, const T& init, device::random_access_iterator_tag )
    {
        const device::size_t threads = device::threads_per_block::value;
        const device::size_t blocks = ( n + threads - 1 ) / threads;
        const device::size_t shared_memory = (threads <= 32) ? 2 * threads * sizeof(T) : threads * sizeof(T);

        T* global_max_element;
        cuda_assert( cudaMalloc( reinterpret_cast<void**>(&global_max_element), blocks * sizeof(T) ) );

        _max_element_n<<<blocks, threads, shared_memory>>>( g_idata_first, n, global_max_element );

        const T ans =   blocks < threads ?  
                        device_to_host_max_element( global_max_element, global_max_element+blocks, init ) :
                        max_element_n( global_max_element, blocks, init, device::random_access_iterator_tag() );

        cuda_assert( cudaFree( global_max_element ) );

        return ans;
    }
}//namespace max_element_impl_sfdoinasdflkjnasfdoijnsdfoijneouibafdkjbfdef

    template<typename InputIterator, typename T> __device__
    T kernel_max_element( InputIterator first, InputIterator last, T init )
    {
        while ( first != last )
            init += *(first++);
        return init;
    }

    template<typename InputIterator, typename T>
    T max_element( InputIterator g_idata_first, InputIterator g_idata_last, const T& init )
    {
        using namespace max_element_impl_sfdoinasdflkjnasfdoijnsdfoijneouibafdkjbfdef;
        typedef typename device::iterator_traits<InputIterator>::iterator_category iterator_category;
        return max_element_n( g_idata_first, g_idata_last-g_idata_first, init, iterator_category() );
    }

}//namespace device

#endif//_MAX_ELEMENT_HPP_INCLUDED_SDOPINJASDP98YUH4LKJFAHPOAHISFKLJ4H098UAFSOIJ4 

