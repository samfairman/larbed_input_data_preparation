#ifndef ADIJAFDSOIU4098UADFKLJVAFD9OHLASKDJFAFDSKJH498YADFBNVJHBASFDUYG4FAUIFDFU
#define ADIJAFDSOIU4098UADFKLJVAFD9OHLASKDJFAFDSKJH498YADFBNVJHBASFDUYG4FAUIFDFU

#include <iterator>
#include <memory>

namespace numeric
{
    template<typename Matrix, typename Type, typename Allocator>
    struct matrix_direct_iterator
    {
        typedef Matrix                                                          zen_type;
        typedef std::allocator_traits<Allocator>                                allocator_trait_type;
        typedef typename allocator_trait_type::value_type                       value_type;
        typedef typename allocator_trait_type::pointer                          pointer;
        typedef typename allocator_trait_type::const_pointer                    const_pointer;
        typedef pointer                                                         iterator;
        typedef std::reverse_iterator<iterator>                                 reverse_iterator;
        typedef const_pointer                                                   const_iterator;
        typedef std::reverse_iterator<const_pointer>                            const_reverse_iterator;

        iterator begin()
        {
            zen_type& zen = static_cast<zen_type&>( *this );
            return zen.data();
        }

        iterator end()
        {
            zen_type& zen = static_cast<zen_type&>( *this );
            return zen.data() + zen.size();
        }

        const_iterator begin() const
        {
            zen_type const& zen = static_cast<zen_type const&>( *this );
            return zen.data();
        }

        const_iterator end() const
        {
            zen_type const& zen = static_cast<zen_type const&>( *this );
            return zen.data() + zen.size();
        }

        const_iterator cbegin() const
        {
            zen_type const& zen = static_cast<zen_type const&>( *this );
            return zen.data();
        }

        const_iterator cend() const
        {
            zen_type const& zen = static_cast<zen_type const&>( *this );
            return zen.data() + zen.size();
        }

        reverse_iterator rbegin()
        {
            return reverse_iterator( end() );
        }

        reverse_iterator rend()
        {
            return reverse_iterator( begin() );
        }

        const_reverse_iterator rbegin() const
        {
            return const_reverse_iterator( end() );
        }

        const_reverse_iterator rend() const
        {
            return const_reverse_iterator( begin() );
        }

        const_reverse_iterator crbegin() const
        {
            return const_reverse_iterator( end() );
        }

        const_reverse_iterator crend() const
        {
            return const_reverse_iterator( begin() );
        }

    };//struct matrix_direct_iterator

}//namespace numeric

#endif//ADIJAFDSOIU4098UADFKLJVAFD9OHLASKDJFAFDSKJH498YADFBNVJHBASFDUYG4FAUIFDFU

