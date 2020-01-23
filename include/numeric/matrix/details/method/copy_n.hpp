#ifndef VSDELTNAVNGTATNLJCTXPPTGFEEVKCRMSICJGYWPYXULCSANAUMIHMUJYUBBNNDGNIXORULVB
#define VSDELTNAVNGTATNLJCTXPPTGFEEVKCRMSICJGYWPYXULCSANAUMIHMUJYUBBNNDGNIXORULVB

#include <algorithm>
#include <cassert>

namespace numeric
{
    template< typename Matrix, typename Type, typename Allocator >
    struct matrix_copy_n
    {
        typedef Matrix                                                  zen_type;
        typedef std::allocator_traits<Allocator>                        allocator_trait_type;
        typedef typename std::allocator_traits<Allocator>::size_type    size_type;

        template< typename InputIterator >
        auto copy_n( InputIterator it, size_type n )
        {
            auto& zen = static_cast<zen_type&>(*this);
            assert( zen.size() >= n );
            return std::copy_n( it, n, zen.begin() );
        }

    };//struct matrix_copy_n

}//namespace numeric

#endif//VSDELTNAVNGTATNLJCTXPPTGFEEVKCRMSICJGYWPYXULCSANAUMIHMUJYUBBNNDGNIXORULVB

