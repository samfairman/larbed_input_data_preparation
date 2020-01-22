#include <f/matrix/matrix.hpp>
#include <cmath>
#include <vector>

int main()
{
    double const pi = 3.1415926535897932384626433;
    unsigned long const tilts = 1024;
    double const radius = 1.0;
    double const grid = std::sqrt(pi) * radius / ( std::sqrt( static_cast<double>(tilts) ) );
    long const dim = static_cast<unsigned long>(radius / grid) + 1;

    std::vector<double> tx;
    std::vector<double> ty;
    std::vector<long> sx;
    std::vector<long> sy;

    long const dim_2 = dim / 2;
    long const dim_4 = dim_2 / 2;

    for ( long ix = -dim; ix != dim+1; ++ix )
        for ( long iy = -dim; iy != dim+1; ++iy )
        {
            // if ( ix == 0 && iy == 0 ) continue;
            // if ( ix == -dim_2 && iy == 0 ) continue;
            // if ( ix == dim_2 && iy == 0 ) continue;
            // if ( ix == 0 && iy == -dim_2 ) continue;
            // if ( ix == 0 && iy == dim_2 ) continue;
            // if ( ix == dim_2 && iy == dim_2 ) continue;
            // if ( ix == -dim_2 && iy == dim_2 ) continue;
            // if ( ix == dim_2 && iy == -dim_2 ) continue;
            // if ( ix == -dim_2 && iy == -dim_2 ) continue;

            double const x = static_cast<double>(ix) * grid;
            double const y = static_cast<double>(iy) * grid;
            if ( x*x + y*y > radius*radius ) continue;
            tx.push_back( x );
            ty.push_back( y );

            sx.push_back( ix );
            sy.push_back( iy );
        }

    f::matrix<double> tilt( tx.size(), 2 );

    std::copy( tx.begin(), tx.end(), tilt.col_begin(0) );
    std::copy( ty.begin(), ty.end(), tilt.col_begin(1) );

    tilt.save_as( "1024_tilt.txt" );


    f::matrix<double> tilt_sig( sx.size(), 2 );
    std::copy( sx.begin(), sx.end(), tilt_sig.col_begin(0) );
    std::copy( sy.begin(), sy.end(), tilt_sig.col_begin(1) );
    tilt_sig.save_as( "1024_tilt_sig.txt" );

    return 0;
}

