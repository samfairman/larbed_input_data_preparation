#ifndef DSFAPINASDKJADSFOIUH4OUHAFDKJBVZJNX9084YAHFLAKJSDF209UASFDLKJHASDFKLJCVMA
#define DSFAPINASDKJADSFOIUH4OUHAFDKJBVZJNX9084YAHFLAKJSDF209UASFDLKJHASDFKLJCVMA

#include <memory>

namespace numeric
{
    template< typename Matrix, typename Type, typename Allocator >
    struct matrix_row
    {
        typedef Matrix                                      zen_type;
        typedef std::allocator_traits<Allocator>            allocator_trait_type;
        typedef typename allocator_trait_type::size_type    size_type;

        size_type row() const
        {
            auto const& zen = static_cast<zen_type const&>(*this);
            return zen.row_;
        }
    };//struct matrix_row
}//namespace numeric

#endif//DSFAPINASDKJADSFOIUH4OUHAFDKJBVZJNX9084YAHFLAKJSDF209UASFDLKJHASDFKLJCVMA

