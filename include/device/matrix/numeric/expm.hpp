#ifndef _DIAG_MAJOR_MATRIX_INVERSE_HPP_INCLUDED_FDPOSIJASDLK498HASFDLIUH498UHFSD
#define _DIAG_MAJOR_MATRIX_INVERSE_HPP_INCLUDED_FDPOSIJASDLK498HASFDLIUH498UHFSD

#include <device/math/ceil.hpp>
#include <device/math/log2.hpp>
#include <device/complex.hpp>
#include <device/matrix.hpp>
#include <device/matrix/functional/eye.hpp>
#include <device/matrix/numeric/norm.hpp>
#include <device/utility/assert.hpp>

#include <device/iostream.hpp>

namespace device
{
    namespace expm_misc_space_sd9ij4398yuasf89yasfdiouh498yfsdf9h4fdef
    {
        template< typename T >
        struct fix_complex_value_type
        {
            typedef T value_type;
        };

        template< typename T >
        struct fix_complex_value_type<device::complex<T> >
        {
            typedef T value_type;
        };

    }//namespace expm_misc_space_sd9ij4398yuasf89yasfdiouh498yfsdf9h4fdef 

    //this one is double precision
    template<typename T>
    const device::matrix<T> expm( const device::matrix<T>& A )
    {
        assert( A.row() == A.col() );
        typedef typename expm_misc_space_sd9ij4398yuasf89yasfdiouh498yfsdf9h4fdef::fix_complex_value_type<T>::value_type value_type;
        static const value_type theta[] = { 0.000000000000000e+000, //0
                                            3.650024139523051e-008, //1
                                            5.317232856892575e-004, //2
                                            1.495585217958292e-002, //3
                                            8.536352760102745e-002, //4
                                            2.539398330063230e-001, //5
                                            5.414660951208968e-001, //6
                                            9.504178996162932e-001, //7
                                            1.473163964234804e+000, //8
                                            2.097847961257068e+000, //9
                                            2.811644121620263e+000, //10
                                            3.602330066265032e+000, //11
                                            4.458935413036850e+000, //12
                                            5.371920351148152e+000  //13
                                          };
        value_type const norm_A         = col_norm( A );
        value_type const ratio          = theta[13] / norm_A;
        device::size_t const s          = ratio < value_type(1) ? 0 : static_cast<device::size_t>( device::ceil<value_type>()( device::log2<value_type>()( ratio ) ) );
        const value_type s__2           = s ? value_type(1 << s) : value_type(1);
        const device::matrix<T>& _A     = A / s__2;
        device::size_t const n          = _A.row();
        static value_type const c []    = { 0.000000000000000,  // 0
                                            //64764752532480000,  // 1
                                            6.4764752532480000e+16,  // 1
                                            //32382376266240000,  // 2
                                            3.2382376266240000e+16,  // 2
                                            //7771770303897600,   // 3
                                            7.771770303897600e+15,   // 3
                                            //1187353796428800,   // 4
                                            1.187353796428800e+15,   // 4
                                            //129060195264000,    // 5
                                            1.29060195264000e+14,    // 5
                                            //10559470521600,     // 6
                                            1.0559470521600e+13,     // 6
                                            //670442572800,       // 7
                                            6.70442572800e+11,       // 7
                                            //33522128640,        // 8
                                            3.3522128640e+10,        // 8
                                            //1323241920,         // 9
                                            1.323241920e+9,         // 9
                                            //40840800,           // 10
                                            4.0840800e+7,           // 10
                                            //960960,             // 11
                                            9.60960e+5,             // 11
                                            //16380,              // 12
                                            1.6380e+4,              // 12
                                            //182,                // 13
                                            1.82e+2,                // 13
                                            1                   // 14
                                        };
        const device::matrix<T>& _A2 = _A * _A;

        const device::matrix<T>& _A4 = _A2 * _A2;
        const device::matrix<T>& _A6 = _A2 * _A4;
        const device::matrix<T>& U = _A * ( _A6 * ( c[14] * _A6 + c[12] * _A4 + c[10] * _A2 ) + c[8] * _A6 + c[6] * _A4 + c[4] * _A2 + eye<T>( n, n, c[2] ) );
        const device::matrix<T>& V = _A6 * ( c[13] * _A6 + c[11] * _A4 + c[9] * _A2 ) + c[7] * _A6 + c[5] * _A4 + c[3] * _A2 + eye<T>( n, n, c[1] );
        //device::matrix<T> F = (V+U)/(V-U);
        device::matrix<T> F = (V-U).inverse()*(V+U);

        for ( device::size_t i = 0; i != s; ++i )
            F *= F;
        return F;
    }

}//namespace device

#endif//_DIAG_MAJOR_MATRIX_INVERSE_HPP_INCLUDED_FDPOSIJASDLK498HASFDLIUH498UHFSD

