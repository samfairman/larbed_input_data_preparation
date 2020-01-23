#ifndef PRDWNTBBOFDAMMJGMXURUYWPHYBPVCLMCWEYOXIPAQNVXMSPNMCECTRCPGRNEDSXEMLPNWMVJ
#define PRDWNTBBOFDAMMJGMXURUYWPHYBPVCLMCWEYOXIPAQNVXMSPNMCECTRCPGRNEDSXEMLPNWMVJ

#include <f/host/cuda/cuda.hpp>
#include <f/host/cuda/cuda_assert.hpp>

#include <cstddef>
#include <type_traits>
#include <memory>
#include <utility>

namespace f
{

    template< typename T >
    struct cuda_allocator;

    template<>
    struct cuda_allocator<void>
    {
        typedef void value_type;
        typedef void* pointer;
        typedef const void* const_pointer;
        template< typename U >
        struct rebind
        {
            typedef cuda_allocator<U> other;
        };
    };

    template< typename T >
    struct cuda_allocator
    {
        typedef std::size_t             size_type;
        typedef std::ptrdiff_t          difference_type;
        typedef T                       value_type;
        typedef value_type*             pointer;
        typedef const value_type*       const_pointer;
        typedef value_type&             reference;
        typedef const value_type&       const_reference;
        template< typename U >
        struct rebind
        {
            typedef cuda_allocator<T> other;
        };
        typedef std::true_type          propagate_on_container_move_assignment;
        typedef std::true_type          is_always_equal;

        typedef cuda_allocator          self_type;
        typedef int                     device_id_type;

        device_id_type                  device_id;

        cuda_allocator( device_id_type const device_id_ ) noexcept : device_id( device_id_ ) {}
        cuda_allocator( self_type const& ) noexcept = default;
        template< typename U >
        cuda_allocator( cuda_allocator<U> const& other ) noexcept : device_id( other.device_id ) {}

        ~cuda_allocator() = default;

        pointer address( reference x ) const noexcept 
        {
            return std::addressof( x );
        }

        const_pointer address( const_reference x ) const noexcept
        {
            return std::addressof( x );
        }

        pointer allocate( size_type const size, cuda_allocator<void>::const_pointer hint = 0 )
        {
            int current_id;
            cuda_assert( cudaGetDevice( std::addressof(current_id) ) );
            if ( current_id != device_id )
                cuda_assert( cudaSetDevice( device_id ) );

            pointer mem;
            //set device
            cuda_assert( cudaMallocManaged( reinterpret_cast<void**>(&mem), sizeof(value_type)*size, 1 ) );
            cuda_assert( cudaMemset( reinterpret_cast<void*>(mem), 0, sizeof(value_type)*size ) );
            cuda_assert( cudaDeviceSynchronize() );
            return mem;
        }

        void deallocate( pointer p, size_type  )
        {
            int current_id;
            cuda_assert( cudaGetDevice( std::addressof(current_id) ) );
            if ( current_id != device_id )
                cuda_assert( cudaSetDevice( device_id ) );

            cuda_assert( cudaDeviceSynchronize() );
            cuda_assert( cudaFree( p ) );
        }

        size_type max_size() const noexcept
        {
            return -1;
        }

        void* operator new( size_type length, void* ptr )
        {
            return ptr;
        }

        template< typename U, typename ... Args >
        void construct( U* p, Args&&... args )
        {
            new(reinterpret_cast<void*>(p)) U(std::forward<Args>(args)...);
        }

        template< typename U >
        void destroy( U* p )
        {
            p -> ~U();
        }
    };

}//namespace f

#endif//PRDWNTBBOFDAMMJGMXURUYWPHYBPVCLMCWEYOXIPAQNVXMSPNMCECTRCPGRNEDSXEMLPNWMVJ

