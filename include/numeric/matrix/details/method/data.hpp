#ifndef FDASP9NIASDFLKJNADSFLKJASNFDI9U4Y98324987AEW9R08Y2398740YQERWIOUY3978YAWE
#define FDASP9NIASDFLKJNADSFLKJASNFDI9U4Y98324987AEW9R08Y2398740YQERWIOUY3978YAWE

#include <memory>

namespace numeric
{
    template< typename Matrix, typename Type, typename Allocator >
    struct matrix_data
    {
        typedef Matrix                                          zen_type;
        typedef std::allocator_traits<Allocator>                allocator_trait_type;
        typedef typename allocator_trait_type::pointer          pointer;
        typedef typename allocator_trait_type::const_pointer    const_pointer;

        pointer data()
        {
            auto& zen = static_cast<zen_type&>(*this);
            return zen.data_;
        }

        const_pointer data() const
        {
            auto const& zen = static_cast<zen_type const&>(*this);
            return zen.data_;
        }
    };//struct matrix_data
}//namespace numeric

#endif//FDASP9NIASDFLKJNADSFLKJASNFDI9U4Y98324987AEW9R08Y2398740YQERWIOUY3978YAWE

