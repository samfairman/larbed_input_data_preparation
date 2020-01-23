#ifndef _COMPLEX_VALUE_TYPE_TCC_INCLUDED_SDNOSAOIUJH498UHAFLKJHASDF9Y8UH4KLAFH94
#define _COMPLEX_VALUE_TYPE_TCC_INCLUDED_SDNOSAOIUJH498UHAFLKJHASDF9Y8UH4KLAFH94

namespace device
{

    template<typename T>
    struct complex_value_type
    {
        typedef T value_type;
    };

    template<typename T>
    struct complex_value_type<device::complex<T> >
    {
        typedef T value_type;
    };

}//namespace device

#endif//_COMPLEX_VALUE_TYPE_TCC_INCLUDED_SDNOSAOIUJH498UHAFLKJHASDF9Y8UH4KLAFH94 

