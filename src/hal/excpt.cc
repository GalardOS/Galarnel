#include "excpt.hh"

namespace cpu {
    namespace excp {

        void setup_vector(const vector_table& vt) {
            auto* sync_func = &vt.sync_excpt;
            auto* irq_func = &vt.irq_excpt;
            auto* fiq_func = &vt.fiq_excpt;
            auto* err_func = &vt.err_excpt;

            
        }

    }
}