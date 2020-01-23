#ifndef _CRYSTAL_H_INCLUDED_DFSOPINASDFLKNSADFLKJNSDAFALKJNASDFLKJNSDFKJFDSIAUHF
#define _CRYSTAL_H_INCLUDED_DFSOPINASDFLKNSADFLKJNSDAFALKJNASDFLKJNSDFKJFDSIAUHF

#include <qeda/DataTypes.h>
#include <qeda/Reflection.h>
#include <qeda/readparams.h>

#include <cstring>
#include <string>

#define PID 3.14159265358979     // pi 
#define PI180  0.017453292519943 // pi/180 
#define NZMAX   98               // max Z (in featom.dat ZMAX=103) 
#define NCMAX   256              // characters per line to read 

typedef struct atomStruct
{
	ftype z, y, x;
	ftype dw;      // Debye-Waller factor
	ftype occ;     // occupancy
	ftype q;       // charge
	int Znum;      // type of atom (nuclear charge)
} atom;


#define N_PARAM 11
#define N_ELEM 99
// The following scattering factor table is taken from L.M. Peng, Micron 30 (1999) 625-648
const ftype pengfacts[N_ELEM][N_PARAM] = {{
	0,  0.0000f,  0.0000f,  0.0000f,  0.0000f,  0.0000f,  0.0000f,   0.0000f,   0.0000f,  0.0000f, 0}, {
	1,  0.0367f,  0.1269f,  0.2360f,  0.1290f,  0.5608f,  3.7913f,  13.5557f,  37.7229f,  0.0011f, 0}, {
	2,  0.0406f,  0.1276f,  0.1738f,  0.0758f,  0.3140f,  2.0952f,   7.1369f,  19.4462f,  0.0003f, 0}, {
	3,  0.1198f,  0.3952f,  1.3794f,  1.3889f,  0.5908f,  6.1114f,  36.7672f, 117.0314f,  0.0029f, 0	}, {
	4,  0.1180f,  0.4394f,  1.4273f,  1.0661f,  0.4599f,  4.4816f,  21.5831f,  66.1150f,  0.0019f, 0	}, {
	5,  0.1298f,  0.5200f,  1.3767f,  0.7666f,  0.4180f,  3.9214f,  16.6634f,  51.7511f,  0.0015f, 0}, {
	6,  0.1361f,  0.5482f,  1.2266f,  0.5971f,  0.3731f,  3.2814f,  13.0456f,  41.0202f,  0.0013f, 0}, {
	7,  0.1372f,  0.5344f,  1.0862f,  0.4547f,  0.3287f,  2.6733f,  10.3165f,  32.7631f,  0.0015f, 0}, {
	8,  0.1433f,  0.5103f,  0.9370f,  0.3923f,  0.3055f,  2.2683f,   8.2625f,  25.6645f,  0.0007f, 0}, {
	9,  0.1516f,  0.5193f,  0.8220f,  0.3081f,  0.2888f,  2.0619f,   7.2628f,  22.0262f,  0.0005f, 0}, {
	10,  0.1575f,  0.5041f,  0.7330f,  0.2572f,  0.2714f,  1.8403f,   6.3059f,  19.1640f,  0.0004f, 0}, {
	11,  0.3319f,  0.9857f,  1.4885f,  1.9657f,  0.4950f,  4.0855f,  31.5107f, 118.4940f,  0.0059f, 0}, {
	12,  0.3248f,  0.9243f,  2.0039f,  1.9507f,  0.4455f,  3.5744f,  24.2702f,  80.7304f,  0.0046f, 0}, {
	13,  0.3582f,  0.9754f,  2.6393f,  1.9103f,  0.4529f,  3.7745f,  23.3862f,  80.5019f,  0.0055f, 0}, {
	14,  0.3626f,  0.9737f,  2.7209f,  1.7660f,  0.4281f,  3.5570f,  19.3905f,  64.3334f,  0.0044f, 0}, {
	15,  0.3540f,  0.9397f,  2.6203f,  1.5707f,  0.3941f,  3.1810f,  15.6579f,  49.5239f,  0.0034f, 0}, {
	16,  0.3478f,  0.9158f,  2.5066f,  1.3884f,  0.3652f,  2.8915f,  13.0522f,  40.1848f,  0.0027f, 0}, {
	17,  0.3398f,  0.8908f,  2.3878f,  1.2376f,  0.3379f,  2.6190f,  11.0684f,  33.5378f,  0.0021f, 0}, {
	18,  0.3409f,  0.8966f,  2.2636f,  1.0786f,  0.3229f,  2.4778f,   9.7408f,  28.9354f,  0.0016f, 0}, {
	19,  0.5658f,  2.4151f,  2.4655f,  3.5240f,  0.5061f,  5.7656f,  31.9169f, 151.2590f,  0.0135f, 0}, {
	20,  0.5474f,  2.2793f,  3.1934f,  3.8824f,  0.4700f,  5.0494f,  29.6928f, 109.5608f,  0.0111f, 0}, {
	21,  0.5389f,  2.2102f,  3.1187f,  3.4302f,  0.4446f,  4.5701f,  26.4597f,  98.1283f,  0.0098f, 0}, {
	22,  0.5398f,  2.1568f,  2.9961f,  3.0751f,  0.4281f,  4.2236f,  24.1928f,  90.6685f,  0.0091f, 0}, {
	23,  0.5412f,  2.1063f,  2.8525f,  2.7967f,  0.4132f,  3.9256f,  22.3625f,  84.4689f,  0.0084f, 0}, {
	24,  0.5478f,  2.0737f,  2.3527f,  1.9866f,  0.4032f,  3.7014f,  20.0893f,  87.9230f,  0.0079f, 0}, {
	25,  0.5552f,  2.0073f,  2.5678f,  2.3695f,  0.3947f,  3.4800f,  19.5862f,  74.9201f,  0.0073f, 0}, {
	26,  0.5627f,  1.9685f,  2.4527f,  2.1750f,  0.3859f,  3.3103f,  18.7003f,  71.6638f,  0.0069f, 0}, {
	27,  0.5730f,  1.9219f,  2.3358f,  2.0177f,  0.3799f,  3.1572f,  17.8168f,  68.4867f,  0.0065f, 0}, {
	28,  0.5785f,  1.8679f,  2.2229f,  1.8940f,  0.3704f,  2.9964f,  16.8507f,  65.2843f,  0.0061f, 0}, {
	29,  0.5932f,  1.8344f,  1.8080f,  1.3586f,  0.3680f,  2.8959f,  15.6333f,  70.6800f,  0.0059f, 0}, {
	30,  0.5996f,  1.7763f,  2.0240f,  1.6598f,  0.3602f,  2.7665f,  15.5278f,  60.2830f,  0.0054f, 0}, {
	31,  0.6737f,  1.8457f,  2.6395f,  1.9413f,  0.3901f,  3.0289f,  19.0448f,  74.1674f,  0.0077f, 0}, {
	32,  0.6660f,  1.7662f,  2.8876f,  2.0510f,  0.3741f,  2.8390f,  17.2911f,  62.5149f,  0.0067f, 0}, {
	33,  0.6504f,  1.6706f,  2.9930f,  2.0018f,  0.3550f,  2.6169f,  15.1100f,  50.8113f,  0.0054f, 0}, {
	34,  0.6343f,  1.5698f,  3.0362f,  1.9607f,  0.3374f,  2.4000f,  13.1385f,  42.4344f,  0.0043f, 0}, {
	35,  0.6216f,  1.4943f,  3.0763f,  1.8642f,  0.3216f,  2.2338f,  11.7075f,  36.7639f,  0.0036f, 0}, {
	36,  0.6240f,  1.4352f,  3.0847f,  1.7511f,  0.3144f,  2.1394f,  10.6060f,  32.4403f,  0.0031f, 0}, {
	37,  1.0180f,  2.8882f,  3.5125f,  4.3375f,  0.4850f,  5.1504f,  26.1762f,  155.1291f, 0.0202f, 0}, {
	38,  1.0127f,  2.9403f,  3.9920f,  5.1441f,  0.4721f,  4.9802f,  26.8565f,  116.0307f, 0.0179f, 0}, {
	39,  0.9722f,  2.8705f,  4.1571f,  4.6466f,  0.4427f,  4.5552f,  24.0646f,  99.1688f,  0.0154f, 0}, {
	40,  0.9592f,  2.8531f,  4.1761f,  4.1491f,  0.4279f,  4.3237f,  22.1510f,  89.7694f,  0.0137f, 0}, {
	41,  0.9337f,  2.8218f,  3.9092f,  2.9880f,  0.4074f,  4.0572f,  19.4778f,  85.5042f,  0.0121f, 0}, {
	42,  0.9334f,  2.8581f,  3.8278f,  2.6302f,  0.3996f,  3.9476f,  18.6153f,  82.5062f,  0.0112f, 0}, {
	43,  0.9282f,  2.8832f,  3.8985f,  3.1237f,  0.3894f,  3.8131f,  18.2715f,  74.4844f,  0.0107f, 0}, {
	44,  0.9175f,  2.8691f,  3.5480f,  2.2030f,  0.3776f,  3.6434f,  16.4538f,  74.4590f,  0.0097f, 0}, {
	45,  0.9046f,  2.8679f,  3.3997f,  2.0510f,  0.3646f,  3.4888f,  15.5106f,  71.3737f,  0.0088f, 0}, {
	46,  0.7832f,  2.1753f,  3.2003f,  1.4127f,  0.3094f,  2.5857f,   9.8481f,  37.4035f,  0.0044f, 0}, {
	47,  0.9085f,  2.9433f,  3.1021f,  1.7092f,  0.3541f,  3.3319f,  14.7723f,  70.5441f,  0.0085f, 0}, {
	48,  0.9056f,  2.9430f,  3.1814f,  2.1946f,  0.3466f,  3.2215f,  14.7749f,  62.3544f,  0.0081f, 0}, {
	49,  0.9660f,  3.1971f,  3.6243f,  2.6351f,  0.3648f,  3.4534f,  18.3358f,  75.8859f,  0.0111f, 0}, {
	50,  0.9481f,  3.1011f,  3.8863f,  2.9142f,  0.3518f,  3.2474f,  17.4348f,  66.0384f,  0.0099f, 0}, {
	51,  0.9323f,  2.9938f,  4.0829f,  2.9578f,  0.3405f,  3.0545f,  16.2843f,  56.5387f,  0.0084f, 0}, {
	52,  0.9060f,  2.8392f,  4.1639f,  3.0782f,  0.3256f,  2.8170f,  14.6041f,  48.0880f,  0.0071f, 0}, {
	53,  0.8912f,  2.7442f,  4.3316f,  2.9328f,  0.3150f,  2.6616f,  13.6958f,  43.2296f,  0.0064f, 0}, {
	54,  0.8749f,  2.6276f,  4.4112f,  2.8758f,  0.3046f,  2.4959f,  12.5908f,  38.5666f,  0.0054f, 0}, {
	55,  1.2968f,  3.8609f,  5.6613f,  5.6489f,  0.4462f,  4.3194f,  24.1136f,  168.3481f, 0.0301f, 0}, {
	56,  1.3111f,  3.9542f,  5.8693f,  7.0998f,  0.4432f,  4.3226f,  24.3857f,  128.5976f, 0.0285f, 0}, {
	57,  1.2872f,  3.8478f,  6.0581f,  6.5606f,  0.4283f,  4.0782f,  22.4363f,  109.8403f, 0.0251f, 0}, {
	58,  1.3019f,  3.8491f,  5.8568f,  6.3222f,  0.4256f,  4.0288f,  22.0020f,  107.6524f, 0.0244f, 0}, {
	59,  1.3354f,  3.8652f,  5.3000f,  6.4296f,  0.4305f,  4.0368f,  22.1273f,  117.0334f, 0.0259f, 0}, {
	60,  1.3473f,  3.8589f,  5.1226f,  6.2264f,  0.4266f,  3.9844f,  21.8395f,  114.8891f, 0.0247f, 0}, {
	61,  1.3631f,  3.8462f,  4.9578f,  6.0228f,  0.4253f,  3.9386f,  21.6330f,  112.8589f, 0.0243f, 0}, {
	62,  1.3702f,  3.8270f,  4.8068f,  5.8402f,  0.4204f,  3.8747f,  21.3840f,  110.9527f, 0.0238f, 0}, {
	63,  1.3963f,  3.8201f,  4.6869f,  5.6321f,  0.4230f,  3.8621f,  21.4604f,  110.3872f, 0.0234f, 0}, {
	64,  1.3784f,  3.7349f,  4.8549f,  5.2564f,  0.4105f,  3.7014f,  20.2877f,   96.0364f, 0.0205f, 0}, {
	65,  1.4257f,  3.7865f,  4.4336f,  5.2698f,  0.4182f,  3.7931f,  21.3185f,  107.6330f, 0.0233f, 0}, {
	66,  1.4104f,  3.6934f,  4.3012f,  5.1904f,  0.4076f,  3.6339f,  20.3594f,  103.6978f, 0.0213f, 0}, {
	67,  1.3805f,  3.5395f,  4.4117f,  5.0148f,  0.3938f,  3.4131f,  18.4989f,  86.9074f,  0.0171f, 0}, {
	68,  1.4391f,  3.6351f,  4.0572f,  4.9059f,  0.4038f,  3.5707f,  20.0727f,  100.4842f, 0.0202f, 0}, {
	69,  1.4561f,  3.6041f,  3.9360f,  4.7711f,  0.4028f,  3.5468f,  19.9521f,  98.6682f,  0.0197f, 0}, {
	70,  1.4617f,  3.5735f,  3.8563f,  4.6254f,  0.3986f,  3.4988f,  19.9050f,  97.9782f,  0.0192f, 0}, {
	71,  1.4381f,  3.4689f,  4.0824f,  4.4599f,  0.3874f,  3.3304f,  18.8077f,  84.5078f,  0.0169f, 0}, {
	72,  1.4209f,  3.3984f,  4.2315f,  4.1000f,  0.3772f,  3.2109f,  17.7720f,  76.0916f,  0.0153f, 0}, {
	73,  1.4163f,  3.3456f,  4.3281f,  3.7406f,  0.3714f,  3.1289f,  16.8719f,  70.3632f,  0.0141f, 0}, {
	74,  1.4109f,  3.2997f,  4.3698f,  3.4408f,  0.3653f,  3.0517f,  15.9630f,  65.7545f,  0.0131f, 0}, {
	75,  1.3898f,  3.2373f,  4.3683f,  3.2472f,  0.3548f,  2.9382f,  14.8500f,  60.6048f,  0.0117f, 0}, {
	76,  1.3877f,  3.2082f,  4.3731f,  2.9958f,  0.3502f,  2.8796f,  14.1535f,  57.3692f,  0.0110f, 0}, {
	77,  1.3783f,  3.1637f,  4.3549f,  2.8050f,  0.3440f,  2.7975f,  13.3640f,  54.3356f,  0.0101f, 0}, {
	78,  1.3489f,  3.0674f,  4.2095f,  2.1738f,  0.3322f,  2.6601f,  12.0128f,  50.3882f,  0.0091f, 0}, {
	79,  1.3413f,  3.0559f,  4.1659f,  2.0022f,  0.3262f,  2.6076f,  11.5043f,  48.4954f,  0.0084f, 0}, {
	80,  1.3592f,  3.1327f,  4.1897f,  2.2748f,  0.3265f,  2.6458f,  11.6919f,  47.9347f,  0.0084f, 0}, {
	81,  1.4735f,  3.6368f,  4.3950f,  2.5803f,  0.3500f,  3.0849f,  14.9338f,  65.0072f,  0.0121f, 0}, {
	82,  1.4700f,  3.6387f,  4.5674f,  2.9103f,  0.3452f,  3.0340f,  14.8562f,  60.2174f,  0.0117f, 0}, {
	83,  1.4616f,  3.6426f,  4.7876f,  3.1935f,  0.3396f,  2.9739f,  14.8388f,  56.7362f,  0.0113f, 0}, {
	84,  1.4255f,  3.5214f,  4.9058f,  3.4925f,  0.3274f,  2.8031f,  13.8305f,  50.1382f,  0.0100f, 0}, {
	85,  1.4170f,  3.4829f,  5.0951f,  3.4639f,  0.3224f,  2.7289f,  13.4904f,  46.2094f,  0.0089f, 0}, {
	86,  1.4001f,  3.4082f,  5.2516f,  3.4250f,  0.3153f,  2.6261f,  12.9003f,  42.3929f,  0.0083f, 0}, {
	87,  1.7697f,  4.6820f,  6.6701f,  5.5268f,  0.3969f,  3.9950f,  23.0274f,  154.8886f, 0.0316f, 0}, {
	88,  1.7704f,  4.6854f,  6.8034f,  7.2352f,  0.3938f,  3.9313f,  22.4168f,  120.9717f, 0.0300f, 0}, {
	89,  1.7346f,  4.5959f,  7.0436f,  7.0521f,  0.3816f,  3.7454f,  21.1330f,  102.1159f, 0.0267f, 0}, {
	90,  1.7012f,  4.5007f,  7.2504f,  6.6077f,  0.3704f,  3.5712f,  19.8632f,  89.3562f,  0.0238f, 0}, {
	91,  1.7266f,  4.6123f,  6.7855f,  6.3876f,  0.3729f,  3.6159f,  19.6433f,  95.2720f,  0.0248f, 0}, {
	92,  1.7417f,  4.7063f,  6.6509f,  5.9929f,  0.3729f,  3.6337f,  19.6579f,  95.0805f,  0.0246f, 0}, {
	93,  1.7327f,  4.6782f,  6.4465f,  5.8528f,  0.3683f,  3.5375f,  18.8556f,  91.5521f,  0.0240f, 0}, {
	94,  1.7491f,  4.7933f,  5.9841f,  5.6139f,  0.3683f,  3.5651f,  18.8727f,  100.8062f, 0.0246f, 0}, {
	95,  1.7519f,  4.8096f,  5.8155f,  5.4119f,  0.3654f,  3.5215f,  18.5120f,  98.8221f,  0.0241f, 0}, {
	96,  1.7284f,  4.7162f,  5.9338f,  5.2896f,  0.3577f,  3.3776f,  17.7168f,  86.4936f,  0.0217f, 0}, {
	97,  1.7298f,  4.7198f,  5.7527f,  5.1576f,  0.3554f,  3.3269f,  17.3659f,  84.3294f,  0.0211f, 0}, {
	98,  1.6401f,  4.3905f,  5.4504f,  5.4542f,  0.3332f,  2.9830f,  14.6892f,  73.0723f,  0.0258f, 0}};



