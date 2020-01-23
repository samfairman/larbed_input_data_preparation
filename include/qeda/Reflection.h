#ifndef RDFSON4OHU9ASFDLKJ498HSDFKLJANSFD9U4HDAFLSUK49HUAFDLKJH4E9IUHASF439UHFAS
#define RDFSON4OHU9ASFDLKJ498HSDFKLJANSFD9U4HDAFLSUK49HUAFDLKJH4E9IUHASF439UHFAS

#include <qeda/DataTypes.h>
#include <vector>
#include <iostream>

class Reflection
{

    public:
        int h, k, l, s; // unsigned 4-indices
        int mh, mk, ml; // Miller indices
        ftype gx, gy, gz;
        ftype ksg2;
        unsigned int masterIndex;
        // vector<unsigned int> indX, indY;

        friend std::ostream& operator << ( std::ostream& os, Reflection const& rf )
        {
            os << "Reflection:\n";
            os << "(h,k,l,s) = (" << rf.h << "," << rf.k << "," << rf.l << "," << rf.s << ")\n"; 
            os << "(mh,mk,ml) = (" << rf.mh << "," << rf.mk << "," << rf.ml << ")\n"; 
            os << "(gx,gy,gz) = (" << rf.gx << "," << rf.gy << "," << rf.gz << ")\n"; 
            os << "ksg2 = " << rf.ksg2 << "\n";
            os << "index = " << rf.masterIndex << "\n";
            return os;
        }

        Reflection( int mh_, int mk_, int ml_ ) : mh( mh_ ), mk( mk_ ), ml( ml_ )
        {
		    ComputeHKLSfromMiller();
        }

        Reflection( void )
        {
            gx = 0;
            gy = 0;
            gz = 0;
			h  = 0;
			k  = 0;
			l  = 0;
			s  = 0; 
			mh = 0;
			mk = 0;
			ml = 0; 
			ksg2  = 0;
			masterIndex = 0;
        }

        Reflection( ftype x, ftype y, ftype z )
        {
            gx = x;
            gy = y;
            gz = z;
        }

		void copy(Reflection &G) {
			h  = G.h;
			k  = G.k;
			l  = G.l;
			s  = G.s; 
			mh = G.mh;
			mk = G.mk;
			ml = G.ml; 
			gx = G.gx;
			gy = G.gy;
			gz = G.gz;
			ksg2  = G.ksg2;
			masterIndex = G.masterIndex;
		}

        ftype GetLength2()
        {
            return gx * gx + gy * gy + gz * gz;
        }

        void ComputeMillerIndices( void )
        {
            mh = ( s & 4 ) ? h : -h;
            mk = ( s & 2 ) ? k : -k;
            ml = ( s & 1 ) ? l : -l;
        }

		void ComputeHKLSfromMiller() 
        {
            s = ( mh > 0 ? 4 : 0 ) + ( mk > 0 ? 2 : 0 ) + ( ml > 0 ? 1 : 0 );
            h = abs( mh );
            k = abs( mk );
            l = abs( ml );
		}

        void AssignFromDifference( Reflection *b1, Reflection *b2 )
        {
            mh = b1->mh - b2->mh;
            mk = b1->mk - b2->mk;
            ml = b1->ml - b2->ml;
			ComputeHKLSfromMiller();
        }

        void PrintReflection( void )
        {
            printf( "[%3d %3d %3d] = [%2d %2d %2d %2d]: (%.2f %.2f %.2f)\n", mh, mk, ml, h, k, l, s, gx, gy, gz );
        }

        ~Reflection( void )
        {
        }

};

#endif//RDFSON4OHU9ASFDLKJ498HSDFKLJANSFD9U4HDAFLSUK49HUAFDLKJH4E9IUHASF439UHFAS

