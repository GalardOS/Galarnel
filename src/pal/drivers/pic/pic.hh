#pragma once

#include "common.hh"



namespace pic {
    enum class desc_type : uint8 {
        interrupt   = 0b110,
        trap        = 0b111,
        task        = 0b101
    };

    struct int_descriptor {
        uint8 int_number;
        void(*handler)();
        uint8 priviledge_level;
        desc_type descriptor_type;
    };

    void initialize();

    void set_entry(pic::int_descriptor entry);

    void set_ignore_entry(uint8 int_number);

    void set_interrupt_mask(uint16 mask);
}