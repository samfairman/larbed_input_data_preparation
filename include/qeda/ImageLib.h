#ifndef _AFPDSOIJELKJNASFLKJASNDF4IEUNAFLKDJNASFDLKJBAWNFDOIBU4ENASLKFJN4PU9HAFS
#define _AFPDSOIJELKJNASFLKJASNDF4IEUNAFLKDJNASFDLKJBAWNFDOIBU4ENASLKFJN4PU9HAFS

#include <qeda/DataTypes.h>
#define VERSION 1  // please update this number, if anything in the image header 
// format changes.

class ImageLib
{
    public:
        int headerSize;  // first byte of image will be size of image header (in bytes)
        // This is the size without the data and comment pointers!!!
        int paramSize;   // number of additional parameters
        int commentSize; // length of comment string
        int nx, ny;
        int complexFlag;
        int dataSize;    // size of one data element in bytes (e.g. complex double: 16)
        int version;     // The version flag will later help to find out how to
        // distinguish between images produced by different versions of stem
        double t;        // thickness
        double dx, dy;   // size of one pixel
        double *params;  // array for additional parameters
        char *comment;   // comment of prev. specified length

        ImageLib( int Nx, int Ny, ftype dxNew = 1.0f, ftype dyNew = 1.0f )
        {
            headerSize = 8 * sizeof( int ) + 3 * sizeof( double );
            params = NULL;
            paramSize = 0;
            nx = Nx;
            ny = Ny;
            version = VERSION;
            t = 0.0;
            dx = dxNew;
            dy = dyNew;
            complexFlag = 0;
            comment = NULL;
            commentSize = 0;
        }

        void WriteRealImage( void *pix, char *fileName, int dataSize, double thickness )
        {
            FILE *fp;
            if ( ( fp = fopen( fileName, "wb" ) ) == NULL )
            {
                printf( "writeRealImage: Could open file %s for writing\n", fileName );
                exit( 0 );
            }
            version = VERSION;
            complexFlag = 0;
            t = thickness;
            fwrite( ( void * )&headerSize, sizeof( int ), 1, fp );
            fwrite( ( void * )&paramSize, sizeof( int ), 1, fp );
            fwrite( ( void * )&commentSize, sizeof( int ), 1, fp );
            fwrite( ( void * )&nx, sizeof( int ), 1, fp );
            fwrite( ( void * )&ny, sizeof( int ), 1, fp );
            fwrite( ( void * )&complexFlag, sizeof( int ), 1, fp );
            fwrite( ( void * )&dataSize, sizeof( int ), 1, fp );
            fwrite( ( void * )&version, sizeof( int ), 1, fp );
            fwrite( ( void * )&t, sizeof( double ), 1, fp );
            fwrite( ( void * )&dx, sizeof( double ), 1, fp );
            fwrite( ( void * )&dy, sizeof( double ), 1, fp );
            // fwrite((void *)(header->params),sizeof(double),header->paramSize,fp);
            // fwrite((void *)(header->comment),1,commentSize,fp);
            if ( fwrite( ( void * )pix, dataSize, ( size_t )( nx * ny ), fp ) != nx * ny )
            {
                printf( "writeRealImage: Error while writing data to file %s\n", fileName );
                fclose( fp );
                exit( 0 );
            }
            fclose( fp );
        }


        ~ImageLib( void )
        {
        }
};

#endif//_AFPDSOIJELKJNASFLKJASNDF4IEUNAFLKDJNASFDLKJBAWNFDOIBU4ENASLKFJN4PU9HAFS

