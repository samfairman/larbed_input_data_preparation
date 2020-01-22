#include <qeda/Crystal.h>
#include <qeda/readparams.h>

#include <cstdlib>
#include <cstring>
#include <cstdio>

#define N_PARAM 11
#define N_ELEM 99
// The following scattering factor table is taken from L.M. Peng, Micron 30 (1999) 625-648
const ftype pengfacts[N_ELEM][N_PARAM] = {{
        0,  0.0000,  0.0000,  0.0000,  0.0000,  0.0000,  0.0000,   0.0000,   0.0000,  0.0000, 0
    }, {
        1,  0.0367,  0.1269,  0.2360,  0.1290,  0.5608,  3.7913,  13.5557,  37.7229,  0.0011, 0
    }, {
        2,  0.0406,  0.1276,  0.1738,  0.0758,  0.3140,  2.0952,   7.1369,  19.4462,  0.0003, 0
    }, {
        3,  0.1198,  0.3952,  1.3794,  1.3889,  0.5908,  6.1114,  36.7672, 117.0314,  0.0029, 0
    }, {
        4,  0.1180,  0.4394,  1.4273,  1.0661,  0.4599,  4.4816,  21.5831,  66.1150,  0.0019, 0
    }, {
        5,  0.1298,  0.5200,  1.3767,  0.7666,  0.4180,  3.9214,  16.6634,  51.7511,  0.0015, 0
    }, {
        6,  0.1361,  0.5482,  1.2266,  0.5971,  0.3731,  3.2814,  13.0456,  41.0202,  0.0013, 0
    }, {
        7,  0.1372,  0.5344,  1.0862,  0.4547,  0.3287,  2.6733,  10.3165,  32.7631,  0.0015, 0
    }, {
        8,  0.1433,  0.5103,  0.9370,  0.3923,  0.3055,  2.2683,   8.2625,  25.6645,  0.0007, 0
    }, {
        9,  0.1516,  0.5193,  0.8220,  0.3081,  0.2888,  2.0619,   7.2628,  22.0262,  0.0005, 0
    }, {
        10,  0.1575,  0.5041,  0.7330,  0.2572,  0.2714,  1.8403,   6.3059,  19.1640,  0.0004, 0
    }, {
        11,  0.3319,  0.9857,  1.4885,  1.9657,  0.4950,  4.0855,  31.5107, 118.4940,  0.0059, 0
    }, {
        12,  0.3248,  0.9243,  2.0039,  1.9507,  0.4455,  3.5744,  24.2702,  80.7304,  0.0046, 0
    }, {
        13,  0.3582,  0.9754,  2.6393,  1.9103,  0.4529,  3.7745,  23.3862,  80.5019,  0.0055, 0
    }, {
        14,  0.3626,  0.9737,  2.7209,  1.7660,  0.4281,  3.5570,  19.3905,  64.3334,  0.0044, 0
    }, {
        15,  0.3540,  0.9397,  2.6203,  1.5707,  0.3941,  3.1810,  15.6579,  49.5239,  0.0034, 0
    }, {
        16,  0.3478,  0.9158,  2.5066,  1.3884,  0.3652,  2.8915,  13.0522,  40.1848,  0.0027, 0
    }, {
        17,  0.3398,  0.8908,  2.3878,  1.2376,  0.3379,  2.6190,  11.0684,  33.5378,  0.0021, 0
    }, {
        18,  0.3409,  0.8966,  2.2636,  1.0786,  0.3229,  2.4778,   9.7408,  28.9354,  0.0016, 0
    }, {
        19,  0.5658,  2.4151,  2.4655,  3.5240,  0.5061,  5.7656,  31.9169, 151.2590,  0.0135, 0
    }, {
        20,  0.5474,  2.2793,  3.1934,  3.8824,  0.4700,  5.0494,  29.6928, 109.5608,  0.0111, 0
    }, {
        21,  0.5389,  2.2102,  3.1187,  3.4302,  0.4446,  4.5701,  26.4597,  98.1283,  0.0098, 0
    }, {
        22,  0.5398,  2.1568,  2.9961,  3.0751,  0.4281,  4.2236,  24.1928,  90.6685,  0.0091, 0
    }, {
        23,  0.5412,  2.1063,  2.8525,  2.7967,  0.4132,  3.9256,  22.3625,  84.4689,  0.0084, 0
    }, {
        24,  0.5478,  2.0737,  2.3527,  1.9866,  0.4032,  3.7014,  20.0893,  87.9230,  0.0079, 0
    }, {
        25,  0.5552,  2.0073,  2.5678,  2.3695,  0.3947,  3.4800,  19.5862,  74.9201,  0.0073, 0
    }, {
        26,  0.5627,  1.9685,  2.4527,  2.1750,  0.3859,  3.3103,  18.7003,  71.6638,  0.0069, 0
    }, {
        27,  0.5730,  1.9219,  2.3358,  2.0177,  0.3799,  3.1572,  17.8168,  68.4867,  0.0065, 0
    }, {
        28,  0.5785,  1.8679,  2.2229,  1.8940,  0.3704,  2.9964,  16.8507,  65.2843,  0.0061, 0
    }, {
        29,  0.5932,  1.8344,  1.8080,  1.3586,  0.3680,  2.8959,  15.6333,  70.6800,  0.0059, 0
    }, {
        30,  0.5996,  1.7763,  2.0240,  1.6598,  0.3602,  2.7665,  15.5278,  60.2830,  0.0054, 0
    }, {
        31,  0.6737,  1.8457,  2.6395,  1.9413,  0.3901,  3.0289,  19.0448,  74.1674,  0.0077, 0
    }, {
        32,  0.6660,  1.7662,  2.8876,  2.0510,  0.3741,  2.8390,  17.2911,  62.5149,  0.0067, 0
    }, {
        33,  0.6504,  1.6706,  2.9930,  2.0018,  0.3550,  2.6169,  15.1100,  50.8113,  0.0054, 0
    }, {
        34,  0.6343,  1.5698,  3.0362,  1.9607,  0.3374,  2.4000,  13.1385,  42.4344,  0.0043, 0
    }, {
        35,  0.6216,  1.4943,  3.0763,  1.8642,  0.3216,  2.2338,  11.7075,  36.7639,  0.0036, 0
    }, {
        36,  0.6240,  1.4352,  3.0847,  1.7511,  0.3144,  2.1394,  10.6060,  32.4403,  0.0031, 0
    }, {
        37,  1.0180,  2.8882,  3.5125,  4.3375,  0.4850,  5.1504,  26.1762,  155.1291, 0.0202, 0
    }, {
        38,  1.0127,  2.9403,  3.9920,  5.1441,  0.4721,  4.9802,  26.8565,  116.0307, 0.0179, 0
    }, {
        39,  0.9722,  2.8705,  4.1571,  4.6466,  0.4427,  4.5552,  24.0646,  99.1688,  0.0154, 0
    }, {
        40,  0.9592,  2.8531,  4.1761,  4.1491,  0.4279,  4.3237,  22.1510,  89.7694,  0.0137, 0
    }, {
        41,  0.9337,  2.8218,  3.9092,  2.9880,  0.4074,  4.0572,  19.4778,  85.5042,  0.0121, 0
    }, {
        42,  0.9334,  2.8581,  3.8278,  2.6302,  0.3996,  3.9476,  18.6153,  82.5062,  0.0112, 0
    }, {
        43,  0.9282,  2.8832,  3.8985,  3.1237,  0.3894,  3.8131,  18.2715,  74.4844,  0.0107, 0
    }, {
        44,  0.9175,  2.8691,  3.5480,  2.2030,  0.3776,  3.6434,  16.4538,  74.4590,  0.0097, 0
    }, {
        45,  0.9046,  2.8679,  3.3997,  2.0510,  0.3646,  3.4888,  15.5106,  71.3737,  0.0088, 0
    }, {
        46,  0.7832,  2.1753,  3.2003,  1.4127,  0.3094,  2.5857,   9.8481,  37.4035,  0.0044, 0
    }, {
        47,  0.9085,  2.9433,  3.1021,  1.7092,  0.3541,  3.3319,  14.7723,  70.5441,  0.0085, 0
    }, {
        48,  0.9056,  2.9430,  3.1814,  2.1946,  0.3466,  3.2215,  14.7749,  62.3544,  0.0081, 0
    }, {
        49,  0.9660,  3.1971,  3.6243,  2.6351,  0.3648,  3.4534,  18.3358,  75.8859,  0.0111, 0
    }, {
        50,  0.9481,  3.1011,  3.8863,  2.9142,  0.3518,  3.2474,  17.4348,  66.0384,  0.0099, 0
    }, {
        51,  0.9323,  2.9938,  4.0829,  2.9578,  0.3405,  3.0545,  16.2843,  56.5387,  0.0084, 0
    }, {
        52,  0.9060,  2.8392,  4.1639,  3.0782,  0.3256,  2.8170,  14.6041,  48.0880,  0.0071, 0
    }, {
        53,  0.8912,  2.7442,  4.3316,  2.9328,  0.3150,  2.6616,  13.6958,  43.2296,  0.0064, 0
    }, {
        54,  0.8749,  2.6276,  4.4112,  2.8758,  0.3046,  2.4959,  12.5908,  38.5666,  0.0054, 0
    }, {
        55,  1.2968,  3.8609,  5.6613,  5.6489,  0.4462,  4.3194,  24.1136,  168.3481, 0.0301, 0
    }, {
        56,  1.3111,  3.9542,  5.8693,  7.0998,  0.4432,  4.3226,  24.3857,  128.5976, 0.0285, 0
    }, {
        57,  1.2872,  3.8478,  6.0581,  6.5606,  0.4283,  4.0782,  22.4363,  109.8403, 0.0251, 0
    }, {
        58,  1.3019,  3.8491,  5.8568,  6.3222,  0.4256,  4.0288,  22.0020,  107.6524, 0.0244, 0
    }, {
        59,  1.3354,  3.8652,  5.3000,  6.4296,  0.4305,  4.0368,  22.1273,  117.0334, 0.0259, 0
    }, {
        60,  1.3473,  3.8589,  5.1226,  6.2264,  0.4266,  3.9844,  21.8395,  114.8891, 0.0247, 0
    }, {
        61,  1.3631,  3.8462,  4.9578,  6.0228,  0.4253,  3.9386,  21.6330,  112.8589, 0.0243, 0
    }, {
        62,  1.3702,  3.8270,  4.8068,  5.8402,  0.4204,  3.8747,  21.3840,  110.9527, 0.0238, 0
    }, {
        63,  1.3963,  3.8201,  4.6869,  5.6321,  0.4230,  3.8621,  21.4604,  110.3872, 0.0234, 0
    }, {
        64,  1.3784,  3.7349,  4.8549,  5.2564,  0.4105,  3.7014,  20.2877,   96.0364, 0.0205, 0
    }, {
        65,  1.4257,  3.7865,  4.4336,  5.2698,  0.4182,  3.7931,  21.3185,  107.6330, 0.0233, 0
    }, {
        66,  1.4104,  3.6934,  4.3012,  5.1904,  0.4076,  3.6339,  20.3594,  103.6978, 0.0213, 0
    }, {
        67,  1.3805,  3.5395,  4.4117,  5.0148,  0.3938,  3.4131,  18.4989,  86.9074,  0.0171, 0
    }, {
        68,  1.4391,  3.6351,  4.0572,  4.9059,  0.4038,  3.5707,  20.0727,  100.4842, 0.0202, 0
    }, {
        69,  1.4561,  3.6041,  3.9360,  4.7711,  0.4028,  3.5468,  19.9521,  98.6682,  0.0197, 0
    }, {
        70,  1.4617,  3.5735,  3.8563,  4.6254,  0.3986,  3.4988,  19.9050,  97.9782,  0.0192, 0
    }, {
        71,  1.4381,  3.4689,  4.0824,  4.4599,  0.3874,  3.3304,  18.8077,  84.5078,  0.0169, 0
    }, {
        72,  1.4209,  3.3984,  4.2315,  4.1000,  0.3772,  3.2109,  17.7720,  76.0916,  0.0153, 0
    }, {
        73,  1.4163,  3.3456,  4.3281,  3.7406,  0.3714,  3.1289,  16.8719,  70.3632,  0.0141, 0
    }, {
        74,  1.4109,  3.2997,  4.3698,  3.4408,  0.3653,  3.0517,  15.9630,  65.7545,  0.0131, 0
    }, {
        75,  1.3898,  3.2373,  4.3683,  3.2472,  0.3548,  2.9382,  14.8500,  60.6048,  0.0117, 0
    }, {
        76,  1.3877,  3.2082,  4.3731,  2.9958,  0.3502,  2.8796,  14.1535,  57.3692,  0.0110, 0
    }, {
        77,  1.3783,  3.1637,  4.3549,  2.8050,  0.3440,  2.7975,  13.3640,  54.3356,  0.0101, 0
    }, {
        78,  1.3489,  3.0674,  4.2095,  2.1738,  0.3322,  2.6601,  12.0128,  50.3882,  0.0091, 0
    }, {
        79,  1.3413,  3.0559,  4.1659,  2.0022,  0.3262,  2.6076,  11.5043,  48.4954,  0.0084, 0
    }, {
        80,  1.3592,  3.1327,  4.1897,  2.2748,  0.3265,  2.6458,  11.6919,  47.9347,  0.0084, 0
    }, {
        81,  1.4735,  3.6368,  4.3950,  2.5803,  0.3500,  3.0849,  14.9338,  65.0072,  0.0121, 0
    }, {
        82,  1.4700,  3.6387,  4.5674,  2.9103,  0.3452,  3.0340,  14.8562,  60.2174,  0.0117, 0
    }, {
        83,  1.4616,  3.6426,  4.7876,  3.1935,  0.3396,  2.9739,  14.8388,  56.7362,  0.0113, 0
    }, {
        84,  1.4255,  3.5214,  4.9058,  3.4925,  0.3274,  2.8031,  13.8305,  50.1382,  0.0100, 0
    }, {
        85,  1.4170,  3.4829,  5.0951,  3.4639,  0.3224,  2.7289,  13.4904,  46.2094,  0.0089, 0
    }, {
        86,  1.4001,  3.4082,  5.2516,  3.4250,  0.3153,  2.6261,  12.9003,  42.3929,  0.0083, 0
    }, {
        87,  1.7697,  4.6820,  6.6701,  5.5268,  0.3969,  3.9950,  23.0274,  154.8886, 0.0316, 0
    }, {
        88,  1.7704,  4.6854,  6.8034,  7.2352,  0.3938,  3.9313,  22.4168,  120.9717, 0.0300, 0
    }, {
        89,  1.7346,  4.5959,  7.0436,  7.0521,  0.3816,  3.7454,  21.1330,  102.1159, 0.0267, 0
    }, {
        90,  1.7012,  4.5007,  7.2504,  6.6077,  0.3704,  3.5712,  19.8632,  89.3562,  0.0238, 0
    }, {
        91,  1.7266,  4.6123,  6.7855,  6.3876,  0.3729,  3.6159,  19.6433,  95.2720,  0.0248, 0
    }, {
        92,  1.7417,  4.7063,  6.6509,  5.9929,  0.3729,  3.6337,  19.6579,  95.0805,  0.0246, 0
    }, {
        93,  1.7327,  4.6782,  6.4465,  5.8528,  0.3683,  3.5375,  18.8556,  91.5521,  0.0240, 0
    }, {
        94,  1.7491,  4.7933,  5.9841,  5.6139,  0.3683,  3.5651,  18.8727,  100.8062, 0.0246, 0
    }, {
        95,  1.7519,  4.8096,  5.8155,  5.4119,  0.3654,  3.5215,  18.5120,  98.8221,  0.0241, 0
    }, {
        96,  1.7284,  4.7162,  5.9338,  5.2896,  0.3577,  3.3776,  17.7168,  86.4936,  0.0217, 0
    }, {
        97,  1.7298,  4.7198,  5.7527,  5.1576,  0.3554,  3.3269,  17.3659,  84.3294,  0.0211, 0
    }, {
        98,  1.6401,  4.3905,  5.4504,  5.4542,  0.3332,  2.9830,  14.6892,  73.0723,  0.0258, 0
    }
};

