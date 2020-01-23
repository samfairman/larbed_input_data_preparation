#ifndef _AFDPOINLKJSFDI4UHAKLFJNSALDFJKNASLDJKNASDLKNSDLJKN4O0IHAFDLKJNSDAFLJNASFDFSD
#define _AFDPOINLKJSFDI4UHAKLFJNSALDFJKNASLDJKNASDLKNSDLJKN4O0IHAFDLKJNSDAFLJNASFDFSD

#include <iterator>
#include <string>
#include <ctime>
#include <vector>
#include <iostream>
#include <fstream>
#include <boost/assign/std/vector.hpp>
#include <boost/random.hpp>
#include <boost/assert.hpp>
#include <boost/numeric/ublas/io.hpp>
#include <iostream>

#include <qeda/expm.hpp>
#include <qeda/DataTypes.h>
#include <qeda/Crystal.h>
#include <qeda/Reflection.h>
#include <qeda/ReflectionArray.h>
#include <qeda/Ccoef.h>
#include <qeda/HelperFunctions.h>

#include <expm/expm.hpp>

#include <f/matrix/matrix.hpp>

using namespace boost::numeric::ublas;

#if 1
namespace cuda_impl
{
    matrix<std::complex<float> > expm( const matrix<std::complex<float> >& A )
    {
        assert( A.size1() == A.size2() );
        const unsigned long n = A.size1();
        matrix<std::complex<float> > E( n, n );
        f::expm( &( A( 0, 0 ) ), n, &( E( 0, 0 ) ) );
        return E;
    }

}//cuda_impl
#endif

class Pattern
{
    public:
        void dump_a( std::string const& file_path )
        {
            f::matrix<complex_type> a( nBeams, nBeams );
            std::copy( Amatrix.begin(), Amatrix.end(), a.begin() );
            a.save_as( file_path );
        }

        void dump_diag( std::string const& file_path )
        {
            //fill_diag();
            f::matrix<complex_type> a( nBeams, nBeams );
            std::copy( Amatrix.begin(), Amatrix.end(), a.begin() );
            f::matrix<complex_type> d( nBeams, 1 );
            std::copy( a.diag_begin(), a.diag_end(), d.begin() );
            d.save_as( file_path );
        }

        void dump_intensities( std::string const& file_path )
        {
            f::matrix<complex_type> it( nBeams, 1 );
            std::copy( intensities.begin(), intensities.end(), it.begin() );
            it.save_as( file_path );
        }

        void dump_ar( std::string const& file_path )
        {
            f::matrix<unsigned int> ar( nBeams, nBeams );
            std::copy( indexMatrix.begin(), indexMatrix.end(), ar.begin() );
            ar.save_as( file_path );
        }

        //dump_all( "dump", 13 ); for example
        void dump_all( std::string const& path, unsigned long index )
        {
            std::string idx_as_str = std::to_string( index );
            std::string const a_str = path + std::string{"/A_"} + idx_as_str + std::string{".txt"};
            std::string const d_str = path + std::string{"/Diag_"} + idx_as_str + std::string{".txt"};
            std::string const i_str = path + std::string{"/Intensities_"} + idx_as_str + std::string{".txt"};
            std::string const r_str = path + std::string{"/Ar_"} + idx_as_str + std::string{".txt"};
            dump_a( a_str );
            dump_diag( d_str );
            dump_intensities( i_str );
            dump_ar( r_str );
        }

    public:
        // member variables
        std::vector <ftype> zone;
        std::vector <ftype> gx;
        std::vector <ftype> gy;
        std::vector <unsigned int> indexMatrix;
        std::vector <Reflection> beams;
        unsigned int nBeams;  // number of beams in this matrix;
        unsigned int beamCount;  // number of different beams in whole matrix
        ReflectionArray beamList;  // 4-dimensional array of offsets into beams-vector.
        int ikx, iky;
        ftype thetaX_mrad, thetaY_mrad;
        ftype kWave, kx, ky, kz, kn;
       	std::vector <complex_type> trialUg;
		std::vector <std::vector<complex_type> > ugListLocal;
		std::vector <std::vector<complex_type> > ugListGradLocal;
		std::vector <std::vector<unsigned int> > ugListGradCountLocal;  // could be made a bitset in future
		// std::vector <unsigned int> ugListGradCountTempLocal;
		int ugListSize;
		int ugListNumber;  // this defines how many separate lists of Ug values we have (default=3).
		std::vector<double> errVal;
		std::vector<double> scale;
		std::vector<double> newScale;
		int skipCentralBeam;  // indicates whether to include the central beam in the diference measurements
		int dataSetOffset;    // provides a way of swapping different data sets between reflections
		ftype minUg;


		// complex_type Uref;  // This variable will be added to all structure factors in order to make the derivatives better behaved
		std::vector <complex_type> Amatrix;  // Structure factor matrix
        std::vector <ftype> intensities;  // these are the simulated intensities for each of the beams in the list of structure factors
        std::vector <ftype> expIntensities;  // these are the experimental intensities for each of the beams in the list of beams
        std::vector <ftype> kinematicIntensities;  // these are the intensities that best fit the experiment, under the assumption of kinematical scattering
		std::vector <ftype> bArray;  // This will collect the excitation errors for the current combination of beams.
		std::vector <unsigned int> lArray;  // This will collect the matrix indices for the current combination of beams.
		std::vector <unsigned int> llArray;  // This will used during gradient calculation.
		Reflection gmin1,gmin2;   // used for keeping track of the lowest excitation errors.

        // methods
        // Default constructor
        Pattern( void )
        {
            thetaX_mrad = 0.0f;
            thetaY_mrad = 0.0f;
            kx = 0.0f;
            ky = 0.0f;
            kz = 0.0f;
            nBeams      = 0;
            beamCount   = 0;
			bArray.resize(10);
			lArray.resize(10);
			llArray.resize(10);
			ugListSize  = 0;
			ugListNumber = 9;
			dataSetOffset = 0;
			errVal.resize(ugListNumber);
			scale.resize(ugListNumber);
			newScale.resize(ugListNumber);
			for (int j=0;j<ugListNumber;j++) {
				scale[j] = 1e-4;
				newScale[j] = 1e-4;
			}
			skipCentralBeam = 1;
			// Uref = complex_type(0.0f,0.0f);
			minUg = 0e-7f;
        }

        friend
        std::ostream& operator << ( std::ostream& os, Pattern const& pt )
        {
            os << "\nzone: "; for ( unsigned long index = 0; index != pt.zone.size(); ++index ) os << pt.zone[index] << " ";
            os << "\ngx: "; for ( unsigned long index = 0; index != pt.gx.size(); ++index ) os << pt.gx[index] << " ";
            os << "\ngy: "; for ( unsigned long index = 0; index != pt.gy.size(); ++index ) os << pt.gy[index] << " ";
            os << "\nnBeams: " << pt.nBeams;
            os << "\nnbeamCount: " << pt.beamCount;
            os << "\nikx: " << pt.ikx;
            os << "\niky: " << pt.iky;
            os << "\nthetaX_mrad: " << pt.thetaX_mrad;
            os << "\nthetaY_mrad: " << pt.thetaY_mrad;
            os << "\nKWave:" << pt.kWave;
            os << "\nkx:" << pt.kx;
            os << "\nky:" << pt.ky;
            os << "\nkz:" << pt.kz;
            os << "\nkn:" << pt.kn;
            os << "\nugListSize: " << pt.ugListSize;
            os << "\nugListNumber: " << pt.ugListNumber;
            os << "\nskipCentralBeam: " << pt.skipCentralBeam;
            os << "\ndataSetOffset: " << pt.dataSetOffset;
            os << "\nminUg: " << pt.minUg;
            os << "\nAMatrix:\n";

            for ( unsigned long r = 0; r != pt.Amatrix.size(); ++r )
            {
                if ( r % pt.nBeams == 0 )
                    os << "\n";
                os << pt.Amatrix[r] << "\t";
            }


            os << "\nthe beams are \n";
            for ( unsigned long index = 0; index != pt.beams.size(); ++index )
                os << pt.beams[index] << "\n";

            return os;
        }

