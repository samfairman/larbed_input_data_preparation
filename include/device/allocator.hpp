#ifndef _ALLOCATOR_HPP_INCLUDED_SFDION498HASFKJNH498ASILFUH498YHAFJUH498YF948YFD
#define _ALLOCATOR_HPP_INCLUDED_SFDION498HASFKJNH498ASILFUH498YHAFJUH498YF948YFD

#include <device/iterator.hpp>
#include <device/typedef.hpp>
#include <device/utility/cuda_assert.hpp>
#include <device/algorithm/swap.hpp>
#include <device/algorithm/copy.hpp>

namespace device
{

template< typename Type >
struct allocator
{

    typedef Type                                        value_type;
    typedef allocator                                   self_type;
    typedef value_type*                                 storage_type;
    typedef value_type*                                 pointer;
    typedef const value_type*                           const_pointer;
    typedef value_type&                                 reference;
    typedef value_type                                  const_reference;
    typedef value_type*                                 iterator;
    typedef device::reverse_iterator<iterator>          reverse_iterator;
    typedef const value_type*                           const_iterator;
    typedef device::reverse_iterator<const_iterator>    const_reverse_iterator;
    typedef device::size_t                              size_type;
    typedef device::ptrdiff_t                           difference_type;

public:
    //we don't need specialization for char/wchar etc.
    pointer allocate( size_type const n ) const
    {
        pointer p = 0;
        if (!!n)
            cuda_assert( cudaMalloc( reinterpret_cast<void**>(&p), n ) );
        return p;
    }

    void deallocate( pointer p, const size_type ) const
    {
        cuda_assert( cudaFree( p ) );
    }
/*    
public:
    template<class Typee>
    struct rebind
    {   //qualified name is not allowed
        typedef device::allocator<Typee> other;
    };//rebind
*/    
public:

    explicit allocator(const size_type dims = 0)
    {
        buffer_ = 0;
        items_ = dims;
        const size_type size_to_allocate = alloc_size(items_);
        max_size_ = size_to_allocate / sizeof(value_type);
        buffer_ = allocate( size_to_allocate );
    }

    template<typename Input_Iterator>
    allocator(Input_Iterator begin_, Input_Iterator end_)
    {
        items_ = device::distance(begin_, end_);
        buffer_ = 0;
        const size_type size_to_allocate = alloc_size(items_);

        buffer_ = allocate( size_to_allocate );
        device::copy(begin_, end_, begin());

        max_size_ = size_to_allocate / sizeof(value_type);
    }

    ~allocator()
    {
        deallocate( buffer_, max_size_ );
        buffer_ = 0;
        items_ = 0;
        max_size_ = 0;
    }

public:

    allocator(const self_type& rhs)
    {
        operator = (rhs);
    }
    
    self_type& operator=(const self_type& rhs)
    {
        do_copy(rhs);
        return *this;
    }

    template< typename T >
    allocator(const allocator<T>& rhs)
    {
        operator = <T>(rhs);
    }
    
    template< typename T >
    self_type & operator=(const allocator<T>& rhs)
    {
        do_copy<T>(rhs);
        return *this;
    }

public:

    bool empty()const
    {
        return !items_;
    }

    size_type size()const
    {
        return items_;
    }

public:

    iterator begin()
    {
        return buffer_;
    }

    const_iterator begin()const
    {
        return buffer_;
    }

    const_iterator cbegin()const
    {
        return buffer_;
    }

    iterator end()
    {
        return buffer_ + items_;
    }

    const_iterator end()const
    {
        return buffer_ + items_;
    }

    const_iterator cend()const
    {
        return buffer_ + items_;
    }
    
    reverse_iterator rbegin()
    {
        return reverse_iterator( end() );
    }
    
    const_reverse_iterator rbegin() const
    {
        return const_reverse_iterator( end() );
    }
    
    const_reverse_iterator crbegin() const
    {
        return const_reverse_iterator( end() );
    }
    
    reverse_iterator rend()
    {
        return reverse_iterator( begin() );
    }
    
    const_reverse_iterator rend() const
    {
        return const_reverse_iterator( begin() );
    }
    
    const_reverse_iterator crend() const
    {
        return const_reverse_iterator( begin() );
    }

private:

    template<typename T>
    void do_copy(const allocator<T>& rhs)
    {
        assign( rhs.begin(), rhs.end() );
    }

    void do_copy(const self_type& rhs)
    {
        assign( rhs.begin(), rhs.end() );
    }

public:

    template<typename Input_Iterator>
    void assign(Input_Iterator begin_, Input_Iterator end_)
    {   //length of array source to copy from
        const size_type length = device::distance(begin_, end_);
        //source size is zero/not enough memory? 
        if ( (!!length) && (length > max_size()) )
        {   //if memory has been allocated
            if ( buffer_ )
                //free allocated memory
                deallocate( buffer_, max_size_ );
            //calculate size of memory to be allocated
            const size_type size_to_allocate = alloc_size(length);
            //allocate memory
            buffer_ = allocate( size_to_allocate );
            //update max_size
            max_size_ = size_to_allocate / sizeof(value_type);
        }
        //do data assignment
        device::copy(begin_, end_, begin());
        //update item size
        items_ = length;
    }

public:
    pointer data()
    {
        return buffer_;
    }

    const_pointer data() const
    {
        return buffer_;
    }

public:
    void swap( self_type& other )
    {
        device::swap( buffer_, other.buffer_ );
        device::swap( items_, other.items_ );
        device::swap( max_size_, other.max_size_ );
    }

private:
    size_type alloc_size( const size_type dim ) const 
    {
        const size_type bit_num = 8;
        const size_type bit_mask = (1 << bit_num) - 1;
        size_type ans = dim * sizeof(value_type);
        if ( !!(ans & bit_mask) ) return ans;
        ans >>= bit_num;
        ans += 1;
        ans <<= bit_num;
        return ans;
    }

    size_type max_size() const 
    {
        return  max_size_;
    }

private:
    pointer buffer_;
    size_type items_;
    size_type max_size_;
};//struct allocator 

}//namespace device

#endif//_ALLOCATOR_HPP_INCLUDED_SFDION498HASFKJNH498ASILFUH498YHAFJUH498YF948YFD 
