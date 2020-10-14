#pragma once

#include "klib/func.hh"

namespace cpu {
    namespace excp {
        struct vector_table {
            kstd::func<void(void)> sync_excpt;
            kstd::func<void(void)> irq_excpt;
            kstd::func<void(void)> fiq_excpt;
            kstd::func<void(void)> err_excpt;
        };

        void setup_vector(const vector_table& vt);
    }
}