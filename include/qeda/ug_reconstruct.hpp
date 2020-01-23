#ifndef _UG_RECONSTRUCT_HPP_INCLUDED_DSPOINJASLKDJ3U89SFDKJHASFKJ34I9UHFSD3UH89F
#define _UG_RECONSTRUCT_HPP_INCLUDED_DSPOINJASLKDJ3U89SFDKJHASFKJ34I9UHFSD3UH89F

#include <f/matrix/matrix.hpp>
#include <f/singleton/singleton.hpp>
#include <f/least_square_fit/nonlinear/levenberg_marquardt_solver.hpp>

#include <f/coefficient/expm.hpp>

#include <vector>
#include <complex>
#include <cstddef>
#include <iostream>
#include <algorithm>
#include <iterator>

namespace qeda
{
    
    template< typename T >
    struct pattern_model
    {
        typedef T                               value_type;
        typedef std::complex<value_type>        complex_type;
        typedef std::size_t                     size_type;
        typedef std::vector<value_type>         intensity_array_type;
        typedef f::matrix<size_type>            ug_marker_matrix_type;
        typedef f::matrix<complex_type>         complex_matrix_type;
        typedef std::vector<complex_type>       diag_array_type;

        intensity_array_type    intensity;
        ug_marker_matrix_type   ug_marker;
        diag_array_type         diag;
        complex_type            img_factor;
        complex_matrix_type           a;
        complex_matrix_type           s;
    };

    template< typename T >
    struct reconstruction_model
    {
        typedef T                               value_type;
        typedef std::complex<value_type>        complex_type;
        typedef std::vector<complex_type>       ug_array_type;
        typedef pattern_model<value_type>       pattern_type;
        typedef std::vector<pattern_type>       pattern_array_type;

        ug_array_type           ug;
        pattern_array_type      pattern;

    };//struct reconstruction_model 

    template< typename T >
    struct ug_reconstruct
    {
        typedef T                                       value_type;
        typedef ug_reconstruct<value_type>              self_type;
        typedef value_type*                             pointer;
        typedef std::vector<value_type>                 array_type;
        typedef std::complex<value_type>                complex_type;
        typedef complex_type*                           complex_pointer;
        typedef std::vector<complex_type>               complex_array_type;
        typedef std::size_t                             size_type;
        typedef reconstruction_model<value_type>        reconstruction_type;
        typedef pattern_model<value_type>               pattern_type;
        typedef f::matrix<complex_type>                 cmatrix_type;

        value_type pattern_residual( const complex_pointer ug, pattern_type& pattern, value_type thickness ) const
        {
            size_type const n = pattern.ug_marker.row();
            array_type I( n );
            calc_intensities( ug, pattern, thickness, I.begin() );

            //return the difference \sum {I-I'}^2
            auto const ans = std::inner_product( I.begin(), I.end(), pattern.intensity.begin(), value_type(0.0), [](value_type x, value_type y){return x+y;}, [](value_type x, value_type y) {return ( x-y ) * ( x-y );} );

            return ans;
        }

        template< typename Output_Iterator >
        void calc_intensities( const complex_pointer ug, pattern_type& pattern, value_type thickness,  Output_Iterator ot ) const
        {
            size_type const n = pattern.ug_marker.row();
            assert( n == pattern.ug_marker.col() );

            pattern.a.resize( n, n );
            pattern.s.resize( n, n );

            //construct A
            cmatrix_type& A = pattern.a;
            cmatrix_type& S = pattern.s;
            //cmatrix_type A( n, n );
            for ( size_type r = 0; r != n; ++r )
            {
                for ( size_type c = 0; c != n; ++c )
                {
                    size_type const offset_in_ug = pattern.ug_marker[r][c];
                    A[r][c] = ug[offset_in_ug];
                }
                A[r][r] = complex_type(0.0, 0.0);
            }
            std::copy( pattern.diag.begin(), pattern.diag.end(), A.diag_begin() );

            //S = f::expm( A, pattern.img_factor * thickness );
            S = f::expm( A, pattern.img_factor * thickness, 0 );
            //construct intensity
            std::transform( S.col_begin(0), S.col_end(0), ot, []( complex_type const& c ) { return std::norm(c); } );
        }