Crystal::Crystal( void )
{
    errorFlag = 0;
    atoms = NULL;
    nAtoms = 0;
    fileName = NULL;
    // memset(&Mm[0][0],0,9*sizeof(double));
    // memset(&MmInv[0][0],0,9*sizeof(double));
    memset( Znums, 0, NZMAX * sizeof( int ) );
}

Crystal::Crystal( char *fn )
{
    errorFlag = 0;
    atoms = NULL;
    nAtoms = 0;
    fileName = NULL;
    memset( Znums, 0, NZMAX * sizeof( int ) );
    SetFileName( fn );
    Load();
}

void Crystal::SetFileName( const char *fn )
{
    fileName = ( char * )malloc( strlen( fn ) + 2 );
    //strcpy_s( fileName, strlen( fn ) + 1, fn );
    unsigned long fs = std::strlen( fn );
    std::fill( fileName, fileName+fs+2, 0 );
    std::copy( fn, fn+fs, fileName );

}


// This function determines the Z-numbewr from the string defining the element (e..g. 'Si' -> 14).
int Crystal::getZNumber( char *element )
{
    const char *elTable =
    {
        "H HeLiBeB C N O F NeNaMgAlSiP S Cl"
        "ArK CaScTiV CrMnFeCoNiCuZnGaGeAsSeBr"
        "KrRbSrY ZrNbMoTcRuRhPdAgCdInSnSbTe"
        "I XeCsBaLaCePrNdPmSmEuGdTbDyHoErTm"
        "YbLuHfTaW ReOsIrPtAuHgTlPbBiPoAtRn"
        "FrRaAcThPaU NpPuAmCmBkCfEsFmMdNoLr"
    };
    const char *elem;
#ifdef __GNUC__
    char widows = '\n';
    widows = ( char )( ( int )widows + 3 );
    // fprintf(stderr,"getZnumber : element = *%s* \n",element);
    element[2] = '\0';
    if ( ( atoi( element + 1 ) != 0 ) || ( element[1] == '\n' ) || ( element[1] == '\0' ) || element[1] == widows )
    {
        element[1] = ' ';
        // fprintf(stderr,"getZnumber : element = *%s*  conversion \n",element);
    }
#else
    element[2] = '\0';
    if ( ( atoi( element + 1 ) != 0 ) || ( element[1] == '\n' ) || ( element[1] == '\0' ) )
        element[1] = ' ';
#endif
    if ( ( elem = strstr( elTable, element ) ) == NULL )
        return 0;
    else
        return ( int )( elem - elTable ) / 2 + 1;
}


