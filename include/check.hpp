#pragma once

#include <cstdlib>
#include <iostream>

inline void check(bool ok, const char* message) {
    if (!ok) {
        std::cerr << "FAIL: " << message << '\n';
        std::exit(1);
    }
}
