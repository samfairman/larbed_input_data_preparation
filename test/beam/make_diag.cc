#include <f/matrix/matrix.hpp>
#include <f/wave_length/wave_length.hpp>
#include <cassert>

void make_diag( unsigned long const dim, double angle, double ev, std::string const& tilt, std::string const& beam, std::string const& unit_cell, std::string const& rotation, std::string const& output )
{
    f::matrix<double> tilt_;
    tilt_.load( tilt );
    assert( tilt_.row() );
    assert( tilt_.col() == 2 );

    f::matrix<int> beam_;
    beam_.load( beam );
    assert( beam_.row() );
    assert( beam_.col() == 3 || beam_.col() == 4 );
    f::matrix<double> new_beam( beam_.row(), 3 );
    if ( 3 == beam_.col() )
    for ( unsigned long r = 0; r != new_beam.row(); ++r )
        for ( unsigned long c = 0; c != new_beam.col(); ++c )
            new_beam[r][c] = beam_[r][c];
    if ( 4 == beam_.col() )
    for ( unsigned long r = 0; r != new_beam.row(); ++r )
        for ( unsigned long c = 0; c != new_beam.col(); ++c )
            new_beam[r][c] = beam_[r][c+1];

    f::matrix<double> unit_cell_;
    unit_cell_.load( unit_cell );
    assert( unit_cell_.row() == 3 );
    assert( unit_cell_.col() == 3 );


    f::matrix<double> rotation_;
    rotation_.load( rotation );
    assert( rotation_.row() == 1 );
    assert( rotation_.col() == 1 );

    // 1
    new_beam /= unit_cell_;

    // 2
    tilt_ *= angle;
    tilt_ /= 1000.0;
    double lambda = f::wave_length( ev );
    f::matrix<double> kt( tilt_.row(), tilt_.col() );
    std::transform( tilt_.begin(), tilt_.end(), kt.begin(), [&]( double ang ){ return std::sin(ang)/lambda; } );

    // 2.5
    double const rotation_angle = rotation_[0][0];
    f::matrix<double> rot( 2, 2 );
    rot[0][0] = std::cos( rotation_angle ); rot[0][1] = -std::sin( rotation_angle );
    rot[1][0] = std::sin( rotation_angle ); rot[1][1] = std::cos( rotation_angle );
    kt *= rot;
    std::cout<<"kt=\n"<<kt<<std::endl;

    // 3
    f::matrix<double> diag( dim, kt.row() );

    for ( unsigned long r = 0; r != diag.row(); ++r )
        for ( unsigned long c = 0; c != diag.col(); ++c )
        {
            double const gx = new_beam[r][0];
            double const gy = new_beam[r][1];
            double const kx = kt[c][0];
            double const ky = kt[c][1];
            diag[r][c] = -2.0*kx*gx - 2.0*ky*gy - gx*gx - gy*gy;
        }
    diag.save_as( output );
}


