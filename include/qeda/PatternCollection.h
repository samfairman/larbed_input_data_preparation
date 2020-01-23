#ifndef _P49IEJASKLNASFNMVLAJN948ASFDKLJV3FZASDSADPOIESAFJDHVM9NQIOU4089KFAJHVAKJHSFDA
#define _P49IEJASKLNASFNMVLAJN948ASFDKLJV3FZASDSADPOIESAFJDHVM9NQIOU4089KFAJHVAKJHSFDA

#include <vector>

#include <f/matrix/matrix.hpp>

#include <qeda/DataTypes.h>
#include <qeda/Pattern.h>
#include <qeda/Crystal.h>
#include <qeda/ReflectionArray.h>
#include <qeda/ImageLib.h>
#include <qeda/HelperFunctions.h>
#include <wchar.h>

#include <string>
#include <iostream>
#include <fstream>

using namespace std;

class intensityHeader
{
    public:
        int headerSize;
        int Ntilts;
        float highVoltage;
        float thickness;
};

// This pattern collection contains
class PatternCollection
{
        ftype highTension;
        ftype lambda;
        ftype thickness;
        ftype dk;             // pixel size of pattern in reciprocal space
        std::vector <ftype> n;     // surface normal
        std::vector <ftype> zone;  // make this array
        std::vector <ftype> gx;    // make this array
        std::vector <ftype> gy;    // make this array
        size_t nPatterns;
        std::vector <Pattern> data;
        Crystal* ptrXtal;
        std::vector <complex_type> trialUg;
        std::vector <complex_type> ugMasterList;
        std::vector <complex_type> ugMasterListGrad;
        std::vector <unsigned int> ugMasterListGradCount;
        std::vector <unsigned int> ugMasterListGradCountTemp;
        int ugMasterListSize;
        int ir;    // disc radius in pixels
        int discRadiusPixels;
        ReflectionArray indexMasterArray;
        ftype gCutoff;
        ftype sgCutoff;
        ftype scale;

        friend
        std::ostream& operator << ( std::ostream& os, PatternCollection const& pc )
        {
            os << "\nhighTension: " << pc.highTension;
            os << "\nlambda: " << pc.lambda;
            os << "\nthickness: " << pc.thickness;
            os << "\ndk: " << pc.dk;
            os << "\nPattern: " << pc.nPatterns;
            os << "\nUgMasterListSize: " << pc.ugMasterListSize;
            os << "\nir: " << pc.ir;
            os << "\ndiscRadiusPixels: " << pc.discRadiusPixels;
            os << "\ngCutoffs: " << pc.gCutoff;
            os << "\nsgCutoffs: " << pc.sgCutoff;
            os << "\nscale: " << pc.scale;
            //os << "\nthe last pattern:\n" << *(pc.data.rbegin()) << "\n";
            return os;
        }

    public:

        void dump( std::string const& path )
        {
            //dump Kn here
            std::ofstream ofs( "kn.txt" );
            for ( unsigned long index = 0; index != data.size(); ++index )
            {
                data[index].dump_all( path, index );
                ofs.precision( 15 );
                ofs << data[index].kn << "\n";
            }
            ofs.close();
        }