        Pattern( ftype lambda, ftype tx_mrad, ftype ty_mrad )
        {
			Pattern();
			thetaX_mrad = tx_mrad;
            thetaY_mrad = ty_mrad;

 	    }

        ~Pattern( void )
        {
            //std::cout << "\ndump pattern\n";
            //std::cout << *this << "\n";
        }

		ftype GetGradientScale() {
			ftype scaleAvg = 0;
			for (int j=0;j<ugListNumber;j++) scaleAvg += scale[j];
			return scaleAvg/ugListNumber;
		}

		void SetTilt( ftype lambda, std::vector <ftype> n, ftype tx_mrad, ftype ty_mrad )
        {
            zone.resize( 3, 0 );
            thetaX_mrad = tx_mrad;
            thetaY_mrad = ty_mrad;
            kWave = ( ftype )( 1.0 / lambda ); // amplitude of wave vector
            kx = ( ftype )sin( thetaX_mrad * 1e-3 ) / lambda; // x-component of wave vector
            ky = ( ftype )sin( thetaY_mrad * 1e-3 ) / lambda; // y-component of wave vector
            kz = ( ftype )sqrt( kWave * kWave - kx * kx - ky * ky ); // z-component of wave vector
            kn = kx * n[0] + ky * n[1] + kz * n[2]; // This is the dot-product of wave vector and surface normal.
            //  printf("kn = %g\n",kn);
        }

        void SetZone( std::vector <ftype> zoneNew, std::vector <ftype> gxNew, std::vector <ftype> gyNew )
        {
			// zone.resize(3,0);
            zone.assign( zoneNew.begin(), zoneNew.end() );
            gx.assign( gxNew.begin(), gxNew.end() );
            gy.assign( gyNew.begin(), gyNew.end() );
        }

        void FindBeams( Crystal* Xtal, ftype gCutoff, ftype sgCutoff )
        {
            int h, k, l, sh, sk, sl, s;
            int maxh = 50;
            int maxk = 50;
            int maxl = 50;
            ftype g2, ksg2, k2, gc2,ksg2Cutoff,ksg2_abs;
            ftype zx, zy, zz, thetaX, thetaY, thetaZ;
            Reflection g;

			// initialize the reflections that we want to keep track of the closest beams with large escitation errors:
			gmin1.ksg2 = 100.0f;
			gmin2.ksg2 = 100.0f;

            //std::cout << "[debug]\n";
            //std::cout << "zone - [" << zone[0] << "," << zone[1] << "," << zone[3] << "]\n";

            // Compute the zone axis vector
            g.mh = zone[0];
            g.mk = zone[1];
            g.ml = zone[2];
            // printf("Selecting beams (gCutoff=%g, sgCutoff=%g)\n",gCutoff,sgCutoff);
            // This is the zone-axis vector:
            Xtal->ComputeGVector( g );
            
            //std::cout << "after ComputeGVector, g is \n" << g << "\n";


            g2 = sqrt( g.GetLength2() );

            //std::cout << "g2 = " << g2 << "\n";

            g.gx = g.gx * kWave / g2;
            g.gy = g.gy * kWave / g2;
            g.gz = g.gz * kWave / g2;
            
            //std::cout << "after scaling, g = \n" << g << "\n";

            /*
            // Apply the tilt of the zone axis:
            ftype cx = cos(thetaY_mrad*1.0e-3);
            ftype sx = sin(thetaY_mrad*1.0e-3);
            ftype cy = cos(thetaX_mrad*1.0e-3);
            ftype sy = sin(thetaX_mrad*1.0e-3);
            // Now, one would need to have the directions gx and gy for reference:
            zx = cy*g.gx-sx*sy*g.gy-cx*sy*g.gz;
            zy =  0*g.gx+   cx*g.gy-   sx*g.gz;
            zz = sy*g.gx+sx*cy*g.gy+cx*cy*g.gz;
            */
            //std::cout << "gx = [" << gx[0] << "," << gx[1] << "," << gx[2] << "]\n";
            //std::cout << "gy = [" << gy[0] << "," << gy[1] << "," << gy[2] << "]\n";
            //std::cout << "thetaX_mrad = " << thetaX_mrad << "\n";
            //std::cout << "thetaY_mrad = " << thetaY_mrad << "\n";
            //std::cout << "KWave = " << kWave << "\n";
            thetaX = -( thetaX_mrad * 1.0e-3 * gx[0] + thetaY_mrad * 1.0e-3 * gy[0] );
            thetaY = -( thetaX_mrad * 1.0e-3 * gx[1] + thetaY_mrad * 1.0e-3 * gy[1] );
            thetaZ = -( thetaX_mrad * 1.0e-3 * gx[2] + thetaY_mrad * 1.0e-3 * gy[2] );
            g.gx += thetaX * kWave;
            g.gy += thetaY * kWave;
            g.gz += thetaZ * kWave;

            //std::cout << "after +=, g = \n" << g << "\n";

            g2 = sqrt( g.GetLength2() );

            //std::cout << "g2 = " << g2 << "\n";

            zx = g.gx * kWave / g2;
            zy = g.gy * kWave / g2;
            zz = g.gz * kWave / g2;

            //std::cout << "zone is (" << zx << "," << zy << "," << zz << ")\n";

            // g2 = sqrt(g.GetLength2());   printf("zone = [%.1f %.1f %.1f]\n",zx,zy,zz);
            nBeams = 0;
            k2 = kWave * kWave;
            gc2 = gCutoff * gCutoff;
			ksg2Cutoff =  sgCutoff*2.0f*kWave;

            bool print_flag = true;

            for ( h = 0; h <= maxh; h++ ) for ( sh = 0; sh <= ( h > 0 ? 4 : 0 ); sh += 4 )
                {
                    for ( k = 0; k <= maxk; k++ )  for ( sk = 0; sk <= ( k > 0 ? 2 : 0 ); sk += 2 )
                        {
                            for ( l = 0; l <= maxl; l++ ) for ( sl = 0; sl <= ( l > 0 ? 1 : 0 ); sl += 1 )
                                {
                                    s = sh + sk + sl;
                                    Xtal->GetBeamLength2( h, k, l, s, g );
                                    g2 = g.GetLength2();

                                    // test to see whether we are inside the sphere
                                    if ( g2 <= gc2 )
                                    {
                                        g.h = h;    g.k = k;  g.l = l;  g.s = s;
                                        // if ((l== 0) && (k==0) && (h==0)) printf("%d %d: z=%f, %f %f %f\n",ikx,iky,sqrt(zx*zx+zy*zy+zz*zz),g.gx,g.gy,g.gz);
                                        g.gx += zx;
                                        g.gy += zy;
                                        g.gz += zz;
                                        ksg2 = k2 - g.GetLength2();
                                        // if ((l== 0) && (k==0) && (h==0)) printf("%d %d: sg = %f, z2=%f, %f %f %f\n",ikx,iky,fabs(ksg2/(2.0*kWave)),zx*zx+zy*zy+zz*zz,g.gx,g.gy,g.gz);
										ksg2_abs = fabs(ksg2);
                                        //if (ksg2_abs < ksg2Cutoff)
                                        //....
                                        if (ksg2_abs < ksg2Cutoff)
                                        {
                                            g.ksg2 = ksg2; // k2 - g.GetLength2();
                                            g.ComputeMillerIndices();
                                            beams.push_back( g );
											// printf("%2d: [%d %d %d]  -> (%d %d %d %d)\n",beams.size()-1,g.mh,g.mk,g.ml,h,k,l,s);
                                            //std::cout << "\nthe generated g is \n" << g << "\n";
                                        }
										// In addition to keeping all the beams within range, we also want to keep the beam2 with the 2 lowest excitation error2,
										// just in case, our criterium was too strict, and we would not find any beam at all:
										if (g2 > 1e-4) {
											if (ksg2_abs < fabs(gmin2.ksg2)) {
												if (ksg2_abs < fabs(gmin1.ksg2)) {  // keep as smallest
													gmin1.copy(g);
													gmin1.ksg2 = ksg2;
				                                    gmin1.ComputeMillerIndices();
												}
												else {  // keep as second smallest
													gmin2.copy(g);
													gmin2.ksg2 = ksg2;
				                                    gmin2.ComputeMillerIndices();
												}
											}
										}
                                    }
                                }//l loop
                        }
                }
			// if our selected beams are less than 3, we will add either one or 2 more beams, to have at least 3:
            if (beams.size() < 3) beams.push_back( gmin1 );
            if (beams.size() < 3) beams.push_back( gmin2 );

            beams.shrink_to_fit();
            nBeams = beams.size();
        }

