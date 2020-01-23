#ifndef VCHJNACHOIXDKXSXONEJMPWDPBXTSHXNDHVAFJAVVYVRSWQPYGNMVPRHYYMNURHRLYHSFVGXO
#define VCHJNACHOIXDKXSXONEJMPWDPBXTSHXNDHVAFJAVVYVRSWQPYGNMVPRHYYMNURHRLYHSFVGXO

#include <f/singleton/singleton.hpp>
#include <device/utility/cuda_assert.hpp>
#include <device/utility/cublas_assert.hpp>

#include <cuda_runtime.h>
#include <cublas_v2.h>
#include <curand.h>

#include <cassert>
#include <iostream>

void cm_eye( float2* v, unsigned long n );
void cm_eye( double2* v, unsigned long n );

namespace matrix_dsajhio4elkjsansafdioh4ekljansfdkljsanfdlkjnfd
{

    struct cublas_handle_initializer
    {
        cublasHandle_t handle;
        
        cublas_handle_initializer()
        {
            cublas_assert( cublasCreate(&handle) );
        }

        ~cublas_handle_initializer()
        {
            cublas_assert( cublasDestroy(handle) );
        }
    };

}

namespace f
{
    
    struct c_matrix
    {
        typedef float2                      value_type;
        typedef value_type*                 pointer;
        typedef unsigned long               size_type;
        typedef c_matrix                    self_type;

        c_matrix( size_type const row, size_type const col, void* host_data ) : row_(row), col_(col)
        {
            const size_type total_size = row * col * sizeof( value_type );
            cuda_assert( cudaMalloc( (void **)&data_, total_size ) );
            cuda_assert( cudaMemcpy( data_, host_data, total_size, cudaMemcpyHostToDevice ) );
        }

        c_matrix( size_type const row, size_type const col ) : row_(row), col_(col)
        {
            const size_type total_size = row * col * sizeof( value_type );
            cuda_assert( cudaMalloc( (void **)&data_, total_size ) );
            cuda_assert( cudaMemset( data_, 0, total_size ) );
        }

        c_matrix( const c_matrix& other ) : row_(other.row()), col_(other.col())
        {
            const size_type total_size = other.size() * sizeof( value_type );
            cuda_assert( cudaMalloc( (void **)&data_, total_size ) );
            cuda_assert( cudaMemcpy( data_, other.data_, total_size, cudaMemcpyDeviceToDevice ) );
        }

        self_type& operator = ( const c_matrix& other )
        {
            const size_type total_size = other.size() * sizeof( value_type );
            
            if ( size() != other.size() )
            {
                if( data_ )
                    cuda_assert( cudaFree( data_ ) );

                cuda_assert( cudaMalloc( (void **)&data_, total_size ) );
            }

            row_ = other.row_;
            col_ = other.col_;

            cuda_assert( cudaMemcpy( data_, other.data_, total_size, cudaMemcpyDeviceToDevice ) );

            return *this;
        }

        ~c_matrix()
        {
            row_ = 0;
            col_ = 0;
            cuda_assert( cudaFree( data_ ) );
            data_ = 0;
        }

        void transpose()
        {
            using matrix_dsajhio4elkjsansafdioh4ekljansfdkljsanfdlkjnfd::cublas_handle_initializer;
            cublas_handle_initializer& ci = singleton<cublas_handle_initializer>::instance();

            self_type clone( *this );
            value_type const alpha={ 1.0, 0.0 };
            value_type const beta={ 0.0, 0.0 }; 
            cublas_assert( cublasCgeam( ci.handle, CUBLAS_OP_T, CUBLAS_OP_N, row(), col(), &alpha, clone.data(), clone.col(), &beta, clone.data(), clone.row(), data(), row()  ) );

            row_ = clone.col();
            col_ = clone.row();
        }

        float norm() const
        {
            using matrix_dsajhio4elkjsansafdioh4ekljansfdkljsanfdlkjnfd::cublas_handle_initializer;
            //auto& ci = singleton<cublas_handle_initializer>::instance();
            cublas_handle_initializer& ci = singleton<cublas_handle_initializer>::instance();

            float result = 0;
            
            //cublas_assert( cublasScnrm2( ci.handle, size(), (const cuComplex*)data(), 1,  &result ) );
            cublas_assert( cublasScasum( ci.handle, size(), (const cuComplex*)data(), 1,  &result ) );

            return result;
        }

        float sim_norm_1() const
        {
            return norm() / col();
        }
        
        void export_to( void* host_data ) const
        {
            const size_type total_size = row() * col() * sizeof( value_type );
            cuda_assert( cudaMemcpy( host_data, data_, total_size, cudaMemcpyDeviceToHost ) );
        }
        