/******************************************************************************
 Routine:   inverse_3x3
 Input:     m - matrix (3x3) address
 Output:    returns the inverse matrix of 'm'
******************************************************************************/
void Crystal::inverse_3x3( double *res, const double *a )
{
    double det = a[0] * ( a[4] * a[8] - a[7] * a[5] )
                 - a[1] * ( a[3] * a[8] - a[6] * a[5] )
                 + a[2] * ( a[3] * a[7] - a[6] * a[4] );
    // printf("det: %g\n",det);
    if ( fabs ( det ) < 0.0005f )
    {
        res[0] = 1.0f;
        res[1] = 0.0f;
        res[2] = 0.0f;
        res[3] = 0.0f;
        res[4] = 1.0f;
        res[5] = 0.0f;
        res[6] = 0.0f;
        res[7] = 0.0f;
        res[8] = 1.0f;
        return;
    }
    det = 1.0f / det;
    res[0] =  ( a[4] * a[8] - a[5] * a[7] ) * det;
    res[1] = -( a[1] * a[8] - a[7] * a[2] ) * det;
    res[2] =  ( a[1] * a[5] - a[4] * a[2] ) * det;
    res[3] = -( a[3] * a[8] - a[5] * a[6] ) * det;
    res[4] =  ( a[0] * a[8] - a[6] * a[2] ) * det;
    res[5] = -( a[0] * a[5] - a[3] * a[2] ) * det;
    res[6] =  ( a[3] * a[7] - a[6] * a[4] ) * det;
    res[7] = -( a[0] * a[7] - a[6] * a[1] ) * det;
    res[8] =  ( a[0] * a[4] - a[1] * a[3] ) * det;
}