int main()
{
    std::cout<<"hello"<<std::endl;
    make_diag( 9, 0, 300.0,
    std::string{"/testpool/ops/samfairman/QEDA/bin/Examples/2020_01_15_SrTiO3_T0/_feng_input_zero_tilt/tilts_simple.txt"}, 
    std::string{"/testpool/ops/samfairman/QEDA/bin/Examples/2020_01_15_SrTiO3_T0/_feng_input_zero_tilt/new_beams.txt"}, 
    std::string{"/testpool/ops/samfairman/QEDA/bin/Examples/2020_01_15_SrTiO3_T0/_feng_input_zero_tilt/SrTiO3_unit_cell.txt"}, 
    std::string{"/testpool/ops/samfairman/QEDA/bin/Examples/2020_01_15_SrTiO3_T0/_feng_input_zero_tilt/SrTiO3_rotation.txt"}, 
    std::string{"/testpool/ops/samfairman/QEDA/bin/Examples/2020_01_15_SrTiO3_T0/_feng_input_zero_tilt/Diag_ALL_output.txt"}  );
    
    //make_diag( 13, 0.0, 300.0, std::string{"testpool/ops/samfairman/feng_MC19/testdata/new_txt_unequal_A_matrix/SiTiO3_tilt.txt"}, std::string{"testpool/ops/samfairman/feng_MC19/testdata/new_txt_unequal_A_matrix/beam_selected.txt"}, std::string{"testpool/ops/samfairman/feng_MC19/testdata/new_txt_unequal_A_matrix/SiTiO3_unit_cell.txt"}, std::string{"testpool/ops/samfairman/feng_MC19/testdata/new_txt_unequal_A_matrix/SiTiO3_rotation.txt"}, std::string{ "testpool/ops/samfairman/feng_MC19/testdata/new_txt_unequal_A_matrix/unequal_diag.txt"} );
#if 0
    make_diag( 13, 100.0, 0.0, std::string{"matrix/tilt/SrTiO3.txt"}, std::string{"matrix/beam/SrTiO3.txt"}, std::string{"matrix/unit_cell/SrTiO3.txt"}, std::string{"matrix/rotation/SrTiO3.txt"}, std::string{ "SrTiO3_100.txt"} );
    make_diag( 13, 100.0, 0.0, std::string{"matrix/tilt/SrTiO3.txt"}, std::string{"matrix/beam/SrTiO3.txt"}, std::string{"matrix/unit_cell/SrTiO3.txt"}, std::string{"matrix/rotation/SrTiO3.txt"}, std::string{ "SrTiO3_100.txt"} );
    make_diag( 13, 100.0, 0.0, std::string{"matrix/tilt/SrTiO3.txt"}, std::string{"matrix/beam/SrTiO3.txt"}, std::string{"matrix/unit_cell/SrTiO3.txt"}, std::string{"matrix/rotation/SrTiO3.txt"}, std::string{ "SrTiO3_100.txt"} );
    make_diag( 13, 100.0, 0.0, std::string{"matrix/tilt/SrTiO3.txt"}, std::string{"matrix/beam/SrTiO3.txt"}, std::string{"matrix/unit_cell/SrTiO3.txt"}, std::string{"matrix/rotation/SrTiO3.txt"}, std::string{ "SrTiO3_100.txt"} );
    make_diag( 13, 100.0, 0.0, std::string{"matrix/tilt/SrTiO3.txt"}, std::string{"matrix/beam/SrTiO3.txt"}, std::string{"matrix/unit_cell/SrTiO3.txt"}, std::string{"matrix/rotation/SrTiO3.txt"}, std::string{ "SrTiO3_100.txt"} );
#endif
    /*
    make_diag( 45, 100.0, 120.0, std::string{"matrix/tilt/SrTiO3.txt"}, std::string{"matrix/beam/SrTiO3.txt"}, std::string{"matrix/unit_cell/SrTiO3.txt"}, std::string{"matrix/rotation/SrTiO3.txt"}, std::string{ "SrTiO3_100.txt"} );
    make_diag( 45, 90.0, 120.0, std::string{"matrix/tilt/SrTiO3.txt"}, std::string{"matrix/beam/SrTiO3.txt"}, std::string{"matrix/unit_cell/SrTiO3.txt"}, std::string{"matrix/rotation/SrTiO3.txt"}, std::string{ "SrTiO3_90.txt"} );
    make_diag( 45, 80.0, 120.0, std::string{"matrix/tilt/SrTiO3.txt"}, std::string{"matrix/beam/SrTiO3.txt"}, std::string{"matrix/unit_cell/SrTiO3.txt"}, std::string{"matrix/rotation/SrTiO3.txt"}, std::string{ "SrTiO3_80.txt"} );
    make_diag( 45, 70.0, 120.0, std::string{"matrix/tilt/SrTiO3.txt"}, std::string{"matrix/beam/SrTiO3.txt"}, std::string{"matrix/unit_cell/SrTiO3.txt"}, std::string{"matrix/rotation/SrTiO3.txt"}, std::string{ "SrTiO3_70.txt"} );
    make_diag( 45, 60.0, 120.0, std::string{"matrix/tilt/SrTiO3.txt"}, std::string{"matrix/beam/SrTiO3.txt"}, std::string{"matrix/unit_cell/SrTiO3.txt"}, std::string{"matrix/rotation/SrTiO3.txt"}, std::string{ "SrTiO3_60.txt"} );
    make_diag( 45, 50.0, 120.0, std::string{"matrix/tilt/SrTiO3.txt"}, std::string{"matrix/beam/SrTiO3.txt"}, std::string{"matrix/unit_cell/SrTiO3.txt"}, std::string{"matrix/rotation/SrTiO3.txt"}, std::string{ "SrTiO3_50.txt"} );
    make_diag( 45, 40.0, 120.0, std::string{"matrix/tilt/SrTiO3.txt"}, std::string{"matrix/beam/SrTiO3.txt"}, std::string{"matrix/unit_cell/SrTiO3.txt"}, std::string{"matrix/rotation/SrTiO3.txt"}, std::string{ "SrTiO3_40.txt"} );
    make_diag( 45, 30.0, 120.0, std::string{"matrix/tilt/SrTiO3.txt"}, std::string{"matrix/beam/SrTiO3.txt"}, std::string{"matrix/unit_cell/SrTiO3.txt"}, std::string{"matrix/rotation/SrTiO3.txt"}, std::string{ "SrTiO3_30.txt"} );
    make_diag( 45, 20.0, 120.0, std::string{"matrix/tilt/SrTiO3.txt"}, std::string{"matrix/beam/SrTiO3.txt"}, std::string{"matrix/unit_cell/SrTiO3.txt"}, std::string{"matrix/rotation/SrTiO3.txt"}, std::string{ "SrTiO3_20.txt"} );
    make_diag( 45, 10.0, 120.0, std::string{"matrix/tilt/SrTiO3.txt"}, std::string{"matrix/beam/SrTiO3.txt"}, std::string{"matrix/unit_cell/SrTiO3.txt"}, std::string{"matrix/rotation/SrTiO3.txt"}, std::string{ "SrTiO3_10.txt"} );
    make_diag( 45, 5.0, 120.0, std::string{"matrix/tilt/SrTiO3.txt"}, std::string{"matrix/beam/SrTiO3.txt"}, std::string{"matrix/unit_cell/SrTiO3.txt"}, std::string{"matrix/rotation/SrTiO3.txt"}, std::string{ "SrTiO3_5.txt"} );
    make_diag( 45, 1.0, 120.0, std::string{"matrix/tilt/SrTiO3.txt"}, std::string{"matrix/beam/SrTiO3.txt"}, std::string{"matrix/unit_cell/SrTiO3.txt"}, std::string{"matrix/rotation/SrTiO3.txt"}, std::string{ "SrTiO3_1.txt"} );
    */
    #if 0
    make_diag( 45, 240.0, 120.0, std::string{"matrix/tilt/TlNbO_demo.txt"}, std::string{"matrix/beam/TlNbO_demo.txt"}, std::string{"matrix/unit_cell/TlNbO_demo.txt"}, std::string{"matrix/rotation/TlNbO_demo.txt"}, std::string{ "TlNbO_demo_240.txt"} );
    make_diag( 45, 200.0, 120.0, std::string{"matrix/tilt/TlNbO_demo.txt"}, std::string{"matrix/beam/TlNbO_demo.txt"}, std::string{"matrix/unit_cell/TlNbO_demo.txt"}, std::string{"matrix/rotation/TlNbO_demo.txt"}, std::string{ "TlNbO_demo_200.txt"} );
    make_diag( 45, 160.0, 120.0, std::string{"matrix/tilt/TlNbO_demo.txt"}, std::string{"matrix/beam/TlNbO_demo.txt"}, std::string{"matrix/unit_cell/TlNbO_demo.txt"}, std::string{"matrix/rotation/TlNbO_demo.txt"}, std::string{ "TlNbO_demo_160.txt"} );
    make_diag( 45, 120.0, 120.0, std::string{"matrix/tilt/TlNbO_demo.txt"}, std::string{"matrix/beam/TlNbO_demo.txt"}, std::string{"matrix/unit_cell/TlNbO_demo.txt"}, std::string{"matrix/rotation/TlNbO_demo.txt"}, std::string{ "TlNbO_demo_120.txt"} );
    make_diag( 45, 100.0, 120.0, std::string{"matrix/tilt/TlNbO_demo.txt"}, std::string{"matrix/beam/TlNbO_demo.txt"}, std::string{"matrix/unit_cell/TlNbO_demo.txt"}, std::string{"matrix/rotation/TlNbO_demo.txt"}, std::string{ "TlNbO_demo_100.txt"} );
    make_diag( 45, 90.0, 120.0, std::string{"matrix/tilt/TlNbO_demo.txt"}, std::string{"matrix/beam/TlNbO_demo.txt"}, std::string{"matrix/unit_cell/TlNbO_demo.txt"}, std::string{"matrix/rotation/TlNbO_demo.txt"}, std::string{ "TlNbO_demo_90.txt"} );
    make_diag( 45, 80.0, 120.0, std::string{"matrix/tilt/TlNbO_demo.txt"}, std::string{"matrix/beam/TlNbO_demo.txt"}, std::string{"matrix/unit_cell/TlNbO_demo.txt"}, std::string{"matrix/rotation/TlNbO_demo.txt"}, std::string{ "TlNbO_demo_80.txt"} );
    make_diag( 45, 70.0, 120.0, std::string{"matrix/tilt/TlNbO_demo.txt"}, std::string{"matrix/beam/TlNbO_demo.txt"}, std::string{"matrix/unit_cell/TlNbO_demo.txt"}, std::string{"matrix/rotation/TlNbO_demo.txt"}, std::string{ "TlNbO_demo_70.txt"} );
    make_diag( 45, 60.0, 120.0, std::string{"matrix/tilt/TlNbO_demo.txt"}, std::string{"matrix/beam/TlNbO_demo.txt"}, std::string{"matrix/unit_cell/TlNbO_demo.txt"}, std::string{"matrix/rotation/TlNbO_demo.txt"}, std::string{ "TlNbO_demo_60.txt"} );
    make_diag( 45, 50.0, 120.0, std::string{"matrix/tilt/TlNbO_demo.txt"}, std::string{"matrix/beam/TlNbO_demo.txt"}, std::string{"matrix/unit_cell/TlNbO_demo.txt"}, std::string{"matrix/rotation/TlNbO_demo.txt"}, std::string{ "TlNbO_demo_50.txt"} );
    make_diag( 45, 40.0, 120.0, std::string{"matrix/tilt/TlNbO_demo.txt"}, std::string{"matrix/beam/TlNbO_demo.txt"}, std::string{"matrix/unit_cell/TlNbO_demo.txt"}, std::string{"matrix/rotation/TlNbO_demo.txt"}, std::string{ "TlNbO_demo_40.txt"} );
    make_diag( 45, 30.0, 120.0, std::string{"matrix/tilt/TlNbO_demo.txt"}, std::string{"matrix/beam/TlNbO_demo.txt"}, std::string{"matrix/unit_cell/TlNbO_demo.txt"}, std::string{"matrix/rotation/TlNbO_demo.txt"}, std::string{ "TlNbO_demo_30.txt"} );
    make_diag( 45, 20.0, 120.0, std::string{"matrix/tilt/TlNbO_demo.txt"}, std::string{"matrix/beam/TlNbO_demo.txt"}, std::string{"matrix/unit_cell/TlNbO_demo.txt"}, std::string{"matrix/rotation/TlNbO_demo.txt"}, std::string{ "TlNbO_demo_20.txt"} );
    make_diag( 45, 10.0, 120.0, std::string{"matrix/tilt/TlNbO_demo.txt"}, std::string{"matrix/beam/TlNbO_demo.txt"}, std::string{"matrix/unit_cell/TlNbO_demo.txt"}, std::string{"matrix/rotation/TlNbO_demo.txt"}, std::string{ "TlNbO_demo_10.txt"} );
    make_diag( 45, 5.0, 120.0, std::string{"matrix/tilt/TlNbO_demo.txt"}, std::string{"matrix/beam/TlNbO_demo.txt"}, std::string{"matrix/unit_cell/TlNbO_demo.txt"}, std::string{"matrix/rotation/TlNbO_demo.txt"}, std::string{ "TlNbO_demo_5.txt"} );
    make_diag( 45, 1.0, 120.0, std::string{"matrix/tilt/TlNbO_demo.txt"}, std::string{"matrix/beam/TlNbO_demo.txt"}, std::string{"matrix/unit_cell/TlNbO_demo.txt"}, std::string{"matrix/rotation/TlNbO_demo.txt"}, std::string{ "TlNbO_demo_1.txt"} );


    make_diag( 53, 240.0, 120.0, std::string{"matrix/tilt/TlNbO_selected.txt"}, std::string{"matrix/beam/TlNbO_selected.txt"}, std::string{"matrix/unit_cell/TlNbO_selected.txt"}, std::string{"matrix/rotation/TlNbO_selected.txt"}, std::string{ "TlNbO_selected_240.txt"} );
    make_diag( 53, 200.0, 120.0, std::string{"matrix/tilt/TlNbO_selected.txt"}, std::string{"matrix/beam/TlNbO_selected.txt"}, std::string{"matrix/unit_cell/TlNbO_selected.txt"}, std::string{"matrix/rotation/TlNbO_selected.txt"}, std::string{ "TlNbO_selected_200.txt"} );
    make_diag( 53, 160.0, 120.0, std::string{"matrix/tilt/TlNbO_selected.txt"}, std::string{"matrix/beam/TlNbO_selected.txt"}, std::string{"matrix/unit_cell/TlNbO_selected.txt"}, std::string{"matrix/rotation/TlNbO_selected.txt"}, std::string{ "TlNbO_selected_160.txt"} );
    make_diag( 53, 120.0, 120.0, std::string{"matrix/tilt/TlNbO_selected.txt"}, std::string{"matrix/beam/TlNbO_selected.txt"}, std::string{"matrix/unit_cell/TlNbO_selected.txt"}, std::string{"matrix/rotation/TlNbO_selected.txt"}, std::string{ "TlNbO_selected_120.txt"} );
    make_diag( 53, 100.0, 120.0, std::string{"matrix/tilt/TlNbO_selected.txt"}, std::string{"matrix/beam/TlNbO_selected.txt"}, std::string{"matrix/unit_cell/TlNbO_selected.txt"}, std::string{"matrix/rotation/TlNbO_selected.txt"}, std::string{ "TlNbO_selected_100.txt"} );
    make_diag( 53, 90.0, 120.0, std::string{"matrix/tilt/TlNbO_selected.txt"}, std::string{"matrix/beam/TlNbO_selected.txt"}, std::string{"matrix/unit_cell/TlNbO_selected.txt"}, std::string{"matrix/rotation/TlNbO_selected.txt"}, std::string{ "TlNbO_selected_90.txt"} );
    make_diag( 53, 80.0, 120.0, std::string{"matrix/tilt/TlNbO_selected.txt"}, std::string{"matrix/beam/TlNbO_selected.txt"}, std::string{"matrix/unit_cell/TlNbO_selected.txt"}, std::string{"matrix/rotation/TlNbO_selected.txt"}, std::string{ "TlNbO_selected_80.txt"} );
    make_diag( 53, 70.0, 120.0, std::string{"matrix/tilt/TlNbO_selected.txt"}, std::string{"matrix/beam/TlNbO_selected.txt"}, std::string{"matrix/unit_cell/TlNbO_selected.txt"}, std::string{"matrix/rotation/TlNbO_selected.txt"}, std::string{ "TlNbO_selected_70.txt"} );
    make_diag( 53, 60.0, 120.0, std::string{"matrix/tilt/TlNbO_selected.txt"}, std::string{"matrix/beam/TlNbO_selected.txt"}, std::string{"matrix/unit_cell/TlNbO_selected.txt"}, std::string{"matrix/rotation/TlNbO_selected.txt"}, std::string{ "TlNbO_selected_60.txt"} );
    make_diag( 53, 50.0, 120.0, std::string{"matrix/tilt/TlNbO_selected.txt"}, std::string{"matrix/beam/TlNbO_selected.txt"}, std::string{"matrix/unit_cell/TlNbO_selected.txt"}, std::string{"matrix/rotation/TlNbO_selected.txt"}, std::string{ "TlNbO_selected_50.txt"} );
    make_diag( 53, 40.0, 120.0, std::string{"matrix/tilt/TlNbO_selected.txt"}, std::string{"matrix/beam/TlNbO_selected.txt"}, std::string{"matrix/unit_cell/TlNbO_selected.txt"}, std::string{"matrix/rotation/TlNbO_selected.txt"}, std::string{ "TlNbO_selected_40.txt"} );
    make_diag( 53, 30.0, 120.0, std::string{"matrix/tilt/TlNbO_selected.txt"}, std::string{"matrix/beam/TlNbO_selected.txt"}, std::string{"matrix/unit_cell/TlNbO_selected.txt"}, std::string{"matrix/rotation/TlNbO_selected.txt"}, std::string{ "TlNbO_selected_30.txt"} );
    make_diag( 53, 20.0, 120.0, std::string{"matrix/tilt/TlNbO_selected.txt"}, std::string{"matrix/beam/TlNbO_selected.txt"}, std::string{"matrix/unit_cell/TlNbO_selected.txt"}, std::string{"matrix/rotation/TlNbO_selected.txt"}, std::string{ "TlNbO_selected_20.txt"} );
    make_diag( 53, 10.0, 120.0, std::string{"matrix/tilt/TlNbO_selected.txt"}, std::string{"matrix/beam/TlNbO_selected.txt"}, std::string{"matrix/unit_cell/TlNbO_selected.txt"}, std::string{"matrix/rotation/TlNbO_selected.txt"}, std::string{ "TlNbO_selected_10.txt"} );
    make_diag( 53, 5.0, 120.0, std::string{"matrix/tilt/TlNbO_selected.txt"}, std::string{"matrix/beam/TlNbO_selected.txt"}, std::string{"matrix/unit_cell/TlNbO_selected.txt"}, std::string{"matrix/rotation/TlNbO_selected.txt"}, std::string{ "TlNbO_selected_5.txt"} );
    make_diag( 53, 1.0, 120.0, std::string{"matrix/tilt/TlNbO_selected.txt"}, std::string{"matrix/beam/TlNbO_selected.txt"}, std::string{"matrix/unit_cell/TlNbO_selected.txt"}, std::string{"matrix/rotation/TlNbO_selected.txt"}, std::string{ "TlNbO_selected_1.txt"} );
#endif

    return 0;
}

