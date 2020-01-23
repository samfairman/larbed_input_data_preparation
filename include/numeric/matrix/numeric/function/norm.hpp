#ifndef CDILFXXWJCEPXVWEMOJPDDYYWCFHBPWWCIXVAJWYGJQQCPRQETIOOJJEBYMIWOYJVTYHSGMVJ
#define CDILFXXWJCEPXVWEMOJPDDYYWCFHBPWWCIXVAJWYGJQQCPRQETIOOJJEBYMIWOYJVTYHSGMVJ

#include <numeric/matrix/details/matrix.hpp>
#include <numeric/matrix/numeric/function/transpose.hpp>
#include <numeric/utility/simple_thread_pool/simple_thread_pool.hpp>

#include <thread>
#include <cmath>
#include <complex>
#include <numeric>
#include <cstddef>
#include <vector>
#include <iterator>
#include <algorithm>

namespace numeric
{

    namespace norm_private_spoinsaflkdj
    {
        template< typename Type >
        struct type_extractor
        {
            typedef Type    result_type;
        };

        template< typename Type >
        struct type_extractor< std::complex<Type> >
        {
            typedef Type    result_type;
        };

        struct abs_accumulator
        {
            template< typename Result_Type, typename Itor >
            void operator()( Itor begin, Itor end, Result_Type initial, Result_Type& ans ) const
            {
                typedef typename std::iterator_traits<Itor>::value_type value_type;
                for ( unsigned long loops = 0; loops != 100; ++loops )
                    ans = std::accumulate( begin, end, initial, []( Result_Type const& initial, value_type const& x ) { return initial + std::abs(x); } );
            }
        };

        template< typename Type, typename Allocator >
        typename type_extractor<Type>::result_type norm_inf_sequential( matrix<Type, Allocator> const& A )
        {
            typedef typename type_extractor<Type>::result_type result_type;

            if ( !A.size() )
                return result_type{0};

            std::vector<result_type> row_sum( A.row() );

            for ( std::size_t r = 0; r != A.row(); ++r )
                abs_accumulator{}( A.row_begin(r), A.row_end(r), result_type{0}, row_sum[r] );
            
            return *(std::max_element( row_sum.begin(), row_sum.end() ));
        }

    }//namespace norm_private_spoinsaflkdj   
    
    template< typename Type, typename Allocator >
    typename norm_private_spoinsaflkdj::type_extractor<Type>::result_type norm_inf( matrix<Type, Allocator> const& A )
    {
        using namespace norm_private_spoinsaflkdj;
        typedef typename type_extractor<Type>::result_type result_type;

#if 1
        return norm_private_spoinsaflkdj::norm_inf_sequential( A );
#endif
#if 0
        //small matrix
        /*
        if ( A.size() < 400 ) //need to test/generate this magic number
            return norm_private_spoinsaflkdj::norm_inf_sequential( A );

        //sequential
        const std::size_t max_thread = std::thread::hardware_concurrency();
        if ( 0 == max_thread )
            return norm_private_spoinsaflkdj::norm_inf_sequential( A );
        */
        //parallel
        std::vector<result_type> accumulator_array( A.row(), result_type{-1.289437239487} );
        {
            simple_thread_pool stp;
            for ( std::size_t r = 0; r != A.row(); ++r )
            {
                stp.submit_work( [&A, &accumulator_array, r](){ abs_accumulator{}( A.row_begin(r), A.row_end(r), result_type{0}, accumulator_array[r] ); } );
            }
        }
        /*
        std::cout << "\nthe array now is \n";
        std::copy( accumulator_array.begin(), accumulator_array.end(), std::ostream_iterator<result_type>( std::cout, "\t" ) );
        std::cout << "\n";
        */

        return *std::max_element( accumulator_array.begin(), accumulator_array.end() );
#endif
#if 0
        //small matrix
        if ( A.size() < 400 ) //need to test/generate this magic number
            return norm_private_spoinsaflkdj::norm_inf_sequential( A );

        //no concurrency
        const std::size_t max_thread = std::thread::hardware_concurrency();
        if ( 0 == max_thread )
            return norm_private_spoinsaflkdj::norm_inf_sequential( A );

        //concurrency 
        std::vector<result_type> accumulator_array( A.row() );

        auto const& bash_abs_accumulator = [&A, &accumulator_array](std::size_t row_first, std::size_t row_last)
        {
            if ( row_first >= row_last ) return;
            for ( std::size_t index = row_first; index != row_last; ++index )
                accumulator_array[index] = abs_accumulator{}( A.row_begin(index), A.row_end(index), result_type{0} );
        };

        std::size_t row_first = 0;
        std::size_t const row_stride = std::max( std::size_t{1}, std::size_t{A.row() / (max_thread+1)} );

        //-- new threads
        std::vector<std::thread> thread_array;
        for ( std::size_t index = 0; index != max_thread; ++index )
        {
            thread_array.push_back( std::thread{ std::bind( bash_abs_accumulator, row_first, row_first+row_stride ) } );
            row_first += row_stride;
            if ( row_first >= A.row() ) break;
        }

        //-- main thread
        bash_abs_accumulator( row_first, A.row() );

        for ( std::size_t index = 0; index != max_thread; ++index )
            thread_array[index].join();

        return *std::max_element( accumulator_array.begin(), accumulator_array.end() );
#endif
    }
    
    template< typename Type, typename Allocator >
    typename norm_private_spoinsaflkdj::type_extractor<Type>::result_type norm_1( matrix<Type, Allocator> const& A )
    {
        return norm_inf( transpose(A) );
    }
    
    template< typename Type, typename Allocator >
    typename norm_private_spoinsaflkdj::type_extractor<Type>::result_type norm( matrix<Type, Allocator> const& A )
    {
        return norm_1( A );
    }

    //TODO:
    //      specialization for cuda allocator based matrix

}//namespace numeric

#endif//CDILFXXWJCEPXVWEMOJPDDYYWCFHBPWWCIXVAJWYGJQQCPRQETIOOJJEBYMIWOYJVTYHSGMVJ

