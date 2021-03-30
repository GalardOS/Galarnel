#pragma once

#include "libsteel/common.hh"

namespace heap {
    void __initialize();

    void* allocate(uint32 size);
    void deallocate(void* ptr);
}