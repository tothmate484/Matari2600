#include "include/tm8_mos6502.hpp"

void tm8::mos6502::SEI(void){
    SR[I] = 1;

    return;
}

void tm8::mos6502::CLI(void){
    SR[I] = 0;

    return;
}

void tm8::mos6502::CLC(void){
    SR[C] = 0;

    return;
}

void tm8::mos6502::SEC(void){
    SR[C] = 1;

    return;
}

void tm8::mos6502::CLV(void){
    SR[V] = 0;

    return;
}

void tm8::mos6502::SED(void){
    SR[D] = 1;

    return;
}

void tm8::mos6502::CLD(void){
    SR[D] = 0;

    return;
}

void tm8::mos6502::LDA(uint8_t value){
    A = value;
    setflags(A);

    return;
}

void tm8::mos6502::STA(uint16_t address){
    bus[address] = A;
    trigger = address;
    
    return;
}

void tm8::mos6502::LDX(uint8_t value){
    X = value;
    setflags(X);

    return;
}

void tm8::mos6502::STX(uint16_t address){
    bus[address] = X;
    trigger = address;
    
    return;
}

void tm8::mos6502::LDY(uint8_t value){
    Y = value;
    setflags(Y);

    return;
}

void tm8::mos6502::STY(uint16_t address){
    bus[address] = Y;
    trigger = address;
    
    return;
}

void tm8::mos6502::TAX(void){
    X = A;
    setflags(X);
    
    return;
}

void tm8::mos6502::TXA(void){
    A = X;
    setflags(A);
    
    return;
}

void tm8::mos6502::TAY(void){
    Y = A;
    setflags(Y);
    
    return;
}

void tm8::mos6502::TYA(void){
    A = Y;
    setflags(Y);
    
    return;
}

void tm8::mos6502::TSX(void){
    X = SP;
    setflags(X);
    
    return;
}

void tm8::mos6502::TXS(void){
    SP = X;
    
    return;
}

void tm8::mos6502::PHA(void){
    push(A);
    
    return;
}

void tm8::mos6502::PLA(void){
    A = pop();
    setflags(A);
    
    return;
}

