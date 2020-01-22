#include <f/matrix/matrix.hpp>

#include <cstdint>
#include <vector>
#include <cassert>

#define cimg_display 0
#define cimg_use_tiff

#include "../../include/3rdparty/CImg.h"


bool tiff_load_from( char const* path, std::vector<f::matrix<std::uint16_t>>& tiff_data  )
{
    tiff_data.clear();


    auto tiff_file = TinyTIFFReader_open( path );
    if ( !tiff_file ) return false;

    tiff_data.resize( TinyTIFFReader_countFrames( tiff_file ) );

    if ( TinyTIFFReader_wasError(tiff_file) )
    {
        TinyTIFFReader_close( tiff_file );
        return false;
    }

    for ( auto& mat : tiff_data )
    {
        if ( !TinyTIFFReader_hasNext( tiff_file ) ) break;

        mat.resize( TinyTIFFReader_getHeight(tiff_file), TinyTIFFReader_getWidth(tiff_file) );

        TinyTIFFReader_getSampleData( tiff_file, reinterpret_cast<void*>(mat.data()), 0 );

        if ( TinyTIFFReader_wasError(tiff_file) )
        {
            TinyTIFFReader_close( tiff_file );
            return false;
        }
    }

    TinyTIFFReader_close( tiff_file );

    return true;
}

bool tiff_save_as( char const* path, std::vector<f::matrix<std::uint16_t>> const& tiff_data )
{
    if ( tiff_data.size() == 0 ) return;

    auto tif = TinyTIFFWriter_open( path, 16, tiff_data[0].col(), tiff_data[0].row() );
    assert( tif && "Failed to open TIFF target file to write." );

    for ( auto const& mat : tiff_data )
        TinyTIFFWriter_writeImage( tif, mat.data() );

    TinyTIFFWriter_close( tif );
}