        size_type size() const
        {
            return row() * col();
        }

        friend self_type const operator + ( const self_type& lhs, const self_type& rhs )
        {
            assert( lhs.row() == rhs.row() );
            assert( lhs.col() == rhs.col() );

            using matrix_dsajhio4elkjsansafdioh4ekljansfdkljsanfdlkjnfd::cublas_handle_initializer;
            //auto& ci = singleton<cublas_handle_initializer>::instance();
            cublas_handle_initializer& ci = singleton<cublas_handle_initializer>::instance();

            self_type ans( lhs );
           
            value_type const alpha={ 1.0, 0.0 };
            cublas_assert( cublasCaxpy( ci.handle, ans.row()*ans.col(), &alpha, rhs.data(), 1, ans.data(), 1 ) ); // ans = lhs + rhs
            
            return ans;
        }

        friend self_type const operator - ( const self_type& lhs, const self_type& rhs )
        {
            assert( lhs.row() == rhs.row() );
            assert( lhs.col() == rhs.col() );

            using matrix_dsajhio4elkjsansafdioh4ekljansfdkljsanfdlkjnfd::cublas_handle_initializer;
            //auto& ci = singleton<cublas_handle_initializer>::instance();
            cublas_handle_initializer& ci = singleton<cublas_handle_initializer>::instance();

            self_type ans( lhs );
           
            value_type const alpha={ -1.0, 0.0 };
            cublas_assert( cublasCaxpy( ci.handle, lhs.row()*lhs.col(), &alpha, rhs.data(), 1, ans.data(), 1 ) ); // ans = lhs - rhs 
            
            return ans;
        }

        friend self_type const operator / ( const self_type& lhs, const float rhs )
        {
            return lhs * (1.0/rhs);
        }

        friend self_type const operator * ( const self_type& lhs, const float rhs )
        {
            using matrix_dsajhio4elkjsansafdioh4ekljansfdkljsanfdlkjnfd::cublas_handle_initializer;
            //auto& ci = singleton<cublas_handle_initializer>::instance();
            cublas_handle_initializer& ci = singleton<cublas_handle_initializer>::instance();

            self_type ans( lhs );
           
            value_type const alpha={ (float)(rhs-1.0), (float)0.0 };
            cublas_assert( cublasCaxpy( ci.handle, ans.row()*ans.col(), &alpha, ans.data(), 1, ans.data(), 1 ) ); //  ans = (alpha-1) ans + ans = alpha ans
            
            return ans;
        }

        friend self_type const operator * ( const float lhs, const self_type& rhs )
        {
            return rhs * lhs;
        }

        friend self_type const operator * ( const self_type& lhs, const self_type& rhs )
        {
            assert( lhs.col() == rhs.row() );

            using matrix_dsajhio4elkjsansafdioh4ekljansfdkljsanfdlkjnfd::cublas_handle_initializer;
            //auto& ci = singleton<cublas_handle_initializer>::instance();
            cublas_handle_initializer& ci = singleton<cublas_handle_initializer>::instance();

            self_type ans( lhs.row(), rhs.col() ); //ans = {0, ....., 0}

            const unsigned long m = lhs.row();
            const unsigned long k = lhs.col();
            const unsigned long n = rhs.col();
            value_type const alpha={ 1.0, 0.0 };
            value_type const beta={ 0.0, 0.0 };

            cublas_assert( cublasCgemm( ci.handle, CUBLAS_OP_N, CUBLAS_OP_N, n, m, k, &alpha, rhs.data(), n, lhs.data(), k, &beta, ans.data(), n ) );
            
            return ans;
        }

        void to_eye()
        {
            assert( row() == col() );
            cm_eye( data(), row() );
        }
         
        friend std::ostream& operator << ( std::ostream& lhs, const self_type& rhs )
        {
            const unsigned long total_size = rhs.row() * rhs.col() * sizeof(value_type);
            pointer data = new value_type[ rhs.row() * rhs.col() ];

            cuda_assert( cudaMemcpy( (void*)data, (const void*)rhs.data(), total_size, cudaMemcpyDeviceToHost ) );

            for ( unsigned long r = 0; r != rhs.row(); ++r )
            {
                for ( unsigned long c = 0; c != rhs.col(); ++c )
                {
                    lhs << "(" << data[r*rhs.col()+c].x << ", " << data[r*rhs.col()+c].y << ")\t";
                }

                lhs << "\n";
            }

            delete[] data;

            return lhs;
        }

        size_type row() const
        {
            return row_;
        }

        size_type col() const
        {
            return col_;
        }

        pointer data() const
        {
            return data_;
        }

        pointer data()
        {
            return data_;
        }

