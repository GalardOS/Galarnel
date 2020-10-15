#pragma once

#include "klib/func.hh"

namespace cpu {
    namespace excp {
        struct vector_table {
            kstd::func<void(long)> sync_excpt;
            kstd::func<void(long)> irq_excpt;
            kstd::func<void(long)> fiq_excpt;
            kstd::func<void(long)> err_excpt;
        };

        void setup_vector(const vector_table& vt);
    }
}