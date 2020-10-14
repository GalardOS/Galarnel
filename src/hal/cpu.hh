#pragma once

namespace cpu {
    int get_thread_id();

    int get_el();
    
    void switch_to_usermode();
}