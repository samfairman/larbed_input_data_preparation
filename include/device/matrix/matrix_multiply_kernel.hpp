#ifndef _MATRIX_MULTIPLY_KERNEL_HPP_INCLUDED_DSOPINASOH8943EUNOIALJSFDNASJHFIUHF
#define _MATRIX_MULTIPLY_KERNEL_HPP_INCLUDED_DSOPINASOH8943EUNOIALJSFDNASJHFIUHF

#include <device/config/threads_per_block.hpp>
#include <device/config/tile_width.hpp>
#include <device/iterator.hpp>
#include <device/typedef.hpp>
#include <device/math/ceil.hpp>
#include <device/complex.hpp>
#include <device/algorithm/for_each.hpp>
#include <device/vector.hpp>

#include <device/matrix/parasite_matrix.hpp>

//#include <device/numeric/static_inner_product.hpp>//for static_mm

namespace device
{

namespace mm_impl_sfdoinaslkfjnsdfijn4eoiunafkjn4eoinfakjdfaiuhfefdef4
{
#if 0
    //this method is slow
    template<typename OutputIterator, typename InputIterator1, typename InputIterator2, typename Distance>
    __global__ void static_mm( OutputIterator P, InputIterator1 M, InputIterator2 N, const Distance m_row, const Distance m_col, const Distance n_col )
    {
        typedef typename iterator_traits<OutputIterator>::value_type value_type;
        const size_t the_tile_width = tile_width::value;

        __shared__ value_type _M[the_tile_width][the_tile_width];
        __shared__ value_type _N[the_tile_width][the_tile_width];
        const size_t bx = blockIdx.x;
        const size_t by = blockIdx.y;
        const size_t tx = threadIdx.x;
        const size_t ty = threadIdx.y;
        const size_t row = by * the_tile_width + ty;
        const size_t col = bx * the_tile_width + tx;
        const size_t iter_n = (m_col+the_tile_width-1)/the_tile_width;

        value_type v(0);

        for ( size_t i = 0; i != iter_n; ++i )
        {
            if ( i * the_tile_width + tx < m_col && row < m_row )
                _M[ty][tx] = *( M + row * m_col + i * the_tile_width + tx );
            else
                _M[ty][tx] = value_type();
            /*
            if ( i * the_tile_width + ty < m_col && col < n_col )
                _N[ty][tx] = *( N + ( i * the_tile_width + ty ) * n_col + col );
            else
                _N[ty][tx] = value_type();
            */
            //transpose of original _N
            if ( i * the_tile_width + ty < m_col && col < n_col )
                _N[tx][ty] = *( N + ( i * the_tile_width + ty ) * n_col + col );
            else
                _N[tx][ty] = value_type();

            __syncthreads();
            
            /*
            #pragma unroll
            for ( size_t j = 0; j != the_tile_width; ++j )
                v += _M[ty][j] * _N[j][tx];
            */
            v += static_inner_product<tile_width::value>( &_M[0][0]+ty*the_tile_width, &_N[0][0]+tx*the_tile_width, value_type(0));

            __syncthreads();
        }

        if ( row < m_row && col < n_col )
            *( P + row * n_col + col ) = v;
    }
#endif

    template<typename OutputIterator, typename InputIterator1, typename InputIterator2, typename Distance>
    __global__ void parasite_mm( OutputIterator P, InputIterator1 M, InputIterator2 N, const Distance m_row, const Distance m_col, const Distance n_col )
    {
        typedef typename iterator_traits<OutputIterator>::value_type value_type;
        const size_t the_tile_width = tile_width::value;

        __shared__ value_type _M[the_tile_width][the_tile_width];
        __shared__ value_type _N[the_tile_width][the_tile_width];
        const size_t bx = blockIdx.x;
        const size_t by = blockIdx.y;
        const size_t tx = threadIdx.x;
        const size_t ty = threadIdx.y;
        const size_t row = by * the_tile_width + ty;
        const size_t col = bx * the_tile_width + tx;
        const size_t iter_n = (m_col+the_tile_width-1)/the_tile_width;
        
        parasite_matrix<value_type> PP( &(*P), m_row, n_col );
        const parasite_matrix<value_type const> MM( &(*M), m_row, m_col );
        const parasite_matrix<value_type const> NN( &(*N), m_col, n_col );

        value_type v(0);

        for ( size_t i = 0; i != iter_n; ++i )
        {
            const size_t offset = i * the_tile_width;
            _M[ty][tx] = MM( row, offset + tx );
            _N[ty][tx] = NN( offset + ty, col );

            __syncthreads();

            #pragma unroll
            for ( size_t j = 0; j != the_tile_width; ++j )
                v += _M[ty][j] * _N[j][tx];
            __syncthreads();
        }

        if ( row < m_row && col < n_col )
            PP( row, col ) = v;
    }

