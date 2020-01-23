#ifndef NWOOVKDPPOLIADIBGMARYOFVHWUTKHYCHPLFEJAYEHAVKPQYKGWWQGTKPYCPFSOPJDIESRKGC
#define NWOOVKDPPOLIADIBGMARYOFVHWUTKHYCHPLFEJAYEHAVKPQYKGWWQGTKPYCPFSOPJDIESRKGC

#include <numeric/utility/cuda/cuda_assert.hpp>

#include <cuda.h>
#include <cuda_runtime.h>

#include <new>

namespace numeric
{

    template <typename T> 
    struct cuda_allocator
    {
            typedef cuda_allocator                  self_type;
            typedef T                               value_type;
            typedef value_type*                     pointer;
            typedef const value_type*               const_pointer;
            typedef value_type&                     reference;
            typedef const value_type&               const_reference;
            typedef std::size_t                     size_type;
            typedef std::ptrdiff_t                  difference_type;
            typedef int                             device_type;
            typedef true_type                       propagate_on_container_move_assignment;

            device_type                             device_index;

            cuda_allocator( device_type const device_index_ ) : device_index( device_index_ ) {}

            template <typename U>
            struct rebind
            {
                typedef cuda_allocator<U> other;
            };

            ~cuda_allocator() {}

            pointer address( reference x ) const
            {
                return &x;
            }

            const_pointer address( const_reference x ) const
            {
                return &x;
            }

            pointer allocate( size_type n, cuda_allocator<void>::const_pointer hint=0 )
            {
                cuda_assert( cudaSetDevice( device_index ) );
                void* p;
                cuda_assert( cudaMallocManaged( static_cast<void**>(&p), n * sizeof(T), cudaMemAttachGlobal ) );

                if ( !p ) throw std::bad_alloc();

                return static_cast<pointer>( p );
            }

            void deallocate( pointer p, size_type )
            {
                cuda_assert( cudaSetDevice( device_index ) );
                cuda_assert( cudaFree( p ) );
            }

            size_type max_size() const
            {
                return static_cast<size_type>( -1 ) / sizeof( T );
            }

            void construct( pointer p, const value_type& x )
            {
                p = (*this).allocate( 1 );
                *p = x;
            }

            void destroy( pointer p )
            {
                (*this).deallocate( p );
                p = nullptr;
            }

            self_type& operator = ( self_type const& ) = default;
            self_type& operator = ( self_type && ) = default;

            cuda_allocator( self_type const& ) = default;
            cuda_allocator( self_type&& ) = default;

            template <typename U>
            self_type& cuda_allocator( const cuda_allocator<U>& other )
            {
                device_index = other.device_index;
                return *this;
            }

            template <typename U>
            self_type& cuda_allocator( cuda_allocator<U>&& other )
            {
                device_index = other.device_index;
                return *this;
            }

            template <typename U>
            cuda_allocator( const cuda_allocator<U>& other ) : device_index( other.device_index ) {}

            template <typename U>
            cuda_allocator( cuda_allocator<U>&& other ) : device_index( other.device_index ) {}

    };//struct cuda_allocator

    template<> 
    struct cuda_allocator<void>
    {
            typedef void                value_type;
            typedef void*               pointer;
            typedef const void*         const_pointer;
            typedef int                 device_type;

            device_type                 device_index;

            cuda_allocator( device_type device_index_ ) : device_index( device_index_ ) {}

            template <typename U>
            struct rebind
            {
                typedef cuda_allocator<U> other;
            };
    };

    template<> 
    struct cuda_allocator<const void>
    {
            typedef void                value_type;
            typedef void*               pointer;
            typedef const void*         const_pointer;
            typedef int                 device_type;

            device_type                 device_index;

            cuda_allocator( device_type device_index_ ) : device_index( device_index_ ) {}

            template <typename U>
            struct rebind
            {
                typedef cuda_allocator<U> other;
            };
    };

    template <typename T>
    inline bool operator == ( const cuda_allocator<T>& lhs, const cuda_allocator<T>& rhs )
    {
        return lhs.device_index == rhs.device_index;
    }

    template <typename T>
    inline bool operator != ( const cuda_allocator<T>& lhs, const cuda_allocator<T>& rhs )
    {
        return lhs.device_index != rhs.device_index;
    }

}//namespace numeric

#endif//NWOOVKDPPOLIADIBGMARYOFVHWUTKHYCHPLFEJAYEHAVKPQYKGWWQGTKPYCPFSOPJDIESRKGC

