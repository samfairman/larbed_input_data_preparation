#include <f/beam/make_beam_selection.hpp>

#include <iostream>
#include <vector>

int main()
{
    /*
    f::make_beam_selection( std::string{"testdata/working/intensity.txt"},
                            std::string{"testdata/working/diag.txt"},
                            std::string{"testdata/working/new_beam.txt"},
                            std::string{"testdata/working/selected"} );
                            */
    f::make_beam_selection( std::string{"testdata/working/intensity.txt"},
                            std::string{"testdata/working/diag.txt"},
                            std::string{"testdata/working/new_beam.txt"},
                            std::string{"testdata/working/selected_45"},
                            45UL );


    return 0;
}

