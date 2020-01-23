#ifndef TJRQMAIDGSWISBEATFOHEMFSBDVQGRSXRWUNFRWMKELMRNHSUJXOATVVRUUXUPFTIRWFIPSBJ
#define TJRQMAIDGSWISBEATFOHEMFSBDVQGRSXRWUNFRWMKELMRNHSUJXOATVVRUUXUPFTIRWFIPSBJ

#include <iterator>

namespace numeric
{
    template< typename Matrix, typename Type, typename Allocator >
    struct matrix_copy
    {
        typedef Matrix                                                  zen_type;
        typedef std::allocator_traits<Allocator>                        allocator_trait_type;
        typedef typename std::allocator_traits<Allocator>::size_type    size_type;

        template< typename InputIterator >
        auto copy( InputIterator it_begin, InputIterator it_end )
        {
            auto& zen = static_cast<zen_type&>(*this);
            return zen.copy_n( it_begin, std::distance( it_begin, it_end) );
        }

    };//struct matrix_copy 

}//namespace numeric

#endif//TJRQMAIDGSWISBEATFOHEMFSBDVQGRSXRWUNFRWMKELMRNHSUJXOATVVRUUXUPFTIRWFIPSBJ

