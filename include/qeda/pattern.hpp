#ifndef NJYBUWEVMMKATXATKGKGJCPBTJERFTBGGJNKWLJGGXBXGDFUVYHFQRKGDOMJYSMFFLXVQVOOJ
#define NJYBUWEVMMKATXATKGKGJCPBTJERFTBGGJNKWLJGGXBXGDFUVYHFQRKGDOMJYSMFFLXVQVOOJ

#include <f/matrix/matrix.hpp>
#include <qeda/pattern_loader_parser.h>

#include <vector>
#include <complex>
#include <cstddef>
#include <iostream>
#include <cassert>
#include <algorithm>
#include <iterator>
#include <string>

#include <boost/lexical_cast.hpp>

namespace qeda
{
    template< typename T >
    struct pattern
    {
        typedef T                               value_type;
        typedef std::complex<value_type>        complex_type;
        typedef std::size_t                     size_type;
        typedef f::matrix<size_type>            ug_marker_matrix_type;
        typedef std::vector<complex_type>       diag_array_type;

        diag_array_type         diag;
        ug_marker_matrix_type   ug_marker;
    };//struct pattern

    template< typename T >
    struct pattern_collection
    {
        typedef T                               value_type;
        typedef std::complex<value_type>        complex_type;
        typedef std::vector<complex_type>       ug_array_type;
        typedef f::matrix<complex_type>         complex_matrix_type;
        typedef pattern<value_type>             pattern_type;
        typedef typename pattern_type::ug_marker_matrix_type ug_marker_matrix_type;
        typedef std::vector<pattern_type>       pattern_array_type;

        pattern_collection( int argc, char** argv )
        {
            gengetopt_args_info arg;
            assert( !cmdline_parser (argc, argv, &arg) );

            auto const& directory = arg.directory_arg;   //the directory
            int const pattern_number = arg.patterns_arg;

            complex_matrix_type cm;

            //load ug
            std::string const ug_path = directory + std::string( "/ug.txt" );
            cm.load( ug_path.c_str() );
            ug.reserve( cm.size() );
            std::copy( cm.begin(), cm.end(), std::back_inserter( ug ) );

            //load pattern i
            for ( int i = 0; i != pattern_number; ++i )
            {
                pattern_type pt;
                //load diag
                std::string const diag_path = directory + std::string( "/" ) + boost::lexical_cast<std::string>(i) + std::string( "_diag.txt" );
                cm.load( diag_path.c_str() );
                pt.diag.reserve( cm.size() );
                std::copy( cm.begin(), cm.end(), std::back_inserter( pt.diag ) );

                //load ug_marker
                ug_marker_matrix_type um;
                std::string const ug_marker_path = directory + std::string( "/" ) + boost::lexical_cast<std::string>(i) + std::string( "_marker.txt" );
                um.load( ug_marker_path.c_str() );
                um.swap( pt.ug_marker );
                //std::swap( um, pt.ug_marker );
                patterns.push_back( pt );
            }

            cmdline_parser_free (&arg);
        }

        ug_array_type           ug;
        pattern_array_type      patterns;
    };//struct pattern_collection

    template< typename T >
    std::ostream& operator << ( std::ostream& os, pattern<T> const& rhs )
    {
        os << "\ndiag:\n";
        for ( auto const& d : rhs.diag ) os << d << "\t";

        os << "\nug_marker:\n" << rhs.ug_marker << "\n";
        return os;
    }

    template< typename T >
    std::ostream& operator << ( std::ostream& os, pattern_collection<T> const& rhs )
    {
        std::cout << "\nug:\n";
        for ( auto const& u : rhs.ug ) os << u << "\t";

        std::cout << "\npatterns:\n";
        //for ( auto const& pt : rhs.patterns ) os << pt << "\n";
        for ( auto it = rhs.patterns.begin(); it != rhs.patterns.end(); ++it )
            os << *it << "\n";

        return os;
    }
}//namespace qeda

#endif//NJYBUWEVMMKATXATKGKGJCPBTJERFTBGGJNKWLJGGXBXGDFUVYHFQRKGDOMJYSMFFLXVQVOOJ