class Crystal
{
protected:
public:
	double Mm[3][3];
	double MmInv[3][3];
	double  ax, by, cz;
	double alpha, beta, gamma;
	double unitCellVolume;

	int nAtoms;
	atom *atoms;
	int Znums[NZMAX];
	char *fileName;
	int errorFlag;

	/*
	Crystal( void );
	Crystal( char *fn ); // create the crystal and load the data right away.
	int getZNumber( char *element );
	void SetFileName( const char *fn );
	int readNextCFGAtom( atom *newAtom, int flag );
	void inverse_3x3( double *res, const double *a );
	int ReadCFGCellParams( void );
	void Load( void );
	void Print( void );
	complex_type ComputeStructureFactor( Reflection *g, ftype energy_kV );
	void ComputeGVector( Reflection& g );
	ftype GetS2( Reflection& g );
	void GetBeamLength2( int h, int k, int l, int s, Reflection& g );
	ftype ComputeScatteringFactor( ftype gLen, int Znum );
	~Crystal( void );
	*/

	Crystal( void )
	{
		errorFlag = 0;
		atoms = NULL;
		nAtoms = 0;
		fileName = NULL;
		// memset(&Mm[0][0],0,9*sizeof(double));
		// memset(&MmInv[0][0],0,9*sizeof(double));
        std::memset( Znums, 0, NZMAX * sizeof( int ) );
	}

