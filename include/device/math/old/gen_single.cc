#include <vg.hpp>
#include <iostream>
#include <string>
#include <algorithm>
#include <fstream>

using std::string;

string gen_macro()
{
    vg::variate_generator<char> vt( 'A', 'Z' );
    std::string macro;
    macro.resize(73);
    std::generate( macro.begin(), macro.end(), vt );
    return macro;
}

string gen_file( string _fun_name)
{
    string macro = gen_macro();
    string ans = "#ifndef " + macro + "\n";
    ans += "#define " + macro + "\n";
    ans += "\n";
    ans += "#include <device/complex.hpp>\n";
    ans += "\n";
    ans += "#include <math_functions.h>\n";
    ans += "\n";
    ans += "namespace device\n";;
    ans += "{\n";;
    ans += "    \n";
    //ans += "    template< typename Type > struct _fun_name;\n";
    ans += "    template< typename Type > struct "; ans += _fun_name; ans += ";\n";
    ans += "\n";
    //ans += "    template<> struct _fun_name<float>\n";
    ans += "    template<> struct "; ans +=_fun_name; ans += "<float>\n";
    ans += "    {\n";
    ans += "        typedef float value_type;\n";
    ans += "\n";
    ans += "        __device__ __host__\n";
    ans += "        value_type operator()( const value_type x ) const\n";
    ans += "        {\n";
    //ans += "            return ::_fun_namef(x);\n";
    ans += "            return ::"; ans += _fun_name; ans += "f(x);\n";
    ans += "        }\n";
    //ans += "    };//struct _fun_name<float>\n";
    ans += "    };//struct "; ans += _fun_name; ans += "<float>\n";
    ans += "\n";
    //ans += "    template<> struct _fun_name<double>\n";
    ans += "    template<> struct "; ans += _fun_name; ans += "<double>\n";
    ans += "    {\n";
    ans += "        typedef double value_type;\n";
    ans += "\n";
    ans += "        __device__ __host__\n";
    ans += "        value_type operator()( const value_type x ) const\n";
    ans += "        {\n";
    //ans += "            return ::_fun_name(x);\n";
    ans += "            return ::"; ans += _fun_name; ans += "(x);\n";
    ans += "        }\n";
    //ans += "    };//struct _fun_name<double>\n";
    ans += "    };//struct "; ans += _fun_name; ans += "<double>\n";
    ans += "\n";
    ans += "    template< typename Type >\n";
    //ans += "    struct _fun_name< device::complex<Type> >\n";
    ans += "    struct "; ans += _fun_name; ans += "< device::complex<Type> >\n";
    ans += "    {\n";
    ans += "        typedef device::complex<Type> value_type;\n";
    ans += "\n";
    ans += "        __device__ __host__\n";
    ans += "        value_type operator()( const value_type x ) const\n";
    ans += "        {\n";
    ans += "            //to be implemented\n";
    ans += "            return value_type(0,0);\n";
    ans += "        }\n";
    //ans += "    };//struct _fun_name<complex<...> >\n";
    ans += "    };//struct "; ans += _fun_name; ans += "<complex<...> >\n";
    ans += "\n";
    ans += "}//namespace device\n";
    ans += "\n";
    ans += "#endif//" + macro + "\n";
    return ans;
}

void create_file( string fun )
{
    string file_name = fun + ".hpp";
    std::ofstream ofs( file_name.c_str() );

    ofs << gen_file( fun );

    ofs.close();
}



int main( int argc , char** argv)
{
    create_file( "exp" );
    create_file( "exp2" );
    create_file( "exp10" );
    create_file( "expm1" );
    create_file( "log" );
    create_file( "log2" );
    create_file( "log10" );
    create_file( "log1p" );
    create_file( "sin" );
    create_file( "cos" );
    create_file( "tan" );
    create_file( "sinpi" );
    create_file( "cospi" );
    create_file( "asin" );
    create_file( "acos" );
    create_file( "atan" );
    create_file( "sinh" );
    create_file( "cosh" );
    create_file( "tanh" );
    create_file( "asinh" );
    create_file( "acosh" );
    create_file( "atanh" );
    create_file( "erf" );
    create_file( "erfc" );
    create_file( "erfinv" );
    create_file( "erfcinv" );
    create_file( "erfcx" );
    create_file( "normcdf" );
    create_file( "normcdfinv" );
    create_file( "lgamma" );
    create_file( "tgamma" );
    create_file( "logb" );
    create_file( "ilogb" );
    create_file( "j0" );
    create_file( "j1" );
    create_file( "jn" );
    create_file( "y0" );
    create_file( "y1" );
    create_file( "yn" );
    create_file( "trunc" );
    create_file( "round" );
    create_file( "rint" );
    create_file( "nearbyint" );
    create_file( "ceil" );
    create_file( "floor" );
    create_file( "lrint" );
    create_file( "llrint" );
    create_file( "llround" );

    return 0;
}







