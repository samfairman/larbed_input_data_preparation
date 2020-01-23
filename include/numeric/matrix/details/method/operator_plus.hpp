#ifndef ILYILKAFTUMIFNQRWBRGPFQGWUTGUBRMDWEKNLWFXCQMQWRXVQLWWVFVHCEAVOIOWKRSWSYXE
#define ILYILKAFTUMIFNQRWBRGPFQGWUTGUBRMDWEKNLWFXCQMQWRXVQLWWVFVHCEAVOIOWKRSWSYXE

namespace numeric
{
    template< typename Matrix, typename Type, typename Allocator >
    struct matrix_operator_plus
    {
        typedef Matrix zen_type;

        friend zen_type const operator + ( zen_type const& zen)
        {
            return zen;
        }

        friend zen_type const operator + ( zen_type&& zen)
        {
            return zen;
        }

    };//struct matrix_operator_plus


}//namespace numeric

#endif//ILYILKAFTUMIFNQRWBRGPFQGWUTGUBRMDWEKNLWFXCQMQWRXVQLWWVFVHCEAVOIOWKRSWSYXE

