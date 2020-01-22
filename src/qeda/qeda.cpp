// program: qeda: 'Quantitative Electron Diffraction Analysis'
//
#include <qeda/readparams.h>
#include <qeda/DataTypes.h>
#include <qeda/Crystal.h>
#include <qeda/PatternCollection.h>

#include <f/matrix/matrix.hpp>

#include <3rdparty/ezOptionParser/ezOptionParser.hpp>

#include <string>

#define MAX_BUF 1024
#define LARBED_SIM 0
#define LARBED_REC 1

void readArray(char *title,std::vector <ftype> &array,int N);

int main(int argc, char *argv[])
{
	// First we read/create in the experimental conditions.
	// We need:
	// - the microscope parameters (high tension)
	// - the (indexed) reciprocal lattice
	// - the zone axis
	// - the array of kt-vectors (this could also be defined as equally spaced, with some maximum value)
	//
	// There are 2 options for this code:
	// a) compute a LARBED pattern (requires knowledge of crystal structure)
	// b) analyze an experimental data set (requires measured intensities and spot positions)
	// We should first complete a), because we can then use that as input to b)

	/////////////////////////////////////////////////////////////////////////////////////////
	// Let's start with a few settings:
	int computeTermMaps = 0;

	/////////////////////////////////////////////////////////////////////////////////////////
	// Here are a few default parameters which should be overwritten by an input data file:
	char mapName[MAX_BUF];
	char dataName[MAX_BUF];
	char cfgName[MAX_BUF];    // name of crystal structure
	char outputName[MAX_BUF]; // name of output file
	char buf[MAX_BUF];
	int mode = LARBED_SIM;
	std::vector <ftype> n(3,0.0f);  // surface normal
	std::vector <ftype> zone(3,0.0f);
	std::vector <ftype> gx(3,0.0f);
	std::vector <ftype> ktOffset(2,0.0f);
	ftype highTension = 120;
	ftype gCutoff     = 2.5f; // 4.0f;      // cut off reflections at 3 1/A
	ftype sgCutoff    = 0.025f; // 0.06f;       // select reflections that are closer than 0.2 1/A to the Ewald sphere.
	ftype thickness   = 130.0f;      // thickness in A.
	ftype scanComp    = 0.0f;    //0.94; //
	int detectorNx  = 700;
	int detectorNy  = detectorNx;
	ftype tiltRange_mrad = 4.2f; //70; //
	int discRadius_pixel = 18;
	int q,approxOrder = 0;
	ftype termThresh = 0.0001f, targetUg = 0.01f;
	ftype errVal;  // residual value during fitting
	//sprintf(cfgName,"TlNbO.cfg");
	sprintf(cfgName,"SrTiO3.cfg");
	sprintf(outputName,"output.img");
	sprintf(dataName,"output.dat");
	n[2] = 1.0f;    // surface slab normal points against the beam
	zone[2] = 1.0f;
	gx[0] = 1.0f;
    std::string tilt_file;

#if 0
	// read input file:
	if (argc > 1)  {
		if (parOpen(argv[1]) != 0) {  // open the input file
			if (readparam("mode:",buf,1)) {
				if (strstr(buf,"LARBED_SIM")) mode = LARBED_SIM;
				if (strstr(buf,"LARBED_REC")) mode = LARBED_REC;
				// printf("buf: %s\n",buf);
			}
			if (readparam("cfg file:",buf,1)) sscanf(buf,"%s",cfgName);
			if (readparam("output file:",buf,1)) sscanf(buf,"%s",outputName);
			if (readparam("data file:",buf,1)) sscanf(buf,"%s",dataName);  // file for saving/loading diffraction intensities
			readArray("zone axis:",zone,3);
			readArray("gx vector:",gx,3);
			readArray("surface normal:",n,3);
			readArray("tilt offset (mrad):",ktOffset,2);
			if (readparam("high tension:",buf,1)) sscanf(buf,"%g",&highTension);
			if (readparam("max g vector:",buf,1)) sscanf(buf,"%g",&gCutoff);
			if (readparam("max sg:",buf,1)) sscanf(buf,"%g",&sgCutoff);
			if (readparam("thickness:",buf,1)) sscanf(buf,"%g",&thickness);
			if (readparam("scan compensation:",buf,1)) sscanf(buf,"%g",&scanComp);
			if (readparam("tilt range (mrad):",buf,1)) sscanf(buf,"%g",&tiltRange_mrad);
			if (readparam("disc radius (pixels):",buf,1)) sscanf(buf,"%d",&discRadius_pixel);
			if (readparam("detector size x:",buf,1)) sscanf(buf,"%d",&detectorNx);
			detectorNy = detectorNx;
			if (readparam("detector size y:",buf,1)) sscanf(buf,"%d",&detectorNy);
			if (readparam("approximation:",buf,1)) sscanf(buf,"%d",&approxOrder);
			if (readparam("term threshold:",buf,1)) sscanf(buf,"%g",&termThresh);
			if (readparam("target Ug:",buf,1)) sscanf(buf,"%g",&targetUg);


			parClose();
		}
	}
#endif

    if ( 1 )
    {
        ez::ezOptionParser opt;
        opt.overview = "QEDA Program";
        opt.syntax = "qeda [OPTIONS]";
        opt.example = "qeda --input simple.qeda\n\n";


        //----

        opt.add(
            "", // Default.
            0, // Required?
            0, // Number of args expected.
            0, // Delimiter if expecting multiple args.
            "Print this usage message.", // Help description.
            "-h",     // Flag token.
            "-help", // Flag token.
            "--help", // Flag token.
            "--usage" // Flag token.
        );

        opt.add(
            "", // Default.
            0, // Required?
            0, // Number of args expected.
            0, // Delimiter if expecting multiple args.
            "input configuration file.", // Help description.
            "-i", // Flag token.
            "--input" // Flag token.
        );

        opt.add(
            "LARBED_SIM", // Default.
            0, // Required?
            1, // Number of args expected.
            0, // Delimiter if expecting multiple args.
            "Specifies different modes of qeda operation.", // Help description.
            "--mode" // Flag token.
        );

        opt.add(
            "SrTiO3.cfg", // Default.
            //"TlNbO.cfg", // Default.
            0, // Required?
            1, // Number of args expected.
            0, // Delimiter if expecting multiple args.
            "crystal configuration file.", // Help description.
            "--configuration" // Flag token.
        );

        opt.add(
            "output.img", // Default.
            0, // Required?
            1, // Number of args expected.
            0, // Delimiter if expecting multiple args.
            "output file.", // Help description.
            "-o", // Flag token.
            "--output" // Flag token.
        );

        opt.add(
            "LARBED.dat", // Default.
            0, // Required?
            1, // Number of args expected.
            0, // Delimiter if expecting multiple args.
            "data file.", // Help description.
            "--datafile" // Flag token.
        );

        opt.add(
            "0,0,1", // Default.
            0, // Required?
            3, // Number of args expected.
            ',', // Delimiter if expecting multiple args.
            "zone axis.", // Help description.
            "--zone" // Flag token.
        );

        opt.add(
            "1,0,0", // Default.
            0, // Required?
            3, // Number of args expected.
            ',', // Delimiter if expecting multiple args.
            "gx vector.", // Help description.
            "--gxvector" // Flag token.
        );

        opt.add(
            "0,0,1", // Default.
            0, // Required?
            3, // Number of args expected.
            ',', // Delimiter if expecting multiple args.
            "surface normal.", // Help description.
            "--surface_normal" // Flag token.
        );

        opt.add(
            "0,0", // Default.
            0, // Required?
            2, // Number of args expected.
            ',', // Delimiter if expecting multiple args.
            "tilt offset.", // Help description.
            "--tilt_offset" // Flag token.
        );

        opt.add(
            "matlab/sto_fit_k/ktArray_new.txt", //default
            0, // Required?
            1, // Number of args expected.
            ',', // Delimiter if expecting multiple args.
            "tilt file.", // Help description.
            "--tilt_file" // Flag token.
        );


        opt.add(
            "0", // Default.
            0, // Required?
            1, // Number of args expected.
            0, // Delimiter if expecting multiple args.
            "approximation method, 0 = bloch wave, 1=kinematic, >1=Scattering patch expansion ", // Help description.
            "--approximation_method" // Flag token.
        );

        opt.add(
            "120", // Default.
            0, // Required?
            1, // Number of args expected.
            0, // Delimiter if expecting multiple args.
            "high tension in Kv", // Help description.
            "--high_tension" // Flag token.
        );

        opt.add(
            "0.0001", // Default.
            0, // Required?
            1, // Number of args expected.
            0, // Delimiter if expecting multiple args.
            "term threshold -- fraction of total intensity above which to include a term", // Help description.
            "--term_threshold" // Flag token.
        );

        opt.add(
            "0.07", // Default.
            0, // Required?
            1, // Number of args expected.
            0, // Delimiter if expecting multiple args.
            "target Ug -- maximum value expected for any Ug", // Help description.
            "--target_ug" // Flag token.
        );

        opt.add(
            "0.96", // Default.
            0, // Required?
            1, // Number of args expected.
            0, // Delimiter if expecting multiple args.
            "max g vector in 1/A", // Help description.
            "--max_g_vector" // Flag token.
        );

        opt.add(
            "0.1", // Default.
            0, // Required?
            1, // Number of args expected.
            0, // Delimiter if expecting multiple args.
            "max sgCutoff, selects reflections that are closer that 0.02/A to the Ewald sphere", // Help description.
            "--max_sg" // Flag token.
        );

        opt.add(
            "120.5", // Default.
            0, // Required?
            1, // Number of args expected.
            0, // Delimiter if expecting multiple args.
            "Thickness in A", // Help description.
            "--thickness" // Flag token.
        );

        opt.add(
            "0.95", // Default.
            0, // Required?
            1, // Number of args expected.
            0, // Delimiter if expecting multiple args.
            "scan compensation", // Help description.
            "--scan_compensation" // Flag token.
        );

        opt.add(
            //"70", // Default.
            "10", // Default.
            0, // Required?
            1, // Number of args expected.
            0, // Delimiter if expecting multiple args.
            "tilt range in mrad", // Help description.
            "--tilt_range" // Flag token.
        );

        opt.add(
            //"18", // Default.
            "8", // Default.
            0, // Required?
            1, // Number of args expected.
            0, // Delimiter if expecting multiple args.
            "disc radius in pixel", // Help description.
            "--disc_radius" // Flag token.
        );

        opt.add(
            "1000", // Default.
            0, // Required?
            1, // Number of args expected.
            0, // Delimiter if expecting multiple args.
            "detector size x, the width of diffraction pattern in pixels", // Help description.
            "--detector_size_x" // Flag token.
        );

        opt.add(
            "1000", // Default.
            0, // Required?
            1, // Number of args expected.
            0, // Delimiter if expecting multiple args.
            "detector size y, the width of diffraction pattern in pixels", // Help description.
            "--detector_size_y" // Flag token.
        );

        //----
        opt.parse(argc, argv);

        //print help/usage information
        auto usage = []( ez::ezOptionParser& opt )
        {
            std::string usage;
            opt.getUsage(usage);
            std::cout << usage;
        };

        //help message?
        if (opt.isSet("-h"))
        {
            usage( opt );
            return 0;
        }

        {//bad options
            std::vector<std::string> badOptions;
            if(!opt.gotRequired(badOptions)) {
                for(unsigned long i=0; i < badOptions.size(); ++i)
                    std::cerr << "ERROR: Missing required option " << badOptions[i] << ".\n\n";
                usage(opt);
                return 1;
            }
            if(!opt.gotExpected(badOptions)) {
                for(unsigned long i=0; i < badOptions.size(); ++i)
                    std::cerr << "ERROR: Got unexpected number of arguments for option " << badOptions[i] << ".\n\n";

                usage(opt);
                return 1;
            }
        }

#if 1
        opt.get("--tilt_file")->getString( tilt_file );
        opt.get("--configuration")->getString( cfgName );
        opt.get("--output")->getString( outputName );
        opt.get("--datafile")->getString( dataName );
        opt.get("--zone")->getDoubles( zone );
        opt.get("--gxvector")->getDoubles( gx );
        opt.get("--surface_normal")->getDoubles( n );
        opt.get("--tilt_offset")->getDoubles( ktOffset );
        opt.get("--approximation_method")->getInt( approxOrder );
        opt.get("--high_tension")->getDouble( highTension );
        opt.get("--term_threshold")->getDouble( termThresh );
        opt.get("--target_ug")->getDouble( targetUg );
        opt.get("--max_g_vector")->getDouble( gCutoff );
        opt.get("--max_sg")->getDouble( sgCutoff );
        opt.get("--thickness")->getDouble( thickness );
        opt.get("--scan_compensation")->getDouble( scanComp );
        opt.get("--tilt_range")->getDouble( tiltRange_mrad );
        opt.get("--disc_radius")->getInt( discRadius_pixel );
        opt.get("--detector_size_x")->getInt( detectorNx );
        opt.get("--detector_size_y")->getInt( detectorNy );
#endif

        {//input
            std::vector< std::vector<std::string> > input_files;
            opt.get("--input")->getMultiStrings(input_files);

            for ( auto&& file : input_files )
            {
                if (! opt.importFile(file[0].c_str(), '%'))
                {
                    std::cerr << "ERROR: Failed to open file " << file[0] << std::endl;

                    usage(opt);
                    return 1;
                }
            }

        }

        {//qeda mode
            std::string the_mode;
            opt.get("--mode")->getString(the_mode);
            if ( the_mode == std::string{"LARBED_SIM"})
            {
               mode = LARBED_SIM;
            }
            else if ( the_mode == std::string{"LARBED_REC"} )
            {
               mode = LARBED_REC;
            }
            else
            {
                std::cerr << "ERROR: Got unexpected argument [" << the_mode <<  "] for option <--mode>.\n\n";
                usage(opt);
                return 1;
            }
        }


#if 0
        opt.get("--tilt_file")->getString( tilt_file );
        opt.get("--configuration")->getString( cfgName );
        opt.get("--output")->getString( outputName );
        opt.get("--datafile")->getString( dataName );
        opt.get("--zone")->getDoubles( zone );
        opt.get("--gxvector")->getDoubles( gx );
        opt.get("--surface_normal")->getDoubles( n );
        opt.get("--tilt_offset")->getDoubles( ktOffset );
        opt.get("--approximation_method")->getInt( approxOrder );
        opt.get("--high_tension")->getDouble( highTension );
        opt.get("--term_threshold")->getDouble( termThresh );
        opt.get("--target_ug")->getDouble( targetUg );
        opt.get("--max_g_vector")->getDouble( gCutoff );
        opt.get("--max_sg")->getDouble( sgCutoff );
        opt.get("--thickness")->getDouble( thickness );
        opt.get("--scan_compensation")->getDouble( scanComp );
        opt.get("--tilt_range")->getDouble( tiltRange_mrad );
        opt.get("--disc_radius")->getInt( discRadius_pixel );
        opt.get("--detector_size_x")->getInt( detectorNx );
        opt.get("--detector_size_y")->getInt( detectorNy );
#endif

    }

    std::cout << "\nQEDA configurations:\n";
    std::cout << "highTension: " << highTension << "\n";
    std::cout << "gCutoff: " << gCutoff << "\n";
    std::cout << "sgCutoff: " << sgCutoff << "\n";
    std::cout << "thickness: " << thickness << "\n";
    std::cout << "scanComp: " << scanComp << "\n";
    std::cout << "detectorNx: " << detectorNx << "\n";
    std::cout << "detectorNy: " << detectorNy << "\n";
    std::cout << "tiltRange_mrad: " << tiltRange_mrad << "\n";
    std::cout << "discRadius_pixel: " << discRadius_pixel << "\n";
    std::cout << "Configuration: " << cfgName << "\n";
    std::cout << "Output: " << outputName << "\n";
    std::cout << "Data: " << dataName << "\n\n";

	// end of setup of default settings
	/////////////////////////////////////////////////////////////////////////////////////////
	int nBeamsTotal;
	// read the crystal structure:
	Crystal Xtal(cfgName);
	// for debugging:
	// Xtal.Print();

	/////////////////////////////////////////////////////////////////////////////////////////
	// Now we can allocate and initialize the pattern collection (e.g. LARBED data set).
	// This also assigns it the crystal object containing lattice parameters, etc.
	PatternCollection dataSet(&Xtal,highTension,zone,n,gx,gCutoff,sgCutoff);

	printf("\n************************************************************* \n");
	switch(mode) {
		case LARBED_SIM:

			printf("* QEDA: Simulation of %s (%.1f %.1f %.1f)\n",cfgName,zone[0],zone[1],zone[2]);

			// If we want to do simulations we can automatically create a disc pattern with a certain radius
			// and a given number of pixels spanning the radius:
			// dataSet.GenerateDisc(tiltRange_mrad,discRadius_pixel,ktOffset);
			dataSet.ReadDisc(tilt_file);
			// For curiosity, we can look how many beams have been selected for each pattern
			dataSet.PrintTilts();
			// dataSet.CreateBeamCountMap();

			// Next, we can generate the structure factor master list
			nBeamsTotal = dataSet.CreateUgMasterList();
			printf("All patterns together contain %d different beams\n",nBeamsTotal);


			// if we use the scattering path expansion, then convergence will be slowed down by the large value of U0.
			// We therefore simply set U0 to zero:
			dataSet.ComputeUgMasterList();
			if (approxOrder !=  0) {
				dataSet.resetU0();
				// compute term strength maps, up to approxOrder:
				if (computeTermMaps) {
					for (q=1;q<=abs(approxOrder);q++) {
						dataSet.ComputeDiffraction(thickness,-q,termThresh,targetUg);
						sprintf(mapName,"termMap_q=%d.img",q);
						dataSet.CreateDiffPat(mapName,detectorNx,detectorNy,scanComp);
					}
				}
			}
            //dataSet.load_intensity("testdata/sto_accr");
			// for debugging purposes only:
			dataSet.PrintUgMasterList(NULL);
			if (approxOrder >= 0) {
				// And now, we can start the dynamical calculation.
				dataSet.ComputeDiffraction(thickness,approxOrder,termThresh,targetUg);

                dataSet.load_intensity("testdata/sto_accr");

                //return 0;

				// Let's save the data in binary format, so that we can analyze it later:
				dataSet.SaveDiffractionIntensities(dataName);

				// Finally, we ant to display the pattern.
				dataSet.CreateDiffPat(outputName,detectorNx,detectorNy,scanComp);

                dataSet.dump( "dump" );
			}

            if( 1 )
            {   //dump img
                f::matrix<double> fit_result_mat;
                //fit_result_mat.load( "./matlab/display_potential/solution.sto_accr.12.2_abs_thickness_dec_3.dat" );
                //fit_result_mat.load( "./matlab/display_potential/solution.sto_accr.12.2_abs_thickness_dec_7.dat" );
                //fit_result_mat.load( "./matlab/display_potential/solution.sto_accr.12.2_thickness_dec_21.dat" );
                //fit_result_mat.load( "./matlab/display_potential/solution.sto_accr.12.2_thickness_2015_jan_23_cuda.dat" );
                //fit_result_mat.load( "./matlab/display_potential/zigmoid_zigmoid_homotopy_cuda_pattern_0.000000--0.010000_Mon_Mar__9_14_25_03_2015.dat" );
                //fit_result_mat.load( "./matlab/display_potential/merit_fixed_0.01_0.000000--0.010000_Thu_Apr__9_13_59_42_2015.dat" );
                //fit_result_mat.load( "./matlab/display_potential/60_abs_zigmoid_homotopy_cuda_pattern_0.000000--0.010000_Mon_Apr_13_14_14_04_2015.dat" );
                fit_result_mat.load( "./matlab/display_potential/merit_E_2PI_G_PIPI_c1_ABS_constrained_scaled_zigmoid_homotopy_cuda_pattern_0.000000--0.010000_Mon_May_11_10_46_07_2015.dat" );
                std::cout << "size for matrix fit_result is " << fit_result_mat.row() << "X" << fit_result_mat.col() << "\n";

                for ( unsigned long index = 0; index != fit_result_mat.row(); ++index )
                {

                    //if ( (index != 0) && (index != 49) && (index != 149) && (index != 2039) ) continue;
                    //if ( index != 11 ) continue;

                    //unsigned long index = 999;
                    std::cout << "\nloading img index " << index << " ...... ";
                    //load ugs
                    //dataSet.load_ug( &fit_result_mat[index][1] );
                    dataSet.load_ug_thickness( &fit_result_mat[index][1] );
                    dataSet.ComputeDiffraction(thickness,approxOrder,termThresh,targetUg);
                    std::string const output_name = std::to_string(index) + std::string{".img"};
                    std::fill( outputName, outputName+MAX_BUF, '\0' );
                    std::copy( output_name.begin(), output_name.end(), outputName );
                    dataSet.CreateDiffPat(outputName,detectorNx,detectorNy,scanComp);

                    if ( index >= 350 ) break;

                    index += 10;
                } 

            }

			// Xtal.Print();

			// write all the simulated intensities, matrix diagonals, and Ar's to disk
			dataSet.WriteSimulationParameters("STO_params");
			////dataSet.PrintUgMasterList("STO_params\\_BeamList.txt",1);
			////dataSet.PrintUgMasterList("STO_params\\_UgMasterList.txt",0);
			dataSet.PrintUgMasterList("_BeamList.txt",1);
			dataSet.PrintUgMasterList("_UgMasterList.txt",0);



			if (0) {
				///////////////////////////////////////////////////////////////////////////////////////////////
				// let's also fit kinematic rocking curves to get a first estimate of the structure factors:
				// First, we need to load the experimental data:
				dataSet.LoadDiffractionIntensities(dataName);
				nBeamsTotal = dataSet.CreateUgMasterList();
				printf("All patterns together contain %d different beams\n",nBeamsTotal);
				// Now, we can fit the diffraction data, first with kinematic theory,
				// then with higher order approximations to dynamical theory:
				// This function will populate the real parts of those Ugs in the masterUg
				// array which are represented by actual diffraction intensities.
				errVal = dataSet.FitKinematicRockingCurves(thickness);
				printf("Residual error after kinematic rocking curve fit: %f\n",errVal);
				dataSet.PrintUgMasterList("_UgMasterList_KinematicFit.txt",0);
			}

            std::cout << dataSet << "\n";

			break;
		case LARBED_REC:
			printf("* QEDA: Reconstruction from file %s\n",dataName);

			////////////////////////////////////////////////////////////////////
			// First, we need to load the experimental data:
			dataSet.LoadDiffractionIntensities(dataName);
			// The crystal unit cell parameters have already been loaded (the actual atom positions will not be used)
			// Next, we can generate the structure factor master list (we won't compute them yet):
			dataSet.PrintTilts();

			nBeamsTotal = dataSet.CreateUgMasterList();
			printf("All patterns together contain %d different beams\n",nBeamsTotal);

			////////////////////////////////////////////////////////////////////
			// Now, we can fit the diffraction data, first with kinematic theory,
			// then with higher order approximations to dynamical theory:
			// This function will populate the real parts of those Ugs in the masterUg
			// array which are represented by actual diffraction intensities.
			errVal = dataSet.FitKinematicRockingCurves(thickness);
			printf("Residual error after kinematic rocking curve fit: %f\n",errVal);

			// Just for debugging purposes, to see if starting with the correct solution we will also stay there:
			// dataSet.ComputeUgMasterList();
			dataSet.resetU0();
			dataSet.PrintUgMasterList(NULL);

			if (approxOrder > 1) {
				switch (0) {
				case 0:
					for (int i=1;i<50;i++) {
						printf("\n\n***** Iteration %d *****\n",i);
						errVal = dataSet.RefineStructureFactorsDynamicOnly(2,100,thickness);
						printf("Residual error after double scattering rocking curve fit to dynamical part only: %f\n",errVal);
						errVal = dataSet.RefineStructureFactors(2,5,thickness);
						printf("Residual error after double scattering rocking curve fit: %f\n",errVal);
						errVal = dataSet.RefineStructureFactorsLocal(2,15,thickness);
						printf("Residual error after multivariate double scattering rocking curve fit: %f\n",errVal);
					}
					errVal = dataSet.RefineStructureFactors(2,5,thickness);
					printf("Residual error after double scattering rocking curve fit: %f\n",errVal);
					break;
				case 1:
					errVal = dataSet.RefineStructureFactors(2,100,thickness);
					printf("Residual error after double scattering rocking curve fit: %f\n",errVal);
					errVal = dataSet.RefineStructureFactorsLocal(2,100,thickness);
					printf("Residual error after multivariate double scattering rocking curve fit: %f\n",errVal);
					break;
				case 2:
					// dataSet.PrintUgMasterList();
					errVal = dataSet.RefineStructureFactors(2,100,thickness);
					printf("Residual error after double scattering rocking curve fit: %f\n",errVal);
					break;
				}
				dataSet.PrintUgMasterList(NULL);
				dataSet.SetDk(tiltRange_mrad,discRadius_pixel);
				dataSet.CreateDiffPat("temp2.img",detectorNx,detectorNy,scanComp);

			}
			// Xtal.Print();


			break;
	}

}


void readArray(char *title,std::vector <ftype> &array,int N) {
	int i;
	char buf[512],*str;

	if (!readparam(title,buf,1)) {
		printf("%s array not found - exit\n",title);
		return;
	}
	i=0;
	str = buf;
	if (strchr(" \t\n",*str) != NULL) str = strnext(str," \t");
	while (i<N) {
		array[i++] = atof(str);
		str = strnext(str," \t\n");
		while (str == NULL) {
			if (!readNextLine(buf,511)) {
				printf("Incomplete reading of %s array - exit\n",title);
				return;
			}
			str = buf;
			if (strchr(" \t\n",*str) != NULL) str = strnext(str," \t\n");
		}
	}
}
