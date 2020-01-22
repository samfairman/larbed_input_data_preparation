#include <f/beam/beam.hpp>

#include <iostream>

int main()
{
    ////f::make_full_beam_list( "./testdata/sto_accr.new_balanced/beams.txt" );
    //
    //f::make_full_beam_list( "./testdata/txt/beam.txt" );
    //f::make_full_beam_list( "./testdata/test_Sam/beam_selected_121.txt" );


    {
        //beam file:
        // [index] h k l

        int const limit = 10;

        unsigned long counter = 0;
        for ( int h = -limit; h <= limit; ++h )
            for ( int k = -limit; k <= limit; ++k )
                if ( h*h + k*k <= limit*limit )
                    ++counter;

        f::matrix<int> beam{ counter, 4 };

        counter = 0;
        for ( int h = -limit; h <= limit; ++h )
            for ( int k = -limit; k <= limit; ++k )
            {
                if ( h*h + k*k > limit*limit ) continue;

                beam[counter][0] = counter;
                beam[counter][1] = h;
                beam[counter][2] = k;
                beam[counter][3] = 0;

                std::cout << "Generating " << counter << " - " << h << ", " << k << ", 0\n";

                ++counter;
            }

        beam.save_as( "./testdata/beam/beam.txt" );
        f::make_full_beam_list( "./testdata/beam/beam.txt" );
    }


    return 0;
}

