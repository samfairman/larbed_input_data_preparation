#ifndef _LIMITS_HPP_INCLUDED_SDPOJINASFLKJN49UHASFDKLJNASFDLJKN49UH8AFDLNJHSAFDF
#define _LIMITS_HPP_INCLUDED_SDPOJINASFLKJN49UHASFDKLJNASFDLJKN49UH8AFDLNJHSAFDF

namespace device
{
    enum float_round_style
    {
        round_indeterminate = -1,
        round_toward_zero = 0,
        round_to_nearest = 1,
        round_toward_infinity = 2,
        round_toward_neg_infinity = 3
    };
    enum float_denorm_style
    {
        denorm_indeterminate = -1,
        denorm_absent = 0,
        denorm_present = 1
    };
    struct __numeric_limits_base
    {
        static const bool is_specialized = false;
        static const int digits = 0;
        static const int digits10 = 0;
        static const bool is_signed = false;
        static const bool is_integer = false;
        static const bool is_exact = false;
        static const int radix = 0;
        static const int min_exponent = 0;
        static const int min_exponent10 = 0;
        static const int max_exponent = 0;
        static const int max_exponent10 = 0;
        static const bool has_infinity = false;
        static const bool has_quiet_NaN = false;
        static const bool has_signaling_NaN = false;
        static const float_denorm_style has_denorm = denorm_absent;
        static const bool has_denorm_loss = false;
        static const bool is_iec559 = false;
        static const bool is_bounded = false;
        static const bool is_modulo = false;
        static const bool traps = false;
        static const bool tinyness_before = false;
        static const float_round_style round_style =
            round_toward_zero;
    };
    template<typename _Tp>
    struct numeric_limits : public __numeric_limits_base
    {
        static _Tp min() { return static_cast<_Tp>( 0 ); }
        static _Tp max() { return static_cast<_Tp>( 0 ); }
        static _Tp epsilon() { return static_cast<_Tp>( 0 ); }
        static _Tp round_error() { return static_cast<_Tp>( 0 ); }
        static _Tp infinity() { return static_cast<_Tp>( 0 ); }
        static _Tp quiet_NaN() { return static_cast<_Tp>( 0 ); }
        static _Tp signaling_NaN() { return static_cast<_Tp>( 0 ); }
        static _Tp denorm_min() { return static_cast<_Tp>( 0 ); }
    };
    template<>
    struct numeric_limits<bool>
    {
        static const bool is_specialized = true;
        static bool min() { return false; }
        static bool max() { return true; }
        static const int digits = 1;
        static const int digits10 = 0;
        static const bool is_signed = false;
        static const bool is_integer = true;
        static const bool is_exact = true;
        static const int radix = 2;
        static bool epsilon() { return false; }
        static bool round_error() { return false; }
        static const int min_exponent = 0;
        static const int min_exponent10 = 0;
        static const int max_exponent = 0;
        static const int max_exponent10 = 0;
        static const bool has_infinity = false;
        static const bool has_quiet_NaN = false;
        static const bool has_signaling_NaN = false;
        static const float_denorm_style has_denorm = denorm_absent;
        static const bool has_denorm_loss = false;
        static bool infinity() { return false; }
        static bool quiet_NaN() { return false; }
        static bool signaling_NaN() { return false; }
        static bool denorm_min() { return false; }
        static const bool is_iec559 = false;
        static const bool is_bounded = true;
        static const bool is_modulo = false;
        static const bool traps = true;
        static const bool tinyness_before = false;
        static const float_round_style round_style = round_toward_zero;
    };
    template<>
    struct numeric_limits<char>
    {
        static const bool is_specialized = true;
        static char min() { return ( ( ( char )( -1 ) < 0 ) ? -( ( ( char )( -1 ) < 0 ) ? ( ( ( ( ( char )1 << ( ( sizeof( char ) * 8 - ( ( char )( -1 ) < 0 ) ) - 1 ) ) - 1 ) << 1 ) + 1 ) : ~( char )0 ) - 1 : ( char )0 ); }
        static char max() { return ( ( ( char )( -1 ) < 0 ) ? ( ( ( ( ( char )1 << ( ( sizeof( char ) * 8 - ( ( char )( -1 ) < 0 ) ) - 1 ) ) - 1 ) << 1 ) + 1 ) : ~( char )0 ); }
        static const int digits = ( sizeof( char ) * 8 - ( ( char )( -1 ) < 0 ) );
        static const int digits10 = ( ( sizeof( char ) * 8 - ( ( char )( -1 ) < 0 ) ) * 643L / 2136 );
        static const bool is_signed = ( ( char )( -1 ) < 0 );
        static const bool is_integer = true;
        static const bool is_exact = true;
        static const int radix = 2;
        static char epsilon() { return 0; }
        static char round_error() { return 0; }
        static const int min_exponent = 0;
        static const int min_exponent10 = 0;
        static const int max_exponent = 0;
        static const int max_exponent10 = 0;
        static const bool has_infinity = false;
        static const bool has_quiet_NaN = false;
        static const bool has_signaling_NaN = false;
        static const float_denorm_style has_denorm = denorm_absent;
        static const bool has_denorm_loss = false;
        static char infinity() { return char(); }
        static char quiet_NaN() { return char(); }
        static char signaling_NaN() { return char(); }
        static char denorm_min() { return static_cast<char>( 0 ); }
        static const bool is_iec559 = false;
        static const bool is_bounded = true;
        static const bool is_modulo = true;
        static const bool traps = true;
        static const bool tinyness_before = false;
        static const float_round_style round_style = round_toward_zero;
    };
    template<>
    struct numeric_limits<signed char>
    {
        static const bool is_specialized = true;
        static signed char min() { return -127 - 1; }
        static signed char max() { return 127; }
        static const int digits = ( sizeof( signed char ) * 8 - ( ( signed char )( -1 ) < 0 ) );
        static const int digits10 = ( ( sizeof( signed char ) * 8 - ( ( signed char )( -1 ) < 0 ) ) * 643L / 2136 );
        static const bool is_signed = true;
        static const bool is_integer = true;
        static const bool is_exact = true;
        static const int radix = 2;
        static signed char epsilon() { return 0; }
        static signed char round_error() { return 0; }
        static const int min_exponent = 0;
        static const int min_exponent10 = 0;
        static const int max_exponent = 0;
        static const int max_exponent10 = 0;
        static const bool has_infinity = false;
        static const bool has_quiet_NaN = false;
        static const bool has_signaling_NaN = false;
        static const float_denorm_style has_denorm = denorm_absent;
        static const bool has_denorm_loss = false;
        static signed char infinity() { return static_cast<signed char>( 0 ); }
        static signed char quiet_NaN() { return static_cast<signed char>( 0 ); }
        static signed char signaling_NaN() { return static_cast<signed char>( 0 ); }
        static signed char denorm_min() { return static_cast<signed char>( 0 ); }
        static const bool is_iec559 = false;
        static const bool is_bounded = true;
        static const bool is_modulo = true;
        static const bool traps = true;
        static const bool tinyness_before = false;
        static const float_round_style round_style = round_toward_zero;
    };
    template<>
    struct numeric_limits<unsigned char>
    {
        static const bool is_specialized = true;
        static unsigned char min() { return 0; }
        static unsigned char max() { return 127 * 2U + 1; }
        static const int digits = ( sizeof( unsigned char ) * 8 - ( ( unsigned char )( -1 ) < 0 ) );
        static const int digits10 = ( ( sizeof( unsigned char ) * 8 - ( ( unsigned char )( -1 ) < 0 ) ) * 643L / 2136 );
        static const bool is_signed = false;
        static const bool is_integer = true;
        static const bool is_exact = true;
        static const int radix = 2;
        static unsigned char epsilon() { return 0; }
        static unsigned char round_error() { return 0; }
        static const int min_exponent = 0;
        static const int min_exponent10 = 0;
        static const int max_exponent = 0;
        static const int max_exponent10 = 0;
        static const bool has_infinity = false;
        static const bool has_quiet_NaN = false;
        static const bool has_signaling_NaN = false;
        static const float_denorm_style has_denorm = denorm_absent;
        static const bool has_denorm_loss = false;
        static unsigned char infinity() { return static_cast<unsigned char>( 0 ); }
        static unsigned char quiet_NaN() { return static_cast<unsigned char>( 0 ); }
        static unsigned char signaling_NaN() { return static_cast<unsigned char>( 0 ); }
        static unsigned char denorm_min() { return static_cast<unsigned char>( 0 ); }
        static const bool is_iec559 = false;
        static const bool is_bounded = true;
        static const bool is_modulo = true;
        static const bool traps = true;
        static const bool tinyness_before = false;
        static const float_round_style round_style = round_toward_zero;
    };
    template<>
    struct numeric_limits<wchar_t>
    {
        static const bool is_specialized = true;
        static wchar_t min() { return ( ( ( wchar_t )( -1 ) < 0 ) ? -( ( ( wchar_t )( -1 ) < 0 ) ? ( ( ( ( ( wchar_t )1 << ( ( sizeof( wchar_t ) * 8 - ( ( wchar_t )( -1 ) < 0 ) ) - 1 ) ) - 1 ) << 1 ) + 1 ) : ~( wchar_t )0 ) - 1 : ( wchar_t )0 ); }
        static wchar_t max() { return ( ( ( wchar_t )( -1 ) < 0 ) ? ( ( ( ( ( wchar_t )1 << ( ( sizeof( wchar_t ) * 8 - ( ( wchar_t )( -1 ) < 0 ) ) - 1 ) ) - 1 ) << 1 ) + 1 ) : ~( wchar_t )0 ); }
        static const int digits = ( sizeof( wchar_t ) * 8 - ( ( wchar_t )( -1 ) < 0 ) );
        static const int digits10 = ( ( sizeof( wchar_t ) * 8 - ( ( wchar_t )( -1 ) < 0 ) ) * 643L / 2136 );
        static const bool is_signed = ( ( wchar_t )( -1 ) < 0 );
        static const bool is_integer = true;
        static const bool is_exact = true;
        static const int radix = 2;
        static wchar_t epsilon() { return 0; }
        static wchar_t round_error() { return 0; }
        static const int min_exponent = 0;
        static const int min_exponent10 = 0;
        static const int max_exponent = 0;
        static const int max_exponent10 = 0;
        static const bool has_infinity = false;
        static const bool has_quiet_NaN = false;
        static const bool has_signaling_NaN = false;
        static const float_denorm_style has_denorm = denorm_absent;
        static const bool has_denorm_loss = false;
        static wchar_t infinity() { return wchar_t(); }
        static wchar_t quiet_NaN() { return wchar_t(); }
        static wchar_t signaling_NaN() { return wchar_t(); }
        static wchar_t denorm_min() { return wchar_t(); }
        static const bool is_iec559 = false;
        static const bool is_bounded = true;
        static const bool is_modulo = true;
        static const bool traps = true;
        static const bool tinyness_before = false;
        static const float_round_style round_style = round_toward_zero;
    };
    template<>
    struct numeric_limits<short>
    {
        static const bool is_specialized = true;
        static short min() { return -32767 - 1; }
        static short max() { return 32767; }
        static const int digits = ( sizeof( short ) * 8 - ( ( short )( -1 ) < 0 ) );
        static const int digits10 = ( ( sizeof( short ) * 8 - ( ( short )( -1 ) < 0 ) ) * 643L / 2136 );
        static const bool is_signed = true;
        static const bool is_integer = true;
        static const bool is_exact = true;
        static const int radix = 2;
        static short epsilon() { return 0; }
        static short round_error() { return 0; }
        static const int min_exponent = 0;
        static const int min_exponent10 = 0;
        static const int max_exponent = 0;
        static const int max_exponent10 = 0;
        static const bool has_infinity = false;
        static const bool has_quiet_NaN = false;
        static const bool has_signaling_NaN = false;
        static const float_denorm_style has_denorm = denorm_absent;
        static const bool has_denorm_loss = false;
        static short infinity() { return short(); }
        static short quiet_NaN() { return short(); }
        static short signaling_NaN() { return short(); }
        static short denorm_min() { return short(); }
        static const bool is_iec559 = false;
        static const bool is_bounded = true;
        static const bool is_modulo = true;
        static const bool traps = true;
        static const bool tinyness_before = false;
        static const float_round_style round_style = round_toward_zero;
    };
    template<>
    struct numeric_limits<unsigned short>
    {
        static const bool is_specialized = true;
        static unsigned short min() { return 0; }
        static unsigned short max() { return 32767 * 2U + 1; }
        static const int digits = ( sizeof( unsigned short ) * 8 - ( ( unsigned short )( -1 ) < 0 ) );
        static const int digits10 = ( ( sizeof( unsigned short ) * 8 - ( ( unsigned short )( -1 ) < 0 ) ) * 643L / 2136 );
        static const bool is_signed = false;
        static const bool is_integer = true;
        static const bool is_exact = true;
        static const int radix = 2;
        static unsigned short epsilon() { return 0; }
        static unsigned short round_error() { return 0; }
        static const int min_exponent = 0;
        static const int min_exponent10 = 0;
        static const int max_exponent = 0;
        static const int max_exponent10 = 0;
        static const bool has_infinity = false;
        static const bool has_quiet_NaN = false;
        static const bool has_signaling_NaN = false;
        static const float_denorm_style has_denorm = denorm_absent;
        static const bool has_denorm_loss = false;
        static unsigned short infinity() { return static_cast<unsigned short>( 0 ); }
        static unsigned short quiet_NaN() { return static_cast<unsigned short>( 0 ); }
        static unsigned short signaling_NaN() { return static_cast<unsigned short>( 0 ); }
        static unsigned short denorm_min() { return static_cast<unsigned short>( 0 ); }
        static const bool is_iec559 = false;
        static const bool is_bounded = true;
        static const bool is_modulo = true;
        static const bool traps = true;
        static const bool tinyness_before = false;
        static const float_round_style round_style = round_toward_zero;
    };
    template<>
    struct numeric_limits<int>
    {
        static const bool is_specialized = true;
        static int min() { return -2147483647 - 1; }
        static int max() { return 2147483647; }
        static const int digits = ( sizeof( int ) * 8 - ( ( int )( -1 ) < 0 ) );
        static const int digits10 = ( ( sizeof( int ) * 8 - ( ( int )( -1 ) < 0 ) ) * 643L / 2136 );
        static const bool is_signed = true;
        static const bool is_integer = true;
        static const bool is_exact = true;
        static const int radix = 2;
        static int epsilon() { return 0; }
        static int round_error() { return 0; }
        static const int min_exponent = 0;
        static const int min_exponent10 = 0;
        static const int max_exponent = 0;
        static const int max_exponent10 = 0;
        static const bool has_infinity = false;
        static const bool has_quiet_NaN = false;
        static const bool has_signaling_NaN = false;
        static const float_denorm_style has_denorm = denorm_absent;
        static const bool has_denorm_loss = false;
        static int infinity() { return static_cast<int>( 0 ); }
        static int quiet_NaN() { return static_cast<int>( 0 ); }
        static int signaling_NaN() { return static_cast<int>( 0 ); }
        static int denorm_min() { return static_cast<int>( 0 ); }
        static const bool is_iec559 = false;
        static const bool is_bounded = true;
        static const bool is_modulo = true;
        static const bool traps = true;
        static const bool tinyness_before = false;
        static const float_round_style round_style = round_toward_zero;
    };
    template<>
    struct numeric_limits<unsigned int>
    {
        static const bool is_specialized = true;
        static unsigned int min() { return 0; }
        static unsigned int max() { return 2147483647 * 2U + 1; }
        static const int digits = ( sizeof( unsigned int ) * 8 - ( ( unsigned int )( -1 ) < 0 ) );
        static const int digits10 = ( ( sizeof( unsigned int ) * 8 - ( ( unsigned int )( -1 ) < 0 ) ) * 643L / 2136 );
        static const bool is_signed = false;
        static const bool is_integer = true;
        static const bool is_exact = true;
        static const int radix = 2;
        static unsigned int epsilon() { return 0; }
        static unsigned int round_error() { return 0; }
        static const int min_exponent = 0;
        static const int min_exponent10 = 0;
        static const int max_exponent = 0;
        static const int max_exponent10 = 0;
        static const bool has_infinity = false;
        static const bool has_quiet_NaN = false;
        static const bool has_signaling_NaN = false;
        static const float_denorm_style has_denorm = denorm_absent;
        static const bool has_denorm_loss = false;
        static unsigned int infinity() { return static_cast<unsigned int>( 0 ); }
        static unsigned int quiet_NaN() { return static_cast<unsigned int>( 0 ); }
        static unsigned int signaling_NaN() { return static_cast<unsigned int>( 0 ); }
        static unsigned int denorm_min() { return static_cast<unsigned int>( 0 ); }
        static const bool is_iec559 = false;
        static const bool is_bounded = true;
        static const bool is_modulo = true;
        static const bool traps = true;
        static const bool tinyness_before = false;
        static const float_round_style round_style = round_toward_zero;
    };
    template<>
    struct numeric_limits<long>
    {
        static const bool is_specialized = true;
        static long min() { return -9223372036854775807L - 1; }
        static long max() { return 9223372036854775807L; }
        static const int digits = ( sizeof( long ) * 8 - ( ( long )( -1 ) < 0 ) );
        static const int digits10 = ( ( sizeof( long ) * 8 - ( ( long )( -1 ) < 0 ) ) * 643L / 2136 );
        static const bool is_signed = true;
        static const bool is_integer = true;
        static const bool is_exact = true;
        static const int radix = 2;
        static long epsilon() { return 0; }
        static long round_error() { return 0; }
        static const int min_exponent = 0;
        static const int min_exponent10 = 0;
        static const int max_exponent = 0;
        static const int max_exponent10 = 0;
        static const bool has_infinity = false;
        static const bool has_quiet_NaN = false;
        static const bool has_signaling_NaN = false;
        static const float_denorm_style has_denorm = denorm_absent;
        static const bool has_denorm_loss = false;
        static long infinity() { return static_cast<long>( 0 ); }
        static long quiet_NaN() { return static_cast<long>( 0 ); }
        static long signaling_NaN() { return static_cast<long>( 0 ); }
        static long denorm_min() { return static_cast<long>( 0 ); }
        static const bool is_iec559 = false;
        static const bool is_bounded = true;
        static const bool is_modulo = true;
        static const bool traps = true;
        static const bool tinyness_before = false;
        static const float_round_style round_style = round_toward_zero;
    };
    template<>
    struct numeric_limits<unsigned long>
    {
        static const bool is_specialized = true;
        static unsigned long min() { return 0; }
        static unsigned long max() { return 9223372036854775807L * 2UL + 1; }
        static const int digits = ( sizeof( unsigned long ) * 8 - ( ( unsigned long )( -1 ) < 0 ) );
        static const int digits10 = ( ( sizeof( unsigned long ) * 8 - ( ( unsigned long )( -1 ) < 0 ) ) * 643L / 2136 );
        static const bool is_signed = false;
        static const bool is_integer = true;
        static const bool is_exact = true;
        static const int radix = 2;
        static unsigned long epsilon() { return 0; }
        static unsigned long round_error() { return 0; }
        static const int min_exponent = 0;
        static const int min_exponent10 = 0;
        static const int max_exponent = 0;
        static const int max_exponent10 = 0;
        static const bool has_infinity = false;
        static const bool has_quiet_NaN = false;
        static const bool has_signaling_NaN = false;
        static const float_denorm_style has_denorm = denorm_absent;
        static const bool has_denorm_loss = false;
        static unsigned long infinity() { return static_cast<unsigned long>( 0 ); }
        static unsigned long quiet_NaN() { return static_cast<unsigned long>( 0 ); }
        static unsigned long signaling_NaN() { return static_cast<unsigned long>( 0 ); }
        static unsigned long denorm_min() { return static_cast<unsigned long>( 0 ); }
        static const bool is_iec559 = false;
        static const bool is_bounded = true;
        static const bool is_modulo = true;
        static const bool traps = true;
        static const bool tinyness_before = false;
        static const float_round_style round_style = round_toward_zero;
    };
    template<>
    struct numeric_limits<long long>
    {
        static const bool is_specialized = true;
        static long long min() { return -9223372036854775807LL - 1; }
        static long long max() { return 9223372036854775807LL; }
        static const int digits = ( sizeof( long long ) * 8 - ( ( long long )( -1 ) < 0 ) );
        static const int digits10 = ( ( sizeof( long long ) * 8 - ( ( long long )( -1 ) < 0 ) ) * 643L / 2136 );
        static const bool is_signed = true;
        static const bool is_integer = true;
        static const bool is_exact = true;
        static const int radix = 2;
        static long long epsilon() { return 0; }
        static long long round_error() { return 0; }
        static const int min_exponent = 0;
        static const int min_exponent10 = 0;
        static const int max_exponent = 0;
        static const int max_exponent10 = 0;
        static const bool has_infinity = false;
        static const bool has_quiet_NaN = false;
        static const bool has_signaling_NaN = false;
        static const float_denorm_style has_denorm = denorm_absent;
        static const bool has_denorm_loss = false;
        static long long infinity() { return static_cast<long long>( 0 ); }
        static long long quiet_NaN() { return static_cast<long long>( 0 ); }
        static long long signaling_NaN() { return static_cast<long long>( 0 ); }
        static long long denorm_min() { return static_cast<long long>( 0 ); }
        static const bool is_iec559 = false;
        static const bool is_bounded = true;
        static const bool is_modulo = true;
        static const bool traps = true;
        static const bool tinyness_before = false;
        static const float_round_style round_style = round_toward_zero;
    };
    template<>
    struct numeric_limits<unsigned long long>
    {
        static const bool is_specialized = true;
        static unsigned long long min() { return 0; }
        static unsigned long long
        max() { return 9223372036854775807LL * 2ULL + 1; }
        static const int digits = ( sizeof( unsigned long long ) * 8 - ( ( unsigned long long )( -1 ) < 0 ) );
        static const int digits10 = ( ( sizeof( unsigned long long ) * 8 - ( ( unsigned long long )( -1 ) < 0 ) ) * 643L / 2136 );
        static const bool is_signed = false;
        static const bool is_integer = true;
        static const bool is_exact = true;
        static const int radix = 2;
        static unsigned long long epsilon() { return 0; }
        static unsigned long long round_error() { return 0; }
        static const int min_exponent = 0;
        static const int min_exponent10 = 0;
        static const int max_exponent = 0;
        static const int max_exponent10 = 0;
        static const bool has_infinity = false;
        static const bool has_quiet_NaN = false;
        static const bool has_signaling_NaN = false;
        static const float_denorm_style has_denorm = denorm_absent;
        static const bool has_denorm_loss = false;
        static unsigned long long infinity() { return static_cast<unsigned long long>( 0 ); }
        static unsigned long long quiet_NaN() { return static_cast<unsigned long long>( 0 ); }
        static unsigned long long signaling_NaN() { return static_cast<unsigned long long>( 0 ); }
        static unsigned long long denorm_min() { return static_cast<unsigned long long>( 0 ); }
        static const bool is_iec559 = false;
        static const bool is_bounded = true;
        static const bool is_modulo = true;
        static const bool traps = true;
        static const bool tinyness_before = false;
        static const float_round_style round_style = round_toward_zero;
    };
    template<>
    struct numeric_limits<float>
    {
        static const bool is_specialized = true;
        static float min() { return 1.17549435082228750797e-38F; }
        static float max() { return 3.40282346638528859812e+38F; }
        static const int digits = 24;
        static const int digits10 = 6;
        static const bool is_signed = true;
        static const bool is_integer = false;
        static const bool is_exact = false;
        static const int radix = 2;
        static float epsilon() { return 1.19209289550781250000e-7F; }
        static float round_error() { return 0.5F; }
        static const int min_exponent = ( -125 );
        static const int min_exponent10 = ( -37 );
        static const int max_exponent = 128;
        static const int max_exponent10 = 38;
        static const bool has_infinity = 1;
        static const bool has_quiet_NaN = 1;
        static const bool has_signaling_NaN = has_quiet_NaN;
        static const float_denorm_style has_denorm = denorm_present;
        static const bool has_denorm_loss = false;
        static float infinity();// { return __builtin_huge_valf(); }
        static float quiet_NaN();// { return __builtin_nanf( "" ); }
        static float signaling_NaN();// { return __builtin_nansf( "" ); }
        static float denorm_min() { return 1.40129846432481707092e-45F; }
        static const bool is_iec559 = has_infinity && has_quiet_NaN && has_denorm == denorm_present;
        static const bool is_bounded = true;
        static const bool is_modulo = false;
        static const bool traps = false;
        static const bool tinyness_before = false;
        static const float_round_style round_style = round_to_nearest;
    };
    template<>
    struct numeric_limits<double>
    {
        static const bool is_specialized = true;
        static double min() { return double( 2.22507385850720138309e-308L ); }
        static double max() { return double( 1.79769313486231570815e+308L ); }
        static const int digits = 53;
        static const int digits10 = 15;
        static const bool is_signed = true;
        static const bool is_integer = false;
        static const bool is_exact = false;
        static const int radix = 2;
        static double epsilon() { return double( 2.22044604925031308085e-16L ); }
        static double round_error() { return 0.5; }
        static const int min_exponent = ( -1021 );
        static const int min_exponent10 = ( -307 );
        static const int max_exponent = 1024;
        static const int max_exponent10 = 308;
        static const bool has_infinity = 1;
        static const bool has_quiet_NaN = 1;
        static const bool has_signaling_NaN = has_quiet_NaN;
        static const float_denorm_style has_denorm =denorm_present;
        static const bool has_denorm_loss = false;
        static double infinity();// { return __builtin_huge_val(); }
        static double quiet_NaN();// { return __builtin_nan( "" ); }
        static double signaling_NaN();// { return __builtin_nans( "" ); }
        static double denorm_min() { return double( 4.94065645841246544177e-324L ); }
        static const bool is_iec559 = has_infinity && has_quiet_NaN && has_denorm == denorm_present;
        static const bool is_bounded = true;
        static const bool is_modulo = false;
        static const bool traps = false;
        static const bool tinyness_before = false;
        static const float_round_style round_style = round_to_nearest;
    };
    template<>
    struct numeric_limits<long double>
    {
        static const bool is_specialized = true;
        static long double min() { return 3.36210314311209350626e-4932L; }
        static long double max() { return 1.18973149535723176502e+4932L; }
        static const int digits = 64;
        static const int digits10 = 18;
        static const bool is_signed = true;
        static const bool is_integer = false;
        static const bool is_exact = false;
        static const int radix = 2;
        static long double epsilon() { return 1.08420217248550443401e-19L; }
        static long double round_error() { return 0.5L; }
        static const int min_exponent = ( -16381 );
        static const int min_exponent10 = ( -4931 );
        static const int max_exponent = 16384;
        static const int max_exponent10 = 4932;
        static const bool has_infinity = 1;
        static const bool has_quiet_NaN = 1;
        static const bool has_signaling_NaN = has_quiet_NaN;
        static const float_denorm_style has_denorm = denorm_present;
        static const bool has_denorm_loss = false;
        static long double infinity();// { return __builtin_huge_vall(); }
        static long double quiet_NaN();// { return __builtin_nanl( "" ); }
        static long double signaling_NaN();// { return __builtin_nansl( "" ); }
        static long double denorm_min() { return 3.64519953188247460253e-4951L; }
        static const bool is_iec559 = has_infinity && has_quiet_NaN && has_denorm == denorm_present;
        static const bool is_bounded = true;
        static const bool is_modulo = false;
        static const bool traps = false;
        static const bool tinyness_before = false;
        static const float_round_style round_style = round_to_nearest;
    };
}//namespace device

#endif//_LIMITS_HPP_INCLUDED_SDPOJINASFLKJN49UHASFDKLJNASFDLJKN49UH8AFDLNJHSAFDF 

