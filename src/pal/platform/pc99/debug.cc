#include "pal/debug.hh"
#include "common.hh"

#define VIDEO_MAP ((unsigned short*) 0xb8000)

namespace pal { namespace debug {
    void initialize() {
        // If a message is already on the screen clear it
        for(uint32 i = 0; i < 200; i++) {
            VIDEO_MAP[i] = (VIDEO_MAP[i] & 0xFF00) | ' '; 
        }
    }

    void write(const char* message) {
        static uint32 cursor_pos = 0;
        for(uint32 i = 0; message[i] != '\0'; i++) {
            VIDEO_MAP[cursor_pos] = (VIDEO_MAP[cursor_pos] & 0xFF00) | message[i];
            cursor_pos++;
        }
    }

    void write_line(const char* message) {
        pal::debug::write(message);
        //pal::debug::write("\r\n");
    }
} }