/***********************************************************************
* The following function returns the number of atoms in the specified
* CFG file and updates the cell parameters in the muls struct
***********************************************************************/
int Crystal::ReadCFGCellParams( void )
{
    int ncoord, i;
    char buf[256];
    double lengthScale;
    // printf("Paramter File pointer (1): %d\n",(int)getFp());
    parFpPush(); /* push the current parameter file file pointer
                 * on the stack to make this function totaly
                 * transparent
                 */
    if ( !parOpen( fileName ) )
    {
        printf( "Could not open CFG input file %s\n", fileName );
        parFpPull();  /* restore old parameter file pointer */
        return 0;
    }
    // printf("Paramter File pointer (2): %d\n",(int)getFp());
    resetParamFile();
    setComment( '#' );
    if ( readparam( "Number of particles =", buf, 1 ) )
        //sscanf( buf, "%d", &ncoord );
        sscanf( buf, "%d", &ncoord );
    if ( readparam( "A =", buf, 1 ) )
        sscanf( buf, "%lf", &lengthScale );
    if ( readparam( "H0(1,1) =", buf, 1 ) )
        sscanf( buf, "%lf", Mm[0] + 0 );
    if ( readparam( "H0(1,2) =", buf, 1 ) )
        sscanf( buf, "%lf", Mm[0] + 1 );
    if ( readparam( "H0(1,3) =", buf, 1 ) )
        sscanf( buf, "%lf", Mm[0] + 2 );
    if ( readparam( "H0(2,1) =", buf, 1 ) )
        sscanf( buf, "%lf", Mm[0] + 3 );
    if ( readparam( "H0(2,2) =", buf, 1 ) )
        sscanf( buf, "%lf", Mm[0] + 4 );
    if ( readparam( "H0(2,3) =", buf, 1 ) )
        sscanf( buf, "%lf", Mm[0] + 5 );
    if ( readparam( "H0(3,1) =", buf, 1 ) )
        sscanf( buf, "%lf", Mm[0] + 6 );
    if ( readparam( "H0(3,2) =", buf, 1 ) )
        sscanf( buf, "%lf", Mm[0] + 7 );
    if ( readparam( "H0(3,3) =", buf, 1 ) )
        sscanf( buf, "%lf", Mm[0] + 8 );
    /*
    if (readparam(".NO_VELOCITY.",buf,1)) noVelocityFlag = 1;
    if (readparam("entry_count =",buf,1)) sscanf(buf,"%lf",&entryCount);
    if (!noVelocityFlag) entryCount+=3;
    */
    setComment( '%' );
    parClose();
    parFpPull();  /* restore old parameter file pointer */
    for ( i = 0; i < 9; i++ )
        Mm[0][i] *= lengthScale;
    inverse_3x3( MmInv[0], Mm[0] );
    // compute the unit cell volume: V=a dot (b cross c)
    unitCellVolume = Mm[0][0] * ( Mm[1][1] * Mm[2][2] - Mm[1][2] * Mm[2][1] )
                     + Mm[0][1] * ( Mm[1][2] * Mm[2][0] - Mm[1][0] * Mm[2][2] )
                     + Mm[0][2] * ( Mm[1][0] * Mm[2][1] - Mm[1][1] * Mm[2][0] );
    ax = sqrt( Mm[0][0] * Mm[0][0] + Mm[0][1] * Mm[0][1] + Mm[0][2] * Mm[0][2] );
    by = sqrt( Mm[1][0] * Mm[1][0] + Mm[1][1] * Mm[1][1] + Mm[1][2] * Mm[1][2] );
    cz  = sqrt( Mm[2][0] * Mm[2][0] + Mm[2][1] * Mm[2][1] + Mm[2][2] * Mm[2][2] );
    gamma = atan2( Mm[1][1], Mm[1][0] );
    beta = acos( Mm[2][0] / cz );
    alpha = acos( Mm[2][1] * sin( gamma ) / cz + cos( beta ) * cos( gamma ) );
    gamma /= ( float )PI180; // convert from rad to deg
    beta  /= ( float )PI180;
    alpha /= ( float )PI180;
    if ( ncoord < 1 )
    {
        printf( "Number of atoms in CFG file not specified!\n" );
        ncoord = 0;
    }
    return ncoord;
}