        void load_intensity( std::string const& file_path )
        {
            f::matrix<double> intensities_mat;
            f::matrix<unsigned long> ar_mat;
            intensities_mat.load( file_path + std::string{"/intensities.txt"} );

            if ( 1 )
            {
                double const all_intensity = std::accumulate( intensities_mat.begin(), intensities_mat.end(), double{0.0} ) / static_cast<double>( intensities_mat.col() );

                std::for_each( intensities_mat.begin(), intensities_mat.end(), [all_intensity]( double& x ) { x /= all_intensity; } );
            }

            if ( 0 )
            {
                std::vector<double> accus;
                accus.resize( intensities_mat.row() );
                for ( unsigned long index = 0; index != intensities_mat.row(); ++index )
                {
                    accus[index] = std::accumulate( intensities_mat.row_begin(index), intensities_mat.row_end(index), double{0.0} );
                    double const average = accus[index] / static_cast<double>( intensities_mat.col() );
                    double variance = 0.0;
                    std::for_each( intensities_mat.row_begin(index), intensities_mat.row_end(index), [&variance, average]( double x ){ double const diff = average - x;  variance += diff*diff; } );
                    //accus[index] *= std::sqrt(variance);
                    accus[index] *= variance;
                }

                std::vector<double> c_accus{ accus };
                std::sort( c_accus.begin(), c_accus.end() );
                double threshold = *(c_accus.rbegin()+45);
                double ignored_max = 0.0;
                for ( unsigned long index = 0; index != intensities_mat.row(); ++index )
                    if ( accus[index] < threshold )
                    {
                        ignored_max = std::max( ignored_max, *std::max_element( intensities_mat.row_begin(index), intensities_mat.row_end(index) ) );
                        std::fill( intensities_mat.row_begin(index), intensities_mat.row_end(index), double{0.0} );
                    }

                //double const factor = 3.14159265358979323846;
                //double const factor = 3.14159265358979323846;
                //double const factor = 5.43656365691809047072;
                //double const factor = 6.28318530717958647692;
                double const factor = 12.56637061435917295384;
                std::for_each( intensities_mat.begin(), intensities_mat.end(), [factor, ignored_max]( double& x ) { if ( factor*x < ignored_max ) x = 0.0; } );
            }

            if ( 0 )
            {
                std::vector<double> accus;
                accus.resize( intensities_mat.row() );
                for ( unsigned long index = 0; index != intensities_mat.row(); ++index )
                {
                    accus[index] = std::accumulate( intensities_mat.row_begin(index), intensities_mat.row_end(index), double{0.0} );
                    double const average = accus[index] / static_cast<double>( intensities_mat.col() );
                    double variance = 0.0;
                    std::for_each( intensities_mat.row_begin(index), intensities_mat.row_end(index), [&variance, average]( double x ){ double const diff = average - x;  variance += diff*diff; } );
                    //accus[index] *= std::sqrt(variance);
                    accus[index] *= variance;
                }

                std::vector<double> c_accus{ accus };
                std::sort( c_accus.begin(), c_accus.end() );
                double threshold = *(c_accus.rbegin()+45);
                for ( unsigned long index = 0; index != intensities_mat.row(); ++index )
                    if ( accus[index] < threshold )
                        std::fill( intensities_mat.row_begin(index), intensities_mat.row_end(index), double{0.0} );
            }

            if ( 0 )
            {
                f::matrix<double> new_mat{ intensities_mat };
                std::sort( new_mat.begin(), new_mat.end() );
                double const threshold = *(new_mat.begin()+new_mat.size() * 90 / 100);
                std::for_each( intensities_mat.begin(), intensities_mat.end(), [threshold]( double& x){ if ( x < threshold ) x = 0.0; } ); 
            }


            if ( 0 )
            {
                f::matrix<double> new_intensity{ intensities_mat };
                std::sort( new_intensity.begin(), new_intensity.end() );
                double const threshold = *(new_intensity.begin() + new_intensity.size() * 90 / 100);
                std::for_each( intensities_mat.begin(), intensities_mat.end(), [threshold]( double& x ) { if ( x < threshold ) x = 0.0; } );
            }


            if ( 0 )
            {   //new uniformer
                double const minimal = *std::min_element( intensities_mat.begin(), intensities_mat.end() );
                std::vector<double> arr( intensities_mat.begin(), intensities_mat.end() );
                std::sort( arr.begin(), arr.end() );
                unsigned long const spot_to_zero = arr.size() * 90 / 100;
                double const val_threshold = arr[spot_to_zero];
                //double const val_threshold = std::accumulate( arr.begin(), arr.begin()+spot_to_zero, double{0.0} ) / static_cast<double>(spot_to_zero);
                std::for_each( intensities_mat.begin(), intensities_mat.end(), [val_threshold]( double& x ){ if ( x <= val_threshold ) x = 0.0; } );
                //double const divider = ( - minimal * intensities_mat.row() * intensities_mat.col() + std::accumulate( intensities_mat.begin(), intensities_mat.end(), double{0.0} ) ) / 1009.0;
                //double const divider = std::accumulate( intensities_mat.begin(), intensities_mat.end(), double{0.0} ) / 1009.0;
                //std::for_each( intensities_mat.begin(), intensities_mat.end(), [divider]( double& x ){ x /= divider; } );
                double const divider = std::accumulate( intensities_mat.begin(), intensities_mat.end(), double{0.0} ) / 1009.0;
                std::for_each( intensities_mat.begin(), intensities_mat.end(), [divider,val_threshold]( double& x ){ if ( x > val_threshold ) x = ( x-val_threshold)/(divider-val_threshold); } );
            }

            f::matrix<long> experimental_beams;
            experimental_beams.load( file_path + std::string{"/experimental_beams.txt"} );

            std::cout << "\ndebug info in method load_intensity.\n";

            double all_chi = 0.0;

            for ( unsigned long index = 0; index != data.size(); ++index )
            {
                data[index].intensities.resize( data[index].nBeams );
                std::fill( data[index].intensities.begin(), data[index].intensities.end(), 0.0 );
                for ( unsigned long row = 0; row != data[index].nBeams;++row )
                {
                    (data[index].intensities)[row] = 0.0;
                    long const sim_accu = data[index].beams[row].mh * 10000 + data[index].beams[row].mk * 100 + data[index].beams[row].ml; 
                    for ( unsigned long idx = 0; idx != experimental_beams.row(); ++idx )
                    {
                        long const exp_accu = experimental_beams[idx][0] * 10000 + experimental_beams[idx][1] * 100 + experimental_beams[idx][2]; 
                        if ( exp_accu == sim_accu )
                        {
                            //std::cout << "\nSuccessfully find beam with index " << index << " and row " << row << "\n";
                            //std::cout << "(mh,mk,ml) is (" << data[index].beams[row].mh << "," << data[index].beams[row].mk << "," << data[index].beams[row].ml << ")\n"; 
                            (data[index].intensities)[row] = intensities_mat[idx][index];
                            break;
                        }
                        if ( idx == experimental_beams.row()-1 )
                        {
                            //std::cout << "\nFailed to find beam with index " << index << " and row " << row << "\n";
                            //std::cout << "(mh,mk,ml) is (" << data[index].beams[row].mh << "," << data[index].beams[row].mk << "," << data[index].beams[row].ml << ")\n"; 
                        }
                    }
                }
                if ( 0 )
                {
                    //uniform all intensities
                    //
                    double const total = std::accumulate( data[index].intensities.begin(), data[index].intensities.end(), 0.0 );
                    std::for_each( data[index].intensities.begin(), data[index].intensities.end(), [total]( auto& x ){ x /= total; } );
                }

                all_chi += std::inner_product( data[index].intensities.begin(), data[index].intensities.end(), data[index].intensities.begin(), 0.0 ); 

                //std::fill( data[index].intensities.begin(), data[index].intensities.end(), 0.0 );
            }

            std::cerr << "all_chi = " << all_chi << "\n";
        }

        PatternCollection( void )
        {
            highTension = 200;
            ComputeWavelength();  // wavelength of 2.5 pm at 200 kV
            gCutoff     = 1.0f;      // cut off reflections at 3 1/A
            sgCutoff    = 3.0f;  // select reflections that are closer than 0.2 1/A to the Ewald sphere.
            scale       = 1e-5;

            ugMasterListSize = 0;
            n.resize( 3, 0 );
            zone.resize( 3, 0 );
            gx.resize( 3, 0 );
            gy.resize( 3, 0 );
            n[2] = 1.0f;
            zone[2] = 1.0f;
            gx[0]  = 1.0f;
            ComputeGxGy();
        }

        PatternCollection( Crystal* xtal, ftype ht, std::vector <ftype> zoneNew, std::vector <ftype> nNew, std::vector <ftype> gxNew, ftype gCutoffNew, ftype sgCutoffNew )
        {
            gCutoff     = gCutoffNew;      // cut off reflections at 3 1/A
            sgCutoff    = sgCutoffNew;  // select reflections that are closer than 0.2 1/A to the Ewald sphere.
            highTension = ht;
            ComputeWavelength();  // wavelength of 2.5 pm at 200 kV
            n.assign( nNew.begin(), nNew.end() );
            zone.assign( zoneNew.begin(), zoneNew.end() );
            gx.assign( gxNew.begin(), gxNew.end() );
            gy.resize( 3, 0 );
            //  gy.assign(gyNew.begin(),gyNew.end());
            ptrXtal = xtal;
            ComputeGxGy();
        }

