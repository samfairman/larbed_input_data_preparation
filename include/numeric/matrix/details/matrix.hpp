#ifndef PXRCCIQLRRPBKRVKCPCTSSONSHSOCKUYBDXGXRAMRXAYBCSJVIUUHILQWOEUJXKEYQBKPTRRS
#define PXRCCIQLRRPBKRVKCPCTSSONSHSOCKUYBDXGXRAMRXAYBCSJVIUUHILQWOEUJXKEYQBKPTRRS

#include <memory>

#include <numeric/matrix/details/method/bracket_operator.hpp>
#include <numeric/matrix/details/method/clear.hpp>
#include <numeric/matrix/details/method/col.hpp>
#include <numeric/matrix/details/method/col_iterator.hpp>
#include <numeric/matrix/details/method/copy.hpp>
#include <numeric/matrix/details/method/copy_n.hpp>
#include <numeric/matrix/details/method/data.hpp>
#include <numeric/matrix/details/method/diag_iterator.hpp>
#include <numeric/matrix/details/method/direct_iterator.hpp>
#include <numeric/matrix/details/method/fill.hpp>
#include <numeric/matrix/details/method/fill_n.hpp>
#include <numeric/matrix/details/method/minus_operator.hpp>
#include <numeric/matrix/details/method/operator_minus.hpp>
#include <numeric/matrix/details/method/operator_plus.hpp>
#include <numeric/matrix/details/method/plus_operator.hpp>
#include <numeric/matrix/details/method/resize.hpp>
#include <numeric/matrix/details/method/row.hpp>
#include <numeric/matrix/details/method/row_iterator.hpp>
#include <numeric/matrix/details/method/size.hpp>
#include <numeric/matrix/details/method/stream_operator.hpp>
#include <numeric/matrix/details/method/swap.hpp>
#include <numeric/matrix/details/method/load.hpp>
#include <numeric/matrix/details/method/save_as.hpp>

namespace numeric
{
    template< typename Type, typename Allocator = std::allocator<Type> >
    struct matrix :    
        public matrix_bracket_operator<matrix<Type, Allocator>, Type, Allocator>,
        public matrix_clear<matrix<Type, Allocator>, Type, Allocator>,
        public matrix_col<matrix<Type, Allocator>, Type, Allocator>,
        public matrix_col_iterator<matrix<Type, Allocator>, Type, Allocator>,
        public matrix_copy<matrix<Type, Allocator>, Type, Allocator>,
        public matrix_copy_n<matrix<Type, Allocator>, Type, Allocator>,
        public matrix_diag_iterator<matrix<Type, Allocator>, Type, Allocator>,
        public matrix_direct_iterator<matrix<Type, Allocator>, Type, Allocator>,
        public matrix_fill<matrix<Type, Allocator>, Type, Allocator>,
        public matrix_fill_n<matrix<Type, Allocator>, Type, Allocator>,
        public matrix_load<matrix<Type, Allocator>, Type, Allocator>,
        public matrix_minus_operator<matrix<Type, Allocator>, Type, Allocator>,
        public matrix_operator_minus<matrix<Type, Allocator>, Type, Allocator>,
        public matrix_operator_plus<matrix<Type, Allocator>, Type, Allocator>,
        public matrix_plus_operator<matrix<Type, Allocator>, Type, Allocator>,
        public matrix_resize<matrix<Type, Allocator>, Type, Allocator>,
        public matrix_row<matrix<Type, Allocator>, Type, Allocator>,
        public matrix_row_iterator<matrix<Type, Allocator>, Type, Allocator>,
        public matrix_save_as<matrix<Type, Allocator>, Type, Allocator>,
        public matrix_size<matrix<Type, Allocator>, Type, Allocator>,
        public matrix_stream_operator<matrix<Type, Allocator>, Type, Allocator>,
        public matrix_swap<matrix<Type, Allocator>, Type, Allocator>,
        public matrix_data<matrix<Type, Allocator>, Type, Allocator>
    {
        typedef matrix                                          self_type;
        typedef Type                                            value_type;
        typedef Allocator                                       allocator_type;
        typedef std::allocator_traits<Allocator>                allocator_trait_type;
        typedef typename allocator_trait_type::size_type        size_type;
        typedef typename allocator_trait_type::pointer          pointer_type;

        size_type                                               row_;
        size_type                                               col_;
        allocator_type                                          alloc_;     //custom allocators may contain state.
        pointer_type                                            data_; 

        matrix() : row_( 0 ), col_( 0 ), alloc_( allocator_type{} ), data_( nullptr ) {}

        matrix( size_type const row, size_type const col ) : row_( row ), col_( col ), alloc_( allocator_type{} )
        {
            data_ = allocator_trait_type::allocate( alloc_, row_*col_ );
        }

        matrix( size_type const row, size_type const col, allocator_type alloc ) : row_( row ), col_( col ), alloc_( alloc )
        {
            data_ = allocator_trait_type::allocate( alloc_, row_*col_ );
        }
        
        matrix( size_type const row, size_type const col, value_type const& val ) : row_( row ), col_( col ), alloc_( allocator_type{} )
        {
            data_ = allocator_trait_type::allocate( alloc_, row_*col_ );
            (*this).fill_n( row_*col_, val );

        }

        matrix( size_type const row, size_type const col, allocator_type alloc, value_type const& val ) : row_( row ), col_( col ), alloc_( alloc )
        {
            data_ = allocator_trait_type::allocate( alloc_, row_*col_ );
            (*this).fill_n( row_*col_, val );
        }

        matrix( matrix const& other ) : row_( other.row_ ), col_( other.col_ ), alloc_( other.alloc_ )
        {
            data_ = allocator_trait_type::allocate( alloc_, row_*col_ );
            (*this).copy( other.begin(), other.end() );
        }

        matrix( matrix && other ) : matrix()
        {
            (*this).swap( other );
        }

        self_type& operator = ( self_type const& other )
        {
            self_type tmp{ other };
            (*this).swap( tmp );

            return *this;
        }

        self_type& operator = ( self_type && other )
        {
            (*this).clear();
            (*this).swap( other );

            return *this;
        }

        ~matrix()
        {
            (*this).clear();
        }

    };//struct matrix

}//namespace numeric

#endif//PXRCCIQLRRPBKRVKCPCTSSONSHSOCKUYBDXGXRAMRXAYBCSJVIUUHILQWOEUJXKEYQBKPTRRS

