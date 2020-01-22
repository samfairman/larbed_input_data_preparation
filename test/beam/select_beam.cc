#include <f/matrix/matrix.hpp>
#include <map>
#include <vector>

using namespace f;

struct pair
{
    long x;
    long y;
    pair( long x_, long y_ ) : x(x_), y(y_) {}
};

bool operator == ( pair const& lhs, pair const& rhs )
{
    return (lhs.x == rhs.x) && (lhs.y == rhs.y);
}

bool operator < ( pair const& lhs, pair const& rhs )
{
    if ( lhs.x < rhs.x ) return true;
    if ( lhs.x > rhs.x ) return false;
    return lhs.y < rhs.y;
}

int main()
{
    matrix<double> intensity;
    matrix<long int> beam;

    intensity.load( "matrix/intensity/SrTiO3.txt" );
    beam.load( "matrix/beam/SrTiO3.txt" );

    std::map<pair, double> mpd;

    matrix<double> sum_intensity{ intensity.row(), 1 };
    for ( unsigned long r = 0; r != sum_intensity.row(); ++r )
    {
        sum_intensity[r][0] = std::accumulate( intensity.row_begin(r), intensity.row_end(r), 0.0 );
        long const x = beam[r][1];
        long const y = beam[r][2];
        mpd[pair{x,y}] = sum_intensity[r][0];
    }

    matrix<double> ug;
    ug.load( "matrix/ug/SrTiO3.txt" );
    std::map<pair, double> mpu;
    for ( unsigned long r = 0; r != ug.row(); ++r )
        mpu[pair{beam[r][1], beam[r][2]}] = ug[r][0];

    std::vector<double> new_intensity;
    std::vector<long> new_beam;

    unsigned long counter = 0;
    for ( unsigned long r = 0; r != sum_intensity.row(); ++r )
    {
        long const x = beam[r][1];
        long const y = beam[r][2];
        double const current = mpd[pair{x,y}];

        double const upper = mpd[pair{x,y+1}];
        double const lower = mpd[pair{x,y-1}];
        double const left = mpd[pair{x-1,y}];
        double const right = mpd[pair{x+1,y}];

        if ( ( upper > current ) || ( lower > current ) || ( left > current ) || ( right > current ) )
            mpd[pair{x,y}] = -1.0;
        else
        {
            new_beam.push_back( counter ); new_beam.push_back( x ); new_beam.push_back( y ); new_beam.push_back( 0 );
            for ( unsigned long c = 0; c != intensity.col(); ++c )
                new_intensity.push_back( intensity[r][c] );

            ++counter;
        }
    }

    for ( auto& elem : mpd )
    {
        std::cout << elem.first.x << "\t\t" << elem.first.y << " \t\t " << elem.second << "\t\t";
        std::cout << mpu[elem.first] << "\n";
    }

    std::cout << counter << "\tBeams selected.\n";

    matrix<double> intensity_{ counter, intensity.col() };
    std::copy( new_intensity.begin(), new_intensity.end(), intensity_.begin() );
    intensity_.save_as( "intensity_.txt" );

    matrix<long> beam_{ counter, 4 };
    std::copy( new_beam.begin(), new_beam.end(), beam_.begin() );
    beam_.save_as( "beam_.txt" );

    return 0;
}