        void SetDk( ftype tiltRange_mrad, int discRadius_pixel )
        {
            dk = tiltRange_mrad * 1.0e-3 / ( lambda * ( ftype )discRadius_pixel );
            printf( "tiltRange = %f, lambda = %f, discRad = %d pixels => dk = %f\n", tiltRange_mrad, lambda, discRadius_pixel, dk );
        }


        // create vectors gx and gy which are perfectly normal to the zone axis, and have unit length
        // This requires zone axis and gx-vector to be defined already
        void ComputeGxGy()
        {
            ftype len;
            // compute the cross product of gx and zone
            gy[0] = zone[1] * gx[2] - zone[2] * gx[1];
            gy[1] = zone[2] * gx[0] - zone[0] * gx[2];
            gy[2] = zone[0] * gx[1] - zone[1] * gx[0];
            len = sqrtf( gy[0] * gy[0] + gy[1] * gy[1] + gy[2] * gy[2] );
            if ( len > 0 )
            {
                gy[0] /= len;
                gy[1] /= len;
                gy[2] /= len;
            }
            // now, recompute gx, to make sure that it is indeed normal to the zone axis:
            gx[0] = gy[1] * zone[2] - gy[2] * zone[1];
            gx[1] = gy[2] * zone[0] - gy[0] * zone[2];
            gx[2] = gy[0] * zone[1] - gy[1] * zone[0];
            len = sqrtf( gx[0] * gx[0] + gx[1] * gx[1] + gx[2] * gx[2] );
            if ( len > 0 )
            {
                gx[0] /= len;
                gx[1] /= len;
                gx[2] /= len;
            }
            printf( "In-plane vectors: gx = (%.1f, %.1f, %.1f),  gy = (%.1f, %.1f, %.1f)\n", gx[0], gx[1], gx[2], gy[0], gy[1], gy[2] );
        }

        void ComputeWavelength( void )
        {
            // returns the electron wavelength in A for a given accelerating voltage in keV

            const ftype emass = 510.99906f;          // electron rest mass in keV
            const ftype hce = 12.3984244f;           // h*c/e  in A/keV
            lambda = hce / sqrt( highTension * ( 2 * emass + highTension ) ); // in Angstroem
        }

        void SetZone( int zh, int zk, int zl )
        {
            zone[0] = ( ftype )zh;
            zone[1] = ( ftype )zk;
            zone[2] = ( ftype )zl;
        }

        size_t GetDiscSize( int ir )
        {
            int ix, iy;
            long int r2 = ir * ir;
            int count = 0;

            for ( ix = -ir; ix <= ir; ix++ )
                for ( iy = -ir; iy <= ir; iy++ )
                    if ( ix * ix + iy * iy <= r2 )
                    {
                        count++;
                    }
            return count;
        }

        // Display the tilts of the pattern colection:
        void PrintTilts( void )
        {
            unsigned int count;
            printf( "Zone-axis = [%.1f %.1f %.1f]\n", zone[0], zone[1], zone[2] );
            printf( "Number of patterns in this collecton: %d (gCutoff = %g 1/A, sgCutoff = %g 1/A)\n", nPatterns, gCutoff, sgCutoff );
            for ( count = 0; count < nPatterns; count += ceil( ( float )nPatterns / 20.0f ) )
            {
                printf( "%3d: (%6.2f, %6.2f) mrad %4d beams - %4d total\n", count, data[count].thetaX_mrad, data[count].thetaY_mrad, data[count].nBeams, data[count].beamCount );
            }
        }


        void ReadDisc( std::string const& tilt_file )
        {
            std::ifstream ifs( tilt_file );

            if ( !ifs.good() )
            {
                std::cerr << "Failed to open file " << tilt_file << "\n";
                return;
            }


            ftype kx, ky, kz;

            ftype tiltRange_mrad = 70;

            int discRadius_pixel = 18;

            ir = discRadius_pixel;

            //ftype dk = tiltRange_mrad * 1.0e-3 / ( lambda * ( ftype )discRadius_pixel );
            //ftype dk = tiltRange_mrad * 1.0e-3 / discRadius_pixel;
            //dk = tiltRange_mrad * 1.0e-3 / discRadius_pixel;
            dk = tiltRange_mrad * 1.0e-3 / ( lambda * discRadius_pixel );

            //std::cout << "\nlambda = " << lambda;
            //std::cout << "\ndk = " << dk;

            discRadiusPixels = discRadius_pixel;

            for (;;)
            {
                if ( ifs.eof() ) break;

                //ifs >> kx >> ky >> kz;
                ifs >> kx >> ky;

                if ( !ifs.good() ) break;

                Pattern pt;

                pt.SetTilt(lambda,n,(ftype)(-kx),(ftype)(-ky));
                //pt.SetTilt(lambda,n,(ftype)(1000.0f*kx),(ftype)(1000.0f*ky));
                //pt.SetTilt(lambda,n,(ftype)(kx/lambda),(ftype)(ky/lambda));
                pt.ikx = floor( 1.0e-3*kx / (lambda*dk) + 0.5f );
                pt.iky = floor( 1.0e-3*ky / (lambda*dk) + 0.5f );
                //pt.ikx = floor( lambda * kx / dk + 0.5f );
                //pt.iky = floor( lambda * ky / dk + 0.5f );

                //pt.SetTilt( lambda, n, ( ftype )( pt.ikx )*tiltRange_mrad / ( ftype )ir, ( ftype )( pt.iky )*tiltRange_mrad / ( ftype )ir );

                pt.SetZone( zone, gx, gy );
                pt.FindBeams( ptrXtal, gCutoff, sgCutoff );
                pt.FillIndexArray();


                //std::cout.precision( 20 );
                //std::cout << "\nikx = " << pt.ikx << " iky = " << pt.iky;
                //std::cout << "\nkx = " << kx << " ky = " << ky << "\n";
                //std::cout << "\nlambda = " << lambda;
                //std::cout << "\ndk = " << dk;

                //std::cout << "\nPattern is\n" << pt << "\n";

                data.emplace_back( pt );
            }

            ifs.close();

            nPatterns = data.size();

            /*
            nPatterns = 1009;

            // open file

            // find number of tilts from file and save this number in nPatterns.

            data.resize( nPatterns );

            for ( count = 0; count < nPatterns; count++ )
            {

                // 1. read kx and ky from file

                // 2. set the zone axis and tilt for the current pattern.

                data[count].SetTilt(lambda,n,(ftype)(kx/lambda),(ftype)(ky/lambda));

                // ikx and iky are only for plotting the pattern, they are not needed for generating the Ar-matrices.

                data[count].ikx = floor( kx / dk + 0.5f );

                data[count].iky = floor( ky / dk + 0.5f );

                data[count].SetZone( zone, gx, gy );

                data[count].FindBeams( ptrXtal, gCutoff, sgCutoff );

                data[count].FillIndexArray();

            }
            */
        }