		// This function searches the smallest excitation error:
		ftype FindSmallestKsg2(int &index) {
			ftype smallestKsg2 = 10;

			for (int j=1;j<nBeams;j++) {
				if (abs(beams[j].ksg2) < smallestKsg2) {
					smallestKsg2 = abs(beams[j].ksg2);
					index = j;
				}
			}
			return smallestKsg2;
		}

        void FillIndexArray( void )
        {
            unsigned int ix, iy;
            Reflection newBeam;
            indexMatrix.resize( nBeams * nBeams, 0 );

            for ( ix = 0; ix < nBeams; ix++ )
            {
                for ( iy = 0; iy < nBeams; iy++ )
                {
                    if ( iy != ix )
                    {
                        // This function creates a new beam, but only with Miller indices and h,k,l,s:
                        // The actual g-vector can be obtained from the Miller indices using
                        // Crystal::GetBeamLength2(h,k,l,s)
                        newBeam.AssignFromDifference( &beams[ix], &beams[iy] );
                        // This will copy the offset of this beam in the local structure factor list
                        // (returned by beamList.AddBeam) into our index matrix.
                        // If we then want to create an actual floating point array, we must simply fill it with the
                        // structure factors that these offsets point to.
                        indexMatrix[ix + iy * nBeams] = beamList.AddBeam( &newBeam );
                        // if ((ix < 5) & (iy < 5)) printf("(%2d, %2d): %d\n",ix,iy,indexMatrix[ix + iy*nBeams]);
                    }
                }
            }

            for ( beamCount = 0, ix = 0; ix < nBeams * nBeams; ix++ ) { beamCount =  std::max( beamCount, indexMatrix[ix] ); }

            // printf("Found %d beams in %d x %d matrix\n",beamCount,nBeams,nBeams);
        }


        void FillAMatrix( std::vector <complex_type> masterUg )
        {
            int ix, iy, ind;
            // allocate memory for the structure factor matrix:
            Amatrix.resize( nBeams * nBeams );

            for ( ix = 0; ix < nBeams; ix++ )
            {
                for ( iy = 0; iy < nBeams; iy++ )
                {
                    ind = ix + iy * nBeams;
                    // printf("ix=%d, iy=%d, ind=%d, index = %d, %d, %d %d\n",ix,iy,ind,indexMatrix[ind],masterUg.size(),beamList.beams.size(),beamList.beams[indexMatrix[ind]].masterIndex);
                    // put the excitation error on the diagonal, adding it to U0:
                    // copy the structure factor from the master list:
                    Amatrix[ind] = masterUg[beamList.beams[indexMatrix[ind]].masterIndex];

                    if ( ix == iy ) 
                    {
                        { Amatrix[ind] += complex_type( beams[ix].ksg2, 0.0f ); }
                        //std::cout << "\nfillAMatrix, the " << ix << "th element is " << Amatrix[ind] << "\n";
                    }
                }
            }
            //std::cout << "\nPattern calling FillAMatrix is\n" << *this << "\n\n";
        }

        /*
        void fill_diag()
        {
            for ( unsigned long idx = 0; idx != nBeams; ++idx )
                    { Amatrix[ idx*nBeams+idx ] = ( complex_type( beams[idx].ksg2, 0.0f ) ); }
        }
        */

        void ComputeIntensities( std::vector <complex_type> masterUg, ftype thickness )
        {
            unsigned int ix, iy, ind;
            float r, i;
            matrix<std::complex<float> > A( nBeams, nBeams );
            std::complex<float> img = std::complex<float>( 0, 1 );
            img = img * ( float )( 3.14159265359 * thickness / kn );
            //std::cout << "thickness is " << img << "\n";

            if ( nBeams > 0 )
            {
                for ( ix = 0; ix < nBeams; ix++ ) for ( iy = 0; iy < nBeams; iy++ )
                    {
                        ind = ix + iy * nBeams;

                        if ( ix == iy )
                        { A( ix, iy ) = ( masterUg[beamList.beams[indexMatrix[ind]].masterIndex] + complex_type( beams[ix].ksg2, 0.0f ) ); }

                        else
                        { A( ix, iy ) = ( masterUg[beamList.beams[indexMatrix[ind]].masterIndex] ); }
                    }

                Amatrix.resize( nBeams*nBeams );
                std::copy( &(A(0,0)), &(A(0,0))+nBeams*nBeams, Amatrix.begin() );

                A = img * A;
                //std::cout<< "A Matrix : "<< A <<"\n\n";
                if ( 1 ) 
                {
                    A = expm_pad(A);
                    A = cuda_impl::expm( A );
                }
                if ( 0 )
                {
                    f::matrix<std::complex<double> > a( nBeams, nBeams );
                    std::copy( &A(0,0), &A(0,0)+nBeams*nBeams, a.begin() );
                    a = f::expm( a );
                    std::copy( a.begin(), a.end(), &A(0,0) );
                }

                intensities.resize( nBeams );

                for ( ind = 0; ind < nBeams; ind++ )
                {
                    r = A( 0, ind ).real();
                    i = A( 0, ind ).imag();
                    intensities[ind] = r * r + i * i;
                }

                /*
                printf("\n\nBeams: %d\n",nBeams);
                for (ind=0;ind<nBeams;ind++) printf("%.3f ",intensities[ind]);
                printf("\n");
                */
            }

            else
            {
                intensities.resize( 1 );
                intensities[0] = 1.0;
            }
        }