/*******************************************************************************
* This function reads the atomic position and element data for a single atom
* from a .cfg file.  The atomic positions are given in reduced coordinates.
* Calling this function several times will read one atom after another from the
* file.
* This function will return -1, if the end of file is reached prematurely, 0 otherwise.
*******************************************************************************/

int Crystal::readNextCFGAtom( atom *newAtom, int flag )
{
    static FILE *fp = NULL;
    static int noVelocityFlag = 1, entryCount = 3, element = 1;
    static char buf[NCMAX];
    static double *atomData = NULL;
    static double mass = 28;
    char *str = NULL;
    int j;
    if ( flag < 0 )
    {
        if ( fp != NULL )
        {
            parClose();
            parFpPull();  /* restore old parameter file pointer */
            fp = NULL;
            setComment( '%' );
        }
        return -1;
    }
    if ( fp == NULL )
    {
        parFpPush();  /* save old parameter file pointer */
        if ( !parOpen( fileName ) )
        {
            printf( "Could not open CFG input file %s\n", fileName );
            parFpPull();  /* restore old parameter file pointer */
            return -1;
        }
        resetParamFile();
        if ( readparam( ".NO_VELOCITY.", buf, 1 ) )
            noVelocityFlag = 1;
        else
            noVelocityFlag = 0;
        if ( readparam( "entry_count =", buf, 1 ) )
            sscanf( buf, "%d", &entryCount );
        if ( !noVelocityFlag )
            entryCount += 3;
        fp = getFp();  /* get the file pointer from the parameter file routines */
        atomData = ( double * )malloc( ( entryCount + 1 ) * sizeof( double ) );
    }
    if ( fgets( buf, NCMAX, fp ) == NULL )
        return -1;
    /* check, if this is a new mass number */
    str = strnext( buf, " \t" );
    if ( ( atof( buf ) >= 1.0 ) && ( ( str == NULL ) || ( *str == '#' ) ) )
    {
        mass = atof( buf );
        // printf("nV: %d, eC: %d (%g)\n",noVelocityFlag, entryCount,atof(buf));
        if ( fgets( buf, NCMAX, fp ) == NULL )
            return -1;
        element = getZNumber( buf );
        // printf("*** found element %d (%s %d) ***\n",element,buf,strlen(buf));
        if ( fgets( buf, NCMAX, fp ) == NULL )
            return -1;
    }
    str = buf;
    // skip leading spaces:
    while ( strchr( " \t", *str ) != NULL )
        str++;
    for ( j = 0; j < entryCount; j++ )
    {
        if ( str == NULL )
        {
            printf( "readNextCFGatom: Error: incomplete data line: >%s<\n", buf );
            return -1;
        }
        atomData[j] = atof( str );
        str = strnext( str, " \t" );
    }
    newAtom->Znum = element;
    newAtom->x    = ( float )atomData[0];
    newAtom->y    = ( float )atomData[1];
    newAtom->z    = ( float )atomData[2];
    // newAtom->dw   = 0.45*28.0/((double)(2*element));
    // printf("Element: %d, mass=%g\n",element,mass);
    newAtom->dw   = ( float )( 0.45 * 28.0 / mass );
    newAtom->occ  = 1.0f;
    newAtom->q    = 0.0f;
    // read the DW-factor
    if ( entryCount > 3 + 3 * ( 1 - noVelocityFlag ) )
        newAtom->dw = ( float )atomData[3 + 3 * ( 1 - noVelocityFlag )];
    // read the atom's occupancy:
    if ( entryCount > 4 + 3 * ( 1 - noVelocityFlag ) )
        newAtom->occ = ( float )atomData[4 + 3 * ( 1 - noVelocityFlag )];
    // read the atom's charge:
    if ( entryCount > 5 + 3 * ( 1 - noVelocityFlag ) )
        newAtom->q = ( float )atomData[5 + 3 * ( 1 - noVelocityFlag )];
    // printf("Atom: %d (%g %g %g), occ=%g, q=%g\n",newAtom->Znum,newAtom->x,newAtom->y,newAtom->z,newAtom->occ,newAtom->q);
    return 0;
}