        void GenerateDisc( ftype tiltRange_mrad, int discRadius_pixel, std::vector <ftype> ktOffset )
        {
            int ix, iy, count = 0;
            ir = discRadius_pixel;
            long int ir2 = ir * ir;
            nPatterns = GetDiscSize( ir );
            printf( "Will create %d patterns\n", nPatterns );

            dk = tiltRange_mrad * 1.0e-3 / ( lambda * ( ftype )discRadius_pixel );
            //std::cout << "\ndk is set to " << dk << "\n";
            discRadiusPixels = discRadius_pixel;
            data.resize( nPatterns );
            for ( ix = -ir; ix <= ir; ix++ )
            {
                for ( iy = -ir; iy <= ir; iy++ )
                {
                    if ( ix * ix + iy * iy <= ir2 )
                    {
                        data[count].SetTilt( lambda, n, ( ftype )( ix )*tiltRange_mrad / ( ftype )ir - ktOffset[1], ( ftype )( iy )*tiltRange_mrad / ( ftype )ir - ktOffset[0] );
                        data[count].ikx = ix;
                        data[count].iky = iy;
                        data[count].SetZone( zone, gx, gy );
                        data[count].FindBeams( ptrXtal, gCutoff, sgCutoff );
                        data[count].FillIndexArray();

                        //!!
                        //data[count].ComputeReflections();
                        //data[count].ComputeScattering();
                        //data[count].FillIndexArray();
                        //data[count].FillAMatrix( ugMasterList );
                        //data[count].ComputeIntensities( ugMasterList, thickness );
                        //!!
                        
                        //std::cout << "\nPattern is\n" << data[count] << "\n";

                        count++;
                        printf( "." );

                    }
                    else
                    {
                        printf( " " );
                    }
                }
                printf( "\n" );
            }

        }

        // This function combines all the structure factor lists present in the individual patterns,
        // determining the set of structure factors containing all sub-lists.
        // Return value: total number of structure factors.
        int CreateUgMasterList( void )
        {
            unsigned int count, j, index;

            for ( count = 0; count < nPatterns; count++ )
            {
                for ( j = 0; j < data[count].beamList.beams.size(); j++ )
                {
                    index = indexMasterArray.AddBeam( &data[count].beamList.beams[j] );
                    // write the index of this element back to the local list
                    data[count].beamList.beams[j].masterIndex = index;
                    // printf("pattern %d, beam %d (%d %d)\n",count,j,data[count].beamCount,index);
                }
            }
            // for (j=0;j<indexMasterArray.beams.size();j++) indexMasterArray.beams[j].PrintReflection();
            // for (j=0;j<50;j++) indexMasterArray.beams[j].PrintReflection();
            return indexMasterArray.beams.size();

        }

        void ComputeUgMasterList( void )
        {
            ugMasterListSize = indexMasterArray.beams.size();
            ugMasterList.resize( ugMasterListSize );

            for ( int it = 0; it < ugMasterListSize; it++ )
            {
                ugMasterList[it] = ptrXtal->ComputeStructureFactor( &( indexMasterArray.beams[it] ), highTension );
            }
        }

        void resetU0()
        {
            if ( ugMasterList.size() > 0 )
            {
                ugMasterList[0] = complex_type( 0.0f, 0.0f );
            }
        }

        void load_ug( double* x )
        {
            std::cout << "\nloading ug, the size of ugMasterList is " << ugMasterList.size() << "\n";

            for ( unsigned long index = 0; index != ugMasterList.size(); ++index )
            {
                unsigned long const offset_r = index+index;
                unsigned long const offset_i = offset_r + 1;
                ugMasterList[index] = complex_type{ *(x+offset_r), *(x+offset_i) };
            }
        }

        void load_ug_thickness( double* x )
        {
            load_ug( x );
            thickness = *(x+ugMasterList.size()*2) * 10.0;
        }


        void PrintUgMasterList( char* fileName, int verbose = 1 )
        {
            int it;
            if ( fileName == NULL )
            {
                for ( it = 0; it < min( ( int )indexMasterArray.beams.size(), 20 ); it++ )
                {
                    // Compute the crystal potential Fourier coefficient without the relativistic correction
                    // (in order to compare with WebEMAPS):
                    complex_type vg =  150.4120928091757f / ( 1 + highTension / 511 ) * ugMasterList[it];
                    printf( "%2d (%3d %3d %3d):  Vg = (%6.3f %6.3f) V, |Ug| = %6.3f A^-2\n", it,
                            indexMasterArray.beams[it].mh, indexMasterArray.beams[it].mk, indexMasterArray.beams[it].ml,
                            vg.real(), vg.imag(), abs( ugMasterList[it] ) );
                }
            }
            else    // write the ugArray to a file:
            {
                FILE* fp = fopen( fileName, "w" );
                if ( fp == NULL )
                {
                    return;
                }
                if ( verbose )
                {
                    fprintf( fp, "index\t  h\t  k\t  l\t Ug_real  \t Ug_imag  \tVg_real(V)\tVg_imag(V)\t |Vg|(V)   \tphi(rad)\n" );
                    for ( it = 0; it < indexMasterArray.beams.size(); it++ )
                    {
                        // Compute the crystal potential Fourier coefficient without the relativistic correction
                        // (in order to compare with WebEMAPS):
                        complex_type vg =  150.4120928091757f / ( 1 + highTension / 511 ) * ugMasterList[it];
                        fprintf( fp, "%3d\t%3d\t%3d\t%3d\t%9.6f\t%9.6f\t%9.6f\t%9.6f\t%9.6f\t%9.6f\n", it,
                                 indexMasterArray.beams[it].mh, indexMasterArray.beams[it].mk, indexMasterArray.beams[it].ml,
                                 ugMasterList[it].real(), ugMasterList[it].imag(),
                                 vg.real(), vg.imag(), abs( vg ), arg( vg ) );
                    }
                }
                else
                {
                    fprintf( fp, "ugMasterList (%d Ug values):\n", ugMasterList.size() );
                    for ( it = 0; it < ugMasterList.size(); it++ )
                    {
                        fprintf( fp, "%3d: %g %g\n", it, real( ugMasterList[it] ), imag( ugMasterList[it] ) );
                    }
                }
                fclose( fp );
            }
        }

