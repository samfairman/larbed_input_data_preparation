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
    ans += "        value_type operator()( const value_type x, const value_type y ) const\n";
    ans += "        {\n";
    //ans += "            return ::_fun_namef(x);\n";
    ans += "            return ::"; ans += _fun_name; ans += "f(x, y);\n";
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
    ans += "        value_type operator()( const value_type x, const value_type y ) const\n";
    ans += "        {\n";
    //ans += "            return ::_fun_name(x);\n";
    ans += "            return ::"; ans += _fun_name; ans += "(x, y);\n";
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
    ans += "        value_type operator()( const value_type x, const value_type y ) const\n";
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
    create_file( "hypot" );
    create_file( "atan2" );
    create_file( "pow" );
    create_file( "frexp" );
    create_file( "ldexp" );
    create_file( "scalbn" );
    create_file( "scalbln" );
    create_file( "fmod" );
    create_file( "reminder" );

    return 0;
}







