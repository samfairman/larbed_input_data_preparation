#include <f/beam/make_beam.hpp>

int main()
{
    //f::make_beam( std::string{"testdata/txt/beam.txt"}, std::string{"new_beam.txt"} );
    f::make_beam( std::string{"./matrix/beam/Si_5.txt"}, std::string{"./matrix/beam/Si_5_full.txt"} );

    return 0;
}
