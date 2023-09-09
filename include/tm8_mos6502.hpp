#ifndef TM8_MOS6502_H
#define TM8_MOS6502_H

#include <cstdint>
#include <array>
#include <iostream>

namespace tm8{

    class mos6502{
        uint8_t A;
        uint8_t X;
        uint8_t Y;
    };
}

#endif
