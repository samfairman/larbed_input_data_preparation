#ifndef NDPTCEIWGYMHBKYTOFGMGNDCRFYSEWHNSECWVDBUQBPXQBSQVRGNINMYKLRFHFULHLRCSXAXJ
#define NDPTCEIWGYMHBKYTOFGMGNDCRFYSEWHNSECWVDBUQBPXQBSQVRGNINMYKLRFHFULHLRCSXAXJ

namespace numeric
{
    template< typename Matrix, typename Type, typename Allocator >
    struct matrix_operator_minus
    {
        typedef Matrix  zen_type;
        typedef Type    value_type;

        friend zen_type const operator - ( zen_type const& zen)
        {
            zen_type ans{ zen };
            std::for_each( ans.begin(), ans.end(), []( auto& v ){ v = -v; } );
            return ans;
        }

        friend zen_type const operator - ( zen_type&& zen)
        {
            zen_type ans{ zen };
            std::for_each( ans.begin(), ans.end(), []( auto& v ){ v = -v; } );
            return ans;
        }

    };//struct matrix_operator_minus


}//namespace numeric

#endif//NDPTCEIWGYMHBKYTOFGMGNDCRFYSEWHNSECWVDBUQBPXQBSQVRGNINMYKLRFHFULHLRCSXAXJ

