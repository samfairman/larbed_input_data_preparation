#ifndef XFDS9UIHKJLAFDLKJHSAFKJX39UASLFDKJASDOFUIH4JKSFDKJBASFDJKAHSFLKJHSFDKJHF
#define XFDS9UIHKJLAFDLKJHSAFKJX39UASLFDKJASDOFUIH4JKSFDKJBASFDJKAHSFLKJHSFDKJHF

#include <iostream>
#include <algorithm>
#include <string>
#include <sstream>
#include <vector>
#include <memory>
#include <iterator>

#include <cassert>

namespace numeric
{
    template<typename Matrix, typename Type, typename Allocator>
    struct matrix_stream_operator
    {
        typedef Matrix                                                          zen_type;
        typedef std::allocator_traits<Allocator>                                allocator_trait_type;
        typedef typename allocator_trait_type::size_type                        size_type;
        typedef typename allocator_trait_type::value_type                       value_type;

        template< typename CharT, typename Traits >
        friend std::basic_ostream<CharT, Traits>& operator << ( std::basic_ostream<CharT, Traits>& os, zen_type const& rhs )
        {
            std::basic_ostringstream<CharT, Traits> os_stream;
            os_stream.flags(os.flags());
            os_stream.imbue(os.getloc());
            os_stream.precision(os.precision());

            for ( size_type i = 0; i < rhs.row(); ++i )
            {
                std::copy( rhs.row_cbegin( i ), rhs.row_cend( i ), std::ostream_iterator<value_type>( os_stream, " \t " ) );
                os_stream << "\n";
            }

            return os << os_stream.str();
        }

        template< typename CharT, typename Traits >
        friend std::basic_istream<CharT, Traits>& operator >> ( std::basic_istream<CharT, Traits>& is, zen_type& rhs )
        {
        
            if ( !is.good() )
            {
                is.setstate( std::ios::failbit );
                assert( !"numeric::matrix_stream_operator >> :: istream is not good." );
                return is;
            }

            std::vector<std::string> row_element;
            std::string string_line;

            while ( std::getline( is, string_line, '\n' ) )
                row_element.push_back( string_line );
            
            size_type const row = row_element.size(); 
            //error control here?????
            size_type const col = std::count_if( row_element[0].begin(), row_element[0].end(), []( char ch ) { return '\t' == ch; } );

            //error check
            if ( row == 0 || col == 0 )
            {
                assert( !"numeric::matrix_stream_operator >> :: row or col is zero." );

                is.setstate( std::ios::failbit );
                return is;
            }

            rhs.resize( row, col );

            for ( size_type r = 0; r != row; ++r )
            {
                std::istringstream the_row( row_element[r] );
                std::copy( std::istream_iterator<value_type>( the_row ), std::istream_iterator<value_type>(), rhs.row_begin(r) );
            }

            return is;
        }

    };//struct

}//namespace numeric

#endif//XFDS9UIHKJLAFDLKJHSAFKJX39UASLFDKJASDOFUIH4JKSFDKJBASFDJKAHSFLKJHSFDKJHF