        // The array pix is already allocated, and we want to add the intensities of this array to it
        void AddPatternToImg( std::vector<ftype>& pix, int Nx, int Ny, ftype dk, Crystal* ptrXtal )
        {
            int ib, ix, iy;
            ftype g2x, g2y; // projected 2D coordinate of beam
            int NxMid = Nx >> 1;
            int NyMid = Ny >> 1;

			// printf("nBeams: %d, intensities %f %f %f\n",nBeams,intensities[0],intensities[1],intensities[2]);
            // printf("%d %d: %d %d %f\n",ikx,iky,nBeams,beams.size(),intensities[0]);
            if ( nBeams == 0 )    { return; }

            for ( ib = 0; ib < nBeams; ib++ )
            {
                ptrXtal->ComputeGVector( beams[ib] );
                g2x = beams[ib].gx * gx[0] + beams[ib].gy * gx[1] + beams[ib].gz * gx[2];
                g2y = beams[ib].gx * gy[0] + beams[ib].gy * gy[1] + beams[ib].gz * gy[2];
                ix = NxMid + ikx + ( int )floor( g2x / dk + 0.5 );
                iy = NyMid + iky + ( int )floor( g2y / dk + 0.5 );

                // printf("%2d: (%7.3f %7.3f) -> (%d %d) %f\n",ib,g2x,g2y,ix,iy,dk);
                //if ( ( ix >= 0 ) && ( ix < Nx ) && ( iy >= 0 ) && ( iy < Ny ) )  { pix[iy * Nx + ix] += intensities[ib]; }
                if ( ( ix >= 0 ) && ( ix < Nx ) && ( iy >= 0 ) && ( iy < Ny ) )  { pix[iy * Nx + ix] = intensities[ib]; }
                  else
                    {
                      //std::cout << "Warning\n" << "ib = " << ib << "\nix = " << ix << "\niy = " << iy << "\n";

                    }

            }
        }


	// recursive function for computing the scattering path expansion up to a maximum scattering order maxQ
	complex_type AccumulatePathExpansionRec(std::vector <complex_type> &masterUg, complex_type T, int maxQ, int n, ftype threshScale, ftype maxUg) {
		complex_type Psi(0.0,0.0);
		int l;

		if (maxQ > 2) {
			for (l=0;l<nBeams;l++) {
				// Psi += Cqcoef(bArray,maxQ-1,T)*masterUg[beamList.beams[indexMatrix[n*nBeams+l]].masterIndex];
			}
		}
		return Psi;
	}

		// This function evaluates the Scattering path expansion recursively, but does not multiply with the structure factors.
	// It just sums up the squared coefficients and returns the sqrt of the sum.
	double ComputeHigherOrderTermStrength(complex_type T, int qMax, int q) {
		int j;
		// if (q==1) return norm(Cqcoef(bArray, qMax,T));
		if (q==1) return abs(Cqcoef(bArray, qMax,T));
		double term = 0.0;
		if (q==0) return term;
		for (j=0;j<nBeams;j++) {
			lArray[q-1] = j;
			bArray[q-1]=beams[j].ksg2;
			term += ComputeHigherOrderTermStrength(T, qMax, q-1);
		}
		// return sqrt(term);  // if we computed the sum of norms we have to take the sqrt now.
		return term;
	}



		// This function uses the scattering path expansion to compute the complex wave vector for a given beam (n).
	double ComputeTermStrength(std::complex<double> T, int q, int n, double threshScale, double targetUg)
	{
		bArray[0] = beams[n].ksg2;
		lArray[0] = n;
		bArray[q] = 0;
		lArray[q] = 0;
		return ComputeHigherOrderTermStrength(T,q,q)*pow(targetUg,q);
	}



	void ComputeTermMap(ftype thickness, int q,ftype termThresh = 0.0001, ftype targetUg = 0.01)
	{
		unsigned int ix;
		int s,l;
		std::complex<double> T(0.0,3.14159265359*thickness/kn);


		bArray.resize(q+1);
		lArray.resize(q+1);
		if (nBeams > 0) {
			intensities.resize(nBeams);
			for (ix=0;ix<nBeams;ix++) {
				intensities[ix] =  ComputeTermStrength(T,q,ix,termThresh,targetUg);
			}
		}
		else {
			intensities.resize(1);
			intensities[0] = 1.0;
		}
	}

	// This function exports the intensities to the file pointed to by fp.
	// Each pattern record starts with the number of beams it contains
	// and its tilt vector, followed by 4-tuples comprised of the 3 indices
	// and then the intensity.
	void writeIntensityData(FILE *fp) {
		fwrite(&nBeams,sizeof(unsigned int), 1, fp );
		fwrite(&thetaX_mrad,sizeof(ftype), 1, fp );
		fwrite(&thetaY_mrad,sizeof(ftype), 1, fp );
		fwrite(&ikx,sizeof(int), 1, fp );
		fwrite(&iky,sizeof(int), 1, fp );
		for (int count =0;count<nBeams;count++)	{
			fwrite(&(beams[count].mh),sizeof(int), 1, fp );
			fwrite(&(beams[count].mk),sizeof(int), 1, fp );
			fwrite(&(beams[count].ml),sizeof(int), 1, fp );
			fwrite(&(intensities[count]),sizeof(ftype), 1, fp );
		}

	}

	// This function exports the intensities to the file given by the fileName.
	void writeIntensityData_ASCII(char *fileName) {
		FILE *fp = fopen(fileName,"w");
		// fprintf(fp,"%d\n",nBeams);
		for (int count =0;count<nBeams;count++)	{
			fprintf(fp,"%.15f\n",intensities[count]);
		}
		fclose(fp);
	}

	// This function exports the intensities to the file given by the fileName.
	void writeArData_ASCII(char *fileName) {
        int ix, iy, ind;

		FILE *fp = fopen(fileName,"w");
		for ( iy = 0; iy < nBeams; iy++ )   {
			for ( ix = 0; ix < nBeams; ix++ )  {
				ind = iy * nBeams + ix;
                    // Amatrix[ind] = masterUg[beamList.beams[indexMatrix[ind]].masterIndex];
                    fprintf(fp,"%d\t",beamList.beams[indexMatrix[ind]].masterIndex);

                    // if ( ix == iy ) { Amatrix[ind] += complex_type( beams[ix].ksg2, 0.0f ); }
			}
			fprintf(fp,"\n");
        }
		fclose(fp);
	}


		// This function exports the intensities to the file given by the fileName.
	void writeDiagData_ASCII(char *fileName) {
        int ind;

		FILE *fp = fopen(fileName,"w");
		for (ind = 0; ind < nBeams; ind++)  fprintf(fp,"%.8f\n",beams[ind].ksg2);
		fclose(fp);
	}



