#ifndef BREFLAFDOPIN4OP9HUAFDKLASDFJNVNBWEORGHU84EKLHJBSFDLKJHBFASD9IUG4EKHJSABD
#define BREFLAFDOPIN4OP9HUAFDKLASDFJNVNBWEORGHU84EKLHJBSFDLKJHBFASD9IUG4EKHJSABD

#include <vector>
#include <qeda/Reflection.h>
#include <iterator>
#include <algorithm>

class ReflectionArray
{
    public:
        long int nElements;
        std::vector< std::vector< std::vector< std::vector <unsigned int> > > > beamIndex;
        std::vector <Reflection> beams;

        /*
        friend std::ostream& operator << ( std::ostream& os, ReflectionArray const& rhs )
        {
            os << "Reflection Array:\n";
            os << "--Beams:\n";
            std::copy( beams.begin(), beams.end(), std::ostream_iterator<Reflection>(os, "\n") );
            std::cout << "\n";
        }
        */

        ReflectionArray( void )
        {
            Reflection g;
            // Allocate memory for the first structure factor which is U(0,0,0) = U_0:
            beamIndex.resize( 1 );
            beamIndex[0].resize( 1 );
            beamIndex[0][0].resize( 1 );
            beamIndex[0][0][0].resize( 8, 0 );
            g.h = 0;
            g.k = 0;
            g.l = 0;
            g.s = 0;
            g.mh = 0;
            g.mk = 0;
            g.ml = 0;
            g.ksg2 = 0;
            beams.push_back( g );
            nElements = 1;
        }

        unsigned int AddBeam( Reflection *b )
        {
            unsigned int offset;
            int h = b->h;
            int k = b->k;
            int l = b->l;
            int s = b->s;
            // First, we need to see if this element is already present
            //
            // If the element is not present, create it, otherwise add to the list of indices
            // We could use an array with indices abs(h) and abs(k) and abs(l)
            if ( h >= beamIndex.size() )
                beamIndex.resize( h + 1 );
            if ( k >= beamIndex[h].size() )
                beamIndex[h].resize( k + 1 );
            if ( l >= beamIndex[h][k].size() )
                beamIndex[h][k].resize( l + 1 );
            if ( beamIndex[h][k][l].size() < 8 )
                beamIndex[h][k][l].resize( 8, 0 );
            offset = beamIndex[h][k][l][s];
            if ( ( offset == 0 ) & ( h + k + l > 0 ) )
            {
                // add another beam to the list and increment its size;
                beams.push_back( *b );
                offset = beams.size() - 1;
                nElements++;
                beamIndex[h][k][l][s] = offset;
            }
            // printf("nElem %d %d (%d %d %d %d)\n",nElements, offset,h,k,l,s);
            return offset;
        }

        ~ReflectionArray( void )
        {
        }
};

#endif//_REFLAFDOPIN4OP9HUAFDKLASDFJNVNBWEORGHU84EKLHJBSFDLKJHBFASD9IUG4EKHJSABD

