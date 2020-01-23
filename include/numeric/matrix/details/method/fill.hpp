#ifndef JYVVQFTPQYFUVEHSSBYYXQPSCGGDJJQGFECENMHDCYVVYXGLLPWIKEYDTRTLQGINVGYAFIMGP
#define JYVVQFTPQYFUVEHSSBYYXQPSCGGDJJQGFECENMHDCYVVYXGLLPWIKEYDTRTLQGINVGYAFIMGP

namespace numeric
{
    template< typename Matrix, typename Type, typename Allocator >
    struct matrix_fill
    {
        typedef Matrix                                                  zen_type;
        typedef std::allocator_traits<Allocator>                        allocator_trait_type;
        typedef typename std::allocator_traits<Allocator>::size_type    size_type;
        typedef typename std::allocator_traits<Allocator>::value_type   value_type;

        auto fill( value_type x )
        {
            auto& zen = static_cast<zen_type&>(*this);
            return zen.fill_n( zen.begin(), zen.size(), x );
        }

    };//struct matrix_fill

#if 0
    template< typename Matrix, typename Type >
    struct matrix_fill< Matrix, Type, cuda_allocator >
    {
        typedef Matrix                                                  zen_type;
        typedef std::allocator_traits<Allocator>                        allocator_trait_type;
        typedef typename std::allocator_traits<Allocator>::size_type    size_type;

    };//struct matrix_fill
#endif




}//namespace numeric

#endif//JYVVQFTPQYFUVEHSSBYYXQPSCGGDJJQGFECENMHDCYVVYXGLLPWIKEYDTRTLQGINVGYAFIMGP