        void operator()( value_type const thickness ) const
        {
            lm_solver( thickness ); 
        }

        void homotopy_solver( value_type const thickness ) const
        {

                   
        
        
        }

        void lm_solver( value_type const thickness ) const
        {
            auto& rec = f::singleton<reconstruction_type>::instance();

            //alloc place for the fitted result
            size_type const ug_length = rec.ug.size();
            array_type fitted_ug( ug_length );

            //calc the real intensities
            size_type const pattern_number = rec.pattern.size();
            
            //for ( size_type i = 0; i != pattern_number; ++i )
            //    calc_intensities( rec.ug.data(), rec.pattern[i], thickness, rec.pattern[i].intensity.begin() );
            
            //dump the real intensities
            for ( size_type i = 0; i != pattern_number; ++i )
            {
                std::cerr << "\nthe intensities for pattern " << i << " is\n";
                std::copy( rec.pattern[i].intensity.begin(), rec.pattern[i].intensity.end(), std::ostream_iterator<value_type>(std::cerr, "\t") );
            }

            //auto const& merit_function = [thickness, rec]( const pointer ug ) -> value_type
            auto const& merit_function = [thickness]( const pointer ug ) -> value_type
            { 
                auto& rec = f::singleton<reconstruction_type>::instance();
                size_type const ug_length = rec.ug.size();

                //float point to complex, assuming the imag part are all 0
                complex_array_type Ug( ug_length );
                for ( size_type i = 0; i!= ug_length; ++i )
                    Ug[i] = complex_type( ug[i], 0.0 );

                //calc the total residual
                value_type residual = 0.0;
                size_type const pattern_number = rec.pattern.size();
                for ( size_type i = 0; i != pattern_number; ++i )
                    residual += self_type().pattern_residual( Ug.data(), rec.pattern[i], thickness );

                //no more than 0.1 for every entry in ug, 
                for ( size_type i = 0; i != ug_length; ++i )
                    if ( std::abs( ug[i] ) > value_type(0.1) ) 
                        residual += ug[i] * ug[i];

                return residual;
            };

            double residual = f::levenberg_marquardt_solver( merit_function, rec.ug.size(), fitted_ug.begin(), 0.01 );

            std::cout << "\nthe fitted ug is \n";
            std::copy( fitted_ug.begin(), fitted_ug.end(), std::ostream_iterator<value_type>( std::cout, "\t" ) );

            std::cout << "\n\nthe real ug is \n";
            std::copy( rec.ug.begin(), rec.ug.end(), std::ostream_iterator<complex_type>( std::cout, "\t" ) );
    
        } 
    };

    

    //for debug
    template< typename T >
    std::ostream& operator << ( std::ostream& os, pattern_model<T> const& rhs )
    {
        os << "\nintensity:\n";
        std::copy( rhs.intensity.begin(), rhs.intensity.end(), std::ostream_iterator<typename pattern_model<T>::value_type>( os, "\t" ) );
        os << "\ndiag:\n";
        std::copy( rhs.diag.begin(), rhs.diag.end(), std::ostream_iterator<typename pattern_model<T>::complex_type>( os, "\t" ) );
        os << "\nug_marker:\n" << rhs.ug_marker << "\n";
        os << "\nimg_factor:\n" << rhs.img_factor << "\n";
        return os;
    }

    template< typename T >
    std::ostream& operator << ( std::ostream& os, reconstruction_model<T> const& rhs )
    {
        std::cout << "\nug:\n";
        std::copy( rhs.ug.begin(), rhs.ug.end(), std::ostream_iterator<typename reconstruction_model<T>::complex_type>( os, "\t" ) );
        std::cout << "\npattern:\n";
        std::copy( rhs.pattern.begin(), rhs.pattern.end(), std::ostream_iterator<typename reconstruction_model<T>::pattern_type>( os, "\t" ) );
        for ( auto& pt : rhs.pattern )
            os << pt << "\n";

        return os;
    }

}//namespace qeda

#endif//_UG_RECONSTRUCT_HPP_INCLUDED_DSPOINJASLKDJ3U89SFDKJHASFKJ34I9UHFSD3UH89F