void Crystal::Print( void )
{
    int i, j;
    printf( "\n**************** Crystal Info ********************\n" );
    printf( "file name: %s\n", fileName );
    printf( "Lattice parameters: \n" );
    printf( "   ax=%g A, by=%g A, cz=%g A\n", ax, by, cz );
    printf( "   alpha=%g deg,, beta=%g deg, gamma=%g deg\n", alpha, beta, gamma );
    printf( "   unit cell volume=%.4f A^3\n", unitCellVolume );
    printf( "Reciprocal space matrix:\n" );
    for ( i = 0; i < 3; i++ )
    {
        for ( j = 0; j < 3; j++ )
            printf( "%10f ", MmInv[i][j] );
        printf( "\n" );
    }
    printf( "\nNumber of atoms: %d\n", nAtoms );
    printf( "Fractional atom positions: \n" );
    for ( j = 0; j < nAtoms; j++ )
        printf( "%2d: Z=%2d (%7.4f %7.4f %7.4f), DW=%7.4f\n", j, atoms[j].Znum, atoms[j].x, atoms[j].y, atoms[j].z, atoms[j].dw );
    printf( "\n" );
}

// Currently, this function cn only read .cfg files.
void Crystal::Load( void )
{
    int ncoord = 0;
    int i, jz, atomKinds = 0;
    errorFlag = 0;
    memset( Znums, 0, NZMAX * sizeof( int ) );
    // read the unit cell parameters: Mm, ax,by,cz,alpha,beta,gamma
    ncoord = ReadCFGCellParams();
    // printf("Lattice parameters: ax=%g by=%g cz=%g (%d atoms)\n",ax,by,cz,ncoord);
    // now that we know how many coordinates there are allocate the arrays
    if ( atoms != NULL )
        free( atoms );
    atoms = ( atom * )malloc( ncoord * sizeof( atom ) );
    if ( atoms == NULL )
    {
        printf( "Could not allocate memory for atoms!\n" );
        errorFlag = 1;
        return;
    }
    atomKinds = 0;
    /***********************************************************
    * Read actual Data
    ***********************************************************/
    for ( jz = 0, i = ncoord - 1; i >= 0; i-- )
    {
        // printf("reading atom nr. %d (iZ = %d)\n",i,jz);
        if ( readNextCFGAtom( atoms + i, 0 ) < 0 )
        {
            printf( "number of atoms does not agree with atoms in file!\n" );
            errorFlag = 2;
            return;
        }
        if ( ( atoms[i].Znum < 1 ) || ( atoms[i].Znum > NZMAX ) )
        {
            /* for (j=ncoord-1;j>=i;j--)
            printf("%2d: %d (%g,%g,%g)\n",j,atoms[j].Znum,atoms[j].x,
            atoms[j].y,atoms[j].z);
            */
            printf( "Error: bad atomic number %d in file %s (atom %d [%d: %g %g %g])\n",
                    atoms[i].Znum, fileName, i, atoms[i].Znum, atoms[i].x, atoms[i].y, atoms[i].z );
            errorFlag = 3;
            return;
        }
        // Keep a record of the kinds of atoms we are reading
        for ( jz = 0; jz < atomKinds; jz++ )
            if ( Znums[jz] == atoms[i].Znum )
                break;
        // allocate more memory, if there is a new element
        if ( jz == atomKinds )
        {
            atomKinds++;
            Znums[jz] = atoms[i].Znum;
        }
    } // for 1=ncoord-1:-1:0  - we've just read all the atoms.
    ////////////////////////////////////////////////////////////////
    // Close the file for further reading, and restore file pointer
    readNextCFGAtom( NULL, -1 );
    nAtoms = ncoord;
}