			// This function exports the intensities to the file pointed to by fp.
	// Each pattern record starts with the number of beams it contains
	// and its tilt vector, followed by 4-tuples comprised of the 3 indices
	// and then the intensity.
	void readIntensityData(FILE *fp,ftype lambda, std::vector<ftype> n,Crystal *Xtal) {
		Reflection g;
        int count = 0;
		std::vector<Reflection>::iterator it;
        ftype g2, k2, gc2;
        ftype zx, zy, zz, thetaX, thetaY, thetaZ;

		fread(&nBeams,sizeof(unsigned int), 1, fp );
		fread(&thetaX_mrad,sizeof(ftype), 1, fp );
		fread(&thetaY_mrad,sizeof(ftype), 1, fp );
		fread(&ikx,sizeof(int), 1, fp );
		fread(&iky,sizeof(int), 1, fp );

        kWave = ( ftype )( 1.0 / lambda ); // amplitude of wave vector
        kx = ( ftype )sin( thetaX_mrad * 1e-3 ) / lambda; // x-component of wave vector
	    ky = ( ftype )sin( thetaY_mrad * 1e-3 ) / lambda; // y-component of wave vector
        kz = ( ftype )sqrt( kWave * kWave - kx * kx - ky * ky ); // z-component of wave vector
        kn = kx * n[0] + ky * n[1] + kz * n[2]; // This is the dot-product of wave vector and surface normal.

        // Compute the zone axis vector
        g.mh = zone[0];
        g.mk = zone[1];
        g.ml = zone[2];
		// printf("zone: %d %d %d\n",g.mh,g.mk,g.ml);
		Xtal->ComputeGVector( g );
	    g2 = sqrt( g.GetLength2() );
        g.gx = g.gx * kWave / g2;
        g.gy = g.gy * kWave / g2;
        g.gz = g.gz * kWave / g2;
        thetaX = -( thetaX_mrad * 1.0e-3 * gx[0] + thetaY_mrad * 1.0e-3 * gy[0] );
        thetaY = -( thetaX_mrad * 1.0e-3 * gx[1] + thetaY_mrad * 1.0e-3 * gy[1] );
        thetaZ = -( thetaX_mrad * 1.0e-3 * gx[2] + thetaY_mrad * 1.0e-3 * gy[2] );
        g.gx += thetaX * kWave;
        g.gy += thetaY * kWave;
        g.gz += thetaZ * kWave;
        g2 = sqrt( g.GetLength2() );
        zx = g.gx * kWave / g2;
        zy = g.gy * kWave / g2;
        zz = g.gz * kWave / g2;
        k2 = kWave * kWave;


		// allocate memory for the arrays:
		beams.resize(nBeams);
		intensities.resize(nBeams);
		expIntensities.resize(nBeams);
		for (it=beams.begin(),count = 0;count < nBeams;++it,count++)	{
			fread(&(it->mh),sizeof(int), 1, fp );
			fread(&(it->mk),sizeof(int), 1, fp );
			fread(&(it->ml),sizeof(int), 1, fp );
			it->ComputeHKLSfromMiller();
            Xtal->ComputeGVector(*it);
			// we must also compute the excitation error:
			it->gx += zx;
            it->gy += zy;
            it->gz += zz;
			it->ksg2 = k2 - it->GetLength2();
			// Finally, let's also read the intensity:
			fread(&(expIntensities[count]),sizeof(ftype), 1, fp );
			// printf("%2d: [%d %d %d] => (%d %d %d %d)\n",count,beams[count].mh,beams[count].mk,beams[count].ml,beams[count].h,beams[count].k,beams[count].l,beams[count].s);
		}

	}
	void displayDiagonal() {
		printf("\nDiagonal for matrix of tilt (%f, %f) mrad:\n",thetaX_mrad,thetaY_mrad);
		for (int ix=0;ix<nBeams;ix++) {
			printf("%3d: [%2d %2d %2d] = (%5.2f %5.2f) %5.2f, ",ix,beams[ix].mh,beams[ix].mk,beams[ix].ml,beams[ix].gx,beams[ix].gy,beams[ix].ksg2);
			if ((ix+1) % 2 == 0) printf("\n");
		}
		printf("\n");
	}



	// Please note that the kinematic contribution to the amplitude is C1=(exp[T*b_n]-1)/b_n
	// By using the identity tat cos(2theta) = 1-2sin(theta)^2 one can show that
	// |C1| = 2sin(T*b_n/2)/b_n  (for |b_n| > 0)
	void AddKinematicRockingCurveContribution(int ib,double &T1,double &T2,double &T3,ftype thickness) {
		int ix;
		double C,sg;

		for (ix=0;ix<nBeams;ix++) if (beamList.beams[indexMatrix[ix*nBeams]].masterIndex == ib) break;
		if (ix == nBeams) return;  // This means we have not found the beam in this pattern.
		sg = abs(beams[ix].ksg2);
		if (sg > 1e-12)	C = 2.0*sin(0.5*3.14159265359*thickness/kn*sg)/sg;
		else C = 3.14159265359*thickness/kn;
		C *= C;
		T1 += C*expIntensities[ix];
		T2 += C*C;
		T3 += expIntensities[ix]*expIntensities[ix];
	}

	// This function evaluates the Scattering path expansion recursively, but instead of computing the diffraction amplitude,
	// it calculates the contribution of these terms to the gradient of the error function with respect to the individual Ugs:
	// Here, preFactor = (I-J)*conj(Psi)
	void ComputeHigherOrderGradient(std::vector <complex_type> &masterUg, std::vector <complex_type> &masterUgGrad, std::vector <unsigned int> &masterUgGradCount, complex_type preFactor, complex_type T, int qMax, int q) {
		int j;
		if (q==1) {
			complex_type C = Cqcoef(bArray, qMax,T);
			// make a list with all the Ug-entries.  This term contributes to the gradients of all those structure factors.
			for (j=0;j<qMax;j++) llArray[j] = beamList.beams[indexMatrix[lArray[j]*nBeams+lArray[j+1]]].masterIndex;
			// Now we will compute the contribution to each of the gradient terms:
			for (j=0;j<qMax;j++) {
				complex_type Psi = C;
				for (int i=0;i<qMax;i++) if (i != j) Psi *= masterUg[llArray[i]];
				masterUgGrad[llArray[j]] += Psi*preFactor;
				masterUgGradCount[llArray[j]]++;
			}
		}
		if (q==0) return;
		for (j=0;j<nBeams;j++) {
			lArray[q-1] = j;
			bArray[q-1]=beams[j].ksg2;
			ComputeHigherOrderGradient(masterUg, masterUgGrad,masterUgGradCount,preFactor,T, qMax, q-1);
		}
	}


		// This function evaluates the Scattering path expansion recursively, but instead of computing the diffraction amplitude,
	// it calculates the contribution of these terms to the gradient of the error function with respect to the individual Ugs:
	// Here, preFactor = (I-J)*conj(Psi)
	void ComputeHigherOrderGradientLocal(complex_type preFactor, complex_type T, int qMax, int q) {
		int j;
		if (q==1) {
			complex_type C = Cqcoef(bArray, qMax,T);
			// make a list with all the Ug-entries.  This term contributes to the gradients of all those structure factors.
			for (j=0;j<qMax;j++) llArray[j] = beamList.beams[indexMatrix[lArray[j]*nBeams+lArray[j+1]]].masterIndex;
			// Now we will compute the contribution to each of the gradient terms:
			for (j=0;j<qMax;j++) {
				complex_type Psi = C;
				int iset = (lArray[0] + dataSetOffset) % ugListNumber;
				// for (int i=0;i<qMax;i++) if (i != j) if (llArray[i] > 0) Psi *= (ugListLocal[iset][llArray[i]]+Uref);
				for (int i=0;i<qMax;i++) if (i != j) if (llArray[i] > 0) Psi *= ugListLocal[iset][llArray[i]];
				ugListGradLocal[iset][llArray[j]] += Psi*preFactor;
				ugListGradCountLocal[iset][llArray[j]]++;
			}
		}
		if (q==0) return;
		for (j=0;j<nBeams;j++) {
			lArray[q-1] = j;
			bArray[q-1]=beams[j].ksg2;
			ComputeHigherOrderGradientLocal(preFactor,T, qMax, q-1);
		}
	}



