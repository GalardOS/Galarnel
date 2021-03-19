#pragma once 

namespace drv {
    namespace bcm2835auxuart {
        void init();
        char recv();
        void send(char c);
        void send_string(const char* str);
    }
}