// This function only assigns the g-vector from the (h,k,l,s)-indices
void Crystal::ComputeGVector( Reflection& g )
{
    int h = g.mh;
    int k = g.mk;
    int l = g.ml;
    g.gx = ( ftype )( MmInv[0][0] * h + MmInv[0][1] * k + MmInv[0][2] * l );
    g.gy = ( ftype )( MmInv[1][0] * h + MmInv[1][1] * k + MmInv[1][2] * l );
    g.gz = ( ftype )( MmInv[2][0] * h + MmInv[2][1] * k + MmInv[2][2] * l );
}

// This function only assigns the g-vector from the (h,k,l,s)-indices
ftype Crystal::GetS2( Reflection& g )
{
    ComputeGVector( g );
    return 0.25 * ( g.gx * g.gx + g.gy * g.gy + g.gz * g.gz );
}


// This function only assigns the g-vector from the (h,k,l,s)-indices
void Crystal::GetBeamLength2( int h, int k, int l, int s, Reflection& g )
{
    if ( s & 4 )
        h = -h;
    if ( s & 2 )
        k = -k;
    if ( s & 1 )
        l = -l;
    g.gx = ( ftype )( MmInv[0][0] * h + MmInv[0][1] * k + MmInv[0][2] * l );
    g.gy = ( ftype )( MmInv[1][0] * h + MmInv[1][1] * k + MmInv[1][2] * l );
    g.gz = ( ftype )( MmInv[2][0] * h + MmInv[2][1] * k + MmInv[2][2] * l );
    g.mh = h;
    g.mk = k;
    g.ml = l;
}