        void ComputeDiffraction( ftype t, int approxOrder = 0, ftype termThresh = 0.0001, ftype targetUg = 0.01 )
        {
            unsigned int count;
            int ix, iy = -1000;

            thickness = t;
            for ( count = 0; count < nPatterns; count++ )
            {
                // data[count].FillAMatrix(ugMasterList);
                //////////////////////////////////////////////////////////////
                // evaluate the matrix expoenential:
                if ( approxOrder == 0 )
                {
                    data[count].ComputeIntensities( ugMasterList, thickness );
                }
                // evaluate the scattering path expansion:
                if ( approxOrder  > 0 )
                {
                    data[count].ApproximateIntensities( ugMasterList, thickness, approxOrder );
                }
                // compute scattering strength map for a single q:
                if ( approxOrder  < 0 )
                {
                    data[count].ComputeTermMap( thickness, -approxOrder, termThresh, targetUg );
                }
                if ( data[count].ikx > iy )
                {
                    iy = data[count].ikx;
                    printf( "\n" );
                    for ( ix = -discRadiusPixels; ix < data[count].iky; ix++ )
                    {
                        printf( " " );
                    }
                }
                printf( "." );
            }
        }

        //  This function writes different files for each incident beam direction, containing diffraction intensities,
        // Diffraction intensities, Ar-matrices, structure factor matrix diagonals, and the master Ug-vector
        void WriteSimulationParameters( char* pathName )
        {
            unsigned int count;
            char fileName[256];
            FILE* fp;


            // _wmkdir((wchar_t *)pathName);

            // save the tilt angles and number of beams for each pattern:
            ////sprintf(fileName,"%s\\_Tilts.txt",pathName);
            sprintf( fileName, "_Tilts.txt" );
            fp = fopen( fileName, "w" );
            fprintf( fp, "index\tbeams\tT\tik_x\tik_y\tthetaX_mrad\tthetaY_mrad\n" );

            for ( count = 0; count < nPatterns; count++ )
            {
                // write the tilt angle and number of beams:
                fprintf( fp, "%d\t%d\t%g\t%d\t%d\t%8.5f\t%8.5f\n", count, data[count].nBeams, 3.14159265359 * thickness / data[count].kn, data[count].ikx, data[count].iky, data[count].thetaX_mrad, data[count].thetaY_mrad );


                ////sprintf(fileName,"%s\\Intensities_%d.txt",pathName,count);
                sprintf( fileName, "Intensities_%d.txt", count );
                data[count].writeIntensityData_ASCII( fileName );

                ////sprintf(fileName,"%s\\Ar_%d.txt",pathName,count);
                sprintf( fileName, "Ar_%d.txt", count );
                data[count].writeArData_ASCII( fileName );


                //sprintf(fileName,"%s\\Diag_%d.txt",pathName,count);
                sprintf( fileName, "Diag_%d.txt", count );
                data[count].writeDiagData_ASCII( fileName );
            }
            fclose( fp );
        }

        // This function/method saves the computed diffraction intensities to a data file, in binary format
        void SaveDiffractionIntensities( char* outputName )
        {
            FILE* fp;
            intensityHeader iHeader;

            iHeader.Ntilts = nPatterns;
            iHeader.highVoltage = highTension;
            iHeader.thickness = thickness;
            iHeader.headerSize = sizeof( intensityHeader );

            if ( ( fp = fopen( outputName, "wb" ) ) == NULL )
            {
                printf( "SaveDiffractionIntensities: Could open file %s for writing\n", outputName );
                return;
            }
            // We will write the data in the following format:
            // A header containing the necessary global information will be written first.
            // Each pattern will be written separately, starting with the number of beams it contains
            // and its tilt vector,
            // followed by 4-tuples comprised of the 3 indices and then the intensity.
            fwrite( ( void* )&iHeader, iHeader.headerSize, 1, fp );
            for ( int count = 0; count < nPatterns; count++ )
            {
                //data[count].writeIntensityData( fp );
                data[count].writeIntensityData( fp );
                // if ( count < 20 )
                  // std::cout << count << ":\n" << data[count] << "\n";
            }
            fclose( fp );

            // data[nPatterns>>2].displayDiagonal();
        }

        // This function/method loads experimental diffraction intensities from a data file, in binary format
        void LoadDiffractionIntensities( char* inputName )
        {
            FILE* fp;
            intensityHeader iHeader;

            if ( ( fp = fopen( inputName, "rb" ) ) == NULL )
            {
                printf( "LoadDiffractionIntensities: Could open file %s for reading\n", inputName );
                return;
            }
            fread( ( void* )&iHeader, sizeof( intensityHeader ), 1, fp );
            nPatterns = iHeader.Ntilts;
            data.resize( nPatterns );
            for ( int count = 0; count < nPatterns; count++ )
            {
                data[count].SetZone( zone, gx, gy );
                data[count].readIntensityData( fp, lambda, n, ptrXtal );
                data[count].FillIndexArray();
            }
            fclose( fp );

            // data[nPatterns>>2].displayDiagonal();

        }



        void CreateDiffPat( char* outputName, int detectorNx, int detectorNy, ftype scanComp )
        {
            int count;
            std::vector<ftype> pix;
            ftype dkDisc = dk * ( 1.0f - scanComp ); // pixel size in diffraction pattern


            pix.resize( detectorNx * detectorNy, 0.0f );
            for ( count = 0; count < nPatterns; count++ )
            {
                data[count].AddPatternToImg( pix, detectorNx, detectorNy, dkDisc, ptrXtal );
            }

            /*
            for (int iy=0;iy<detectorNy;iy++) {
            for (int ix=0;ix<detectorNx;ix++) printf("%7.3f ",pix[ix+iy*detectorNx]);
            printf("\n");
            }
            */

            ImageLib img( detectorNx, detectorNy, dkDisc, dkDisc );
            img.WriteRealImage( ( void* ) & ( pix[0] ), outputName, sizeof( ftype ), thickness );
            pix.resize( 0 );
        }

