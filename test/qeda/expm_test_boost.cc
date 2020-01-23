#include <qeda/expm.hpp>
#include <f/timer/timer.hpp>
#include <f/variate_generator/variate_generator.hpp>

#include <complex>
#include <iostream>
#include <fstream>

using namespace boost::numeric::ublas;
typedef matrix<std::complex<float> >  matrix_type;

int counter = 0;

void ff( const matrix_type& cm )
{
    counter += cm.size1();
}

f::variate_generator<float> vg(0.0, 1.0);

const matrix_type rand_matrix( unsigned long m, unsigned long n )
{
    matrix_type ans( m, n );

    for ( unsigned long r = 0; r != m; ++r )
    {
        for ( unsigned long c = 0; c != n; ++c )
        {
            ans( r, c ) = std::complex<float>( vg(), vg() );
        }
    }

    return ans;
}

int main()
{
    unsigned long start = 100;
    unsigned long stride = 100;
    unsigned long end = 2100;

    std::ofstream ofs( "ublas.dat" );

    for ( unsigned long n = start; n != end; n += stride )
    {
        matrix_type const& A = rand_matrix( n, n );
        
        {
            f::timer ft( n );
            ff( expm_pad( A ) );
            const double d = ft;
            ofs << n << "  " <<  d << "\n";
        }
    }

    ofs.close();

    std::cout << counter << "\n";




    return 0;
}

