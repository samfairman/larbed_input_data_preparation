#include "pattern_loader_parser.h"

#include <iostream>
#include <cstdlib>

using namespace std;


int main( int argc, char** argv )
{
    gengetopt_args_info arg;

    if (cmdline_parser (argc, argv, &arg) )
        std::exit( 1 );


    std::cout << "\n the directory passed is \n\t" << arg.directory_arg << "\n\n";
    std::cout << "\n the patterns passed is \n\t" << arg.patterns_arg << "\n\n";
    
    cmdline_parser_free (&arg);

    return 0;
}