// ComputeStructureFactor:
// Input: pointer to reflection g and beam energy in kV
#define ONE_PI 3.141592653589793
#define TWO_PI 6.283185307179586
#define V_SCALE 47.878009
complex_type Crystal::ComputeStructureFactor( Reflection *g, ftype energy_kV )
{
    int i;
    ftype gDotR, s2;
    complex_type ug( 0.0, 0.0 );
    s2 = GetS2( *g );
    for ( i = 0; i < nAtoms; i++ )
    {
        gDotR = TWO_PI * ( g->mh * atoms[i].x + g->mk * atoms[i].y + g->ml * atoms[i].z );
        ug += ComputeScatteringFactor( s2, atoms[i].Znum ) * ( ftype )exp( -s2 * atoms[i].dw ) * complex_type( cosf( gDotR ), sinf( gDotR ) );
    }
    // multiply by gamma = (1+energy/restEnergy) and divide by unit cell volume
    // Spence and Zuo book, page 33:
    ug *= ( 1 + energy_kV / 511 ) * ( ftype )exp( -s2 * atoms[i].dw ) / ( unitCellVolume * ONE_PI ); // unit is A^-2
    return ug;
}

ftype Crystal::ComputeScatteringFactor( ftype s2, int Znum )
{
    // This function must compute the scattering factor for the atom of type Znum:
    ftype f = 0;
    for ( int i = 1; i < 5; i++ )
    {
        f += pengfacts[Znum][i] * ( ftype )exp( -pengfacts[Znum][i + 4] * s2 );
    }
    // must still be multiplied by (1+E/E0) = (1+E/511)
    return f;
}

Crystal::~Crystal( void )
{
    if ( atoms != NULL )
        free( atoms );
    atoms = NULL;
    nAtoms = 0;
}

