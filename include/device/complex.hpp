#ifndef _COMPLEX_HPP_INCLUDED_SAFODINSLFDJH349UHAFS87Y4OIAUHF498YASFIUDH498Y7HFI
#define _COMPLEX_HPP_INCLUDED_SAFODINSLFDJH349UHAFS87Y4OIAUHF498YASFIUDH498Y7HFI

namespace device
{
    template<typename Type>
    struct complex
    {
        typedef Type        value_type;
        typedef complex     self_type;

        value_type real_;
        value_type imag_;

        __device__ __host__
        complex( const value_type& real = value_type(0) , const value_type& imag = value_type(0) ) : real_(real), imag_(imag) {}

        template<typename Typee> __device__ __host__
        complex( const Typee& real, const Typee& imag ) : real_(real), imag_(imag) {}

        __device__ __host__
        complex( const self_type& other ) : real_(other.real_), imag_(other.imag_) {}

        template<typename Typee> __device__ __host__
        complex( const complex<Typee>& other ) : real_(other.real_), imag_(other.imag_) {}

        __device__ __host__
        self_type& operator = ( const self_type& other )
        {
            real_ = other.real_;
            imag_ = other.imag_;
            return *this;
        }

        template<typename Typee> __device__ __host__
        self_type& operator = ( const complex<Typee>& other )
        {
            real_ = other.real_;
            imag_ = other.imag_;
            return *this;
        }

        __device__ __host__
        value_type& real() { return real_; }

        __device__ __host__
        value_type& imag() { return imag_; }

        __device__ __host__
        void real( const value_type& v ) { real_ = v; }

        __device__ __host__
        void imag( const value_type& v ) { imag_ = v; }

        __device__ __host__
        value_type real() const { return real_; }

        __device__ __host__
        value_type imag() const { return imag_; }

        __device__ __host__
        self_type& operator += ( const value_type& v )
        {
            real_ += v;
            return *this;
        }

        __device__ __host__
        const self_type operator + () const 
        {
            const self_type ans(real_, imag_);
            return ans;
        }

        __device__ __host__
        const self_type operator - () const 
        {
            const self_type ans(-real_, -imag_);
            return ans;
        }

        __device__ __host__
        self_type& operator += ( const self_type& other )
        {
            real_ += other.real_;
            imag_ += other.imag_;
            return *this;
        }

        __device__ __host__
        friend const self_type operator + ( const value_type& lhs, const self_type& rhs )
        {
            const self_type ans( lhs+rhs.real_, rhs.imag_ );
            return ans;
        }

        __device__ __host__
        friend const self_type operator + ( const self_type& lhs, const value_type& rhs )
        {
            return rhs + lhs;
        }

        __device__ __host__
        friend const self_type operator + ( const self_type& lhs, const self_type& rhs )
        {
            const self_type ans( lhs.real_+rhs.real_, lhs.imag_+rhs.imag_ );
            return ans;
        }

        __device__ __host__
        self_type& operator -= ( const value_type& v )
        {
            real_ -= v;
            return *this;
        }

        __device__ __host__
        self_type& operator -= ( const self_type& other )
        {
            real_ -= other.real_;
            imag_ -= other.imag_;
            return *this;
        }

        __device__ __host__
        friend const self_type operator - ( const value_type& lhs, const self_type& rhs )
        {
            const self_type ans( lhs-rhs.real_, -rhs.imag_ );
            return ans;
        }

        __device__ __host__
        friend const self_type operator - ( const self_type& lhs, const value_type& rhs )
        {
            const self_type ans( lhs.real_-rhs, lhs.imag_ );
            return ans;
        }

        __device__ __host__
        friend const self_type operator - ( const self_type& lhs, const self_type& rhs )
        {
            const self_type ans( lhs.real_-rhs.real_, lhs.imag_-rhs.imag_ );
            return ans;
        }

        __device__ __host__
        self_type& operator *= ( const value_type& v )
        {
            real_ *= v;
            imag_ *= v;
            return *this;
        }