	// This function evaluates the Scattering path expansion recursively:
	complex_type ComputeHigherOrder(std::vector <complex_type> &masterUg, complex_type T, int qMax, int q) {
		int j;
		if (q==1) {
			complex_type Psi = Cqcoef(bArray, qMax,T);
			for (j=0;j<qMax;j++) {
				// if (beamList.beams[indexMatrix[lArray[j]*nBeams+lArray[j+1]]].masterIndex > 0)
				// Psi *= (masterUg[beamList.beams[indexMatrix[lArray[j]*nBeams+lArray[j+1]]].masterIndex]+Uref);
				Psi *= masterUg[beamList.beams[indexMatrix[lArray[j]*nBeams+lArray[j+1]]].masterIndex];
				// printf("%3d (%.2f)",beamList.beams[indexMatrix[lArray[j]*nBeams+lArray[j+1]]].masterIndex,1.0e3*masterUg[beamList.beams[indexMatrix[lArray[j]*nBeams+lArray[j+1]]].masterIndex].real());
			}

			if (!std::isfinite(Psi.real())) {
					printf("Found infty(%d): (%f +i*%f) (%d %d) (%f %f)\n",qMax,Psi.real(),Psi.imag(),lArray[0],lArray[1],bArray[0],bArray[1]);
					for (j=0;j<qMax;j++) printf("%d (%d): %f %f\n",j,beamList.beams[indexMatrix[lArray[j]*nBeams+lArray[j+1]]].masterIndex,masterUg[beamList.beams[indexMatrix[lArray[j]*nBeams+lArray[j+1]]].masterIndex].real(),masterUg[beamList.beams[indexMatrix[lArray[j]*nBeams+lArray[j+1]]].masterIndex].imag());
					Psi = Cqcoef(bArray, qMax,T);
					printf("Found infty(%d): (%f +i*%f) (%d %d) (%f %f)\n",qMax,Psi.real(),Psi.imag(),lArray[0],lArray[1],bArray[0],bArray[1]);
					exit(0);
			}
			// printf(" Psi = %7.4f,%7.4f \n",1e3*Psi.real(),1e3*Psi.imag());
			return Psi;
		}
		complex_type PsiQ(0.0,0.0);
		if (q==0) return PsiQ;
		for (j=0;j<nBeams;j++) {
			lArray[q-1] = j;
			bArray[q-1]=beams[j].ksg2;
			PsiQ += ComputeHigherOrder(masterUg, T, qMax, q-1);
		}
		return PsiQ;
	}


	// This function uses the scattering path expansion to compute the complex wave vector for a given beam (n).
	complex_type ApproximateWave(std::vector <complex_type> &masterUg, std::complex<double> T, int maxQ, int ib)
	{
		std::complex<double> C, Psi(((ib== 0) ? 1.0f : 0.0f),0.0f);
		ftype eps = 1e-8f;
		int l,ll,q,recursive = 1;

		// First, we want to compute the single scattering (kinematic) wave function
		bArray[0] = beams[ib].ksg2;
		bArray[1] = 0;
		lArray[0] = ib;
		lArray[1] = 0;
		if (recursive == 0) {
			Psi +=  Cqcoef(bArray, 1,T)*masterUg[beamList.beams[indexMatrix[ib*nBeams]].masterIndex];
			if (maxQ > 1) {
				/*
				bArray[2] = 0;
				for (l=0;l<nBeams;l++) {
					bArray[1] = beams[l].ksg2;
					if (abs(bArray[1] - bArray[0]) < eps) {
						if (abs(bArray[0]) < eps) C = 0.5*T*T;
						else C = T*(exp(T*bArray[0])-1.0f)/bArray[0] - (exp(T*bArray[0])-1.0f-T*bArray[0])/(bArray[0]*bArray[0]);
					}
					else {
						if ((abs(bArray[0]) > eps) && (abs(bArray[1]) > eps))
							C = (exp(T*bArray[0])-1-T*bArray[0])/((bArray[0]-bArray[1])*bArray[0]) + (exp(T*bArray[1])-1-T*bArray[1])/((bArray[1]-bArray[0])*bArray[1]);
						else if ((abs(bArray[0]) <= eps) && (abs(bArray[1]) > eps))
							C = (exp(T*bArray[1])-1-T*bArray[1])/(bArray[1]*bArray[1]);
						else if ((abs(bArray[0]) > eps) && (abs(bArray[1]) <= eps))
							C = (exp(T*bArray[0])-1-T*bArray[0])/(bArray[0]*bArray[0]);
					}
					Psi += C*masterUg[beamList.beams[indexMatrix[n*nBeams+l]].masterIndex] * masterUg[beamList.beams[indexMatrix[l*nBeams]].masterIndex];
				}
				*/
			}
			if (maxQ > 2) {
				bArray[3] = 0;
				for (l=0;l<nBeams;l++) {
					bArray[1] = beams[l].ksg2;
					for (ll=0;ll<nBeams;ll++) {
						bArray[2] = beams[ll].ksg2;
						Psi += Cqcoef(bArray,3,T) * masterUg[beamList.beams[indexMatrix[ib*nBeams+l]].masterIndex] * masterUg[beamList.beams[indexMatrix[l*nBeams+ll]].masterIndex] * masterUg[beamList.beams[indexMatrix[ll*nBeams]].masterIndex];
					}
				}
			}

		}
		else {
			// now, we want to add the computation for higher powers of the matrix elements:
			for (q=1;q<=maxQ;q++) {
				bArray[q] = 0;
				lArray[q] = 0;
				Psi += ComputeHigherOrder(masterUg,T,q,q);
				// printf("q=%d, Psi = %f,%f (%d %d %d) (%6.3f %6.3f %6.3f)\n",q,Psi.real(),Psi.imag(),lArray[0],lArray[1],lArray[2],bArray[0],bArray[1],bArray[2]);
			}
		}
		// if (n == 0) printf("n=%d, Psi = %f,%f\n",n,Psi.real(),Psi.imag());
		return Psi;
	}

	void ComputeKinematicIntensity( std::vector <complex_type> &masterUg, ftype thickness ) {
		unsigned int ix;
		complex_type Psi;
		std::complex<double> T(0.0,3.14159265359*thickness/kn);


		if (nBeams > 0) {
			kinematicIntensities.resize(nBeams);
			for (ix=0;ix<nBeams;ix++) {
				// compute Psi under kinematic approximation (q=1):
				Psi = ApproximateWave(masterUg,T,1,ix);
				kinematicIntensities[ix] = norm(Psi);
			}
		}
		else {
			kinematicIntensities.resize(1);
			kinematicIntensities[0] = 1.0;
		}
	}



	void ApproximateIntensities(std::vector <complex_type> &masterUg, ftype thickness, int maxQ = 2)
	{
		unsigned int ix;
		complex_type Psi;
		std::complex<double> T(0.0,3.14159265359*thickness/kn);


		if (nBeams > 0) {
			intensities.resize(nBeams);
			for (ix=0;ix<nBeams;ix++) {
				Psi = ApproximateWave(masterUg,T,maxQ,ix);
				intensities[ix] = norm(Psi);
			}
		}
		else {
			intensities.resize(1);
			intensities[0] = 1.0;
		}
	}

