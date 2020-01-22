#include <f/simulate_intensity/simulate_intensity.hpp>

int main()
{
    using namespace f;

    //simulate_intensity( "./matrix/ar/SrTiO3_demo.txt", "./matrix/ug/SrTiO3_demo.txt", "./matrix/diag/SrTiO3_5.txt", 5.0, "./it.d5t5.txt" );
    //simulate_intensity( "./matrix/ar/SrTiO3_demo.txt", "./matrix/ug/SrTiO3_demo.txt", "./matrix/diag/SrTiO3_5.txt", 40.0, "./it.d5t40.txt" );
    //simulate_intensity( "./matrix/ar/SrTiO3_demo.txt", "./matrix/ug/SrTiO3_demo.txt", "./matrix/diag/SrTiO3_40.txt", 40.0, "./it.d40t40.txt" );
    //simulate_intensity_with_tilt( "./matrix/beam/SrTiO3_demo.txt", "./matrix/ar/SrTiO3_demo.txt", "./matrix/ug/SrTiO3_demo.txt", "./matrix/tilt/base_1024.txt", 130.0, "./matrix/intensity/SrTiO3_demo_d5t130.txt", 5.0 );
    //simulate_intensity_with_tilt( "./matrix/beam/TlNbO_457.txt", "./matrix/ar/TlNbO_457.txt", "./matrix/ug/TlNbO_457.txt", "./matrix/tilt/base_1024.txt", 50.0, "./matrix/intensity/TlNbO_457_d120t50.txt", 120.0 );
    double const thickness = 20;
    double const eV = 300;
    double radius = 0; //mrads
    std::string folder_string = "/testpool/ops/samfairman/QEDA/bin/Examples/2020_01_15_SrTiO3_T0/_feng_input_zero_tilt/";
    std::string beam_selection_string = folder_string + "new_beams.txt";
    std::string ug_string = folder_string + "ug.txt";
    std::string tilt_index_string = folder_string + "tilts_simple.txt";
    std::string unit_cell = folder_string + "SrTiO3_unit_cell.txt";
    std::string ar_string = folder_string + "Ar_ALL.txt";
    std::string output_folder = folder_string + "/Intensities_ALL.txt";

    std::vector<char> beam_selection(beam_selection_string.begin(), beam_selection_string.end());   beam_selection.push_back('\0');
    std::vector<char> ug(ug_string.begin(), ug_string.end());                                       ug.push_back('\0');
    std::vector<char> tilt_index(tilt_index_string.begin(), tilt_index_string.end());               tilt_index.push_back('\0');
    std::vector<char> ar(ar_string.begin(), ar_string.end());                                       ar.push_back('\0');

    //
    //output_folder.append(std::to_string(index)); 
    //output_folder.append(".txt");
    f::simulate_intensity_with_tilt( unit_cell.c_str(), &beam_selection[0] , &ar[0] , &ug[0], &tilt_index[0] , thickness, output_folder.c_str(), radius, eV);
    
    

#if 0 
    simulate_intensity_with_tilt( "./matrix/beam/TlNbO_457.txt", "./matrix/ar/TlNbO_457.txt", "./matrix/ug/TlNbO_457.txt", "./matrix/tilt/base_1024.txt", 40.0, "./matrix/intensity/TlNbO_457_d5t40.txt", 5.0 );
    simulate_intensity_with_tilt( "./matrix/beam/TlNbO_457.txt", "./matrix/ar/TlNbO_457.txt", "./matrix/ug/TlNbO_457.txt", "./matrix/tilt/base_1024.txt", 40.0, "./matrix/intensity/TlNbO_457_d10t40.txt", 10.0 );
    simulate_intensity_with_tilt( "./matrix/beam/TlNbO_457.txt", "./matrix/ar/TlNbO_457.txt", "./matrix/ug/TlNbO_457.txt", "./matrix/tilt/base_1024.txt", 40.0, "./matrix/intensity/TlNbO_457_d20t40.txt", 20.0 );
    simulate_intensity_with_tilt( "./matrix/beam/TlNbO_457.txt", "./matrix/ar/TlNbO_457.txt", "./matrix/ug/TlNbO_457.txt", "./matrix/tilt/base_1024.txt", 40.0, "./matrix/intensity/TlNbO_457_d40t40.txt", 40.0 );
    simulate_intensity_with_tilt( "./matrix/beam/TlNbO_457.txt", "./matrix/ar/TlNbO_457.txt", "./matrix/ug/TlNbO_457.txt", "./matrix/tilt/base_1024.txt", 40.0, "./matrix/intensity/TlNbO_457_d80t40.txt", 80.0 );
    simulate_intensity_with_tilt( "./matrix/beam/TlNbO_457.txt", "./matrix/ar/TlNbO_457.txt", "./matrix/ug/TlNbO_457.txt", "./matrix/tilt/base_1024.txt", 40.0, "./matrix/intensity/TlNbO_457_d120t40.txt", 120.0 );
    simulate_intensity_with_tilt( "./matrix/beam/TlNbO_457.txt", "./matrix/ar/TlNbO_457.txt", "./matrix/ug/TlNbO_457.txt", "./matrix/tilt/base_1024.txt", 20.0, "./matrix/intensity/TlNbO_457_d5t20.txt", 5.0 );
    simulate_intensity_with_tilt( "./matrix/beam/TlNbO_457.txt", "./matrix/ar/TlNbO_457.txt", "./matrix/ug/TlNbO_457.txt", "./matrix/tilt/base_1024.txt", 20.0, "./matrix/intensity/TlNbO_457_d10t20.txt", 10.0 );
    simulate_intensity_with_tilt( "./matrix/beam/TlNbO_457.txt", "./matrix/ar/TlNbO_457.txt", "./matrix/ug/TlNbO_457.txt", "./matrix/tilt/base_1024.txt", 20.0, "./matrix/intensity/TlNbO_457_d20t20.txt", 20.0 );
    simulate_intensity_with_tilt( "./matrix/beam/TlNbO_457.txt", "./matrix/ar/TlNbO_457.txt", "./matrix/ug/TlNbO_457.txt", "./matrix/tilt/base_1024.txt", 20.0, "./matrix/intensity/TlNbO_457_d40t20.txt", 40.0 );
    simulate_intensity_with_tilt( "./matrix/beam/TlNbO_457.txt", "./matrix/ar/TlNbO_457.txt", "./matrix/ug/TlNbO_457.txt", "./matrix/tilt/base_1024.txt", 20.0, "./matrix/intensity/TlNbO_457_d80t20.txt", 80.0 );
    simulate_intensity_with_tilt( "./matrix/beam/TlNbO_457.txt", "./matrix/ar/TlNbO_457.txt", "./matrix/ug/TlNbO_457.txt", "./matrix/tilt/base_1024.txt", 20.0, "./matrix/intensity/TlNbO_457_d120t20.txt", 120.0 );
    simulate_intensity_with_tilt( "./matrix/beam/TlNbO_457.txt", "./matrix/ar/TlNbO_457.txt", "./matrix/ug/TlNbO_457.txt", "./matrix/tilt/base_1024.txt", 10.0, "./matrix/intensity/TlNbO_457_d5t10.txt", 5.0 );
    simulate_intensity_with_tilt( "./matrix/beam/TlNbO_457.txt", "./matrix/ar/TlNbO_457.txt", "./matrix/ug/TlNbO_457.txt", "./matrix/tilt/base_1024.txt", 10.0, "./matrix/intensity/TlNbO_457_d10t10.txt", 10.0 );
    simulate_intensity_with_tilt( "./matrix/beam/TlNbO_457.txt", "./matrix/ar/TlNbO_457.txt", "./matrix/ug/TlNbO_457.txt", "./matrix/tilt/base_1024.txt", 10.0, "./matrix/intensity/TlNbO_457_d20t10.txt", 20.0 );
    simulate_intensity_with_tilt( "./matrix/beam/TlNbO_457.txt", "./matrix/ar/TlNbO_457.txt", "./matrix/ug/TlNbO_457.txt", "./matrix/tilt/base_1024.txt", 10.0, "./matrix/intensity/TlNbO_457_d40t10.txt", 40.0 );
    simulate_intensity_with_tilt( "./matrix/beam/TlNbO_457.txt", "./matrix/ar/TlNbO_457.txt", "./matrix/ug/TlNbO_457.txt", "./matrix/tilt/base_1024.txt", 10.0, "./matrix/intensity/TlNbO_457_d80t10.txt", 80.0 );
    simulate_intensity_with_tilt( "./matrix/beam/TlNbO_457.txt", "./matrix/ar/TlNbO_457.txt", "./matrix/ug/TlNbO_457.txt", "./matrix/tilt/base_1024.txt", 10.0, "./matrix/intensity/TlNbO_457_d120t10.txt", 120.0 );
    simulate_intensity_with_tilt( "./matrix/beam/TlNbO_457.txt", "./matrix/ar/TlNbO_457.txt", "./matrix/ug/TlNbO_457.txt", "./matrix/tilt/base_1024.txt", 5.0, "./matrix/intensity/TlNbO_457_d5t5.txt", 5.0 );
    simulate_intensity_with_tilt( "./matrix/beam/TlNbO_457.txt", "./matrix/ar/TlNbO_457.txt", "./matrix/ug/TlNbO_457.txt", "./matrix/tilt/base_1024.txt", 5.0, "./matrix/intensity/TlNbO_457_d10t5.txt", 10.0 );
    simulate_intensity_with_tilt( "./matrix/beam/TlNbO_457.txt", "./matrix/ar/TlNbO_457.txt", "./matrix/ug/TlNbO_457.txt", "./matrix/tilt/base_1024.txt", 5.0, "./matrix/intensity/TlNbO_457_d20t5.txt", 20.0 );
    simulate_intensity_with_tilt( "./matrix/beam/TlNbO_457.txt", "./matrix/ar/TlNbO_457.txt", "./matrix/ug/TlNbO_457.txt", "./matrix/tilt/base_1024.txt", 5.0, "./matrix/intensity/TlNbO_457_d40t5.txt", 40.0 );
    simulate_intensity_with_tilt( "./matrix/beam/TlNbO_457.txt", "./matrix/ar/TlNbO_457.txt", "./matrix/ug/TlNbO_457.txt", "./matrix/tilt/base_1024.txt", 5.0, "./matrix/intensity/TlNbO_457_d80t5.txt", 80.0 );
    simulate_intensity_with_tilt( "./matrix/beam/TlNbO_457.txt", "./matrix/ar/TlNbO_457.txt", "./matrix/ug/TlNbO_457.txt", "./matrix/tilt/base_1024.txt", 5.0, "./matrix/intensity/TlNbO_457_d120t5.txt", 120.0 );
#endif 
#if 0
    simulate_intensity_with_tilt( "./matrix/beam/TlNbO_selected_full.txt", "./matrix/ar/TlNbO_selected.txt", "./matrix/ug/TlNbO_selected.txt", "./matrix/tilt/base_1024.txt", 40.0, "./matrix/intensity/TlNbO_selected_d5t40.txt", 5.0 );
    simulate_intensity_with_tilt( "./matrix/beam/TlNbO_selected_full.txt", "./matrix/ar/TlNbO_selected.txt", "./matrix/ug/TlNbO_selected.txt", "./matrix/tilt/base_1024.txt", 40.0, "./matrix/intensity/TlNbO_selected_d10t40.txt", 10.0 );
    simulate_intensity_with_tilt( "./matrix/beam/TlNbO_selected_full.txt", "./matrix/ar/TlNbO_selected.txt", "./matrix/ug/TlNbO_selected.txt", "./matrix/tilt/base_1024.txt", 40.0, "./matrix/intensity/TlNbO_selected_d20t40.txt", 20.0 );
    simulate_intensity_with_tilt( "./matrix/beam/TlNbO_selected_full.txt", "./matrix/ar/TlNbO_selected.txt", "./matrix/ug/TlNbO_selected.txt", "./matrix/tilt/base_1024.txt", 40.0, "./matrix/intensity/TlNbO_selected_d40t40.txt", 40.0 );
    simulate_intensity_with_tilt( "./matrix/beam/TlNbO_selected_full.txt", "./matrix/ar/TlNbO_selected.txt", "./matrix/ug/TlNbO_selected.txt", "./matrix/tilt/base_1024.txt", 40.0, "./matrix/intensity/TlNbO_selected_d80t40.txt", 80.0 );
    simulate_intensity_with_tilt( "./matrix/beam/TlNbO_selected_full.txt", "./matrix/ar/TlNbO_selected.txt", "./matrix/ug/TlNbO_selected.txt", "./matrix/tilt/base_1024.txt", 40.0, "./matrix/intensity/TlNbO_selected_d120t40.txt", 120.0 );
    simulate_intensity_with_tilt( "./matrix/beam/TlNbO_selected_full.txt", "./matrix/ar/TlNbO_selected.txt", "./matrix/ug/TlNbO_selected.txt", "./matrix/tilt/base_1024.txt", 40.0, "./matrix/intensity/TlNbO_selected_d160t40.txt", 160.0 );
    simulate_intensity_with_tilt( "./matrix/beam/TlNbO_selected_full.txt", "./matrix/ar/TlNbO_selected.txt", "./matrix/ug/TlNbO_selected.txt", "./matrix/tilt/base_1024.txt", 40.0, "./matrix/intensity/TlNbO_selected_d200t40.txt", 200.0 );
    simulate_intensity_with_tilt( "./matrix/beam/TlNbO_selected_full.txt", "./matrix/ar/TlNbO_selected.txt", "./matrix/ug/TlNbO_selected.txt", "./matrix/tilt/base_1024.txt", 40.0, "./matrix/intensity/TlNbO_selected_d240t40.txt", 240.0 );
    simulate_intensity_with_tilt( "./matrix/beam/TlNbO_selected_full.txt", "./matrix/ar/TlNbO_selected.txt", "./matrix/ug/TlNbO_selected.txt", "./matrix/tilt/base_1024.txt", 20.0, "./matrix/intensity/TlNbO_selected_d5t20.txt", 5.0 );
    simulate_intensity_with_tilt( "./matrix/beam/TlNbO_selected_full.txt", "./matrix/ar/TlNbO_selected.txt", "./matrix/ug/TlNbO_selected.txt", "./matrix/tilt/base_1024.txt", 20.0, "./matrix/intensity/TlNbO_selected_d10t20.txt", 10.0 );
    simulate_intensity_with_tilt( "./matrix/beam/TlNbO_selected_full.txt", "./matrix/ar/TlNbO_selected.txt", "./matrix/ug/TlNbO_selected.txt", "./matrix/tilt/base_1024.txt", 20.0, "./matrix/intensity/TlNbO_selected_d20t20.txt", 20.0 );
    simulate_intensity_with_tilt( "./matrix/beam/TlNbO_selected_full.txt", "./matrix/ar/TlNbO_selected.txt", "./matrix/ug/TlNbO_selected.txt", "./matrix/tilt/base_1024.txt", 20.0, "./matrix/intensity/TlNbO_selected_d40t20.txt", 40.0 );
    simulate_intensity_with_tilt( "./matrix/beam/TlNbO_selected_full.txt", "./matrix/ar/TlNbO_selected.txt", "./matrix/ug/TlNbO_selected.txt", "./matrix/tilt/base_1024.txt", 20.0, "./matrix/intensity/TlNbO_selected_d80t20.txt", 80.0 );
    simulate_intensity_with_tilt( "./matrix/beam/TlNbO_selected_full.txt", "./matrix/ar/TlNbO_selected.txt", "./matrix/ug/TlNbO_selected.txt", "./matrix/tilt/base_1024.txt", 20.0, "./matrix/intensity/TlNbO_selected_d120t20.txt", 120.0 );
    simulate_intensity_with_tilt( "./matrix/beam/TlNbO_selected_full.txt", "./matrix/ar/TlNbO_selected.txt", "./matrix/ug/TlNbO_selected.txt", "./matrix/tilt/base_1024.txt", 20.0, "./matrix/intensity/TlNbO_selected_d160t20.txt", 160.0 );
    simulate_intensity_with_tilt( "./matrix/beam/TlNbO_selected_full.txt", "./matrix/ar/TlNbO_selected.txt", "./matrix/ug/TlNbO_selected.txt", "./matrix/tilt/base_1024.txt", 20.0, "./matrix/intensity/TlNbO_selected_d200t20.txt", 200.0 );
    simulate_intensity_with_tilt( "./matrix/beam/TlNbO_selected_full.txt", "./matrix/ar/TlNbO_selected.txt", "./matrix/ug/TlNbO_selected.txt", "./matrix/tilt/base_1024.txt", 20.0, "./matrix/intensity/TlNbO_selected_d240t20.txt", 240.0 );
    simulate_intensity_with_tilt( "./matrix/beam/TlNbO_selected_full.txt", "./matrix/ar/TlNbO_selected.txt", "./matrix/ug/TlNbO_selected.txt", "./matrix/tilt/base_1024.txt", 10.0, "./matrix/intensity/TlNbO_selected_d5t10.txt", 5.0 );
    simulate_intensity_with_tilt( "./matrix/beam/TlNbO_selected_full.txt", "./matrix/ar/TlNbO_selected.txt", "./matrix/ug/TlNbO_selected.txt", "./matrix/tilt/base_1024.txt", 10.0, "./matrix/intensity/TlNbO_selected_d10t10.txt", 10.0 );
    simulate_intensity_with_tilt( "./matrix/beam/TlNbO_selected_full.txt", "./matrix/ar/TlNbO_selected.txt", "./matrix/ug/TlNbO_selected.txt", "./matrix/tilt/base_1024.txt", 10.0, "./matrix/intensity/TlNbO_selected_d20t10.txt", 20.0 );
    simulate_intensity_with_tilt( "./matrix/beam/TlNbO_selected_full.txt", "./matrix/ar/TlNbO_selected.txt", "./matrix/ug/TlNbO_selected.txt", "./matrix/tilt/base_1024.txt", 10.0, "./matrix/intensity/TlNbO_selected_d40t10.txt", 40.0 );
    simulate_intensity_with_tilt( "./matrix/beam/TlNbO_selected_full.txt", "./matrix/ar/TlNbO_selected.txt", "./matrix/ug/TlNbO_selected.txt", "./matrix/tilt/base_1024.txt", 10.0, "./matrix/intensity/TlNbO_selected_d80t10.txt", 80.0 );
    simulate_intensity_with_tilt( "./matrix/beam/TlNbO_selected_full.txt", "./matrix/ar/TlNbO_selected.txt", "./matrix/ug/TlNbO_selected.txt", "./matrix/tilt/base_1024.txt", 10.0, "./matrix/intensity/TlNbO_selected_d120t10.txt", 120.0 );
    simulate_intensity_with_tilt( "./matrix/beam/TlNbO_selected_full.txt", "./matrix/ar/TlNbO_selected.txt", "./matrix/ug/TlNbO_selected.txt", "./matrix/tilt/base_1024.txt", 10.0, "./matrix/intensity/TlNbO_selected_d160t10.txt", 160.0 );
    simulate_intensity_with_tilt( "./matrix/beam/TlNbO_selected_full.txt", "./matrix/ar/TlNbO_selected.txt", "./matrix/ug/TlNbO_selected.txt", "./matrix/tilt/base_1024.txt", 10.0, "./matrix/intensity/TlNbO_selected_d200t10.txt", 200.0 );
    simulate_intensity_with_tilt( "./matrix/beam/TlNbO_selected_full.txt", "./matrix/ar/TlNbO_selected.txt", "./matrix/ug/TlNbO_selected.txt", "./matrix/tilt/base_1024.txt", 10.0, "./matrix/intensity/TlNbO_selected_d240t10.txt", 240.0 );
    simulate_intensity_with_tilt( "./matrix/beam/TlNbO_selected_full.txt", "./matrix/ar/TlNbO_selected.txt", "./matrix/ug/TlNbO_selected.txt", "./matrix/tilt/base_1024.txt", 5.0, "./matrix/intensity/TlNbO_selected_d5t5.txt", 5.0 );
    simulate_intensity_with_tilt( "./matrix/beam/TlNbO_selected_full.txt", "./matrix/ar/TlNbO_selected.txt", "./matrix/ug/TlNbO_selected.txt", "./matrix/tilt/base_1024.txt", 5.0, "./matrix/intensity/TlNbO_selected_d10t5.txt", 10.0 );
    simulate_intensity_with_tilt( "./matrix/beam/TlNbO_selected_full.txt", "./matrix/ar/TlNbO_selected.txt", "./matrix/ug/TlNbO_selected.txt", "./matrix/tilt/base_1024.txt", 5.0, "./matrix/intensity/TlNbO_selected_d20t5.txt", 20.0 );
    simulate_intensity_with_tilt( "./matrix/beam/TlNbO_selected_full.txt", "./matrix/ar/TlNbO_selected.txt", "./matrix/ug/TlNbO_selected.txt", "./matrix/tilt/base_1024.txt", 5.0, "./matrix/intensity/TlNbO_selected_d40t5.txt", 40.0 );
    simulate_intensity_with_tilt( "./matrix/beam/TlNbO_selected_full.txt", "./matrix/ar/TlNbO_selected.txt", "./matrix/ug/TlNbO_selected.txt", "./matrix/tilt/base_1024.txt", 5.0, "./matrix/intensity/TlNbO_selected_d80t5.txt", 80.0 );
    simulate_intensity_with_tilt( "./matrix/beam/TlNbO_selected_full.txt", "./matrix/ar/TlNbO_selected.txt", "./matrix/ug/TlNbO_selected.txt", "./matrix/tilt/base_1024.txt", 5.0, "./matrix/intensity/TlNbO_selected_d120t5.txt", 120.0 );
    simulate_intensity_with_tilt( "./matrix/beam/TlNbO_selected_full.txt", "./matrix/ar/TlNbO_selected.txt", "./matrix/ug/TlNbO_selected.txt", "./matrix/tilt/base_1024.txt", 5.0, "./matrix/intensity/TlNbO_selected_d160t5.txt", 160.0 );
    simulate_intensity_with_tilt( "./matrix/beam/TlNbO_selected_full.txt", "./matrix/ar/TlNbO_selected.txt", "./matrix/ug/TlNbO_selected.txt", "./matrix/tilt/base_1024.txt", 5.0, "./matrix/intensity/TlNbO_selected_d200t5.txt", 200.0 );
    simulate_intensity_with_tilt( "./matrix/beam/TlNbO_selected_full.txt", "./matrix/ar/TlNbO_selected.txt", "./matrix/ug/TlNbO_selected.txt", "./matrix/tilt/base_1024.txt", 5.0, "./matrix/intensity/TlNbO_selected_d240t5.txt", 240.0 );
#endif 
#if 0 
    simulate_intensity_with_tilt( "./matrix/beam/TlNbO_demo_full.txt", "./matrix/ar/TlNbO_demo.txt", "./matrix/ug/TlNbO_demo.txt", "./matrix/tilt/base_1024.txt", 40.0, "./matrix/intensity/TlNbO_demo_d5t40.txt", 5.0 );
    simulate_intensity_with_tilt( "./matrix/beam/TlNbO_demo_full.txt", "./matrix/ar/TlNbO_demo.txt", "./matrix/ug/TlNbO_demo.txt", "./matrix/tilt/base_1024.txt", 40.0, "./matrix/intensity/TlNbO_demo_d10t40.txt", 10.0 );
    simulate_intensity_with_tilt( "./matrix/beam/TlNbO_demo_full.txt", "./matrix/ar/TlNbO_demo.txt", "./matrix/ug/TlNbO_demo.txt", "./matrix/tilt/base_1024.txt", 40.0, "./matrix/intensity/TlNbO_demo_d20t40.txt", 20.0 );
    simulate_intensity_with_tilt( "./matrix/beam/TlNbO_demo_full.txt", "./matrix/ar/TlNbO_demo.txt", "./matrix/ug/TlNbO_demo.txt", "./matrix/tilt/base_1024.txt", 40.0, "./matrix/intensity/TlNbO_demo_d40t40.txt", 40.0 );
    simulate_intensity_with_tilt( "./matrix/beam/TlNbO_demo_full.txt", "./matrix/ar/TlNbO_demo.txt", "./matrix/ug/TlNbO_demo.txt", "./matrix/tilt/base_1024.txt", 40.0, "./matrix/intensity/TlNbO_demo_d80t40.txt", 80.0 );
    simulate_intensity_with_tilt( "./matrix/beam/TlNbO_demo_full.txt", "./matrix/ar/TlNbO_demo.txt", "./matrix/ug/TlNbO_demo.txt", "./matrix/tilt/base_1024.txt", 40.0, "./matrix/intensity/TlNbO_demo_d120t40.txt", 120.0 );
    simulate_intensity_with_tilt( "./matrix/beam/TlNbO_demo_full.txt", "./matrix/ar/TlNbO_demo.txt", "./matrix/ug/TlNbO_demo.txt", "./matrix/tilt/base_1024.txt", 20.0, "./matrix/intensity/TlNbO_demo_d5t20.txt", 5.0 );
    simulate_intensity_with_tilt( "./matrix/beam/TlNbO_demo_full.txt", "./matrix/ar/TlNbO_demo.txt", "./matrix/ug/TlNbO_demo.txt", "./matrix/tilt/base_1024.txt", 20.0, "./matrix/intensity/TlNbO_demo_d10t20.txt", 10.0 );
    simulate_intensity_with_tilt( "./matrix/beam/TlNbO_demo_full.txt", "./matrix/ar/TlNbO_demo.txt", "./matrix/ug/TlNbO_demo.txt", "./matrix/tilt/base_1024.txt", 20.0, "./matrix/intensity/TlNbO_demo_d20t20.txt", 20.0 );
    simulate_intensity_with_tilt( "./matrix/beam/TlNbO_demo_full.txt", "./matrix/ar/TlNbO_demo.txt", "./matrix/ug/TlNbO_demo.txt", "./matrix/tilt/base_1024.txt", 20.0, "./matrix/intensity/TlNbO_demo_d40t20.txt", 40.0 );
    simulate_intensity_with_tilt( "./matrix/beam/TlNbO_demo_full.txt", "./matrix/ar/TlNbO_demo.txt", "./matrix/ug/TlNbO_demo.txt", "./matrix/tilt/base_1024.txt", 20.0, "./matrix/intensity/TlNbO_demo_d80t20.txt", 80.0 );
    simulate_intensity_with_tilt( "./matrix/beam/TlNbO_demo_full.txt", "./matrix/ar/TlNbO_demo.txt", "./matrix/ug/TlNbO_demo.txt", "./matrix/tilt/base_1024.txt", 20.0, "./matrix/intensity/TlNbO_demo_d120t20.txt", 120.0 );
    simulate_intensity_with_tilt( "./matrix/beam/TlNbO_demo_full.txt", "./matrix/ar/TlNbO_demo.txt", "./matrix/ug/TlNbO_demo.txt", "./matrix/tilt/base_1024.txt", 10.0, "./matrix/intensity/TlNbO_demo_d5t10.txt", 5.0 );
    simulate_intensity_with_tilt( "./matrix/beam/TlNbO_demo_full.txt", "./matrix/ar/TlNbO_demo.txt", "./matrix/ug/TlNbO_demo.txt", "./matrix/tilt/base_1024.txt", 10.0, "./matrix/intensity/TlNbO_demo_d10t10.txt", 10.0 );
    simulate_intensity_with_tilt( "./matrix/beam/TlNbO_demo_full.txt", "./matrix/ar/TlNbO_demo.txt", "./matrix/ug/TlNbO_demo.txt", "./matrix/tilt/base_1024.txt", 10.0, "./matrix/intensity/TlNbO_demo_d20t10.txt", 20.0 );
    simulate_intensity_with_tilt( "./matrix/beam/TlNbO_demo_full.txt", "./matrix/ar/TlNbO_demo.txt", "./matrix/ug/TlNbO_demo.txt", "./matrix/tilt/base_1024.txt", 10.0, "./matrix/intensity/TlNbO_demo_d40t10.txt", 40.0 );
    simulate_intensity_with_tilt( "./matrix/beam/TlNbO_demo_full.txt", "./matrix/ar/TlNbO_demo.txt", "./matrix/ug/TlNbO_demo.txt", "./matrix/tilt/base_1024.txt", 10.0, "./matrix/intensity/TlNbO_demo_d80t10.txt", 80.0 );
    simulate_intensity_with_tilt( "./matrix/beam/TlNbO_demo_full.txt", "./matrix/ar/TlNbO_demo.txt", "./matrix/ug/TlNbO_demo.txt", "./matrix/tilt/base_1024.txt", 10.0, "./matrix/intensity/TlNbO_demo_d120t10.txt", 120.0 );
    simulate_intensity_with_tilt( "./matrix/beam/TlNbO_demo_full.txt", "./matrix/ar/TlNbO_demo.txt", "./matrix/ug/TlNbO_demo.txt", "./matrix/tilt/base_1024.txt", 5.0, "./matrix/intensity/TlNbO_demo_d5t5.txt", 5.0 );
    simulate_intensity_with_tilt( "./matrix/beam/TlNbO_demo_full.txt", "./matrix/ar/TlNbO_demo.txt", "./matrix/ug/TlNbO_demo.txt", "./matrix/tilt/base_1024.txt", 5.0, "./matrix/intensity/TlNbO_demo_d10t5.txt", 10.0 );
    simulate_intensity_with_tilt( "./matrix/beam/TlNbO_demo_full.txt", "./matrix/ar/TlNbO_demo.txt", "./matrix/ug/TlNbO_demo.txt", "./matrix/tilt/base_1024.txt", 5.0, "./matrix/intensity/TlNbO_demo_d20t5.txt", 20.0 );
    simulate_intensity_with_tilt( "./matrix/beam/TlNbO_demo_full.txt", "./matrix/ar/TlNbO_demo.txt", "./matrix/ug/TlNbO_demo.txt", "./matrix/tilt/base_1024.txt", 5.0, "./matrix/intensity/TlNbO_demo_d40t5.txt", 40.0 );
    simulate_intensity_with_tilt( "./matrix/beam/TlNbO_demo_full.txt", "./matrix/ar/TlNbO_demo.txt", "./matrix/ug/TlNbO_demo.txt", "./matrix/tilt/base_1024.txt", 5.0, "./matrix/intensity/TlNbO_demo_d80t5.txt", 80.0 );
    simulate_intensity_with_tilt( "./matrix/beam/TlNbO_demo_full.txt", "./matrix/ar/TlNbO_demo.txt", "./matrix/ug/TlNbO_demo.txt", "./matrix/tilt/base_1024.txt", 5.0, "./matrix/intensity/TlNbO_demo_d120t5.txt", 120.0 );
#endif 
#if 0
    simulate_intensity_with_tilt( "./matrix/beam/SrTiO3_demo.txt", "./matrix/ar/SrTiO3_demo.txt", "./matrix/ug/SrTiO3_demo.txt", "./matrix/tilt/base_1024.txt", 40.0, "./matrix/intensity/SrTiO3_demo_d5t40.txt", 5.0 );
    simulate_intensity_with_tilt( "./matrix/beam/SrTiO3_demo.txt", "./matrix/ar/SrTiO3_demo.txt", "./matrix/ug/SrTiO3_demo.txt", "./matrix/tilt/base_1024.txt", 40.0, "./matrix/intensity/SrTiO3_demo_d10t40.txt", 10.0 );
    simulate_intensity_with_tilt( "./matrix/beam/SrTiO3_demo.txt", "./matrix/ar/SrTiO3_demo.txt", "./matrix/ug/SrTiO3_demo.txt", "./matrix/tilt/base_1024.txt", 40.0, "./matrix/intensity/SrTiO3_demo_d20t40.txt", 20.0 );
    simulate_intensity_with_tilt( "./matrix/beam/SrTiO3_demo.txt", "./matrix/ar/SrTiO3_demo.txt", "./matrix/ug/SrTiO3_demo.txt", "./matrix/tilt/base_1024.txt", 40.0, "./matrix/intensity/SrTiO3_demo_d40t40.txt", 40.0 );
    simulate_intensity_with_tilt( "./matrix/beam/SrTiO3_demo.txt", "./matrix/ar/SrTiO3_demo.txt", "./matrix/ug/SrTiO3_demo.txt", "./matrix/tilt/base_1024.txt", 20.0, "./matrix/intensity/SrTiO3_demo_d5t20.txt", 5.0 );
    simulate_intensity_with_tilt( "./matrix/beam/SrTiO3_demo.txt", "./matrix/ar/SrTiO3_demo.txt", "./matrix/ug/SrTiO3_demo.txt", "./matrix/tilt/base_1024.txt", 20.0, "./matrix/intensity/SrTiO3_demo_d10t20.txt", 10.0 );
    simulate_intensity_with_tilt( "./matrix/beam/SrTiO3_demo.txt", "./matrix/ar/SrTiO3_demo.txt", "./matrix/ug/SrTiO3_demo.txt", "./matrix/tilt/base_1024.txt", 20.0, "./matrix/intensity/SrTiO3_demo_d20t20.txt", 20.0 );
    simulate_intensity_with_tilt( "./matrix/beam/SrTiO3_demo.txt", "./matrix/ar/SrTiO3_demo.txt", "./matrix/ug/SrTiO3_demo.txt", "./matrix/tilt/base_1024.txt", 20.0, "./matrix/intensity/SrTiO3_demo_d40t20.txt", 40.0 );
    simulate_intensity_with_tilt( "./matrix/beam/SrTiO3_demo.txt", "./matrix/ar/SrTiO3_demo.txt", "./matrix/ug/SrTiO3_demo.txt", "./matrix/tilt/base_1024.txt", 10.0, "./matrix/intensity/SrTiO3_demo_d5t10.txt", 5.0 );
    simulate_intensity_with_tilt( "./matrix/beam/SrTiO3_demo.txt", "./matrix/ar/SrTiO3_demo.txt", "./matrix/ug/SrTiO3_demo.txt", "./matrix/tilt/base_1024.txt", 10.0, "./matrix/intensity/SrTiO3_demo_d10t10.txt", 10.0 );
    simulate_intensity_with_tilt( "./matrix/beam/SrTiO3_demo.txt", "./matrix/ar/SrTiO3_demo.txt", "./matrix/ug/SrTiO3_demo.txt", "./matrix/tilt/base_1024.txt", 10.0, "./matrix/intensity/SrTiO3_demo_d20t10.txt", 20.0 );
    simulate_intensity_with_tilt( "./matrix/beam/SrTiO3_demo.txt", "./matrix/ar/SrTiO3_demo.txt", "./matrix/ug/SrTiO3_demo.txt", "./matrix/tilt/base_1024.txt", 10.0, "./matrix/intensity/SrTiO3_demo_d40t10.txt", 40.0 );
    simulate_intensity_with_tilt( "./matrix/beam/SrTiO3_demo.txt", "./matrix/ar/SrTiO3_demo.txt", "./matrix/ug/SrTiO3_demo.txt", "./matrix/tilt/base_1024.txt", 5.0, "./matrix/intensity/SrTiO3_demo_d5t5.txt", 5.0 );
    simulate_intensity_with_tilt( "./matrix/beam/SrTiO3_demo.txt", "./matrix/ar/SrTiO3_demo.txt", "./matrix/ug/SrTiO3_demo.txt", "./matrix/tilt/base_1024.txt", 5.0, "./matrix/intensity/SrTiO3_demo_d10t5.txt", 10.0 );
    simulate_intensity_with_tilt( "./matrix/beam/SrTiO3_demo.txt", "./matrix/ar/SrTiO3_demo.txt", "./matrix/ug/SrTiO3_demo.txt", "./matrix/tilt/base_1024.txt", 5.0, "./matrix/intensity/SrTiO3_demo_d20t5.txt", 20.0 );
    simulate_intensity_with_tilt( "./matrix/beam/SrTiO3_demo.txt", "./matrix/ar/SrTiO3_demo.txt", "./matrix/ug/SrTiO3_demo.txt", "./matrix/tilt/base_1024.txt", 5.0, "./matrix/intensity/SrTiO3_demo_d40t5.txt", 40.0 );
#endif 
#if 0
    simulate_intensity_with_tilt( "./matrix/beam/SrTiO3_demo.txt", "./matrix/ar/SrTiO3_demo.txt", "./matrix/ug/si_d5t40_f.dat", "./matrix/tilt/base_1024.txt", 40.0, "./matrix/intensity/SrTiO3_demo_d5t40_f.txt", 5.0 );
    simulate_intensity_with_tilt( "./matrix/beam/SrTiO3_demo.txt", "./matrix/ar/SrTiO3_demo.txt", "./matrix/ug/si_d10t40_f.dat", "./matrix/tilt/base_1024.txt", 40.0, "./matrix/intensity/SrTiO3_demo_d10t40_f.txt", 10.0 );
    simulate_intensity_with_tilt( "./matrix/beam/SrTiO3_demo.txt", "./matrix/ar/SrTiO3_demo.txt", "./matrix/ug/si_d20t40_f.dat", "./matrix/tilt/base_1024.txt", 40.0, "./matrix/intensity/SrTiO3_demo_d20t40_f.txt", 20.0 );
    simulate_intensity_with_tilt( "./matrix/beam/SrTiO3_demo.txt", "./matrix/ar/SrTiO3_demo.txt", "./matrix/ug/si_d40t40_f.dat", "./matrix/tilt/base_1024.txt", 40.0, "./matrix/intensity/SrTiO3_demo_d40t40_f.txt", 40.0 );
    simulate_intensity_with_tilt( "./matrix/beam/SrTiO3_demo.txt", "./matrix/ar/SrTiO3_demo.txt", "./matrix/ug/si_d5t20_f.dat", "./matrix/tilt/base_1024.txt", 20.0, "./matrix/intensity/SrTiO3_demo_d5t20_f.txt", 5.0 );
    simulate_intensity_with_tilt( "./matrix/beam/SrTiO3_demo.txt", "./matrix/ar/SrTiO3_demo.txt", "./matrix/ug/si_d10t20_f.dat", "./matrix/tilt/base_1024.txt", 20.0, "./matrix/intensity/SrTiO3_demo_d10t20_f.txt", 10.0 );
    simulate_intensity_with_tilt( "./matrix/beam/SrTiO3_demo.txt", "./matrix/ar/SrTiO3_demo.txt", "./matrix/ug/si_d20t20_f.dat", "./matrix/tilt/base_1024.txt", 20.0, "./matrix/intensity/SrTiO3_demo_d20t20_f.txt", 20.0 );
    simulate_intensity_with_tilt( "./matrix/beam/SrTiO3_demo.txt", "./matrix/ar/SrTiO3_demo.txt", "./matrix/ug/si_d40t20_f.dat", "./matrix/tilt/base_1024.txt", 20.0, "./matrix/intensity/SrTiO3_demo_d40t20_f.txt", 40.0 );
    simulate_intensity_with_tilt( "./matrix/beam/SrTiO3_demo.txt", "./matrix/ar/SrTiO3_demo.txt", "./matrix/ug/si_d5t10_f.dat", "./matrix/tilt/base_1024.txt", 10.0, "./matrix/intensity/SrTiO3_demo_d5t10_f.txt", 5.0 );
    simulate_intensity_with_tilt( "./matrix/beam/SrTiO3_demo.txt", "./matrix/ar/SrTiO3_demo.txt", "./matrix/ug/si_d10t10_f.dat", "./matrix/tilt/base_1024.txt", 10.0, "./matrix/intensity/SrTiO3_demo_d10t10_f.txt", 10.0 );
    simulate_intensity_with_tilt( "./matrix/beam/SrTiO3_demo.txt", "./matrix/ar/SrTiO3_demo.txt", "./matrix/ug/si_d20t10_f.dat", "./matrix/tilt/base_1024.txt", 10.0, "./matrix/intensity/SrTiO3_demo_d20t10_f.txt", 20.0 );
    simulate_intensity_with_tilt( "./matrix/beam/SrTiO3_demo.txt", "./matrix/ar/SrTiO3_demo.txt", "./matrix/ug/si_d20t10_f.dat", "./matrix/tilt/base_1024.txt", 10.0, "./matrix/intensity/SrTiO3_demo_d40t10_f.txt", 40.0 );
    simulate_intensity_with_tilt( "./matrix/beam/SrTiO3_demo.txt", "./matrix/ar/SrTiO3_demo.txt", "./matrix/ug/si_d5t5_f.dat", "./matrix/tilt/base_1024.txt", 5.0, "./matrix/intensity/SrTiO3_demo_d5t5_f.txt", 5.0 );
    simulate_intensity_with_tilt( "./matrix/beam/SrTiO3_demo.txt", "./matrix/ar/SrTiO3_demo.txt", "./matrix/ug/si_d10t5_f.dat", "./matrix/tilt/base_1024.txt", 5.0, "./matrix/intensity/SrTiO3_demo_d10t5_f.txt", 10.0 );
    simulate_intensity_with_tilt( "./matrix/beam/SrTiO3_demo.txt", "./matrix/ar/SrTiO3_demo.txt", "./matrix/ug/si_d20t5_f.dat", "./matrix/tilt/base_1024.txt", 5.0, "./matrix/intensity/SrTiO3_demo_d20t5_f.txt", 20.0 );
    simulate_intensity_with_tilt( "./matrix/beam/SrTiO3_demo.txt", "./matrix/ar/SrTiO3_demo.txt", "./matrix/ug/si_d40t5_f.dat", "./matrix/tilt/base_1024.txt", 5.0, "./matrix/intensity/SrTiO3_demo_d40t5_f.txt", 40.0 );
#endif
#if 0
    simulate_intensity_with_tilt( "./matrix/beam/SrTiO3_demo.txt", "./matrix/ar/SrTiO3_demo.txt", "./matrix/ug/si_d40t10_f.dat", "./matrix/tilt/base_1024.txt", 40.0, "./matrix/intensity/SrTiO3_demo_d10t40_f.txt", 10.0 );
    simulate_intensity_with_tilt( "./matrix/beam/SrTiO3_demo.txt", "./matrix/ar/SrTiO3_demo.txt", "./matrix/ug/si_d10t40_f.dat", "./matrix/tilt/base_1024.txt", 10.0, "./matrix/intensity/SrTiO3_demo_d40t10_f.txt", 40.0 );
#endif
    //simulate_intensity_with_tilt( "./matrix/beam/SrTiO3_demo.txt", "./matrix/ar/SrTiO3_demo.txt", "./matrix/ug/si_d20t5_f.dat", "./matrix/tilt/base_1024.txt", 5.0, "./matrix/intensity/SrTiO3_demo_d20t5_f.txt", 20.0 );
    //simulate_intensity_with_tilt( "./matrix/beam/SrTiO3_demo.txt", "./matrix/ar/SrTiO3_demo.txt", "./matrix/ug/SrTiO3_demo.txt", "./matrix/tilt/base_1024.txt", 10.0, "./matrix/intensity/SrTiO3_demo_d40t10.txt", 40.0 );
    //
    //simulate_intensity( "./matrix/ar/SrTiO3_full.txt",  "./matlab/display_experimental/best_so_far_abs.dat", "./testdata/txt/diag.txt", 15.581, "./matrix/intensity/SrTiO3_full_best.txt"  );
    //simulate_intensity( "./matrix/ar/SrTiO3_full.txt",  "./matrix/journal_experimental/fitting.dat", "./testdata/txt/diag.txt", 11.9957, "./matrix/journal_experimental/fitted_intensity.txt"  );
    //simulate_intensity( "./matrix/ar/SrTiO3_full.txt",  "./matrix/journal_experimental_2/fitting.dat", "./testdata/txt/diag.txt", 11.9957, "./matrix/journal_experimental_2/fitted_intensity.txt"  );
    //
#if 0
    simulate_intensity_with_tilt( "./matrix/beam/SrTiO3_demo.txt", "./matrix/ar/SrTiO3_demo.txt", "./matrix/ug/Si_demo_full.txt", "./matrix/tilt/base_1024.txt", 40.0, "./matrix/intensity/Si_demo_d5t40.txt", 5.0 );
    simulate_intensity_with_tilt( "./matrix/beam/SrTiO3_demo.txt", "./matrix/ar/SrTiO3_demo.txt", "./matrix/ug/Si_demo_full.txt", "./matrix/tilt/base_1024.txt", 40.0, "./matrix/intensity/Si_demo_d10t40.txt", 10.0 );
    simulate_intensity_with_tilt( "./matrix/beam/SrTiO3_demo.txt", "./matrix/ar/SrTiO3_demo.txt", "./matrix/ug/Si_demo_full.txt", "./matrix/tilt/base_1024.txt", 40.0, "./matrix/intensity/Si_demo_d20t40.txt", 20.0 );
    simulate_intensity_with_tilt( "./matrix/beam/SrTiO3_demo.txt", "./matrix/ar/SrTiO3_demo.txt", "./matrix/ug/Si_demo_full.txt", "./matrix/tilt/base_1024.txt", 40.0, "./matrix/intensity/Si_demo_d40t40.txt", 40.0 );
    simulate_intensity_with_tilt( "./matrix/beam/SrTiO3_demo.txt", "./matrix/ar/SrTiO3_demo.txt", "./matrix/ug/Si_demo_full.txt", "./matrix/tilt/base_1024.txt", 20.0, "./matrix/intensity/Si_demo_d5t20.txt", 5.0 );
    simulate_intensity_with_tilt( "./matrix/beam/SrTiO3_demo.txt", "./matrix/ar/SrTiO3_demo.txt", "./matrix/ug/Si_demo_full.txt", "./matrix/tilt/base_1024.txt", 20.0, "./matrix/intensity/Si_demo_d10t20.txt", 10.0 );
    simulate_intensity_with_tilt( "./matrix/beam/SrTiO3_demo.txt", "./matrix/ar/SrTiO3_demo.txt", "./matrix/ug/Si_demo_full.txt", "./matrix/tilt/base_1024.txt", 20.0, "./matrix/intensity/Si_demo_d20t20.txt", 20.0 );
    simulate_intensity_with_tilt( "./matrix/beam/SrTiO3_demo.txt", "./matrix/ar/SrTiO3_demo.txt", "./matrix/ug/Si_demo_full.txt", "./matrix/tilt/base_1024.txt", 20.0, "./matrix/intensity/Si_demo_d40t20.txt", 40.0 );
    simulate_intensity_with_tilt( "./matrix/beam/SrTiO3_demo.txt", "./matrix/ar/SrTiO3_demo.txt", "./matrix/ug/Si_demo_full.txt", "./matrix/tilt/base_1024.txt", 10.0, "./matrix/intensity/Si_demo_d5t10.txt", 5.0 );
    simulate_intensity_with_tilt( "./matrix/beam/SrTiO3_demo.txt", "./matrix/ar/SrTiO3_demo.txt", "./matrix/ug/Si_demo_full.txt", "./matrix/tilt/base_1024.txt", 10.0, "./matrix/intensity/Si_demo_d10t10.txt", 10.0 );
    simulate_intensity_with_tilt( "./matrix/beam/SrTiO3_demo.txt", "./matrix/ar/SrTiO3_demo.txt", "./matrix/ug/Si_demo_full.txt", "./matrix/tilt/base_1024.txt", 10.0, "./matrix/intensity/Si_demo_d20t10.txt", 20.0 );
    simulate_intensity_with_tilt( "./matrix/beam/SrTiO3_demo.txt", "./matrix/ar/SrTiO3_demo.txt", "./matrix/ug/Si_demo_full.txt", "./matrix/tilt/base_1024.txt", 10.0, "./matrix/intensity/Si_demo_d40t10.txt", 40.0 );
    simulate_intensity_with_tilt( "./matrix/beam/SrTiO3_demo.txt", "./matrix/ar/SrTiO3_demo.txt", "./matrix/ug/Si_demo_full.txt", "./matrix/tilt/base_1024.txt", 5.0, "./matrix/intensity/Si_demo_d5t5.txt", 5.0 );
    simulate_intensity_with_tilt( "./matrix/beam/SrTiO3_demo.txt", "./matrix/ar/SrTiO3_demo.txt", "./matrix/ug/Si_demo_full.txt", "./matrix/tilt/base_1024.txt", 5.0, "./matrix/intensity/Si_demo_d10t5.txt", 10.0 );
    simulate_intensity_with_tilt( "./matrix/beam/SrTiO3_demo.txt", "./matrix/ar/SrTiO3_demo.txt", "./matrix/ug/Si_demo_full.txt", "./matrix/tilt/base_1024.txt", 5.0, "./matrix/intensity/Si_demo_d20t5.txt", 20.0 );
    simulate_intensity_with_tilt( "./matrix/beam/SrTiO3_demo.txt", "./matrix/ar/SrTiO3_demo.txt", "./matrix/ug/Si_demo_full.txt", "./matrix/tilt/base_1024.txt", 5.0, "./matrix/intensity/Si_demo_d40t5.txt", 40.0 );
#endif 
#if 0 
    simulate_intensity_with_tilt( "./matrix/beam/Si_se_selected.txt", "./matrix/ar/Si_se.txt", "./matrix/ug/Si_se_full.txt", "./matrix/tilt/base_1024.txt", 30.0, "./matrix/intensity/Si_se_d5t30.txt", 5.0 );
    simulate_intensity_with_tilt( "./matrix/beam/Si_se_selected.txt", "./matrix/ar/Si_se.txt", "./matrix/ug/Si_se_full.txt", "./matrix/tilt/base_1024.txt", 30.0, "./matrix/intensity/Si_se_d10t30.txt", 10.0 );
    simulate_intensity_with_tilt( "./matrix/beam/Si_se_selected.txt", "./matrix/ar/Si_se.txt", "./matrix/ug/Si_se_full.txt", "./matrix/tilt/base_1024.txt", 30.0, "./matrix/intensity/Si_se_d20t30.txt", 20.0 );
    simulate_intensity_with_tilt( "./matrix/beam/Si_se_selected.txt", "./matrix/ar/Si_se.txt", "./matrix/ug/Si_se_full.txt", "./matrix/tilt/base_1024.txt", 30.0, "./matrix/intensity/Si_se_d40t30.txt", 40.0 );
    simulate_intensity_with_tilt( "./matrix/beam/Si_se_selected.txt", "./matrix/ar/Si_se.txt", "./matrix/ug/Si_se_full.txt", "./matrix/tilt/base_1024.txt", 20.0, "./matrix/intensity/Si_se_d5t20.txt", 5.0 );
    simulate_intensity_with_tilt( "./matrix/beam/Si_se_selected.txt", "./matrix/ar/Si_se.txt", "./matrix/ug/Si_se_full.txt", "./matrix/tilt/base_1024.txt", 20.0, "./matrix/intensity/Si_se_d10t20.txt", 10.0 );
    simulate_intensity_with_tilt( "./matrix/beam/Si_se_selected.txt", "./matrix/ar/Si_se.txt", "./matrix/ug/Si_se_full.txt", "./matrix/tilt/base_1024.txt", 20.0, "./matrix/intensity/Si_se_d20t20.txt", 20.0 );
    simulate_intensity_with_tilt( "./matrix/beam/Si_se_selected.txt", "./matrix/ar/Si_se.txt", "./matrix/ug/Si_se_full.txt", "./matrix/tilt/base_1024.txt", 20.0, "./matrix/intensity/Si_se_d40t20.txt", 40.0 );
    simulate_intensity_with_tilt( "./matrix/beam/Si_se_selected.txt", "./matrix/ar/Si_se.txt", "./matrix/ug/Si_se_full.txt", "./matrix/tilt/base_1024.txt", 10.0, "./matrix/intensity/Si_se_d5t10.txt", 5.0 );
    simulate_intensity_with_tilt( "./matrix/beam/Si_se_selected.txt", "./matrix/ar/Si_se.txt", "./matrix/ug/Si_se_full.txt", "./matrix/tilt/base_1024.txt", 10.0, "./matrix/intensity/Si_se_d10t10.txt", 10.0 );
    simulate_intensity_with_tilt( "./matrix/beam/Si_se_selected.txt", "./matrix/ar/Si_se.txt", "./matrix/ug/Si_se_full.txt", "./matrix/tilt/base_1024.txt", 10.0, "./matrix/intensity/Si_se_d20t10.txt", 20.0 );
    simulate_intensity_with_tilt( "./matrix/beam/Si_se_selected.txt", "./matrix/ar/Si_se.txt", "./matrix/ug/Si_se_full.txt", "./matrix/tilt/base_1024.txt", 10.0, "./matrix/intensity/Si_se_d40t10.txt", 40.0 );
    simulate_intensity_with_tilt( "./matrix/beam/Si_se_selected.txt", "./matrix/ar/Si_se.txt", "./matrix/ug/Si_se_full.txt", "./matrix/tilt/base_1024.txt", 5.0, "./matrix/intensity/Si_se_d5t5.txt", 5.0 );
    simulate_intensity_with_tilt( "./matrix/beam/Si_se_selected.txt", "./matrix/ar/Si_se.txt", "./matrix/ug/Si_se_full.txt", "./matrix/tilt/base_1024.txt", 5.0, "./matrix/intensity/Si_se_d10t5.txt", 10.0 );
    simulate_intensity_with_tilt( "./matrix/beam/Si_se_selected.txt", "./matrix/ar/Si_se.txt", "./matrix/ug/Si_se_full.txt", "./matrix/tilt/base_1024.txt", 5.0, "./matrix/intensity/Si_se_d20t5.txt", 20.0 );
    simulate_intensity_with_tilt( "./matrix/beam/Si_se_selected.txt", "./matrix/ar/Si_se.txt", "./matrix/ug/Si_se_full.txt", "./matrix/tilt/base_1024.txt", 5.0, "./matrix/intensity/Si_se_d40t5.txt", 40.0 );
#endif 
#if 0
    simulate_intensity_with_tilt( "./matrix/beam/SrTiO3_demo.txt", "./matrix/ar/SrTiO3_demo.txt", "./matrix/ug/Si_demo_full.txt", "./matrix/tilt/base_1024.txt", 40.0, "./matrix/intensity/Si_demo_d5t40.txt", 5.0 );
    simulate_intensity_with_tilt( "./matrix/beam/SrTiO3_demo.txt", "./matrix/ar/SrTiO3_demo.txt", "./matrix/ug/Si_demo_full.txt", "./matrix/tilt/base_1024.txt", 40.0, "./matrix/intensity/Si_demo_d10t40.txt", 10.0 );
    simulate_intensity_with_tilt( "./matrix/beam/SrTiO3_demo.txt", "./matrix/ar/SrTiO3_demo.txt", "./matrix/ug/Si_demo_full.txt", "./matrix/tilt/base_1024.txt", 40.0, "./matrix/intensity/Si_demo_d20t40.txt", 20.0 );
    simulate_intensity_with_tilt( "./matrix/beam/SrTiO3_demo.txt", "./matrix/ar/SrTiO3_demo.txt", "./matrix/ug/Si_demo_full.txt", "./matrix/tilt/base_1024.txt", 40.0, "./matrix/intensity/Si_demo_d40t40.txt", 40.0 );
    simulate_intensity_with_tilt( "./matrix/beam/SrTiO3_demo.txt", "./matrix/ar/SrTiO3_demo.txt", "./matrix/ug/Si_demo_full.txt", "./matrix/tilt/base_1024.txt", 20.0, "./matrix/intensity/Si_demo_d5t20.txt", 5.0 );
    simulate_intensity_with_tilt( "./matrix/beam/SrTiO3_demo.txt", "./matrix/ar/SrTiO3_demo.txt", "./matrix/ug/Si_demo_full.txt", "./matrix/tilt/base_1024.txt", 20.0, "./matrix/intensity/Si_demo_d10t20.txt", 10.0 );
    simulate_intensity_with_tilt( "./matrix/beam/SrTiO3_demo.txt", "./matrix/ar/SrTiO3_demo.txt", "./matrix/ug/Si_demo_full.txt", "./matrix/tilt/base_1024.txt", 20.0, "./matrix/intensity/Si_demo_d20t20.txt", 20.0 );
    simulate_intensity_with_tilt( "./matrix/beam/SrTiO3_demo.txt", "./matrix/ar/SrTiO3_demo.txt", "./matrix/ug/Si_demo_full.txt", "./matrix/tilt/base_1024.txt", 20.0, "./matrix/intensity/Si_demo_d40t20.txt", 40.0 );
    simulate_intensity_with_tilt( "./matrix/beam/SrTiO3_demo.txt", "./matrix/ar/SrTiO3_demo.txt", "./matrix/ug/Si_demo_full.txt", "./matrix/tilt/base_1024.txt", 10.0, "./matrix/intensity/Si_demo_d5t10.txt", 5.0 );
    simulate_intensity_with_tilt( "./matrix/beam/SrTiO3_demo.txt", "./matrix/ar/SrTiO3_demo.txt", "./matrix/ug/Si_demo_full.txt", "./matrix/tilt/base_1024.txt", 10.0, "./matrix/intensity/Si_demo_d10t10.txt", 10.0 );
    simulate_intensity_with_tilt( "./matrix/beam/SrTiO3_demo.txt", "./matrix/ar/SrTiO3_demo.txt", "./matrix/ug/Si_demo_full.txt", "./matrix/tilt/base_1024.txt", 10.0, "./matrix/intensity/Si_demo_d20t10.txt", 20.0 );
    simulate_intensity_with_tilt( "./matrix/beam/SrTiO3_demo.txt", "./matrix/ar/SrTiO3_demo.txt", "./matrix/ug/Si_demo_full.txt", "./matrix/tilt/base_1024.txt", 10.0, "./matrix/intensity/Si_demo_d40t10.txt", 40.0 );
    simulate_intensity_with_tilt( "./matrix/beam/SrTiO3_demo.txt", "./matrix/ar/SrTiO3_demo.txt", "./matrix/ug/Si_demo_full.txt", "./matrix/tilt/base_1024.txt", 5.0, "./matrix/intensity/Si_demo_d5t5.txt", 5.0 );
    simulate_intensity_with_tilt( "./matrix/beam/SrTiO3_demo.txt", "./matrix/ar/SrTiO3_demo.txt", "./matrix/ug/Si_demo_full.txt", "./matrix/tilt/base_1024.txt", 5.0, "./matrix/intensity/Si_demo_d10t5.txt", 10.0 );
    simulate_intensity_with_tilt( "./matrix/beam/SrTiO3_demo.txt", "./matrix/ar/SrTiO3_demo.txt", "./matrix/ug/Si_demo_full.txt", "./matrix/tilt/base_1024.txt", 5.0, "./matrix/intensity/Si_demo_d20t5.txt", 20.0 );
    simulate_intensity_with_tilt( "./matrix/beam/SrTiO3_demo.txt", "./matrix/ar/SrTiO3_demo.txt", "./matrix/ug/Si_demo_full.txt", "./matrix/tilt/base_1024.txt", 5.0, "./matrix/intensity/Si_demo_d40t5.txt", 40.0 );
#endif 
#if 0
    simulate_intensity_with_tilt( "./matrix/beam/SrTiO3_demo.txt", "./matrix/ar/SrTiO3_demo.txt", "./matrix/ug/si_d5t30.dat", "./matrix/tilt/base_1024.txt", 40.0, "./matrix/intensity/si_d5t30_f.txt", 5.0 );
    simulate_intensity_with_tilt( "./matrix/beam/SrTiO3_demo.txt", "./matrix/ar/SrTiO3_demo.txt", "./matrix/ug/si_d10t30.dat", "./matrix/tilt/base_1024.txt", 40.0, "./matrix/intensity/si_d10t30_f.txt", 10.0 );
    simulate_intensity_with_tilt( "./matrix/beam/SrTiO3_demo.txt", "./matrix/ar/SrTiO3_demo.txt", "./matrix/ug/si_d20t30.dat", "./matrix/tilt/base_1024.txt", 40.0, "./matrix/intensity/si_d20t30_f.txt", 20.0 );
    simulate_intensity_with_tilt( "./matrix/beam/SrTiO3_demo.txt", "./matrix/ar/SrTiO3_demo.txt", "./matrix/ug/si_d40t30.dat", "./matrix/tilt/base_1024.txt", 40.0, "./matrix/intensity/si_d40t30_f.txt", 40.0 );
    simulate_intensity_with_tilt( "./matrix/beam/SrTiO3_demo.txt", "./matrix/ar/SrTiO3_demo.txt", "./matrix/ug/si_d5t20.dat", "./matrix/tilt/base_1024.txt", 20.0, "./matrix/intensity/si_d5t20_f.txt", 5.0 );
    simulate_intensity_with_tilt( "./matrix/beam/SrTiO3_demo.txt", "./matrix/ar/SrTiO3_demo.txt", "./matrix/ug/si_d10t20.dat", "./matrix/tilt/base_1024.txt", 20.0, "./matrix/intensity/si_d10t20_f.txt", 10.0 );
    simulate_intensity_with_tilt( "./matrix/beam/SrTiO3_demo.txt", "./matrix/ar/SrTiO3_demo.txt", "./matrix/ug/si_d20t20.dat", "./matrix/tilt/base_1024.txt", 20.0, "./matrix/intensity/si_d20t20_f.txt", 20.0 );
    simulate_intensity_with_tilt( "./matrix/beam/SrTiO3_demo.txt", "./matrix/ar/SrTiO3_demo.txt", "./matrix/ug/si_d40t20.dat", "./matrix/tilt/base_1024.txt", 20.0, "./matrix/intensity/si_d40t20_f.txt", 40.0 );
    simulate_intensity_with_tilt( "./matrix/beam/SrTiO3_demo.txt", "./matrix/ar/SrTiO3_demo.txt", "./matrix/ug/si_d5t10.dat", "./matrix/tilt/base_1024.txt", 10.0, "./matrix/intensity/si_d5t10_f.txt", 5.0 );
    simulate_intensity_with_tilt( "./matrix/beam/SrTiO3_demo.txt", "./matrix/ar/SrTiO3_demo.txt", "./matrix/ug/si_d10t10.dat", "./matrix/tilt/base_1024.txt", 10.0, "./matrix/intensity/si_d10t10_f.txt", 10.0 );
    simulate_intensity_with_tilt( "./matrix/beam/SrTiO3_demo.txt", "./matrix/ar/SrTiO3_demo.txt", "./matrix/ug/si_d20t10.dat", "./matrix/tilt/base_1024.txt", 10.0, "./matrix/intensity/si_d20t10_f.txt", 20.0 );
    simulate_intensity_with_tilt( "./matrix/beam/SrTiO3_demo.txt", "./matrix/ar/SrTiO3_demo.txt", "./matrix/ug/si_d20t10.dat", "./matrix/tilt/base_1024.txt", 10.0, "./matrix/intensity/si_d40t10_f.txt", 40.0 );
    simulate_intensity_with_tilt( "./matrix/beam/SrTiO3_demo.txt", "./matrix/ar/SrTiO3_demo.txt", "./matrix/ug/si_d5t5.dat", "./matrix/tilt/base_1024.txt", 5.0, "./matrix/intensity/si_d5t5_f.txt", 5.0 );
    simulate_intensity_with_tilt( "./matrix/beam/SrTiO3_demo.txt", "./matrix/ar/SrTiO3_demo.txt", "./matrix/ug/si_d10t5.dat", "./matrix/tilt/base_1024.txt", 5.0, "./matrix/intensity/si_d10t5_f.txt", 10.0 );
    simulate_intensity_with_tilt( "./matrix/beam/SrTiO3_demo.txt", "./matrix/ar/SrTiO3_demo.txt", "./matrix/ug/si_d20t5.dat", "./matrix/tilt/base_1024.txt", 5.0, "./matrix/intensity/si_d20t5_f.txt", 20.0 );
    simulate_intensity_with_tilt( "./matrix/beam/SrTiO3_demo.txt", "./matrix/ar/SrTiO3_demo.txt", "./matrix/ug/si_d40t5.dat", "./matrix/tilt/base_1024.txt", 5.0, "./matrix/intensity/si_d40t5_f.txt", 40.0 );
#endif
#if 0
    simulate_intensity_with_tilt( "./matrix/beam/SrTiO3_demo.txt", "./matrix/ar/SrTiO3_demo.txt", "./matrix/ug/Si_demo_full.txt", "./matrix/tilt/base_1024.txt", 30.0, "./matrix/intensity/Si_demo_d5t30.txt", 5.0 );
    simulate_intensity_with_tilt( "./matrix/beam/SrTiO3_demo.txt", "./matrix/ar/SrTiO3_demo.txt", "./matrix/ug/Si_demo_full.txt", "./matrix/tilt/base_1024.txt", 30.0, "./matrix/intensity/Si_demo_d10t30.txt", 10.0 );
    simulate_intensity_with_tilt( "./matrix/beam/SrTiO3_demo.txt", "./matrix/ar/SrTiO3_demo.txt", "./matrix/ug/Si_demo_full.txt", "./matrix/tilt/base_1024.txt", 30.0, "./matrix/intensity/Si_demo_d20t30.txt", 20.0 );
    simulate_intensity_with_tilt( "./matrix/beam/SrTiO3_demo.txt", "./matrix/ar/SrTiO3_demo.txt", "./matrix/ug/Si_demo_full.txt", "./matrix/tilt/base_1024.txt", 30.0, "./matrix/intensity/Si_demo_d40t30.txt", 40.0 );
    simulate_intensity_with_tilt( "./matrix/beam/SrTiO3_demo.txt", "./matrix/ar/SrTiO3_demo.txt", "./matrix/ug/si_d5t30.dat", "./matrix/tilt/base_1024.txt", 30.0, "./matrix/intensity/si_d5t30_f.txt", 5.0 );
    simulate_intensity_with_tilt( "./matrix/beam/SrTiO3_demo.txt", "./matrix/ar/SrTiO3_demo.txt", "./matrix/ug/si_d10t30.dat", "./matrix/tilt/base_1024.txt", 30.0, "./matrix/intensity/si_d10t30_f.txt", 10.0 );
    simulate_intensity_with_tilt( "./matrix/beam/SrTiO3_demo.txt", "./matrix/ar/SrTiO3_demo.txt", "./matrix/ug/si_d20t30.dat", "./matrix/tilt/base_1024.txt", 30.0, "./matrix/intensity/si_d20t30_f.txt", 20.0 );
    simulate_intensity_with_tilt( "./matrix/beam/SrTiO3_demo.txt", "./matrix/ar/SrTiO3_demo.txt", "./matrix/ug/si_d40t30.dat", "./matrix/tilt/base_1024.txt", 30.0, "./matrix/intensity/si_d40t30_f.txt", 40.0 );
#endif
#if 0
    simulate_intensity_with_tilt( "./matrix/beam/Si_se_selected.txt", "./matrix/ar/Si_se.txt", "./matrix/ug/Si_se_full.txt", "./matrix/tilt/base_1024.txt", 30.0, "./matrix/intensity/Si_se_d5t30.txt", 5.0 );
    simulate_intensity_with_tilt( "./matrix/beam/Si_se_selected.txt", "./matrix/ar/Si_se.txt", "./matrix/ug/Si_se_full.txt", "./matrix/tilt/base_1024.txt", 30.0, "./matrix/intensity/Si_se_d10t30.txt", 10.0 );
    simulate_intensity_with_tilt( "./matrix/beam/Si_se_selected.txt", "./matrix/ar/Si_se.txt", "./matrix/ug/Si_se_full.txt", "./matrix/tilt/base_1024.txt", 30.0, "./matrix/intensity/Si_se_d20t30.txt", 20.0 );
    simulate_intensity_with_tilt( "./matrix/beam/Si_se_selected.txt", "./matrix/ar/Si_se.txt", "./matrix/ug/Si_se_full.txt", "./matrix/tilt/base_1024.txt", 30.0, "./matrix/intensity/Si_se_d40t30.txt", 40.0 );
#endif
#if 0 
    simulate_intensity_with_tilt( "./matrix/beam/Si_se_selected.txt", "./matrix/ar/Si_se.txt", "./matrix/ug/Si_se_full.txt", "./matrix/tilt/base_1024.txt", 30.0, "./matrix/intensity/Si_se_d5t30.txt", 5.0 );
    simulate_intensity_with_tilt( "./matrix/beam/Si_se_selected.txt", "./matrix/ar/Si_se.txt", "./matrix/ug/Si_se_full.txt", "./matrix/tilt/base_1024.txt", 30.0, "./matrix/intensity/Si_se_d10t30.txt", 10.0 );
    simulate_intensity_with_tilt( "./matrix/beam/Si_se_selected.txt", "./matrix/ar/Si_se.txt", "./matrix/ug/Si_se_full.txt", "./matrix/tilt/base_1024.txt", 30.0, "./matrix/intensity/Si_se_d20t30.txt", 20.0 );
    simulate_intensity_with_tilt( "./matrix/beam/Si_se_selected.txt", "./matrix/ar/Si_se.txt", "./matrix/ug/Si_se_full.txt", "./matrix/tilt/base_1024.txt", 30.0, "./matrix/intensity/Si_se_d40t30.txt", 40.0 );
    simulate_intensity_with_tilt( "./matrix/beam/Si_se_selected.txt", "./matrix/ar/Si_se.txt", "./matrix/ug/Si_se_full.txt", "./matrix/tilt/base_1024.txt", 20.0, "./matrix/intensity/Si_se_d5t20.txt", 5.0 );
    simulate_intensity_with_tilt( "./matrix/beam/Si_se_selected.txt", "./matrix/ar/Si_se.txt", "./matrix/ug/Si_se_full.txt", "./matrix/tilt/base_1024.txt", 20.0, "./matrix/intensity/Si_se_d10t20.txt", 10.0 );
    simulate_intensity_with_tilt( "./matrix/beam/Si_se_selected.txt", "./matrix/ar/Si_se.txt", "./matrix/ug/Si_se_full.txt", "./matrix/tilt/base_1024.txt", 20.0, "./matrix/intensity/Si_se_d20t20.txt", 20.0 );
    simulate_intensity_with_tilt( "./matrix/beam/Si_se_selected.txt", "./matrix/ar/Si_se.txt", "./matrix/ug/Si_se_full.txt", "./matrix/tilt/base_1024.txt", 20.0, "./matrix/intensity/Si_se_d40t20.txt", 40.0 );
    simulate_intensity_with_tilt( "./matrix/beam/Si_se_selected.txt", "./matrix/ar/Si_se.txt", "./matrix/ug/Si_se_full.txt", "./matrix/tilt/base_1024.txt", 10.0, "./matrix/intensity/Si_se_d5t10.txt", 5.0 );
    simulate_intensity_with_tilt( "./matrix/beam/Si_se_selected.txt", "./matrix/ar/Si_se.txt", "./matrix/ug/Si_se_full.txt", "./matrix/tilt/base_1024.txt", 10.0, "./matrix/intensity/Si_se_d10t10.txt", 10.0 );
    simulate_intensity_with_tilt( "./matrix/beam/Si_se_selected.txt", "./matrix/ar/Si_se.txt", "./matrix/ug/Si_se_full.txt", "./matrix/tilt/base_1024.txt", 10.0, "./matrix/intensity/Si_se_d20t10.txt", 20.0 );
    simulate_intensity_with_tilt( "./matrix/beam/Si_se_selected.txt", "./matrix/ar/Si_se.txt", "./matrix/ug/Si_se_full.txt", "./matrix/tilt/base_1024.txt", 10.0, "./matrix/intensity/Si_se_d40t10.txt", 40.0 );
    simulate_intensity_with_tilt( "./matrix/beam/Si_se_selected.txt", "./matrix/ar/Si_se.txt", "./matrix/ug/Si_se_full.txt", "./matrix/tilt/base_1024.txt", 5.0, "./matrix/intensity/Si_se_d5t5.txt", 5.0 );
    simulate_intensity_with_tilt( "./matrix/beam/Si_se_selected.txt", "./matrix/ar/Si_se.txt", "./matrix/ug/Si_se_full.txt", "./matrix/tilt/base_1024.txt", 5.0, "./matrix/intensity/Si_se_d10t5.txt", 10.0 );
    simulate_intensity_with_tilt( "./matrix/beam/Si_se_selected.txt", "./matrix/ar/Si_se.txt", "./matrix/ug/Si_se_full.txt", "./matrix/tilt/base_1024.txt", 5.0, "./matrix/intensity/Si_se_d20t5.txt", 20.0 );
    simulate_intensity_with_tilt( "./matrix/beam/Si_se_selected.txt", "./matrix/ar/Si_se.txt", "./matrix/ug/Si_se_full.txt", "./matrix/tilt/base_1024.txt", 5.0, "./matrix/intensity/Si_se_d40t5.txt", 40.0 );
#endif 
#if 0
    simulate_intensity_with_tilt( "./matrix/beam/Si_se_selected.txt", "./matrix/ar/Si_se.txt", "./matrix/ug/si_se_d5t30.dat", "./matrix/tilt/base_1024.txt", 40.0, "./matrix/intensity/si_se_d5t30_f.txt", 5.0 );
    simulate_intensity_with_tilt( "./matrix/beam/Si_se_selected.txt", "./matrix/ar/Si_se.txt", "./matrix/ug/si_se_d10t30.dat", "./matrix/tilt/base_1024.txt", 40.0, "./matrix/intensity/si_se_d10t30_f.txt", 10.0 );
    simulate_intensity_with_tilt( "./matrix/beam/Si_se_selected.txt", "./matrix/ar/Si_se.txt", "./matrix/ug/si_se_d20t30.dat", "./matrix/tilt/base_1024.txt", 40.0, "./matrix/intensity/si_se_d20t30_f.txt", 20.0 );
    simulate_intensity_with_tilt( "./matrix/beam/Si_se_selected.txt", "./matrix/ar/Si_se.txt", "./matrix/ug/si_se_d40t30.dat", "./matrix/tilt/base_1024.txt", 40.0, "./matrix/intensity/si_se_d40t30_f.txt", 40.0 );
    simulate_intensity_with_tilt( "./matrix/beam/Si_se_selected.txt", "./matrix/ar/Si_se.txt", "./matrix/ug/si_se_d5t20.dat", "./matrix/tilt/base_1024.txt", 20.0, "./matrix/intensity/si_se_d5t20_f.txt", 5.0 );
    simulate_intensity_with_tilt( "./matrix/beam/Si_se_selected.txt", "./matrix/ar/Si_se.txt", "./matrix/ug/si_se_d10t20.dat", "./matrix/tilt/base_1024.txt", 20.0, "./matrix/intensity/si_se_d10t20_f.txt", 10.0 );
    simulate_intensity_with_tilt( "./matrix/beam/Si_se_selected.txt", "./matrix/ar/Si_se.txt", "./matrix/ug/si_se_d20t20.dat", "./matrix/tilt/base_1024.txt", 20.0, "./matrix/intensity/si_se_d20t20_f.txt", 20.0 );
    simulate_intensity_with_tilt( "./matrix/beam/Si_se_selected.txt", "./matrix/ar/Si_se.txt", "./matrix/ug/si_se_d40t20.dat", "./matrix/tilt/base_1024.txt", 20.0, "./matrix/intensity/si_se_d40t20_f.txt", 40.0 );
    simulate_intensity_with_tilt( "./matrix/beam/Si_se_selected.txt", "./matrix/ar/Si_se.txt", "./matrix/ug/si_se_d5t10.dat", "./matrix/tilt/base_1024.txt", 10.0, "./matrix/intensity/si_se_d5t10_f.txt", 5.0 );
    simulate_intensity_with_tilt( "./matrix/beam/Si_se_selected.txt", "./matrix/ar/Si_se.txt", "./matrix/ug/si_se_d10t10.dat", "./matrix/tilt/base_1024.txt", 10.0, "./matrix/intensity/si_se_d10t10_f.txt", 10.0 );
    simulate_intensity_with_tilt( "./matrix/beam/Si_se_selected.txt", "./matrix/ar/Si_se.txt", "./matrix/ug/si_se_d20t10.dat", "./matrix/tilt/base_1024.txt", 10.0, "./matrix/intensity/si_se_d20t10_f.txt", 20.0 );
    simulate_intensity_with_tilt( "./matrix/beam/Si_se_selected.txt", "./matrix/ar/Si_se.txt", "./matrix/ug/si_se_d20t10.dat", "./matrix/tilt/base_1024.txt", 10.0, "./matrix/intensity/si_se_d40t10_f.txt", 40.0 );
    simulate_intensity_with_tilt( "./matrix/beam/Si_se_selected.txt", "./matrix/ar/Si_se.txt", "./matrix/ug/si_se_d5t5.dat", "./matrix/tilt/base_1024.txt", 5.0, "./matrix/intensity/si_se_d5t5_f.txt", 5.0 );
    simulate_intensity_with_tilt( "./matrix/beam/Si_se_selected.txt", "./matrix/ar/Si_se.txt", "./matrix/ug/si_se_d10t5.dat", "./matrix/tilt/base_1024.txt", 5.0, "./matrix/intensity/si_se_d10t5_f.txt", 10.0 );
    simulate_intensity_with_tilt( "./matrix/beam/Si_se_selected.txt", "./matrix/ar/Si_se.txt", "./matrix/ug/si_se_d20t5.dat", "./matrix/tilt/base_1024.txt", 5.0, "./matrix/intensity/si_se_d20t5_f.txt", 20.0 );
    simulate_intensity_with_tilt( "./matrix/beam/Si_se_selected.txt", "./matrix/ar/Si_se.txt", "./matrix/ug/si_se_d40t5.dat", "./matrix/tilt/base_1024.txt", 5.0, "./matrix/intensity/si_se_d40t5_f.txt", 40.0 );
#endif
#if 0
    //simulate_intensity_with_tilt( "./matrix/beam/SrTiO3_demo.txt", "./matrix/ar/SrTiO3_demo.txt", "./matrix/ug/SrTiO3_demo_d5t20_f_se.dat", "./matrix/tilt/base_1024.txt", 20.0, "./matrix/intensity/SrTiO3_demo_d5t20_se.txt", 5.0 );
    simulate_intensity_with_tilt( "./matrix/beam/SrTiO3_demo.txt", "./matrix/ar/SrTiO3_demo.txt", "./matrix/ug/SrTiO3_demo_d40t5_f.dat", "./matrix/tilt/base_1024.txt", 5.0, "./matrix/intensity/SrTiO3_demo_d40t5_se.txt", 40.0 );
    simulate_intensity_with_tilt( "./matrix/beam/SrTiO3_demo.txt", "./matrix/ar/SrTiO3_demo.txt", "./matrix/ug/SrTiO3_demo_d40t10_f.dat", "./matrix/tilt/base_1024.txt", 10.0, "./matrix/intensity/SrTiO3_demo_d40t10_se.txt", 40.0 );
    simulate_intensity_with_tilt( "./matrix/beam/SrTiO3_demo.txt", "./matrix/ar/SrTiO3_demo.txt", "./matrix/ug/SrTiO3_demo_d40t20_f.dat", "./matrix/tilt/base_1024.txt", 20.0, "./matrix/intensity/SrTiO3_demo_d40t20_se.txt", 40.0 );
    simulate_intensity_with_tilt( "./matrix/beam/SrTiO3_demo.txt", "./matrix/ar/SrTiO3_demo.txt", "./matrix/ug/SrTiO3_demo_d40t40_f.dat", "./matrix/tilt/base_1024.txt", 40.0, "./matrix/intensity/SrTiO3_demo_d40t40_se.txt", 40.0 );

    simulate_intensity_with_tilt( "./matrix/beam/SrTiO3_demo.txt", "./matrix/ar/SrTiO3_demo.txt", "./matrix/ug/SrTiO3_demo_d20t5_f.dat", "./matrix/tilt/base_1024.txt", 5.0, "./matrix/intensity/SrTiO3_demo_d20t5_se.txt", 20.0 );
    simulate_intensity_with_tilt( "./matrix/beam/SrTiO3_demo.txt", "./matrix/ar/SrTiO3_demo.txt", "./matrix/ug/SrTiO3_demo_d20t10_f.dat", "./matrix/tilt/base_1024.txt", 10.0, "./matrix/intensity/SrTiO3_demo_d20t10_se.txt", 20.0 );
    simulate_intensity_with_tilt( "./matrix/beam/SrTiO3_demo.txt", "./matrix/ar/SrTiO3_demo.txt", "./matrix/ug/SrTiO3_demo_d20t20_f.dat", "./matrix/tilt/base_1024.txt", 20.0, "./matrix/intensity/SrTiO3_demo_d20t20_se.txt", 20.0 );
    simulate_intensity_with_tilt( "./matrix/beam/SrTiO3_demo.txt", "./matrix/ar/SrTiO3_demo.txt", "./matrix/ug/SrTiO3_demo_d20t40_f.dat", "./matrix/tilt/base_1024.txt", 40.0, "./matrix/intensity/SrTiO3_demo_d20t40_se.txt", 20.0 );

    simulate_intensity_with_tilt( "./matrix/beam/SrTiO3_demo.txt", "./matrix/ar/SrTiO3_demo.txt", "./matrix/ug/SrTiO3_demo_d10t5_f.dat", "./matrix/tilt/base_1024.txt", 5.0, "./matrix/intensity/SrTiO3_demo_d10t5_se.txt", 10.0 );
    simulate_intensity_with_tilt( "./matrix/beam/SrTiO3_demo.txt", "./matrix/ar/SrTiO3_demo.txt", "./matrix/ug/SrTiO3_demo_d10t10_f.dat", "./matrix/tilt/base_1024.txt", 10.0, "./matrix/intensity/SrTiO3_demo_d10t10_se.txt", 10.0 );
    simulate_intensity_with_tilt( "./matrix/beam/SrTiO3_demo.txt", "./matrix/ar/SrTiO3_demo.txt", "./matrix/ug/SrTiO3_demo_d10t20_f.dat", "./matrix/tilt/base_1024.txt", 20.0, "./matrix/intensity/SrTiO3_demo_d10t20_se.txt", 10.0 );
    simulate_intensity_with_tilt( "./matrix/beam/SrTiO3_demo.txt", "./matrix/ar/SrTiO3_demo.txt", "./matrix/ug/SrTiO3_demo_d10t40_f.dat", "./matrix/tilt/base_1024.txt", 40.0, "./matrix/intensity/SrTiO3_demo_d10t40_se.txt", 10.0 );

    simulate_intensity_with_tilt( "./matrix/beam/SrTiO3_demo.txt", "./matrix/ar/SrTiO3_demo.txt", "./matrix/ug/SrTiO3_demo_d5t5_f.dat", "./matrix/tilt/base_1024.txt", 5.0, "./matrix/intensity/SrTiO3_demo_d5t5_se.txt", 5.0 );
    simulate_intensity_with_tilt( "./matrix/beam/SrTiO3_demo.txt", "./matrix/ar/SrTiO3_demo.txt", "./matrix/ug/SrTiO3_demo_d5t10_f.dat", "./matrix/tilt/base_1024.txt", 10.0, "./matrix/intensity/SrTiO3_demo_d5t10_se.txt", 5.0 );
    simulate_intensity_with_tilt( "./matrix/beam/SrTiO3_demo.txt", "./matrix/ar/SrTiO3_demo.txt", "./matrix/ug/SrTiO3_demo_d5t20_f.dat", "./matrix/tilt/base_1024.txt", 20.0, "./matrix/intensity/SrTiO3_demo_d5t20_se.txt", 5.0 );
    simulate_intensity_with_tilt( "./matrix/beam/SrTiO3_demo.txt", "./matrix/ar/SrTiO3_demo.txt", "./matrix/ug/SrTiO3_demo_d5t40_f.dat", "./matrix/tilt/base_1024.txt", 40.0, "./matrix/intensity/SrTiO3_demo_d5t40_se.txt", 5.0 );
#endif
#if 0 
    simulate_intensity_with_tilt( "./matrix/beam/SrTiO3_demo.txt", "./matrix/ar/SrTiO3_demo.txt", "./matrix/ug/SrTiO3_abs_d5t20.dat", "./matrix/tilt/base_1024.txt", 20.0, "./matrix/intensity/SrTiO3_abs_d5t20.txt", 5.0 );
    simulate_intensity_with_tilt( "./matrix/beam/SrTiO3_demo.txt", "./matrix/ar/SrTiO3_demo.txt", "./matrix/ug/SrTiO3_abs_d40t5.dat", "./matrix/tilt/base_1024.txt", 5.0, "./matrix/intensity/SrTiO3_abs_d40t5.txt", 40.0 );
    simulate_intensity_with_tilt( "./matrix/beam/SrTiO3_demo.txt", "./matrix/ar/SrTiO3_demo.txt", "./matrix/ug/SrTiO3_abs_d40t10.dat", "./matrix/tilt/base_1024.txt", 10.0, "./matrix/intensity/SrTiO3_abs_d40t10.txt", 40.0 );
    simulate_intensity_with_tilt( "./matrix/beam/SrTiO3_demo.txt", "./matrix/ar/SrTiO3_demo.txt", "./matrix/ug/SrTiO3_abs_d40t20.dat", "./matrix/tilt/base_1024.txt", 20.0, "./matrix/intensity/SrTiO3_abs_d40t20.txt", 40.0 );
    simulate_intensity_with_tilt( "./matrix/beam/SrTiO3_demo.txt", "./matrix/ar/SrTiO3_demo.txt", "./matrix/ug/SrTiO3_abs_d40t40.dat", "./matrix/tilt/base_1024.txt", 40.0, "./matrix/intensity/SrTiO3_abs_d40t40.txt", 40.0 );

    simulate_intensity_with_tilt( "./matrix/beam/SrTiO3_demo.txt", "./matrix/ar/SrTiO3_demo.txt", "./matrix/ug/SrTiO3_abs_d20t5.dat", "./matrix/tilt/base_1024.txt", 5.0, "./matrix/intensity/SrTiO3_abs_d20t5.txt", 20.0 );
    simulate_intensity_with_tilt( "./matrix/beam/SrTiO3_demo.txt", "./matrix/ar/SrTiO3_demo.txt", "./matrix/ug/SrTiO3_abs_d20t10.dat", "./matrix/tilt/base_1024.txt", 10.0, "./matrix/intensity/SrTiO3_abs_d20t10.txt", 20.0 );
    simulate_intensity_with_tilt( "./matrix/beam/SrTiO3_demo.txt", "./matrix/ar/SrTiO3_demo.txt", "./matrix/ug/SrTiO3_abs_d20t20.dat", "./matrix/tilt/base_1024.txt", 20.0, "./matrix/intensity/SrTiO3_abs_d20t20.txt", 20.0 );
    simulate_intensity_with_tilt( "./matrix/beam/SrTiO3_demo.txt", "./matrix/ar/SrTiO3_demo.txt", "./matrix/ug/SrTiO3_abs_d20t40.dat", "./matrix/tilt/base_1024.txt", 40.0, "./matrix/intensity/SrTiO3_abs_d20t40.txt", 20.0 );

    simulate_intensity_with_tilt( "./matrix/beam/SrTiO3_demo.txt", "./matrix/ar/SrTiO3_demo.txt", "./matrix/ug/SrTiO3_abs_d10t5.dat", "./matrix/tilt/base_1024.txt", 5.0, "./matrix/intensity/SrTiO3_abs_d10t5.txt", 10.0 );
    simulate_intensity_with_tilt( "./matrix/beam/SrTiO3_demo.txt", "./matrix/ar/SrTiO3_demo.txt", "./matrix/ug/SrTiO3_abs_d10t10.dat", "./matrix/tilt/base_1024.txt", 10.0, "./matrix/intensity/SrTiO3_abs_d10t10.txt", 10.0 );
    simulate_intensity_with_tilt( "./matrix/beam/SrTiO3_demo.txt", "./matrix/ar/SrTiO3_demo.txt", "./matrix/ug/SrTiO3_abs_d10t20.dat", "./matrix/tilt/base_1024.txt", 20.0, "./matrix/intensity/SrTiO3_abs_d10t20.txt", 10.0 );
    simulate_intensity_with_tilt( "./matrix/beam/SrTiO3_demo.txt", "./matrix/ar/SrTiO3_demo.txt", "./matrix/ug/SrTiO3_abs_d10t40.dat", "./matrix/tilt/base_1024.txt", 40.0, "./matrix/intensity/SrTiO3_abs_d10t40.txt", 10.0 );

    simulate_intensity_with_tilt( "./matrix/beam/SrTiO3_demo.txt", "./matrix/ar/SrTiO3_demo.txt", "./matrix/ug/SrTiO3_abs_d5t5.dat", "./matrix/tilt/base_1024.txt", 5.0, "./matrix/intensity/SrTiO3_abs_d5t5.txt", 5.0 );
    simulate_intensity_with_tilt( "./matrix/beam/SrTiO3_demo.txt", "./matrix/ar/SrTiO3_demo.txt", "./matrix/ug/SrTiO3_abs_d5t10.dat", "./matrix/tilt/base_1024.txt", 10.0, "./matrix/intensity/SrTiO3_abs_d5t10.txt", 5.0 );
    simulate_intensity_with_tilt( "./matrix/beam/SrTiO3_demo.txt", "./matrix/ar/SrTiO3_demo.txt", "./matrix/ug/SrTiO3_abs_d5t20.dat", "./matrix/tilt/base_1024.txt", 20.0, "./matrix/intensity/SrTiO3_abs_d5t20.txt", 5.0 );
    simulate_intensity_with_tilt( "./matrix/beam/SrTiO3_demo.txt", "./matrix/ar/SrTiO3_demo.txt", "./matrix/ug/SrTiO3_abs_d5t40.dat", "./matrix/tilt/base_1024.txt", 40.0, "./matrix/intensity/SrTiO3_abs_d5t40.txt", 5.0 );
#endif
#if 0 
    simulate_intensity_with_tilt( "./matrix/beam/Si_se_selected.txt", "./matrix/ar/Si_se.txt", "./matrix/ug/si_se_abs/si_se_d5t30.dat", "./matrix/tilt/base_1024.txt", 40.0, "./matrix/intensity/si_se_abs/si_se_d5t30_f.txt", 5.0 );
    simulate_intensity_with_tilt( "./matrix/beam/Si_se_selected.txt", "./matrix/ar/Si_se.txt", "./matrix/ug/si_se_abs/si_se_d10t30.dat", "./matrix/tilt/base_1024.txt", 40.0, "./matrix/intensity/si_se_abs/si_se_d10t30_f.txt", 10.0 );
    simulate_intensity_with_tilt( "./matrix/beam/Si_se_selected.txt", "./matrix/ar/Si_se.txt", "./matrix/ug/si_se_abs/si_se_d20t30.dat", "./matrix/tilt/base_1024.txt", 40.0, "./matrix/intensity/si_se_abs/si_se_d20t30_f.txt", 20.0 );
    simulate_intensity_with_tilt( "./matrix/beam/Si_se_selected.txt", "./matrix/ar/Si_se.txt", "./matrix/ug/si_se_abs/si_se_d40t30.dat", "./matrix/tilt/base_1024.txt", 40.0, "./matrix/intensity/si_se_abs/si_se_d40t30_f.txt", 40.0 );
    simulate_intensity_with_tilt( "./matrix/beam/Si_se_selected.txt", "./matrix/ar/Si_se.txt", "./matrix/ug/si_se_abs/si_se_d5t20.dat", "./matrix/tilt/base_1024.txt", 20.0, "./matrix/intensity/si_se_abs/si_se_d5t20_f.txt", 5.0 );
    simulate_intensity_with_tilt( "./matrix/beam/Si_se_selected.txt", "./matrix/ar/Si_se.txt", "./matrix/ug/si_se_abs/si_se_d10t20.dat", "./matrix/tilt/base_1024.txt", 20.0, "./matrix/intensity/si_se_abs/si_se_d10t20_f.txt", 10.0 );
    simulate_intensity_with_tilt( "./matrix/beam/Si_se_selected.txt", "./matrix/ar/Si_se.txt", "./matrix/ug/si_se_abs/si_se_d20t20.dat", "./matrix/tilt/base_1024.txt", 20.0, "./matrix/intensity/si_se_abs/si_se_d20t20_f.txt", 20.0 );
    simulate_intensity_with_tilt( "./matrix/beam/Si_se_selected.txt", "./matrix/ar/Si_se.txt", "./matrix/ug/si_se_abs/si_se_d40t20.dat", "./matrix/tilt/base_1024.txt", 20.0, "./matrix/intensity/si_se_abs/si_se_d40t20_f.txt", 40.0 );
    simulate_intensity_with_tilt( "./matrix/beam/Si_se_selected.txt", "./matrix/ar/Si_se.txt", "./matrix/ug/si_se_abs/si_se_d5t10.dat", "./matrix/tilt/base_1024.txt", 10.0, "./matrix/intensity/si_se_abs/si_se_d5t10_f.txt", 5.0 );
    simulate_intensity_with_tilt( "./matrix/beam/Si_se_selected.txt", "./matrix/ar/Si_se.txt", "./matrix/ug/si_se_abs/si_se_d10t10.dat", "./matrix/tilt/base_1024.txt", 10.0, "./matrix/intensity/si_se_abs/si_se_d10t10_f.txt", 10.0 );
    simulate_intensity_with_tilt( "./matrix/beam/Si_se_selected.txt", "./matrix/ar/Si_se.txt", "./matrix/ug/si_se_abs/si_se_d20t10.dat", "./matrix/tilt/base_1024.txt", 10.0, "./matrix/intensity/si_se_abs/si_se_d20t10_f.txt", 20.0 );
    simulate_intensity_with_tilt( "./matrix/beam/Si_se_selected.txt", "./matrix/ar/Si_se.txt", "./matrix/ug/si_se_abs/si_se_d20t10.dat", "./matrix/tilt/base_1024.txt", 10.0, "./matrix/intensity/si_se_abs/si_se_d40t10_f.txt", 40.0 );
    simulate_intensity_with_tilt( "./matrix/beam/Si_se_selected.txt", "./matrix/ar/Si_se.txt", "./matrix/ug/si_se_abs/si_se_d5t5.dat", "./matrix/tilt/base_1024.txt", 5.0, "./matrix/intensity/si_se_abs/si_se_d5t5_f.txt", 5.0 );
    simulate_intensity_with_tilt( "./matrix/beam/Si_se_selected.txt", "./matrix/ar/Si_se.txt", "./matrix/ug/si_se_abs/si_se_d10t5.dat", "./matrix/tilt/base_1024.txt", 5.0, "./matrix/intensity/si_se_abs/si_se_d10t5_f.txt", 10.0 );
    simulate_intensity_with_tilt( "./matrix/beam/Si_se_selected.txt", "./matrix/ar/Si_se.txt", "./matrix/ug/si_se_abs/si_se_d20t5.dat", "./matrix/tilt/base_1024.txt", 5.0, "./matrix/intensity/si_se_abs/si_se_d20t5_f.txt", 20.0 );
    simulate_intensity_with_tilt( "./matrix/beam/Si_se_selected.txt", "./matrix/ar/Si_se.txt", "./matrix/ug/si_se_abs/si_se_d40t5.dat", "./matrix/tilt/base_1024.txt", 5.0, "./matrix/intensity/si_se_abs/si_se_d40t5_f.txt", 40.0 );
#endif
#if 0 
    simulate_intensity_with_tilt( "./matrix/beam/SrTiO3_demo.txt", "./matrix/ar/SrTiO3_demo.txt", "./matrix/ug/si_abs_fitting/d5t30.dat", "./matrix/tilt/base_1024.txt", 30.0, "./matrix/intensity/si_abs/si_d5t30_f.txt", 5.0 );
    simulate_intensity_with_tilt( "./matrix/beam/SrTiO3_demo.txt", "./matrix/ar/SrTiO3_demo.txt", "./matrix/ug/si_abs_fitting/d10t30.dat", "./matrix/tilt/base_1024.txt", 30.0, "./matrix/intensity/si_abs/si_d10t30_f.txt", 10.0 );
    simulate_intensity_with_tilt( "./matrix/beam/SrTiO3_demo.txt", "./matrix/ar/SrTiO3_demo.txt", "./matrix/ug/si_abs_fitting/d20t30.dat", "./matrix/tilt/base_1024.txt", 30.0, "./matrix/intensity/si_abs/si_d20t30_f.txt", 20.0 );
    simulate_intensity_with_tilt( "./matrix/beam/SrTiO3_demo.txt", "./matrix/ar/SrTiO3_demo.txt", "./matrix/ug/si_abs_fitting/d40t30.dat", "./matrix/tilt/base_1024.txt", 30.0, "./matrix/intensity/si_abs/si_d40t30_f.txt", 40.0 );
    simulate_intensity_with_tilt( "./matrix/beam/SrTiO3_demo.txt", "./matrix/ar/SrTiO3_demo.txt", "./matrix/ug/si_abs_fitting/d5t20.dat", "./matrix/tilt/base_1024.txt", 20.0, "./matrix/intensity/si_abs/si_d5t20_f.txt", 5.0 );
    simulate_intensity_with_tilt( "./matrix/beam/SrTiO3_demo.txt", "./matrix/ar/SrTiO3_demo.txt", "./matrix/ug/si_abs_fitting/d10t20.dat", "./matrix/tilt/base_1024.txt", 20.0, "./matrix/intensity/si_abs/si_d10t20_f.txt", 10.0 );
    simulate_intensity_with_tilt( "./matrix/beam/SrTiO3_demo.txt", "./matrix/ar/SrTiO3_demo.txt", "./matrix/ug/si_abs_fitting/d20t20.dat", "./matrix/tilt/base_1024.txt", 20.0, "./matrix/intensity/si_abs/si_d20t20_f.txt", 20.0 );
    simulate_intensity_with_tilt( "./matrix/beam/SrTiO3_demo.txt", "./matrix/ar/SrTiO3_demo.txt", "./matrix/ug/si_abs_fitting/d40t20.dat", "./matrix/tilt/base_1024.txt", 20.0, "./matrix/intensity/si_abs/si_d40t20_f.txt", 4_with_tilt( "./matrix/beam/Si_se_selected.txt", "./matrix/ar/Si_se.txt", "./matrix/ug/si_se_d20t20.dat", "./matrix/tilt/base_1024.txt", 20.0, "./matrix/intensity/si_se_d20t20_f.txt", 20.0 );
    simulate_intensity_with_tilt( "./matrix/beam/Si_se_selected.txt", "./matrix/ar/Si_se.txt", "./matrix/ug/si_se_d40t20.dat", "./matrix/tilt/base_1024.txt", 20.0, "./matrix/intensity/si_se_d40t20_f.txt", 40.0 );
    simulate_intensity_with_tilt( "./matrix/beam/Si_se_selected.txt", "./matrix/ar/Si_se.txt", "./matrix/ug/si_se_d5t10.dat", "./matrix/tilt/base_1024.txt", 10.0, "./matrix/intensity/si_se_d5t10_f.txt", 5.0 );
    simulate_intensity_with_tilt( "./matrix/beam/Si_se_selected.txt", "./matrix/ar/Si_se.txt", "./matrix/ug/si_se_d10t10.dat", "./matrix/tilt/base_1024.txt", 10.0, "./matrix/intensity/si_se_d10t10_f.txt", 10.0 );
    simulate_intensity_with_tilt( "./matrix/beam/Si_se_selected.txt", "./matrix/ar/Si_se.txt", "./matrix/ug/si_se_d20t10.dat", "./matrix/tilt/base_1024.txt", 10.0, "./matrix/intensity/si_se_d20t10_rix/ug/si_abs_fitting/d5t5.dat", "./matrix/tilt/base_1024.txt", 5.0, "./matrix/intensity/si_abs/si_d5t5_f.txt", 5.0 );
    simulate_intensity_with_tilt( "./matrix/beam/SrTiO3_demo.txt", "./matrix/ar/SrTiO3_demo.txt", "./matrix/ug/si_abs_fitting/d10t5.dat", "./matrix/tilt/base_1024.txt", 5.0, "./matrix/intensity/si_abs/si_d10t5_f.txt", 10.0 );
    simulate_intensity_with_tilt( "./matrix/beam/SrTiO3_demo.txt", "./matrix/ar/SrTiO3_demo.txt", "./matrix/ug/si_abs_fitting/d20t5.dat", "./matrix/tilt/base_1024.txt", 5.0, "./matrix/intensity/si_abs/si_d20t5_f.txt", 20.0 );
    simulate_intensity_with_tilt( "./matrix/beam/SrTiO3_demo.txt", "./matrix/ar/SrTiO3_demo.txt", "./matrix/ug/si_abs_fitting/d40t5.dat", "./matrix/tilt/base_1024.txt", 5.0, "./matrix/intensity/si_abs/si_d40t5_f.txt", 40.0 );
#endif

#if 0
    simulate_intensity_with_tilt( "./matrix/beam/SrTiO3_demo.txt", "./matrix/ar/SrTiO3_demo.txt", "./matrix/ug/limited_beam/SrTiO3_demo.txt", "./matrix/tilt/base_1024.txt", 30.0, "./matrix/ug/limited_beam/intensity/SrTiO3_1024.txt", 40.0 );

    simulate_intensity_with_tilt( "./matrix/beam/SrTiO3_demo.txt", "./matrix/ar/SrTiO3_demo.txt", "./matrix/ug/limited_beam/srtio3_512.dat", "./matrix/tilt/base_1024.txt", 30.0, "./matrix/ug/limited_beam/intensity/srtio3_512.txt", 40.0 );
    simulate_intensity_with_tilt( "./matrix/beam/SrTiO3_demo.txt", "./matrix/ar/SrTiO3_demo.txt", "./matrix/ug/limited_beam/poisson_srtio3_512.dat", "./matrix/tilt/base_1024.txt", 30.0, "./matrix/ug/limited_beam/intensity/poisson_srtio3_512.txt", 40.0 );

    simulate_intensity_with_tilt( "./matrix/beam/SrTiO3_demo.txt", "./matrix/ar/SrTiO3_demo.txt", "./matrix/ug/limited_beam/srtio3_256.dat", "./matrix/tilt/base_1024.txt", 30.0, "./matrix/ug/limited_beam/intensity/srtio3_256.txt", 40.0 );
    simulate_intensity_with_tilt( "./matrix/beam/SrTiO3_demo.txt", "./matrix/ar/SrTiO3_demo.txt", "./matrix/ug/limited_beam/poisson_srtio3_256.dat", "./matrix/tilt/base_1024.txt", 30.0, "./matrix/ug/limited_beam/intensity/poisson_srtio3_256.txt", 40.0 );

    simulate_intensity_with_tilt( "./matrix/beam/SrTiO3_demo.txt", "./matrix/ar/SrTiO3_demo.txt", "./matrix/ug/limited_beam/srtio3_128.dat", "./matrix/tilt/base_1024.txt", 30.0, "./matrix/ug/limited_beam/intensity/srtio3_128.txt", 40.0 );
    simulate_intensity_with_tilt( "./matrix/beam/SrTiO3_demo.txt", "./matrix/ar/SrTiO3_demo.txt", "./matrix/ug/limited_beam/poisson_srtio3_128.dat", "./matrix/tilt/base_1024.txt", 30.0, "./matrix/ug/limited_beam/intensity/poisson_srtio3_128.txt", 40.0 );

    simulate_intensity_with_tilt( "./matrix/beam/SrTiO3_demo.txt", "./matrix/ar/SrTiO3_demo.txt", "./matrix/ug/limited_beam/srtio3_64.dat", "./matrix/tilt/base_1024.txt", 30.0, "./matrix/ug/limited_beam/intensity/srtio3_64.txt", 40.0 );
    simulate_intensity_with_tilt( "./matrix/beam/SrTiO3_demo.txt", "./matrix/ar/SrTiO3_demo.txt", "./matrix/ug/limited_beam/poisson_srtio3_64.dat", "./matrix/tilt/base_1024.txt", 30.0, "./matrix/ug/limited_beam/intensity/poisson_srtio3_64.txt", 40.0 );

    simulate_intensity_with_tilt( "./matrix/beam/SrTiO3_demo.txt", "./matrix/ar/SrTiO3_demo.txt", "./matrix/ug/limited_beam/srtio3_32.dat", "./matrix/tilt/base_1024.txt", 30.0, "./matrix/ug/limited_beam/intensity/srtio3_32.txt", 40.0 );
    simulate_intensity_with_tilt( "./matrix/beam/SrTiO3_demo.txt", "./matrix/ar/SrTiO3_demo.txt", "./matrix/ug/limited_beam/poisson_srtio3_32.dat", "./matrix/tilt/base_1024.txt", 30.0, "./matrix/ug/limited_beam/intensity/poisson_srtio3_32.txt", 40.0 );

    simulate_intensity_with_tilt( "./matrix/beam/SrTiO3_demo.txt", "./matrix/ar/SrTiO3_demo.txt", "./matrix/ug/limited_beam/srtio3_16.dat", "./matrix/tilt/base_1024.txt", 30.0, "./matrix/ug/limited_beam/intensity/srtio3_16.txt", 40.0 );
    simulate_intensity_with_tilt( "./matrix/beam/SrTiO3_demo.txt", "./matrix/ar/SrTiO3_demo.txt", "./matrix/ug/limited_beam/poisson_srtio3_16.dat", "./matrix/tilt/base_1024.txt", 30.0, "./matrix/ug/limited_beam/intensity/poisson_srtio3_16.txt", 40.0 );
#endif

    //simulate_intensity_with_tilt( "./matrix/beam/SrTiO3_demo.txt", "./matrix/ar/SrTiO3_demo.txt", "./matrix/ug/SrTiO3_demo.txt", "./matrix/tilt/base_1024.txt", 11.0, "./matrix/intensity/SrTiO3_demo_d40t11.txt", 40.0 );
    //simulate_intensity_with_tilt( "./matrix/beam/SrTiO3_demo.txt", "./matrix/ar/SrTiO3_demo.txt", "./matrix/ug/SrTiO3_demo.txt", "./matrix/tilt/base_1024.txt", 12.0, "./matrix/intensity/SrTiO3_demo_d40t12.txt", 40.0 );

    //simulate_intensity_with_tilt( "./matrix/beam/SrTiO3_demo.txt", "./matrix/ar/SrTiO3_demo.txt", "./matrix/ug/SrTiO3_demo.txt", "./matrix/tilt/base_1024.txt", 11.0, "./matrix/intensity/SrTiO3_demo_d70t11.txt", 70.0 );
    //simulate_intensity_with_tilt( "./matrix/beam/SrTiO3_demo.txt", "./matrix/ar/SrTiO3_demo.txt", "./matrix/ug/SrTiO3_demo.txt", "./matrix/tilt/base_1024.txt", 12.0, "./matrix/intensity/SrTiO3_demo_d70t12.txt", 70.0 );

#if 0
    simulate_intensity_with_tilt( "./matrix/beam/SrTiO3_demo.txt", "./matrix/ar/SrTiO3_demo.txt", "./matrix/ug/hybrid_01_homotopy/hybrid_d40t5_ug.dat", "./matrix/tilt/base_1024.txt", 5.0, "./matrix/intensity/hybrid_01_homotopy/hybrid_d40t5_intensity.txt", 40.0 );
    simulate_intensity_with_tilt( "./matrix/beam/SrTiO3_demo.txt", "./matrix/ar/SrTiO3_demo.txt", "./matrix/ug/hybrid_01_homotopy/hybrid_d40t10_ug.dat", "./matrix/tilt/base_1024.txt", 10.0, "./matrix/intensity/hybrid_01_homotopy/hybrid_d40t10_intensity.txt", 40.0 );
    simulate_intensity_with_tilt( "./matrix/beam/SrTiO3_demo.txt", "./matrix/ar/SrTiO3_demo.txt", "./matrix/ug/hybrid_01_homotopy/hybrid_d40t20_ug.dat", "./matrix/tilt/base_1024.txt", 20.0, "./matrix/intensity/hybrid_01_homotopy/hybrid_d40t20_intensity.txt", 40.0 );
    simulate_intensity_with_tilt( "./matrix/beam/SrTiO3_demo.txt", "./matrix/ar/SrTiO3_demo.txt", "./matrix/ug/hybrid_01_homotopy/hybrid_d40t40_ug.dat", "./matrix/tilt/base_1024.txt", 40.0, "./matrix/intensity/hybrid_01_homotopy/hybrid_d40t40_intensity.txt", 40.0 );
#endif

    return 0;
}
