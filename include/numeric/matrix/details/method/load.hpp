#ifndef YABSHXRBIJUBXCIXHIPJYJSIAFGYOFWBWBBVPFJYVBVTITLOEXBDCINXCYRKIMRINTEDSOMRE
#define YABSHXRBIJUBXCIXHIPJYJSIAFGYOFWBWBBVPFJYVBVTITLOEXBDCINXCYRKIMRINTEDSOMRE

#include <cassert>
#include <string>
#include <fstream>

namespace numeric
{
    template<typename Matrix, typename Type, typename Allocator>
    struct matrix_load
    {
        typedef Matrix                                                          zen_type;
        typedef std::allocator_traits<Allocator>                                allocator_trait_type;
        typedef typename allocator_trait_type::size_type                        size_type;
        typedef typename allocator_trait_type::value_type                       value_type;

        void load( std::string const& file_path ) noexcept
        {
            auto& zen = static_cast<zen_type&>(*this);
            std::ifstream ifs( file_path, std::ios_base::in );
            ifs >> zen;
        }

        void load( char const* const file_path ) noexcept
        {
            load( std::string{file_path} );
        }

    };//struct

}//namespace numeric

#endif//YABSHXRBIJUBXCIXHIPJYJSIAFGYOFWBWBBVPFJYVBVTITLOEXBDCINXCYRKIMRINTEDSOMRE

