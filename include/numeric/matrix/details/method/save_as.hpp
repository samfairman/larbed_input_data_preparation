#ifndef CVSAUXEKUMTBKOMNVKRQRMIJPRSMJCIXXTDUTDDVOSTOXSTUPSJSVFQDXYVYEAHXWBHVQSTBT
#define CVSAUXEKUMTBKOMNVKRQRMIJPRSMJCIXXTDUTDDVOSTOXSTUPSJSVFQDXYVYEAHXWBHVQSTBT

#include <cassert>
#include <string>
#include <fstream>

namespace numeric
{
    template<typename Matrix, typename Type, typename Allocator>
    struct matrix_save_as
    {
        typedef Matrix                                                          zen_type;
        typedef std::allocator_traits<Allocator>                                allocator_trait_type;
        typedef typename allocator_trait_type::size_type                        size_type;
        typedef typename allocator_trait_type::value_type                       value_type;

        void save_as( std::string const& file_path ) noexcept
        {
            auto& zen = static_cast<zen_type&>(*this);
            std::ofstream ofs( file_path, std::ios_base::out );
            ofs << zen;
        }

        void save_as( char const* const file_path ) noexcept
        {
            save_as( std::string{file_path} );
        }

    };//struct

}//namespace numeric

#endif//CVSAUXEKUMTBKOMNVKRQRMIJPRSMJCIXXTDUTDDVOSTOXSTUPSJSVFQDXYVYEAHXWBHVQSTBT

