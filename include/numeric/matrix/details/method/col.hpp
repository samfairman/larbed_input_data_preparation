#ifndef QSDF98J5KMNVSFD9UH45LKJAHFDLKJASHFDAKLJH498AFDLKJHAFLKJHAWS98Y4KJHAF98Y44
#define QSDF98J5KMNVSFD9UH45LKJAHFDLKJASHFDAKLJH498AFDLKJHAFLKJHAWS98Y4KJHAF98Y44

#include <memory>

namespace numeric
{
    template< typename Matrix, typename Type, typename Allocator >
    struct matrix_col
    {
        typedef Matrix                                      zen_type;
        typedef std::allocator_traits<Allocator>            allocator_trait_type;
        typedef typename allocator_trait_type::size_type    size_type;

        size_type col() const
        {
            auto const& zen = static_cast<zen_type const&>(*this);
            return zen.col_;
        }
    };//struct matrix_col
}//namespace numeric

#endif//QSDF98J5KMNVSFD9UH45LKJAHFDLKJASHFDAKLJH498AFDLKJHAFLKJHAWS98Y4KJHAF98Y44

