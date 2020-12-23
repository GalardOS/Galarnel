#pragma once

#include "common.hh"

namespace pal { namespace cltimer { 

    void set_interval(uint32 interval);

    void reset();

    void set_handler(void(*handler)());

} }