        void CreateBeamCountMap()
        {
            int count, index;
            std::vector<ftype> pix;
            std::vector<ftype> pix2;
            ftype dkDisc = dk;  // pixel size in diffraction pattern


            pix.resize( ( 2 * ir + 1 ) * ( 2 * ir + 1 ), 0.0f );
            pix2.resize( ( 2 * ir + 1 ) * ( 2 * ir + 1 ), 0.0f );
            ImageLib img( ( 2 * ir + 1 ), ( 2 * ir + 1 ), dkDisc, dkDisc );

            // map of the number of beams (size of A-matrix)
            for ( count = 0; count < nPatterns; count++ )
            {
                pix[data[count].ikx + ir + ( 2 * ir + 1 ) * ( data[count].iky + ir )] = data[count].nBeams;
            }
            img.WriteRealImage( ( void* ) & ( pix[0] ), "nBeamMap.img", sizeof( ftype ), thickness );

            // map of the number of unique beams in matrix:
            for ( count = 0; count < nPatterns; count++ )
            {
                pix[data[count].ikx + ir + ( 2 * ir + 1 ) * ( data[count].iky + ir )] = data[count].beamCount;
            }
            img.WriteRealImage( ( void* ) & ( pix[0] ), "beamCountMap.img", sizeof( ftype ), thickness );

            // map of the smallest excitation error:
            for ( count = 0; count < nPatterns; count++ )
            {
                pix[data[count].ikx + ir + ( 2 * ir + 1 ) * ( data[count].iky + ir )] = data[count].FindSmallestKsg2( index );
                pix2[data[count].ikx + ir + ( 2 * ir + 1 ) * ( data[count].iky + ir )] = index;
            }
            img.WriteRealImage( ( void* ) & ( pix[0] ), "smallestKsg2.img", sizeof( ftype ), thickness );
            img.WriteRealImage( ( void* ) & ( pix2[0] ), "closestBeamIndex.img", sizeof( ftype ), thickness );

            for ( count = 0; count < nPatterns; count++ )
            {
                pix[data[count].ikx + ir + ( 2 * ir + 1 ) * ( data[count].iky + ir )] = data[count].gmin1.ksg2;
            }
            img.WriteRealImage( ( void* ) & ( pix[0] ), "smallestKsg2a.img", sizeof( ftype ), thickness );

            for ( count = 0; count < nPatterns; count++ )
            {
                pix[data[count].ikx + ir + ( 2 * ir + 1 ) * ( data[count].iky + ir )] = data[count].gmin2.ksg2;
            }
            img.WriteRealImage( ( void* ) & ( pix[0] ), "smallestKsg2b.img", sizeof( ftype ), thickness );

            pix.resize( 0 );
        }

        ftype FitKinematicRockingCurves( ftype& thickness )
        {
            double T1, T2, T3;
            ftype absUnSquared, errVal = 0.0f;
            // each pattern can access the structure factor values in the Ug matser list in the following way:
            // masterUg[beamList.beams[indexMatrix[ix*nBeams]].masterIndex]
            // We will therefore simply loop through all reflections in the masterUg-list and ask each pattern
            // to loo if this beam is somewhere in its list of beams.  If yes, we let that pattern compute its
            // contribution to the following terms:
            // T_1 = sum_j |C1_nm(kj,t)|^2*Iexp_n(kj)   and   T_2 = sum_j |C1_nm(kj,t)|^4
            // The structure factor amplitude squared is then given by |U_n|^2 = T_1 / T_2, for some trial thickness t

            printf( "Fitting linear rocking curve using trial thickness = %f nm\n", 0.1 * thickness );
            ugMasterListSize = indexMasterArray.beams.size();
            ugMasterList.resize( ugMasterListSize, 0 );
            for ( int ib = 1; ib < ugMasterListSize; ib++ )
            {
                // assign, initially, some small random number:
                ugMasterList[ib] = complex_type( 1e-6 * ( rand() / RAND_MAX - 0.5 ), 1e-6 * ( rand() / RAND_MAX - 0.5 ) );
                // if (ib % 50 == 0) printf(".");
                T1 = 0.0;
                T2 = 0.0;
                T3 = 0.0;
                for ( int ip = 0; ip < nPatterns; ip++ )
                {
                    data[ip].AddKinematicRockingCurveContribution( ib, T1, T2, T3, thickness );
                    // printf("ib = %2d, ip = %d\n",ib,ip);
                }
                absUnSquared = ( T2 > 1e-12 ) ? abs( T1 / T2 ) : 0.0f;
                errVal += 0.5 * ( absUnSquared * absUnSquared * T2 - 2.0 * absUnSquared * T1 + T3 );
                // ugMasterList[ib] = complex_type(sqrt(absUnSquared)*(1.0f-2.0f*(std::rand()>>14)), 0.0f);
                // ugMasterList[ib] = (complex_type)polar((ftype)sqrt(absUnSquared), 6.2832f*(ftype)std::rand()/RAND_MAX);
                // ugMasterList[ib] = complex_type(sqrt(absUnSquared), 0.0f)+2e-8f*((ftype)(std::rand())/RAND_MAX-0.5f);
                ugMasterList[ib] = complex_type( sqrt( absUnSquared ), 0.0f );
            }
            // We now have a chance to also refine the specimen thickness:

            return errVal / nPatterns;
        }