	Crystal( std::string const& fn )
	{
		errorFlag = 0;
		atoms = NULL;
		nAtoms = 0;
		fileName = NULL;
		memset( Znums, 0, NZMAX * sizeof( int ) );
		SetFileName( fn.c_str() );
		Load();
	}

	Crystal( char *fn )
	{
		errorFlag = 0;
		atoms = NULL;
		nAtoms = 0;
		fileName = NULL;
		memset( Znums, 0, NZMAX * sizeof( int ) );
		SetFileName( fn );
		Load();
	}

	void  SetFileName( const char *fn )
	{
		fileName = ( char * )malloc( strlen( fn ) + 2 );
		//strcpy_s( fileName, strlen( fn ) + 1, fn );
		unsigned long fs = std::strlen( fn );
		std::fill( fileName, fileName+fs+2, 0 );
		std::copy( fn, fn+fs, fileName );

	}


	// This function determines the Z-numbewr from the string defining the element (e..g. 'Si' -> 14).
	int  getZNumber( char *element )
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
	void  inverse_3x3( double *res, const double *a )
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
	int  ReadCFGCellParams( void )
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

	int  readNextCFGAtom( atom *newAtom, int flag )
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


	void  Print( void )
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
	void  Load( void )
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
	void  ComputeGVector( Reflection& g )
	{
		g.gx = ( ftype )( MmInv[0][0] * g.mh + MmInv[0][1] * g.mk + MmInv[0][2] * g.ml );
		g.gy = ( ftype )( MmInv[1][0] * g.mh + MmInv[1][1] * g.mk + MmInv[1][2] * g.ml );
		g.gz = ( ftype )( MmInv[2][0] * g.mh + MmInv[2][1] * g.mk + MmInv[2][2] * g.ml );
	}