        size_type row_;
        size_type col_;
        pointer data_;

    };//struct c_matrix
    

    inline const c_matrix eye_c_matrix( unsigned long n )
    {
        c_matrix ans( n, n );
        cm_eye( ans.data(), n );
        return ans;
    }

    inline const c_matrix rand_c_matrix( unsigned long r, unsigned long c )
    {
        c_matrix ans( r, c );

        curandGenerator_t prng;   
        curandCreateGenerator(&prng, CURAND_RNG_PSEUDO_DEFAULT);
        curandSetPseudoRandomGeneratorSeed(prng, (unsigned long long) clock());
        curandGenerateUniform(prng, (float*)ans.data(), 2 * r * c);

        return ans;
    }

    struct z_matrix
    {
        typedef double2                     value_type;
        typedef value_type*                 pointer;
        typedef unsigned long               size_type;
        typedef z_matrix                    self_type;

        z_matrix( size_type const row, size_type const col, void* host_data ) : row_(row), col_(col)
        {
            const size_type total_size = row * col * sizeof( value_type );
            cuda_assert( cudaMalloc( (void **)&data_, total_size ) );
            cuda_assert( cudaMemcpy( data_, host_data, total_size, cudaMemcpyHostToDevice ) );
        }

        z_matrix( size_type const row, size_type const col ) : row_(row), col_(col)
        {
            const size_type total_size = row * col * sizeof( value_type );
            cuda_assert( cudaMalloc( (void **)&data_, total_size ) );
            cuda_assert( cudaMemset( data_, 0, total_size ) );
        }

        z_matrix( const z_matrix& other ) : row_(other.row()), col_(other.col())
        {
            const size_type total_size = other.size() * sizeof( value_type );
            cuda_assert( cudaMalloc( (void **)&data_, total_size ) );
            cuda_assert( cudaMemcpy( data_, other.data_, total_size, cudaMemcpyDeviceToDevice ) );
        }

        self_type& operator = ( const z_matrix& other )
        {
            const size_type total_size = other.size() * sizeof( value_type );
            
            if ( size() != other.size() )
            {
                if( data_ )
                    cuda_assert( cudaFree( data_ ) );

                cuda_assert( cudaMalloc( (void **)&data_, total_size ) );
            }

            row_ = other.row_;
            col_ = other.col_;

            cuda_assert( cudaMemcpy( data_, other.data_, total_size, cudaMemcpyDeviceToDevice ) );

            return *this;
        }

        ~z_matrix()
        {
            row_ = 0;
            col_ = 0;
            cuda_assert( cudaFree( data_ ) );
            data_ = 0;
        }

        void transpose()
        {
            using matrix_dsajhio4elkjsansafdioh4ekljansfdkljsanfdlkjnfd::cublas_handle_initializer;
            //auto& ci = singleton<cublas_handle_initializer>::instance();
            cublas_handle_initializer& ci = singleton<cublas_handle_initializer>::instance();

            self_type clone( *this );
            value_type const alpha={ 1.0, 0.0 };
            value_type const beta={ 0.0, 0.0 }; 
            cublas_assert( cublasZgeam( ci.handle, CUBLAS_OP_T, CUBLAS_OP_N, row(), col(), &alpha, clone.data(), clone.col(), &beta, clone.data(), clone.row(), data(), row()  ) );

            row_ = clone.col();
            col_ = clone.row();
        }

        double norm() const
        {
            using matrix_dsajhio4elkjsansafdioh4ekljansfdkljsanfdlkjnfd::cublas_handle_initializer;
            //auto& ci = singleton<cublas_handle_initializer>::instance();
            cublas_handle_initializer& ci = singleton<cublas_handle_initializer>::instance();

            double result = 0;
            
            //cublas_assert( cublasScnrm2( ci.handle, size(), (const cuDoubleComplex*)data(), 1,  &result ) );
            cublas_assert( cublasDzasum( ci.handle, size(), (const cuDoubleComplex*)data(), 1,  &result ) );

            return result;
        }

        double sim_norm_1() const
        {
            return norm() / col();
        }
        
        void export_to( void* host_data ) const
        {
            const size_type total_size = row() * col() * sizeof( value_type );
            cuda_assert( cudaMemcpy( host_data, data_, total_size, cudaMemcpyDeviceToHost ) );
        }
        
        size_type size() const
        {
            return row() * col();
        }

