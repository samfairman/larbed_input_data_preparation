#include <qeda/Crystal.h>
#include <qeda/Reflection.h>
#include <qeda/readparams.h>
#include <qeda/DataTypes.h>
#include <qeda/Crystal.h>
#include <qeda/PatternCollection.h>
#include <f/matrix/matrix.hpp>


#include <string>
#include <cassert>
#include <iomanip>

int main()
{

    #if 0
    {
        f::matrix<int> reflections;
        //reflections.load("./testdata/working/new_beam.txt");
        //reflections.load("./matrix/beam/SrTiO3.txt");
        //reflections.load("./matrix/beam/SrTiO3_selected.txt");
        //reflections.load("./matrix/beam/SrTiO3_selected_full.txt");
        reflections.load("./matrix/beam/SrTiO3_full.txt");
        //reflections.load("./matrix/beam/TlNbO_demo_full.txt");
        //reflections.load("./matrix/beam/TlNbO_selected_full.txt");
        assert( reflections.row() );
        assert( reflections.col() == 4 );
        //assert( reflections.col() == 3 );

        std::string file_path{"SrTiO3.cfg"};
        //std::string file_path{"TlNbO.cfg"};
        Crystal xtal( file_path.c_str() );
        double const energy = 120.0;

        f::matrix<double> mug{ reflections.row(), 2 };

        for ( unsigned long index = 0; index != reflections.row(); ++index )
        {
            Reflection r{ reflections[index][1], reflections[index][2], reflections[index][3] };
            auto ug = xtal.ComputeStructureFactor( &r, energy );
            std::cout.precision( 15 );

            std::cout   << reflections[index][1] << "\t"
                        << reflections[index][2] << "\t" 
                        << reflections[index][3] << "\t" 
                        << std::real(ug) << "\t" 
                        << std::imag(ug) << "\n";
            mug[index][0] = std::real(ug);
            mug[index][1] = std::imag(ug);
        }

        //mug.save_as( "./matrix/ug/TlNbO_selected_full.txt" );
        mug.save_as( "./matrix/ug/SrTiO3_full.txt" );
    }
    #endif 
    #if 0
    {
        f::matrix<int> reflections;
        //reflections.load("./testdata/working/new_beam.txt");
        //reflections.load("./matrix/beam/SrTiO3.txt");
        //reflections.load("./matrix/beam/SrTiO3_selected.txt");
        //reflections.load("./matrix/beam/SrTiO3_selected_full.txt");
        //reflections.load("./matrix/beam/SrTiO3_full.txt");
        //reflections.load("./matrix/beam/TlNbO_demo_full.txt");
        reflections.load("./matrix/beam/Si_se_full.txt");
        //reflections.load("./matrix/beam/TlNbO_selected_full.txt");
        assert( reflections.row() );
        assert( reflections.col() == 4 );
        //assert( reflections.col() == 3 );

        std::string file_path{"Si.cfg"};
        //std::string file_path{"TlNbO.cfg"};
        Crystal xtal( file_path.c_str() );
        double const energy = 120.0;

        f::matrix<double> mug{ reflections.row(), 2 };

        for ( unsigned long index = 0; index != reflections.row(); ++index )
        {
            Reflection r{ reflections[index][1], reflections[index][2], reflections[index][3] };
            auto ug = xtal.ComputeStructureFactor( &r, energy );
            std::cout.precision( 15 );

            std::cout   << reflections[index][1] << "\t"
                        << reflections[index][2] << "\t" 
                        << reflections[index][3] << "\t" 
                        << std::real(ug) << "\t" 
                        << std::imag(ug) << "\n";
            mug[index][0] = std::real(ug);
            mug[index][1] = std::imag(ug);
        }

        //mug.save_as( "./matrix/ug/TlNbO_selected_full.txt" );
        mug.save_as( "./matrix/ug/Si_se_full.txt" );
    }
    #endif 

    #if 0
    {
        f::matrix<int> reflections;
        reflections.load("./matrix/beam/TlNbO_selected_full.txt");
        assert( reflections.row() );
        assert( reflections.col() == 4 );

        std::string file_path{"TlNbO.cfg"};
        Crystal xtal( file_path.c_str() );
        double const energy = 120.0;

        f::matrix<double> mug{ reflections.row(), 2 };

        for ( unsigned long index = 0; index != reflections.row(); ++index )
        {
            Reflection r{ reflections[index][1], reflections[index][2], reflections[index][3] };
            auto ug = xtal.ComputeStructureFactor( &r, energy );
            std::cout.precision( 15 );

            std::cout   << reflections[index][1] << "\t"
                        << reflections[index][2] << "\t" 
                        << reflections[index][3] << "\t" 
                        << std::real(ug) << "\t" 
                        << std::imag(ug) << "\n";
            mug[index][0] = std::real(ug);
            mug[index][1] = std::imag(ug);
        }

        mug.save_as( "./matrix/ug/TlNbO_selected_full.txt" );
    }
    #endif 

    #if 1
    {
        f::matrix<int> reflections;
        reflections.load("/testpool/ops/samfairman/QEDA/bin/Examples/2020_01_15_SrTiO3_T0/_feng_input_zero_tilt/make_beam_list.txt");

        assert( reflections.row() );
        assert( reflections.col() == 4 );

        std::string file_path{"/testpool/ops/samfairman/QEDA/bin/materials/SrTiO3.cfg"};
        Crystal xtal( file_path.c_str() );
        double const energy = 300.0;

        f::matrix<double> mug{ reflections.row(), 2 };

        for ( unsigned long index = 0; index != reflections.row(); ++index )
        {
            std::cout<<"\nSAM"<<reflections.row()<<"\n"<<std::endl;
            Reflection r{ reflections[index][1], reflections[index][2], reflections[index][3] };
            auto ug = xtal.ComputeStructureFactor( &r, energy );
            std::cout.precision( 15 );

            std::cout   << reflections[index][1] << "\t"
                        << reflections[index][2] << "\t" 
                        << reflections[index][3] << "\t" 
                        << std::real(ug) << "\t" 
                        << std::imag(ug) << "\n";
            mug[index][0] = std::real(ug);
            mug[index][1] = std::imag(ug);
        }


        //mug.save_as( "./matrix/ug/TlNbO_selected_full.txt" );
        mug.save_as( "/testpool/ops/samfairman/QEDA/bin/Examples/2020_01_15_SrTiO3_T0/_feng_input_zero_tilt/ug.txt" );
        
        std::cout<<"\nDid this run\n"<<std::endl;
    }
    #endif

    return 0;
}
