#ifndef _ACCUMULATE_HPP_INCLUDED_FSONASFPOI3JOIUASFHDLKJASNF498HIAFDSJKN498HUF3F
#define _ACCUMULATE_HPP_INCLUDED_FSONASFPOI3JOIUASFHDLKJASNF498HIAFDSJKN498HUF3F

#include <cuda.h>

#include <device/algorithm/copy_n.hpp>
#include <device/config/threads_per_block.hpp>
#include <device/iterator.hpp>
#include <device/typedef.hpp>
#include <device/utility/cuda_assert.hpp>
#include <device/utility/device_to_host.hpp>

namespace device
{

namespace accumulate_impl_sfdoinasdflkjnasfdoijnsdfoijneouibafdkjbfdef
{

    template<typename InputIterator, typename Distance, typename OutputIterator>
    __global__
    void _accumulate_n( InputIterator g_idata, const Distance n, OutputIterator g_odata )
    {
        typedef typename device::iterator_traits<InputIterator>::value_type T;
        extern __shared__ T sdata[];

        // perform g_idata_first level of reduction,
        // reading from global memory, writing to shared memory
        const device::size_t tid = threadIdx.x;
        //const device::size_t block_size = device::threads_per_block::value;
        const device::size_t block_size = blockDim.x;
        const device::size_t gridSize = block_size * gridDim.x * 2;
        const device::int32_t n_is_pow_2 = !(n&(n-1));
        device::size_t i = blockIdx.x * block_size * 2 + threadIdx.x;

        T sum(0);

        // we reduce multiple elements per thread.  The number is determined by the
        // number of active thread blocks (via gridDim).  More blocks will result
        // in a larger gridSize and therefore fewer elements per thread
        while (i < n)
        {
            sum += *(g_idata+i);

            // ensure we don't read out of bounds -- this is optimized away for powerOf2 sized arrays
            if (n_is_pow_2 || i + block_size < n)
                sum += *(g_idata+i+block_size);

            i += gridSize;
        }

        // each thread puts its local sum into shared memory
        sdata[tid] = sum;
        __syncthreads();

        // do reduction in shared mem
        if (block_size >= 1024)
        {
            if (tid < 512)
                sdata[tid] = sum = sum + sdata[tid + 512];

            __syncthreads();
        }

        if (block_size >= 512)
        {
            if (tid < 256)
                sdata[tid] = sum = sum + sdata[tid + 256];

            __syncthreads();
        }

        if (block_size >= 256)
        {
            if (tid < 128)
                sdata[tid] = sum = sum + sdata[tid + 128];

            __syncthreads();
        }

        if (block_size >= 128)
        {
            if (tid <  64)
                sdata[tid] = sum = sum + sdata[tid +  64];

            __syncthreads();
        }

        if (tid < 32)
        {
            // now that we are using warp-synchronous programming (below)
            // we need to declare our shared memory volatile so that the compiler
            // doesn't reorder stores to it and induce incorrect behavior.
            volatile T *smem = sdata;

            if (block_size >=  64)
                smem[tid] = sum = sum + smem[tid + 32];

            if (block_size >=  32)
                smem[tid] = sum = sum + smem[tid + 16];

            if (block_size >=  16)
                smem[tid] = sum = sum + smem[tid +  8];

            if (block_size >=   8)
                smem[tid] = sum = sum + smem[tid +  4];

            if (block_size >=   4)
                smem[tid] = sum = sum + smem[tid +  2];

            if (block_size >=   2)
                smem[tid] = sum = sum + smem[tid +  1];
        }

        // write result for this block to global mem
        if (tid == 0)
            *(g_odata+blockIdx.x) = sdata[0];
    }

    template<class InputIt, class T>
    T host_accumulate(InputIt first, InputIt last, T value)
    {
        while ( first != last )
            value += *first++;

        return value;
    }

    template<typename Device_Iterator, typename T>
    T device_to_host_accumulate( Device_Iterator d_first, Device_Iterator d_last, T value )
    {
        const device::size_t n = device::distance( d_first, d_last );

        if ( !!n )
        {
            T* h_first = new T[n];

            device::device_to_host( d_first, d_last, h_first );

            value = host_accumulate( h_first, h_first+n, value );
            
            delete[] h_first;
        }

        return value;
    }

    template<typename InputIterator, typename Distance, typename T>
    T accumulate_n( InputIterator g_idata_first, const Distance n, const T& init, device::random_access_iterator_tag )
    {
        const device::size_t threads = device::threads_per_block::value;
        const device::size_t blocks = ( n + threads - 1 ) / threads;
        const device::size_t shared_memory = (threads <= 32) ? 2 * threads * sizeof(T) : threads * sizeof(T);

        T* global_accumulate;
        cuda_assert( cudaMalloc( reinterpret_cast<void**>(&global_accumulate), blocks * sizeof(T) ) );

        _accumulate_n<<<blocks, threads, shared_memory>>>( g_idata_first, n, global_accumulate );

        const T ans =   blocks < threads ?  
                        device_to_host_accumulate( global_accumulate, global_accumulate+blocks, init ) :
                        accumulate_n( global_accumulate, blocks, init, device::random_access_iterator_tag() );

        cuda_assert( cudaFree( global_accumulate ) );

        return ans;
    }
/*
    template<typename InputIterator, typename Distance, typename T, typename Function>
    T accumulate_n_f( InputIterator g_idata_first, const Distance n, const T& init, Function f, device::random_access_iterator_tag )
    {
        T* f_idata_first;
        cuda_assert( cudaMalloc( reinterpret_cast<void**>(&f_idata_first), n * sizeof(T) ) );
        device::transform( g_idata_first, g_idata_first+n, f_idata_first, f );
        const T ans = accumulate_n( f_idata_first, n, init, device::random_access_iterator_tag() );
        cuda_assert( cudaFree( f_idata_first ) );
        return ans;
    }
*/
}//namespace accumulate_impl_sfdoinasdflkjnasfdoijnsdfoijneouibafdkjbfdef

    template<typename InputIterator, typename T> __device__ 
    T kernel_accumulate( InputIterator first, InputIterator last, T init )
    {
        while ( first != last )
            init += *(first++);
        return init;
    }

    template<typename InputIterator, typename T>
    T accumulate( InputIterator g_idata_first, InputIterator g_idata_last, const T& init )
    {
        using namespace accumulate_impl_sfdoinasdflkjnasfdoijnsdfoijneouibafdkjbfdef;
        typedef typename device::iterator_traits<InputIterator>::iterator_category iterator_category;
        return accumulate_n( g_idata_first, g_idata_last-g_idata_first, init, iterator_category() );
    }
/*
    template<typename InputIterator, typename T, typename Function>
    T accumulate( InputIterator g_idata_first, InputIterator g_idata_last, const T& init, Functon f )
    {
        using namespace accumulate_impl_sfdoinasdflkjnasfdoijnsdfoijneouibafdkjbfdef;
        typedef typename device::iterator_traits<InputIterator>::iterator_category;
        return accumulate_n_f( g_idata_first, g_idata_last-g_idata_first, init, f, iterator_category() );
    }
*/




}//namespace device

#endif//_ACCUMULATE_HPP_INCLUDED_FSONASFPOI3JOIUASFHDLKJASNF498HIAFDSJKN498HUF3F