	// This function uses the scattering path expansion to compute the complex wave vector for a given beam (n).
	// preFactor = (I-J)*conj(Psi)
	// It will add the appropriate contributions to the Gradient array masterUgGrad which contains the partial
	// derivatives of the error function E=0.5*sum(I-J)^2 w.r.t. all the structure factors.
	// This array must have bee allocated already, of course.
	// the input parameter subtractKinematic decides whether the full experimental intensities will be used, or
	// the the difference between experimental intensities and the kinematic intensities.
	ftype ApproximateWaveGradient(std::vector <complex_type> &masterUg,std::vector <complex_type> &masterUgGrad, std::vector <unsigned int> &masterUgGradCount, ftype thickness, int maxQ=2,int subtractKinematic= 0)
	{
		complex_type preFactor;
		std::complex<double> T(0.0,3.14159265359*thickness/kn);
		std::complex<double> Psi,Psi1;
		double normPsi,intDiff;
		ftype errValue = 0.0f;
		int ix,l,ll,q;

		// printf("kn = %f, T = %f %f\n",kn,T.real(),T.imag());
		intensities.resize(nBeams);
		intensities[0] = 1.0f;
		for (ix=skipCentralBeam;ix<nBeams;ix++) {
			Psi = ApproximateWave(masterUg,T,maxQ,ix);
			normPsi =  norm(Psi);
			intensities[ix] = normPsi;

			bArray[0] = beams[ix].ksg2;
			bArray[1] = 0;
			lArray[0] = ix;
			lArray[1] = 0;


			if (subtractKinematic) {
				Psi1 = ApproximateWave(masterUg,T,1,ix);
				// intensities[ix] = normPsi-norm(Psi1);
				intDiff = (normPsi-norm(Psi1))-(expIntensities[ix]-kinematicIntensities[ix]);
				errValue += intDiff*intDiff;
				// the factor 2 is due to the fact that I = |Psi|^2:
				preFactor = 2.0*intDiff*conj(Psi);

				for (q=1;q<=maxQ;q++) {
					bArray[q] = 0;
					lArray[q] = 0;
					ComputeHigherOrderGradient(masterUg,masterUgGrad,masterUgGradCount,preFactor,T,q,q);
				}
				// finally, subtract 2.0*indDiff*|c^1_ix|^2*conj(Ug_ix)
				// the structure factor is accessed by the element ix in the first column if the index matrix (iy = 0):
				complex_type C = Cqcoef(bArray,1,T);
				masterUgGrad[ix] -= (ftype)(2.0*intDiff*norm(C))*conj(masterUg[beamList.beams[indexMatrix[ix*nBeams+0]].masterIndex]);
			}
			else {
				intDiff = normPsi-expIntensities[ix];
				errValue += intDiff*intDiff;
				preFactor = (double)(2.0*intDiff)*conj(Psi);
				// the q=0 term has no dependence on structure factors and thus also no gradient in any of them.
				for (q=1;q<=maxQ;q++) {
					bArray[q] = 0;
					lArray[q] = 0;
					ComputeHigherOrderGradient(masterUg,masterUgGrad,masterUgGradCount,preFactor,T,q,q);
				}
			}
		}  // end of ix-loop
		// make sure that we do not fit the Ug(0 0 0) component.
		masterUgGrad[0] = 0;
		return 0.5*errValue;
	}




	void DoLineSearch(int maxQ,ftype thickness) {
		int iset,ib,ip;
		double errVal1=0,errVal2=0,errValActual;
		double der2;  // 2nd derivative

		for (iset=0;iset<ugListNumber;iset++) {
			newScale[iset] = scale[iset];
			errVal1 += errVal[iset];
		}
		if (errVal1 < 1e-6) return;

		for (iset=0;iset<ugListNumber;iset++) {
			if (scale[iset] < 1e-10) scale[iset] = 1e-10;
			errVal1 = MeasureErrorLocal(thickness, maxQ,iset,1.0f);
			errVal2 = MeasureErrorLocal(thickness, maxQ,iset,0.5f);

			if (errVal1 < 1e-6) newScale[iset] = scale[iset];
			else if (errVal2 < 1e-6) newScale[iset] = 0.5*scale[iset];
			else {
				// estimate a new scale value for future use:
				CalcParabolaVertex(0,errVal[iset],scale[iset],errVal1,0.5*scale[iset],errVal2,newScale[iset],der2);
				// printf("new value for scale: %f (2nd derivative = %g)\n",newScale,der2);
				if (der2 > 0) {
					if (newScale[iset] > 1.5*dmax(scale[iset],1e-6)) newScale[iset] = 1.5*dmax(scale[iset],1e-6);
				}
				else newScale[iset] = 1e-6;
			}
			// we have to make sure that this new value gives indeed a lower error
			for (ib=0;ib<5;ib++) {
				errValActual = MeasureErrorLocal(thickness, maxQ,iset,newScale[iset]/scale[iset]);
				if (errVal1 <= errVal[iset]) break;
				newScale[iset] *= 0.5;
			}

			// printf("%d (%3d): %f %f %f => %f => scale = %f\n",iset,nBeams,errVal[iset],errVal2,errVal1,errValActual,newScale[iset]/scale[iset]);
			scale[iset] = newScale[iset];
			// if (scale[iset] < 1e-5) scale[iset] = 1e-5;
		}
		return;

	}



	ftype RefineStructurefactorsLocal(ftype thickness, int maxQ) {
		complex_type preFactor;
		std::complex<double> T(0.0,3.14159265359*thickness/kn);
		std::complex<double> Psi;
		double intensityDifference;
		ftype errValue;
		int iset,ix,q,iter,maxIter = 2;


		for(iter=0;iter<maxIter;iter++) {
			// clear the gradient container:

			// reset the structure factor corresponding to the central beam:
			for (iset =0;iset<ugListNumber;iset++) {
				memset(ugListGradLocal[iset].data(),0,ugListSize*sizeof(complex_type));
				// ugListLocal[iset][0] = -Uref;
				ugListLocal[iset][0] = 0;
				errVal[iset] = 0;
			}
			// First, we compute the amplitude, intensity and gradient for each beam:
			for (ix=skipCentralBeam;ix<nBeams;ix++) {
				iset = (ix + dataSetOffset) % ugListNumber;
				Psi = ApproximateWave(ugListLocal[iset],T,maxQ,ix);
				intensityDifference = norm(Psi)-expIntensities[ix];
				errVal[iset] += 0.5*intensityDifference*intensityDifference;
				preFactor = 2.0*conj(Psi)*intensityDifference;
				bArray[0] = beams[ix].ksg2;
				bArray[1] = 0;
				lArray[0] = ix;
				lArray[1] = 0;
				for (q=1;q<=maxQ;q++) {
					bArray[q] = 0;
					lArray[q] = 0;
					ComputeHigherOrderGradientLocal(preFactor,T,q,q);
				}
				// printf("Wave %d %d approximated\n",ix,iset);
			}
			// Now that we have the gradient, we must do the line-search along its direction:
			DoLineSearch(maxQ,thickness);
			// printf("Did line search\n");
			// Check if the average scale value is very small:
			if (GetGradientScale() < 1e-12) break;
			for (iset =0;iset<ugListNumber;iset++) {
				ugListGradLocal[iset][0] = 0;
				for (ix = 1;ix<ugListSize;ix++) {
					ugListLocal[iset][ix] -= (ftype)(scale[iset])*ugListGradLocal[iset][ix];
					if (abs(ugListLocal[iset][ix]) < minUg) ugListLocal[iset][ix] = ApplyMinimumConstraint(ugListLocal[iset][ix]);
					if (abs(ugListLocal[iset][ix]) > 1) ugListLocal[iset][ix] = ugListLocal[iset][ix]/abs(ugListLocal[iset][ix]);
				}
			}
		}
		for (errValue = 0,iset=0;iset<ugListNumber;iset++)   {
			errVal[iset] = MeasureErrorLocal(thickness, maxQ,iset,0.0f);
			errValue += errVal[iset];
		}
		// printf("********** error: %f *************\n",errValue);

		return errValue;
	}

