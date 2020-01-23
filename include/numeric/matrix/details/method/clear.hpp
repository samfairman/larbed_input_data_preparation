#ifndef SFDUHSFDLKJH49YUH8ASFDKLJVCX3UHAFKSJDHASFDKLJSAHDLKSAJFH9847YUHASFJUHSADF
#define SFDUHSFDLKJH49YUH8ASFDKLJVCX3UHAFKSJDHASFDKLJSAHDLKSAJFH9847YUHASFJUHSADF

#include <memory>

namespace numeric
{
    template< typename Matrix, typename Type, typename Allocator >
    struct matrix_clear
    {
        typedef Matrix                                      zen_type;
        typedef std::allocator_traits<Allocator>            allocator_trait_type;
        typedef typename allocator_trait_type::pointer      pointer;

        void clear()
        {
            auto& zen = static_cast<zen_type&>(*this);

            if ( zen.data_ )
            {
                for ( pointer p = zen.data_; p != zen.data_ + zen.size(); ++p ) 
                    zen.alloc_.destroy( p );

                allocator_trait_type::deallocate( zen.alloc_, zen.data_, zen.row_*zen.col_ );
            }
            zen.data_ = nullptr;
            zen.row_ = 0;
            zen.col_ = 0;
        }
    };
}//namespace numeric

#endif//SFDUHSFDLKJH49YUH8ASFDKLJVCX3UHAFKSJDHASFDKLJSAHDLKSAJFH9847YUHASFJUHSADF

