#ifndef BMVRDIKXVUSLLLGRDWOMFQORMFLAUCVQPXESEKTRQKORVYTLNAWFRLAJVWMJDAEDEIVSPHXQJ
#define BMVRDIKXVUSLLLGRDWOMFQORMFLAUCVQPXESEKTRQKORVYTLNAWFRLAJVWMJDAEDEIVSPHXQJ

#include <memory>

namespace numeric
{
    template< typename Matrix, typename Type, typename Allocator >
    struct matrix_resize
    {
        typedef Matrix                                      zen_type;
        typedef std::allocator_traits<Allocator>            allocator_trait_type;
        typedef typename allocator_trait_type::size_type    size_type;

        void resize( size_type row, size_type col )
        {
            auto& zen = static_cast<zen_type&>(*this);
            if ( row*col != zen.size() ) 
            {
                if ( zen.data_ )
                    allocator_trait_type::deallocate( zen.alloc_, zen.data_, zen.size() );
                zen.data_ = allocator_trait_type::allocate( zen.alloc_, row*col );
            }
            zen.row_ = row;
            zen.col_ = col;
        }
    };
}//namespace numeric

#endif//BMVRDIKXVUSLLLGRDWOMFQORMFLAUCVQPXESEKTRQKORVYTLNAWFRLAJVWMJDAEDEIVSPHXQJ