    template<typename OutputIterator, typename InputIterator1, typename InputIterator2, typename Distance>
    __global__ void mm( OutputIterator P, InputIterator1 M, InputIterator2 N, const Distance m_row, const Distance m_col, const Distance n_col )
    {
        typedef typename iterator_traits<OutputIterator>::value_type value_type;
        const size_t the_tile_width = tile_width::value;

        __shared__ value_type _M[the_tile_width][the_tile_width];
        __shared__ value_type _N[the_tile_width][the_tile_width];
        const size_t bx = blockIdx.x;
        const size_t by = blockIdx.y;
        const size_t tx = threadIdx.x;
        const size_t ty = threadIdx.y;
        const size_t row = by * the_tile_width + ty;
        const size_t col = bx * the_tile_width + tx;
        const size_t iter_n = (m_col+the_tile_width-1)/the_tile_width;

        value_type v(0);

        for ( size_t i = 0; i != iter_n; ++i )
        {
            if ( i * the_tile_width + tx < m_col && row < m_row )
                _M[ty][tx] = *( M + row * m_col + i * the_tile_width + tx );
            else
                _M[ty][tx] = value_type();

            if ( i * the_tile_width + ty < m_col && col < n_col )
                _N[ty][tx] = *( N + ( i * the_tile_width + ty ) * n_col + col );
            else
                _N[ty][tx] = value_type();

            __syncthreads();

            #pragma unroll
            for ( size_t j = 0; j != the_tile_width; ++j )
                v += _M[ty][j] * _N[j][tx];
            __syncthreads();
        }

        if ( row < m_row && col < n_col )
            *( P + row * n_col + col ) = v;
    }

    template<size_t Row_Scalar, size_t Col_Scalar, typename OutputIterator, typename InputIterator1, typename InputIterator2, typename Distance>
    __global__ void scalar_mm( OutputIterator P, InputIterator1 M, InputIterator2 N, const Distance m_row, const Distance m_col, const Distance n_col )
    {
        typedef typename iterator_traits<OutputIterator>::value_type value_type;
        const size_t the_tile_width = tile_width::value;

        __shared__ value_type _M[the_tile_width][the_tile_width];
        __shared__ value_type _N[the_tile_width][the_tile_width];
        const size_t bx = blockIdx.x;
        const size_t by = blockIdx.y;
        const size_t tx = threadIdx.x;
        const size_t ty = threadIdx.y;
        const size_t row = by * the_tile_width + ty;
        const size_t col = bx * the_tile_width + tx;
        const size_t iter_n = (m_col+the_tile_width-1)/the_tile_width;
        
        parasite_matrix<value_type> PP( &(*P), m_row, n_col );
        const parasite_matrix<value_type const> MM( &(*M), m_row, m_col );
        const parasite_matrix<value_type const> NN( &(*N), m_col, n_col );

        value_type v[Row_Scalar][Col_Scalar];

        for ( size_t i = 0; i != iter_n; ++i )
        {
            const size_t offset = i * the_tile_width;

            #pragma unroll
            for ( size_t r = 0; r != Row_Scalar; ++r )
            {
                #pragma unroll
                for ( size_t c = 0; c != Col_Scalar; ++c )
                {
                    _M[ty+r][tx+c] = MM( row+r, offset + tx+c );
                    _N[ty+r][tx+c] = NN( offset + ty+r, col+c );
                }
            }
            __syncthreads();

            #pragma unroll
            for ( size_t j = 0; j != the_tile_width; ++j )
            {
                v += _M[ty][j] * _N[j][tx];
            }

            __syncthreads();
        }
        
        #pragma unroll
        for ( size_t r = 0; r != Row_Scalar; ++r )
        {
            #pragma unroll
            for ( size_t c = 0; c != Col_Scalar; ++c )
            {
                if ( row < m_row && col < n_col )
                    PP( row, col ) = v;
            }
        }
    }

}//namespace mm_impl_sfdoinaslkfjnsdfijn4eoiunafkjn4eoinfakjdfaiuhfefdef4 


namespace mm_private
{
    struct complex_tag{};
    struct none_complex_tag{};

    template<typename T>
    struct extract_tag
    {
        typedef T value_type;
        typedef none_complex_tag result_type;
    };

    template<typename T>
    struct extract_tag<complex<T> >
    {
        typedef T value_type;
        typedef complex_tag result_type;
    };

    //calculate P = MN
    template<typename OutputIterator, typename InputIterator1, typename InputIterator2, typename Distance>
    void matrix_multiply_impl( OutputIterator P_begin, InputIterator1 M_begin, InputIterator2 N_begin, const Distance m_row, const Distance m_col, const Distance n_col, none_complex_tag )
    {
        const size_t the_tile_width = tile_width::value;
        const size_t dim_x = static_cast<size_t>( ceil<float>()(static_cast<float>(m_row)/the_tile_width) );
        const size_t dim_y = static_cast<size_t>( ceil<float>()(static_cast<float>(n_col)/the_tile_width) );
        const dim3 grid(dim_x, dim_y);
        const dim3 block(the_tile_width, the_tile_width);
        using namespace mm_impl_sfdoinaslkfjnsdfijn4eoiunafkjn4eoinfakjdfaiuhfefdef4;
        //mm<<<grid, block>>>( P_begin, M_begin, N_begin, m_row, m_col, n_col );
        parasite_mm<<<grid, block>>>( P_begin, M_begin, N_begin, m_row, m_col, n_col );
        //static_mm<<<grid, block>>>( P_begin, M_begin, N_begin, m_row, m_col, n_col ); //slow
    }

