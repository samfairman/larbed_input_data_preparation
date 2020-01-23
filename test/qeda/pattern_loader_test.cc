#include <qeda/pattern.hpp>

#include <iostream>

int main( int argc, char** argv )
{
    using namespace qeda;

    pattern_collection<double> pc( argc, argv );

    std::cout << pc;

    return 0;
}