        __device__ __host__
        self_type& operator *= ( const self_type& other )
        {
            const value_type& r = real_*other.real_ - imag_*other.imag_;
            const value_type& i = real_*other.imag_ + imag_*other.real_;
            real_ = r;
            imag_ = i;
            return *this;
        }

        __device__ __host__
        friend const self_type operator * ( const value_type& lhs, const self_type& rhs )
        {
            const self_type ans( lhs*rhs.real_, lhs*rhs.imag_ );
            return ans;
        }

        __device__ __host__
        friend const self_type operator * ( const self_type& lhs, const value_type& rhs )
        {
            const self_type ans( lhs.real_*rhs, lhs.imag_*rhs );
            return ans;
        }

        __device__ __host__
        friend const self_type operator * ( const self_type& lhs, const self_type& rhs )
        {
            //const self_type ans( lhs.real_*rhs.real_ - lhs.imag_*rhs.imag_, lhs.real_*rhs.imag_ + lhs.imag_*rhs.real_ );
            
            const value_type ac = lhs.real_ * rhs.real_;
            const value_type bd = lhs.imag_ * rhs.imag_;
            const value_type acbd = ( lhs.real_+lhs.imag_ ) * ( rhs.real_+rhs.imag_ );
            const self_type ans( ac-bd, acbd-ac-bd );

            return ans;
        }

        __device__ __host__
        self_type& operator /= ( const value_type& v )
        {
            real_ /= v;
            imag_ /= v;
            return *this;
        }

        __device__ __host__
        self_type& operator /= ( const self_type& other )
        {
            //needs optimization
            operator *= ( self_type( other.real_, -other.imag_ ) );
            operator /= ( value_type( other.real_*other.real_ + other.imag_*other.imag_ ) );
            return *this;
        }

        __device__ __host__
        friend const self_type operator / ( const self_type& lhs, const value_type& rhs )
        {
            self_type ans( lhs );
            ans /= rhs;
            return ans;
        }

        __device__ __host__
        friend const self_type operator / ( const self_type& lhs, const self_type& rhs  )
        {
            self_type ans( lhs );
            ans /= rhs;
            return ans;
        }

        __device__ __host__
        friend const self_type operator / ( const value_type& lhs, const self_type& rhs )
        {
            //needs optimization
            self_type ans( rhs.real_, -rhs.imag_ );
            ans *= lhs;
            ans /= rhs.real_*rhs.real_ + rhs.imag_*rhs.imag_;
            return ans;
        }

        __device__ __host__
        friend bool operator == ( const self_type& lhs, const self_type& rhs )
        {
            return lhs.real_ == rhs.real_ && lhs.imag_ == rhs.imag_;
        }

        __device__ __host__
        friend bool operator != ( const self_type& lhs, const self_type& rhs )
        {
            return lhs.real_ != rhs.real_ || lhs.imag_ != rhs.imag_;
        }

        __device__ __host__
        friend bool operator > ( const self_type& lhs, const self_type& rhs )
        {
            if ( lhs.real_ > rhs.real_ ) return true;
            if ( lhs.real_ < rhs.real_ ) return false;
            if ( lhs.imag_ > rhs.imag_ ) return true;
            return false;
        }

        __device__ __host__
        friend bool operator < ( const self_type& lhs, const self_type& rhs )
        {
            if ( lhs.real_ < rhs.real_ ) return true;
            if ( lhs.real_ > rhs.real_ ) return false;
            if ( lhs.imag_ < rhs.imag_ ) return true;
            return false;
        }

        __device__ __host__
        friend bool operator >= ( const self_type& lhs, const self_type& rhs )
        {
            return lhs > rhs || lhs == rhs;
        }

        __device__ __host__
        friend bool operator <= ( const self_type& lhs, const self_type& rhs )
        {
            return lhs < rhs || lhs == rhs;
        }

    };//struct complex

}//namespace device

#include <device/complex/complex_value_type.tcc>

#endif//_COMPLEX_HPP_INCLUDED_SAFODINSLFDJH349UHAFS87Y4OIAUHF498YASFIUDH498Y7HFI

