#ifndef _TILE_WIDTH_HPP_INCLUDED_DOSPINASFDLKJNDSFIOUJN4EOIUAJNFSDLKJNDFKJASNFJF
#define _TILE_WIDTH_HPP_INCLUDED_DOSPINASFDLKJNDSFIOUJN4EOIUAJNFSDLKJNDFKJASNFJF

#include <device/typedef.hpp>

#include <device/config/threads_per_block.hpp>
#include <device/utility/sqrt.hpp>

namespace device
{

    struct tile_width
    {
        static const device::size_t value = device::sqrt_<device::threads_per_block::value>::value;
    };//struct tile_width 

}//namespace device

#endif//_TILE_WIDTH_HPP_INCLUDED_DOSPINASFDLKJNDSFIOUJN4EOIUAJNFSDLKJNDFKJASNFJF

