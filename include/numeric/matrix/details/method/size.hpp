#ifndef SDPFOIN3LKJNAFSKMNASDFLKJASNFDOIUH4KLJAFDSHLKJASFDHLKAJSFLAKSDJHASLKDFJHA
#define SDPFOIN3LKJNAFSKMNASDFLKJASNFDOIUH4KLJAFDSHLKJASFDHLKAJSFLAKSDJHASLKDFJHA

#include <memory>

namespace numeric
{
    template< typename Matrix, typename Type, typename Allocator >
    struct matrix_size
    {
        typedef Matrix                                      zen_type;
        typedef std::allocator_traits<Allocator>            allocator_trait_type;
        typedef typename allocator_trait_type::size_type    size_type;

        size_type size() const
        {
            auto const& zen = static_cast<zen_type const&>(*this);
            return zen.row() * zen.col();
        }
    };
}//namespace numeric

#endif//SDPFOIN3LKJNAFSKMNASDFLKJASNFDOIUH4KLJAFDSHLKJASFDHLKAJSFLAKSDJHASLKDFJHA

