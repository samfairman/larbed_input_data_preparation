#include <f/beam/make_ar.hpp>
#include <iostream>
#include <vector>

int main()
{
#if 0
    if (0)
    {
        //auto bl = f::make_beam_list("./testdata/txt/beam.txt");
        //std::vector<unsigned long> varr( 63 );
        //auto bl = f::make_beam_list("./matrix/beam/SrTiO3_selected.txt");
        //auto bl = f::make_beam_list("./matrix/beam/SrTiO3_demo.txt");
        //auto bl = f::make_beam_list("./matrix/beam/SrTiO3_full.txt");
        auto bl = f::make_beam_list("/testpool/ops/samfairman/feng_MC19/testdata/test_Sam/beam_selected.txt");
        //std::vector<unsigned long> varr( 45 );
        std::vector<unsigned long> varr( 53 );
        for ( unsigned long index = 0; index != varr.size(); ++index )
            varr[index] = index;

        auto const& ar = f::make_ar( bl, varr.begin(), varr.end() );

        ar.save_as( "/testpool/ops/samfairman/feng_MC19/testdata/test_Sam/23_10_19_ar.txt" );

        f::matrix<long> new_beam( bl.index_beam_map.size(), 4 );
        for ( auto& elem : bl.index_beam_map )
        {
            long index = elem.first;
            long mh = elem.second.mh;
            long mk = elem.second.mk;
            long ml = elem.second.ml;
            new_beam[index][0] = index;
            new_beam[index][1] = mh;
            new_beam[index][2] = mk;
            new_beam[index][3] = ml;
        }

        new_beam.save_as( "new_beam.txt" );
    }

    if (0)
    {
        auto bl = f::make_beam_list("./matrix/beam/Si_se_selected.txt");
        std::vector<unsigned long> varr( 45 );
        for ( unsigned long index = 0; index != varr.size(); ++index )
            varr[index] = index;

        auto const& ar = f::make_ar( bl, varr.begin(), varr.end() );

        ar.save_as( "./new_ar.txt" );

        f::matrix<long> new_beam( bl.index_beam_map.size(), 45 );
        for ( auto& elem : bl.index_beam_map )
        {
            long index = elem.first;
            long mh = elem.second.mh;
            long mk = elem.second.mk;
            long ml = elem.second.ml;
            new_beam[index][0] = index;
            new_beam[index][1] = mh;
            new_beam[index][2] = mk;
            new_beam[index][3] = ml;
        }

        new_beam.save_as( "new_beam.txt" );
    }
#endif
    
#if 1
    {
        //auto bl = f::make_beam_list("/testpool/ops/samfairman/feng_MC19/testdata/test_Sam/beam_selected_6.txt");
        auto bl = f::make_beam_list("/testpool/ops/samfairman/QEDA/bin/Examples/2020_01_15_SrTiO3_T0/_feng_input_zero_tilt/beams.txt");
        std::vector<unsigned long> varr( 9 );
        for ( unsigned long index = 0; index != varr.size(); ++index )
            varr[index] = index;

        auto const& ar = f::make_ar( bl, varr.begin(), varr.end() );

        //ar.save_as( "/testpool/ops/samfairman/feng_MC19/testdata/test_Sam/Ar_0.txt" );
        
        ar.save_as( "/testpool/ops/samfairman/QEDA/bin/Examples/2020_01_15_SrTiO3_T0/_feng_input_zero_tilt/Ar_ALL.txt" );

        f::matrix<long> new_beam( bl.index_beam_map.size(), 4 );
        for ( auto& elem : bl.index_beam_map )
        {
            long index = elem.first;
            long mh = elem.second.mh;
            long mk = elem.second.mk;
            long ml = elem.second.ml;
            new_beam[index][0] = index;
            new_beam[index][1] = mh;
            new_beam[index][2] = mk;
            new_beam[index][3] = ml;
        }

         //new_beam.save_as( "/testpool/ops/samfairman/feng_MC19/testdata/test_Sam/new_beam.txt" );
         new_beam.save_as( "/testpool/ops/samfairman/QEDA/bin/Examples/2020_01_15_SrTiO3_T0/_feng_input_zero_tilt/new_beams.txt" );
        
    }
    
    
#endif
    return 0;
}