	void InitUgListLocal(std::vector<complex_type> &ugMasterList) {
		int j;
		ugListSize = ugMasterList.size();
		ugListNumber = nBeams;

		// Uref = complex_type(0.0,0.0);
		errVal.resize(ugListNumber);
		scale.resize(ugListNumber);
		newScale.resize(ugListNumber);
		for (int j=1;j<ugListNumber;j++) {
			scale[j] = scale[0];
			newScale[j] = newScale[0];
		}

		trialUg.resize(ugListSize);
		ugListLocal.resize(ugListNumber);
		ugListGradLocal.resize(ugListNumber);
		ugListGradCountLocal.resize(ugListNumber);

		for (int iset =0;iset<ugListNumber;iset++) {
			ugListLocal[iset].resize(ugListSize);
			ugListGradLocal[iset].resize(ugListSize);
			ugListGradCountLocal[iset].resize(ugListSize);
			for (j=1;j<ugListSize;j++) {
				ugListLocal[iset][j] = ugMasterList[j];
				/*
				// if (ugListNumber < nBeams) ugListLocal[iset][j] = ugMasterList[j]-Uref;
				if (ugListNumber < nBeams) ugListLocal[iset][j] = ugMasterList[j];
				// if we have one set per reflection then set all other structure factors to zero,
				// except for the one corresponding to the current beam:
				else {
					// if (j == beamList.beams[indexMatrix[iset*nBeams]].masterIndex) ugListLocal[iset][j] = ugMasterList[j]-Uref;
					if (j == beamList.beams[indexMatrix[iset*nBeams]].masterIndex) ugListLocal[iset][j] = ugMasterList[j];
					else
					{
						ugListLocal[iset][j] = std::polar(minUg,6.3f*(ftype)(std::rand()/RAND_MAX));
					}
				}
				*/
			}
			// ugListLocal[iset][0] = -Uref;
			ugListLocal[iset][0] = 0;
			memset(ugListGradCountLocal[iset].data(),0,ugListSize*sizeof(unsigned int));
		}
	}

	void ContributeToAverage(std::vector<complex_type> &ugMasterList,std::vector<unsigned int> &ugMasterListGradCount) {
	int iset;
		// printf("computing average\n");
		for (iset=0;iset<ugListNumber;iset++) {
			for (int ix=skipCentralBeam;ix<ugListSize;ix++) {
				if (ugListGradCountLocal[iset][ix]) {
					ugMasterListGradCount[ix]++;
					// ugMasterList[ix] += (ugListLocal[iset][ix]+Uref);
					ugMasterList[ix] += ugListLocal[iset][ix];
				}
			}
		}
		// printf("computed average\n");
	}

	ftype MeasureError(std::vector <complex_type> &masterUg, ftype thickness, int maxQ,int  subtractKinematic= 0)
	{
		std::complex<double> T(0.0,3.14159265359*thickness/kn);
		std::complex<double> Psi,Psi1;
		double normPsi,intDiff;
		ftype errValue = 0.0f;
		int ix;

		intensities[0] = 1.0f;
		for (ix=skipCentralBeam;ix<nBeams;ix++) {
			Psi = ApproximateWave(masterUg,T,maxQ,ix);
			normPsi = norm(Psi);
			intensities[ix] = normPsi;
			if (subtractKinematic) {
				Psi1 = ApproximateWave(masterUg,T,1,ix);
				intDiff = (normPsi-norm(Psi1))-(expIntensities[ix]-kinematicIntensities[ix]);
			}
			else {
				intDiff = normPsi-expIntensities[ix];
			}
			errValue += intDiff*intDiff;
		}
		// printf("Error: %g\n",0.5*errValue);
		return 0.5*errValue;
	}

	// This function applies applies to complex numbers whose amplitude is smaller than minUg
	// it makes sure that the amplitude will not be smaller than 0.5*minUg, but the phase will be preserved.
	complex_type ApplyMinimumConstraint(complex_type c) {
		ftype phi = arg(c);
		ftype amplitude = abs(c);
		if (amplitude >= minUg) return c;
		// printf("Applying min constraint: %f,%f => ",amplitude,phi);
		// phi += 0.5f*(1.0f-exp(2.0f*(amplitude-minUg)/minUg));
		amplitude = minUg*(1.0f - 0.5*(1.0f-exp(2.0f*(amplitude-minUg)/minUg)));
		// printf("%f, %f\n",amplitude,phi);
		// Matlab:	y=minUg*(1-0.5*(1-exp(2*(c-minUg)/minUg)));
		return std::polar(amplitude,phi);
	}

	ftype MeasureErrorLocal(ftype thickness, int maxQ,int iset,ftype scaleFactor)
	{
		std::complex<double> T(0.0,3.14159265359*thickness/kn);
		std::complex<double> Psi;
		double normPsi;
		ftype errValue = 0.0f;
		int ix;

		// copy the structure factors from the current set into trialUg and use those for calculation:
		for (ix=0;ix<ugListSize;ix++) {
				trialUg[ix] = ugListLocal[iset][ix] - scaleFactor*(ftype)(scale[iset])*ugListGradLocal[iset][ix];
				if (abs(trialUg[ix]) < minUg) trialUg[ix] = ApplyMinimumConstraint(trialUg[ix]);
		}
		for (ix=skipCentralBeam;ix<nBeams;ix++) {
			if ((ix + dataSetOffset) % ugListNumber == iset) {
				Psi = ApproximateWave(trialUg,T,maxQ,ix);
				normPsi = norm(Psi);
				intensities[ix] = normPsi;
				if (!std::isfinite(normPsi)) {
					printf("Found infty: %f (%f +i*%f), beam=%d\n",normPsi,Psi.real(),Psi.imag(),ix);
					exit(0);
				}
				errValue += (normPsi-expIntensities[ix])*(normPsi-expIntensities[ix]);
			}
		}
		// printf("Error (%d, %7.5f): %g\n",iset,scaleFactor*scale[iset],0.5*errValue);
		// if (!isfinite(errValue)) printf("Found infty!!!\n");
		return 0.5*errValue;
	}


	void IncrementDatasetOffset() {
		dataSetOffset++;
		for (int iset=0;iset<ugListNumber;iset++) scale[iset] = 1e-4;
	}

};

#endif//_AFDPOINLKJSFDI4UHAKLFJNSALDFJKNASLDJKNASDLKNSDLJKN4O0IHAFDLKJNSDAFLJNASFDFSD