    struct extract_real
    {
        template<typename T>
        T const operator()( const complex<T>& c ) const 
        {
            return c.real();
        }
    };

    struct assign_real
    {
        template<typename T>
        void operator()( const T& v, complex<T>& c ) const 
        {
            return c.real(v);
        }
    };

    struct extract_imag
    {
        template<typename T>
        T const operator()( const complex<T>& c ) const 
        {
            return c.imag();
        }
    };

    struct assign_imag
    {
        template<typename T>
        void operator()( const T& v, complex<T>& c ) const 
        {
            return c.imag(v);
        }
    };

    template<typename T>
    struct extract
    {
        __host__ __device__
        void operator()( const complex<T>& c, T& r, T& i ) const 
        {
            r = c.real();
            i = c.imag(); 
        }
    };

    template<typename T>
    struct combine
    {
        __host__ __device__
        void operator()( complex<T>& c, const T& r, const T& i ) const
        {
            c.real(r);
            c.imag(i);
        }
    };

    // complex case
    // M = a+ib  [m_row][m_col]
    // N = c+id  [m_col][n_col]
    // P = MN = ac - bd + i ( (a+b)*(c+d) - ac - bd ) [m_row][n_col]
    template<typename OutputIterator, typename InputIterator1, typename InputIterator2, typename Distance>
    void matrix_multiply_impl( OutputIterator P_begin, InputIterator1 M_begin, InputIterator2 N_begin, const Distance m_row, const Distance m_col, const Distance n_col, complex_tag )
    {
        typedef typename iterator_traits<OutputIterator>::value_type value_type; //complex<something>
        typedef typename extract_tag<value_type>::value_type real_type; //can be double, float, int ...
        
        typedef vector<real_type> vector_type;
        const size_t M_size = m_row * m_col;
        const size_t N_size = m_col * n_col;
        const size_t P_size = m_row * n_col;

        //make array for a b 
        vector_type a( M_size );
        ////transform( M_begin, M_begin+M_size, a.begin(), extract_real() );
        vector_type b( M_size );
        ////transform( M_begin, M_begin+M_size, b.begin(), extract_imag() );
        for_each( M_begin, M_begin+M_size, a.begin(), b.begin(), extract<real_type>() );

        const vector_type& a_b = a + b;

        //make array for c and d
        vector_type c( N_size );
        ////transform( N_begin, N_begin+N_size, c.begin(), extract_real() );
        vector_type d( N_size );
        ////transform( N_begin, N_begin+N_size, d.begin(), extract_imag() );
        for_each( N_begin, N_begin+N_size, c.begin(), d.begin(), extract<real_type>() );

        const vector_type& c_d = c+d;

        //make array for ac, bd, a+b, c+d and (a+b)(c+d)
        vector_type ac( P_size ); // a*c
        matrix_multiply_impl( ac.begin(), a.begin(), c.begin(), m_row, m_col, n_col, none_complex_tag() );

        vector_type bd( P_size ); // b*d
        matrix_multiply_impl( bd.begin(), b.begin(), d.begin(), m_row, m_col, n_col, none_complex_tag() );

        vector_type abcd( P_size ); // (a+b)*(c+d)
        matrix_multiply_impl( abcd.begin(), a_b.begin(), c_d.begin(), m_row, m_col, n_col, none_complex_tag() );

        const vector_type& P_real = ac - bd; //calc ac-bd
        const vector_type& P_imag = abcd - ac - bd; // calc (a+b)(c+d)-ac-bd

        //combine real and imag part to P
        for_each( P_begin, P_begin+P_size, P_real.begin(), P_imag.begin(), combine<real_type>() );
    }


}//namespace mm_private

    template<typename OutputIterator, typename InputIterator1, typename InputIterator2, typename Distance>
    void matrix_multiply( OutputIterator P_begin, InputIterator1 M_begin, InputIterator2 N_begin, const Distance m_row, const Distance m_col, const Distance n_col )
    {
        typedef typename iterator_traits<OutputIterator>::value_type value_type;
        typedef typename mm_private::extract_tag<value_type>::result_type tag_type;
        mm_private::matrix_multiply_impl( P_begin, M_begin, N_begin, m_row, m_col, n_col, tag_type() );
    }

}//namespace device

#endif//_MATRIX_MULTIPLY_KERNEL_HPP_INCLUDED_DSOPINASOH8943EUNOIALJSFDNASJHFIUHF