        ftype DoLineSearch( int maxQ, ftype thickness, ftype curScale, ftype errVal, int  subtractKinematic = 0 )
        {
            int ib, ip;
            double errVal1 = 0, errVal2 = 0, newScale;
            double der2;  // 2nd derivative

            if ( errVal < 1e-6 )
            {
                return 0.0;
            }
            for ( ib = 0; ib < ugMasterListSize; ib++ )
            {
                trialUg[ib] = ugMasterList[ib] - curScale * ugMasterListGrad[ib];
                if ( abs( trialUg[ib] ) > 1.1 )
                {
                    trialUg[ib] = 1.1 * trialUg[ib] / abs( trialUg[ib] );
                }
            }
            for ( ip = 0; ip < nPatterns; ip++ )
            {
                errVal1 += data[ip].MeasureError( trialUg, thickness, maxQ, subtractKinematic );
            }

            for ( ib = 0; ib < ugMasterListSize; ib++ )
            {
                trialUg[ib] = ugMasterList[ib] - 0.5 * curScale * ugMasterListGrad[ib];
                if ( abs( trialUg[ib] ) > 1.05 )
                {
                    trialUg[ib] = 1.05 * trialUg[ib] / abs( trialUg[ib] );
                }
            }
            for ( ip = 0; ip < nPatterns; ip++ )
            {
                errVal2 += data[ip].MeasureError( trialUg, thickness, maxQ, subtractKinematic );
            }
            // printf("Errors: %f, %f %f\n",errVal,errVal1,errVal2);
            if ( errVal1 < 1e-6 )
            {
                return curScale;
            }
            if ( errVal2 < 1e-6 )
            {
                return 0.5 * curScale;
            }
            // estimate a new scale value for future use:
            CalcParabolaVertex( 0, errVal, curScale, errVal1, 0.5 * curScale, errVal2, newScale, der2 );
            // printf("new value for scale: %f (2nd derivative = %g)\n",newScale,der2);
            if ( der2 > 0 )
            {
                // if (newScale < 0.1f*scale) newScale = 0.1f*scale;
                if ( newScale > 1.5 * curScale )
                {
                    newScale = 1.5 * curScale;
                }
                // if (newScale < 1e-6) newScale = 1e-6;
            }
            else
            {
                newScale = 1e-6;
            }
            return newScale;

        }

        ftype RefineStructureFactors( int maxQ, int maxIter, ftype& thickness )
        {
            ftype errVal, gradLen;
            int ib, ip, iter, emptyCount;

            printf( "** Global refinement:\n" );


            if ( scale < 5e-6 )
            {
                scale = 5e-6;
            }
            trialUg.resize( ugMasterListSize );
            ugMasterListGrad.resize( ugMasterListSize );
            ugMasterListGradCount.resize( ugMasterListSize );
            ugMasterListGradCountTemp.resize( ugMasterListSize );
            for ( iter = 0; iter < maxIter; iter++ )
            {
                emptyCount = 0;  // this counts th number of structure factors that we cannot measure from this data.
                // clear the gradient container:
                memset( ugMasterListGrad.data(), 0, ugMasterListSize * sizeof( complex_type ) );
                memset( ugMasterListGradCount.data(), 0, ugMasterListSize * sizeof( unsigned int ) );
                errVal = 0.0f;
                gradLen = 0.0f;
                for ( ip = 0; ip < nPatterns; ip++ )
                {
                    memset( ugMasterListGradCountTemp.data(), 0, ugMasterListSize * sizeof( unsigned int ) );
                    errVal += data[ip].ApproximateWaveGradient( ugMasterList, ugMasterListGrad, ugMasterListGradCountTemp, thickness, maxQ );
                    for ( ib = 0; ib < ugMasterListSize; ib++ )
                    {
                        ugMasterListGradCount[ib] += ( ugMasterListGradCountTemp[ib] > 0 );
                        gradLen += norm( ugMasterListGrad[ib] );
                    }
                }
                gradLen = sqrt( gradLen ) / nPatterns;

                // Now search along the line given by the gradient in ugMasterListGrad and then update ugMasterList.
                for ( ib = 0; ib < ugMasterListSize; ib++ )
                {
                    if ( ugMasterListGradCount[ib] == 0 )
                    {
                        emptyCount++;
                    }
                    // if (ugMasterListGradCount[ib] > 0) ugMasterListGrad[ib] /= ugMasterListGradCount[ib];
                    // if (ib < 20) printf("%3d: Ug=(%6.3f+i%6.3f), gradUg=(%6.3f+i%6.3f) [%d]\n",ib,100*ugMasterList[ib].real(),100*ugMasterList[ib].imag(),100*ugMasterListGrad[ib].real(),100*ugMasterListGrad[ib].imag(),ugMasterListGradCount[ib]);
                }



                scale = DoLineSearch( maxQ, thickness, scale, errVal );
                // printf("%3d: Current error value: %f, emptyCount = %d, scale = %g, |grad| = %g\n",iter,errVal/nPatterns,emptyCount,scale,gradLen);
                printf( "%3d: error: %f, ec = %d, scale = %g, |grad| = %g\n", iter, errVal / nPatterns, emptyCount, scale, gradLen );
                // data[nPatterns>>2].displayDiagonal();
                if ( ( scale < 1e-10 ) || ( errVal / nPatterns < 1e-8 ) )
                {
                    printf( "**************  Converged! (error = %f) *******************\n", errVal / nPatterns );
                    break;
                }
                for ( ib = 0; ib < ugMasterListSize; ib++ )
                {
                    ugMasterList[ib] -= scale * ugMasterListGrad[ib];
                }
                for ( ib = 0; ib < ugMasterListSize; ib++ ) if ( abs( ugMasterList[ib] ) > 1 )
                    {
                        ugMasterList[ib] = ugMasterList[ib] / abs( ugMasterList[ib] );
                    }

                resetU0();
            }
            return errVal / nPatterns;
        }


