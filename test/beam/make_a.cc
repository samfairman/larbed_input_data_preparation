#include <f/matrix/matrix.hpp>

#include <complex>

int main()
{
    using namespace f;

    matrix<double> ug;
    ug.load( "./matrix/ug/SrTiO3_selected_full.txt" );

    matrix<unsigned long> ar;
    ar.load( "./matrix/ar/SrTiO3_selected.txt" );

    matrix<std::complex<double> > a( ar.row(), ar.col() );

    for ( unsigned long r = 0; r != a.row(); ++r )
        for ( unsigned long c = 0; c != a.col(); ++c )
        {
            a[r][c] = std::complex<double>{ ug[ar[r][c]][0], ug[ar[r][c]][1] };
        }

    a.save_as( "SrTiO3_selected.txt" );

    return 0;
}
