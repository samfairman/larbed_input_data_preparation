#ifndef KWKMUOMJSNFNFUJUUUXOCCRKVYPFPTMQWOWPWSAXSHTKOHXBDLIQVUYSAUOFRSJUTXSUFBVTR
#define KWKMUOMJSNFNFUJUUUXOCCRKVYPFPTMQWOWPWSAXSHTKOHXBDLIQVUYSAUOFRSJUTXSUFBVTR

#include <ostream>
#include <sstream>
#include <string>
#include <functional>
#include <type_traits>
#include <iostream>

namespace numeric
{

    template< typename Char, typename Trait = std::char_traits<Char> >
    struct test_base
    {
        typedef std::basic_ostream<Char, Trait> ostream_type;
        ostream_type&                           os_;            //ok
        std::basic_stringstream<Char, Trait>    bos_;           //ok
        unsigned long                           counter_;       //ok

        test_base( test_base const& other ) : os_(other.os_), counter_( other.counter_ )
        {
            bos_.flags( other.os_.flags() );
            bos_.imbue( other.os_.getloc() );
            bos_.precision( other.os_.precision() );

            bos_ << other.bos_.str();
        }

        test_base( ostream_type& os__ ) : os_( os__ ), counter_(0)
        {
            bos_.flags( os_.flags() );
            bos_.imbue( os_.getloc() );
            bos_.precision( os_.precision() );
        }
  
        template< typename Message >
        void register_message( Message const& msg ) //check operator << overloadedable
        {
            bos_ << msg << "\n";
        }
  
        template< typename Message >
        void register_case( Message const& msg ) //check operator << overloadedable
        {
            bos_ << ++counter_ << ":\t\t" << msg << "\n";
        }

        template< typename T >
        void operator()( T const& msg )
        {
            if ( !counter_ ) return;

            os_ << bos_.str() << "\n";
            os_ << "\t\t---- ";
            os_ << msg;
            os_ << counter_ << "\n\n";
            clear();
        }

        void operator()()
        {
            os_ << bos_.str() << "\n";
            clear();
        }

        void clear()
        {
            std::basic_stringstream<Char, Trait> other;
            bos_.swap(other);
            counter_ = 0;
        }

        unsigned long counter() const
        {
            return counter_;
        }

    };

    template< typename Char, typename Trait = std::char_traits<Char> >
    struct test
    {
        test_base<Char, Trait> success_test_;
        test_base<Char, Trait> failure_test_;

        std::string             test_name_;

        test( test const& ) = default;
        
        test( std::basic_ostream< Char, Trait > & os, std::string const& test_name = std::string{"default"} ) : success_test_( os ), failure_test_( os ) 
        {
            success_test_.register_message( std::string{"Details for Test --[["} + test_name + std::string{"]]--"} );
            failure_test_.register_message( std::string{"Details for Test --[["} + test_name + std::string{"]]--"} );
        }

        template< typename Function, typename Action > 
        void assert( std::string const& description_,  Function const& func_, Action const& act_ )
        {
            if ( func_() )
            {
                success_test_.register_case( description_ );
                act_(true);
            }
            else
            {
                failure_test_.register_case( description_ );
                act_(false);
            }
        }

        template< typename Function >
        void assert( std::string const& description_,  Function const& func_ )
        {
            assert( description_, func_, [](bool){});
        }

        template< typename Function >
        void assert( Function const& func_ )
        {
            assert( std::string{}, func_, [](bool){} );
        }

        void operator()()
        {
            success_test_("Success Cases: ");
            failure_test_("Failure Cases: ");
        }

        ~test()
        {
            (*this)();
        }

    };//struct test

    template< typename Char, typename Trait = std::char_traits<Char> >
    test<Char, Trait> make_test( std::basic_ostream< Char, Trait >& os_, std::string const& name_ = std::string{"default"} )
    {
        return test<Char, Trait>{os_, name_};
    }

    test< char, std::char_traits<char> > make_test()
    {
        return make_test(std::cout);
    }

}//namespace numeric

#endif//KWKMUOMJSNFNFUJUUUXOCCRKVYPFPTMQWOWPWSAXSHTKOHXBDLIQVUYSAUOFRSJUTXSUFBVTR

