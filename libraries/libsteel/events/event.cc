#include "event.hh"

#include "../devices/mini_uart.hh"
 
enum class exception_type : uint64 {
    synchronous = 0,
    interrupt = 1,
    finterrupt = 2,
    serror = 3
};

void(*events[4])(steel::cpu_status);

extern "C" void exception_entry(uint64 type, uint64 esr, uint64 elr, uint64 sp, uint64 spsr) {
    steel::uart_send_string("entered an exception: ");

    steel::cpu_status status;
    status.pc = elr;
    status.sp = sp;
    status.spsr = spsr;

    // Call the event given by the user if it exists, if not,
    // do nothing
    if(events[type] != nullptr)
        events[type](status);
}

extern "C" void setup_vector_table();
extern "C" void set_cpu_status_and_eret(uint64 sp, uint64 pc, uint64 spsr);

namespace steel {
    void __event_initialize() {
        // Function that setups the vector table used by the cpu
        // to know where to jump in case of exceptions
        setup_vector_table();

        // In case that the event table has garbage values
        // that could lead to jumps to nowhere, add nullptr so
        // the exception entry can know if it needs to jump or 
        // not
        for(uint32 i = 0; i < 4; i++)
            events[i] = nullptr;
    }

    void event(exception_type type, event_handler handler) {
        auto index = static_cast<uint64>(type);
        events[index] = handler;
    }

    void return_from_event(const cpu_status& status) {
        set_cpu_status_and_eret(status.sp, status.pc, status.spsr);
    }
}