        friend self_type const operator + ( const self_type& lhs, const self_type& rhs )
        {
            assert( lhs.row() == rhs.row() );
            assert( lhs.col() == rhs.col() );

            using matrix_dsajhio4elkjsansafdioh4ekljansfdkljsanfdlkjnfd::cublas_handle_initializer;
            //auto& ci = singleton<cublas_handle_initializer>::instance();
            cublas_handle_initializer& ci = singleton<cublas_handle_initializer>::instance();

            self_type ans( lhs );
           
            value_type const alpha={ 1.0, 0.0 };
            cublas_assert( cublasZaxpy( ci.handle, ans.row()*ans.col(), &alpha, rhs.data(), 1, ans.data(), 1 ) ); // ans = lhs + rhs
            
            return ans;
        }

        friend self_type const operator - ( const self_type& lhs, const self_type& rhs )
        {
            assert( lhs.row() == rhs.row() );
            assert( lhs.col() == rhs.col() );

            using matrix_dsajhio4elkjsansafdioh4ekljansfdkljsanfdlkjnfd::cublas_handle_initializer;
            //auto& ci = singleton<cublas_handle_initializer>::instance();
            cublas_handle_initializer& ci = singleton<cublas_handle_initializer>::instance();

            self_type ans( lhs );
           
            value_type const alpha={ -1.0, 0.0 };
            cublas_assert( cublasZaxpy( ci.handle, lhs.row()*lhs.col(), &alpha, rhs.data(), 1, ans.data(), 1 ) ); // ans = lhs - rhs 
            
            return ans;
        }

        friend self_type const operator / ( const self_type& lhs, const double rhs )
        {
            return lhs * (1.0/rhs);
        }

        friend self_type const operator * ( const self_type& lhs, const double rhs )
        {
            using matrix_dsajhio4elkjsansafdioh4ekljansfdkljsanfdlkjnfd::cublas_handle_initializer;
            //auto& ci = singleton<cublas_handle_initializer>::instance();
            cublas_handle_initializer& ci = singleton<cublas_handle_initializer>::instance();

            self_type ans( lhs );
           
            value_type const alpha={ (double)(rhs-1.0), (double)0.0 };
            cublas_assert( cublasZaxpy( ci.handle, ans.row()*ans.col(), &alpha, ans.data(), 1, ans.data(), 1 ) ); //  ans = (alpha-1) ans + ans = alpha ans
            
            return ans;
        }

        friend self_type const operator * ( const double lhs, const self_type& rhs )
        {
            return rhs * lhs;
        }

        friend self_type const operator * ( const self_type& lhs, const self_type& rhs )
        {
            assert( lhs.col() == rhs.row() );

            using matrix_dsajhio4elkjsansafdioh4ekljansfdkljsanfdlkjnfd::cublas_handle_initializer;
            //auto& ci = singleton<cublas_handle_initializer>::instance();
            cublas_handle_initializer& ci = singleton<cublas_handle_initializer>::instance();

            self_type ans( lhs.row(), rhs.col() ); //ans = {0, ....., 0}

            const unsigned long m = lhs.row();
            const unsigned long k = lhs.col();
            const unsigned long n = rhs.col();
            value_type const alpha={ 1.0, 0.0 };
            value_type const beta={ 0.0, 0.0 };

            cublas_assert( cublasZgemm( ci.handle, CUBLAS_OP_N, CUBLAS_OP_N, n, m, k, &alpha, rhs.data(), n, lhs.data(), k, &beta, ans.data(), n ) );
            
            return ans;
        }

        void to_eye()
        {
            assert( row() == col() );
            cm_eye( data(), row() );
        }
         
        friend std::ostream& operator << ( std::ostream& lhs, const self_type& rhs )
        {
            const unsigned long total_size = rhs.row() * rhs.col() * sizeof(value_type);
            pointer data = new value_type[ rhs.row() * rhs.col() ];

            cuda_assert( cudaMemcpy( (void*)data, (const void*)rhs.data(), total_size, cudaMemcpyDeviceToHost ) );

            for ( unsigned long r = 0; r != rhs.row(); ++r )
            {
                for ( unsigned long c = 0; c != rhs.col(); ++c )
                {
                    lhs << "(" << data[r*rhs.col()+c].x << ", " << data[r*rhs.col()+c].y << ")\t";
                }

                lhs << "\n";
            }

            delete[] data;

            return lhs;
        }

        size_type row() const
        {
            return row_;
        }

        size_type col() const
        {
            return col_;
        }

        pointer data() const
        {
            return data_;
        }

        pointer data()
        {
            return data_;
        }

        size_type row_;
        size_type col_;
        pointer data_;

    };//struct z_matrix
    

    inline const z_matrix eye_z_matrix( unsigned long n )
    {
        z_matrix ans( n, n );
        cm_eye( ans.data(), n );
        return ans;
    }

}//namespace f
#endif//VCHJNACHOIXDKXSXONEJMPWDPBXTSHXNDHVAFJAVVYVRSWQPYGNMVPRHYYMNURHRLYHSFVGXO

