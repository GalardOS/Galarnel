#pragma once

namespace pal { namespace debug {
    void initialize();

    void write(const char* message);
    void write_line(const char* message);
} }