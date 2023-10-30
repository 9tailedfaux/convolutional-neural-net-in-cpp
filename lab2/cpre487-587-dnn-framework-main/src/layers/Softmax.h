#pragma once


#include "../Types.h"

namespace ML {
    

    void softMax(Array1D_fp32 input, size_t size);
    void softMax(Array1D_ui8 input, size_t size);
    
}