#include "include/tm8_mos6502.hpp"

void tm8::mos6502::SEI(void){
    SR.I = true;

    return;
}

void tm8::mos6502::CLI(void){
    SR.I = false;

    return;
}