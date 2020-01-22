#include <f/matrix/matrix.hpp>
#include <map>

int main()
{
    using namespace f;

    matrix<double> intensity;
    matrix<int> beam;

    intensity.load( "matrix/intensity/SrTiO3.txt" );
    //beam.load( "matrix/beam/SrTiO3.txt" );
    beam.load( "new_beam.txt" );

    for ( unsigned long c = 0; c != intensity.col(); ++c )
    {
        double const sum = std::accumulate( intensity.col_begin(c), intensity.col_end(c), 0.0 );
        std::for_each( intensity.col_begin(c), intensity.col_end(c), [sum](double& x){ x/=sum; } );
    }

    std::map<double, int> smap;

    for ( int r = 0; r != intensity.row(); ++r )
    {
        double const sum = std::accumulate( intensity.row_begin(r), intensity.row_end(r), 0.0 );
        smap[sum] = r;
    }

    for ( auto& elem : smap )
    {
        std::cout << beam[elem.second][1] << " " << beam[elem.second][2] << " -- ";
        std::cout << elem.second << " \t: \t " << elem.first << "\n";
    }

    return 0;
}