	// This function only assigns the g-vector from the (h,k,l,s)-indices
	ftype  GetS2( Reflection& g )
	{
		ComputeGVector(g);
		return 0.25 * ( g.gx * g.gx + g.gy * g.gy + g.gz * g.gz );
	}


	// This function only assigns the g-vector from the (h,k,l,s)-indices
	void  GetBeamLength2( int h, int k, int l, int s, Reflection& g )
	{
		// g.h = h; g.k = k; g.l = l;
		g.mh = ( s & 4) ? h : -h;
		g.mk = ( s & 2) ? k : -k;
		g.ml = ( s & 1) ? l : -l;
		ComputeGVector(g);
	}


	// ComputeStructureFactor:
	// Input: pointer to reflection g and beam energy in kV
#define ONE_PI 3.141592653589793
#define TWO_PI 6.283185307179586
#define V_SCALE 47.878009
	complex_type  ComputeStructureFactor( Reflection *g, ftype energy_kV )
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
		// if (g->mh == 0) printf("\n"); {g->PrintReflection(); printf("ug = %.f, %.f, \n",ug.real(),ug.imag());} 
		// multiply by gamma = (1+energy/restEnergy) and divide by unit cell volume
		// Spence and Zuo book, page 33:
		// ug *= ( 1 + energy_kV / 511 ) * ( ftype )exp( -s2 * atoms[i].dw ) / ( unitCellVolume * ONE_PI ); // unit is A^-2
		ug *= ( 1 + energy_kV / 511 )  / ( unitCellVolume * ONE_PI ); // unit is A^-2
		return ug;
	}

	ftype  ComputeScatteringFactor( ftype s2, int Znum )
	{
		// This function must compute the scattering factor for the atom of type Znum:
		ftype f = 0.0f;
		for ( int i = 1; i < 5; i++ )
		{
			f += pengfacts[Znum][i] * ( ftype )exp( -pengfacts[Znum][i + 4] * s2 );
		}
		// must still be multiplied by (1+E/E0) = (1+E/511)
		return f;
	}

	~Crystal( void )
	{
		if ( atoms != NULL ) free( atoms );
		atoms = NULL;
		nAtoms = 0;
	}



};

#endif//_CRYSTAL_H_INCLUDED_DFSOPINASDFLKNSADFLKJNSDAFALKJNASDFLKJNSDFKJFDSIAUHF