        ftype RefineStructureFactorsDynamicOnly( int maxQ, int maxIter, ftype& thickness )
        {
            ftype errVal;
            int ib, ip, iter, emptyCount;

            if ( scale < 5e-6 )
            {
                scale = 5e-6;
            }
            for ( int ip = 0; ip < nPatterns; ip++ )
            {
                data[ip].ComputeKinematicIntensity( ugMasterList, thickness );
                // printf("ib = %2d, ip = %d\n",ib,ip);
            }

            printf( "** Refinement of dynamical intensity only:\n" );

            trialUg.resize( ugMasterListSize );
            ugMasterListGrad.resize( ugMasterListSize );
            ugMasterListGradCount.resize( ugMasterListSize );
            ugMasterListGradCountTemp.resize( ugMasterListSize );
            for ( iter = 0; iter < maxIter; iter++ )
            {
                emptyCount = 0;  // this counts th number of structure factors that we cannot measure from this data.
                // clear the gradient container:
                memset( ugMasterListGrad.data(), 0, ugMasterListSize * sizeof( complex_type ) );
                memset( ugMasterListGradCount.data(), 0, ugMasterListSize * sizeof( unsigned int ) );
                errVal = 0.0f;
                for ( ip = 0; ip < nPatterns; ip++ )
                {
                    memset( ugMasterListGradCountTemp.data(), 0, ugMasterListSize * sizeof( unsigned int ) );
                    errVal += data[ip].ApproximateWaveGradient( ugMasterList, ugMasterListGrad, ugMasterListGradCountTemp, thickness, maxQ, 1 );
                    for ( ib = 0; ib < ugMasterListSize; ib++ )
                    {
                        ugMasterListGradCount[ib] += ( ugMasterListGradCountTemp[ib] > 0 );
                    }
                }

                // Now search along the line given by the gradient in ugMasterListGrad and then update ugMasterList.
                for ( ib = 0; ib < ugMasterListSize; ib++ )
                {
                    if ( ugMasterListGradCount[ib] == 0 )
                    {
                        emptyCount++;
                    }
                    // if (ugMasterListGradCount[ib] > 0) ugMasterListGrad[ib] /= ugMasterListGradCount[ib];
                    // if (ib < 20) printf("%3d: Ug=(%6.3f+i%6.3f), gradUg=(%6.3f+i%6.3f) [%d]\n",ib,100*ugMasterList[ib].real(),100*ugMasterList[ib].imag(),100*ugMasterListGrad[ib].real(),100*ugMasterListGrad[ib].imag(),ugMasterListGradCount[ib]);
                }

                scale = DoLineSearch( maxQ, thickness, scale, errVal, 1 );
                printf( "%3d: Current error value: %f, emptyCount = %d, scale = %g\n", iter, errVal / nPatterns, emptyCount, scale );
                // data[nPatterns>>2].displayDiagonal();
                if ( ( scale < 1e-10 ) || ( errVal / nPatterns < 1e-5 ) )
                {
                    printf( "**************  Converged! (error = %f) *******************\n", errVal / nPatterns );
                    break;
                }
                for ( ib = 0; ib < ugMasterListSize; ib++ )
                {
                    ugMasterList[ib] -= scale * ugMasterListGrad[ib];
                }
                PrintUgMasterList( "beams.txt" );


                for ( ib = 0; ib < ugMasterListSize; ib++ ) if ( abs( ugMasterList[ib] ) > 1 )
                    {
                        ugMasterList[ib] = ugMasterList[ib] / abs( ugMasterList[ib] );
                    }
                resetU0();
            }
            return errVal / nPatterns;
        }



        ftype RefineStructureFactorsLocal( int maxQ, int maxIter, ftype& thickness )
        {
            ftype errVal, errContrib;
            int ib, ip, iter, emptyCount;

            if ( scale < 5e-6 )
            {
                scale = 5e-6;
            }
            // initialize the necessary vectors:
            ugMasterListGradCount.resize( ugMasterListSize );
            // for (ib = 0;ib<ugMasterListSize;ib++) ugMasterList[ib] += complex_type(1e-6*(rand()/RAND_MAX-0.5),1e-6*(rand()/RAND_MAX-0.5));
            for ( ip = 0; ip < nPatterns; ip++ )
            {
                data[ip].InitUgListLocal( ugMasterList );
            }

            printf( "** Multivariate refinement:\n" );
            for ( iter = 0; iter < maxIter; iter++ )
            {
                // reset the global structure factor maste list.  It will be used to
                // hold the average structure factor at each iteration.
                memset( ugMasterList.data(), 0, ugMasterListSize * sizeof( complex_type ) );
                memset( ugMasterListGradCount.data(), 0, ugMasterListSize * sizeof( unsigned int ) );


                emptyCount = 0;  // this counts th number of structure factors that we cannot measure from this data.
                // clear the gradient container:
                errVal = 0.0f;

                for ( ip = 0; ip < nPatterns; ip++ )
                {
                    // if (iter % 3 == 0) data[ip].IncrementDatasetOffset();
                    errContrib = data[ip].RefineStructurefactorsLocal( thickness, maxQ );
                    // if (ip < 60) {printf("%2d-%2d: %6.4f, ",ip,data[ip].nBeams,errContrib);  if ((ip+1) % 5 == 0) printf("\n"); }

                    errVal += errContrib;
                    data[ip].ContributeToAverage( ugMasterList, ugMasterListGradCount );
                }
                // Now search along the line given by the gradient in ugMasterListGrad and then update ugMasterList.
                for ( ib = 0; ib < ugMasterListSize; ib++ )
                {
                    if ( ugMasterListGradCount[ib] > 0 )
                    {
                        ugMasterList[ib] /= ugMasterListGradCount[ib];
                    }
                    else
                    {
                        emptyCount++;
                    }
                    // if (ib < 20) printf("%3d: Ug=(%6.3f+i%6.3f), gradUg=(%6.3f+i%6.3f) [%d]\n",ib,100*ugMasterList[ib].real(),100*ugMasterList[ib].imag(),100*ugMasterListGrad[ib].real(),100*ugMasterListGrad[ib].imag(),ugMasterListGradCount[ib]);
                }

                PrintUgMasterList( "beams.txt" );

                for ( ib = 0; ib < ugMasterListSize; ib++ ) if ( abs( ugMasterList[ib] ) > 1 )
                    {
                        ugMasterList[ib] = ugMasterList[ib] / abs( ugMasterList[ib] );
                    }
                PrintUgMasterList( "beams.txt" );
                for ( scale = 0, ip = 0; ip < nPatterns; ip++ )
                {
                    scale += data[ip].GetGradientScale();
                }
                printf( "%3d: error: %f, emptyCount = %d, scale = %g\n", iter, errVal / nPatterns, emptyCount, scale / nPatterns );
                if ( ( scale / nPatterns < 1e-10 ) || ( errVal / nPatterns < 1e-6 ) )
                {
                    printf( "**************  Converged! (error = %f) *******************\n", errVal / nPatterns );
                    break;
                }

            }
            return errVal / nPatterns;
        }





        ~PatternCollection( void )
        {
        }



};

#endif//_P49IEJASKLNASFNMVLAJN948ASFDKLJV3FZASDSADPOIESAFJDHVM9NQIOU4089KFAJHVAKJHSFDA
