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

void tm8::mos6502::LDA(const uint8_t value){
    A = value;
    setflags(A);

    return;
}

void tm8::mos6502::STA(const uint16_t address){
    bus[address] = A;
    trigger = address;
    
    return;
}

void tm8::mos6502::LDX(const uint8_t value){
    X = value;
    setflags(X);

    return;
}

void tm8::mos6502::STX(const uint16_t address){
    bus[address] = X;
    trigger = address;
    
    return;
}

void tm8::mos6502::LDY(const uint8_t value){
    Y = value;
    setflags(Y);

    return;
}

void tm8::mos6502::STY(const uint16_t address){
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

void tm8::mos6502::PHP(void){
    SR[i] = 1;
    SR[B] = 1;
    push((uint8_t) SR.to_ulong());
    
    return;
}

void tm8::mos6502::PLP(void){
    SR = pop();
    
    return;
}

void tm8::mos6502::INX(void){
    X++;
    setflags(X);
    
    return;
}

void tm8::mos6502::INY(void){
    Y++;
    setflags(Y);
    
    return;
}

void tm8::mos6502::DEY(void){
    Y--;
    setflags(Y);
    
    return;
}

void tm8::mos6502::DEX(void){
    X--;
    setflags(X);
    
    return;
}

void tm8::mos6502::INC(const uint16_t address){
    bus[address]++;
    setflags(bus[address]);

    return;
}

void tm8::mos6502::DEC(const uint16_t address){
    bus[address]--;
    setflags(bus[address]);

    return;
}

void tm8::mos6502::ADC(const uint8_t value){
    uint16_t sum = A + value + (uint16_t)SR[C];
    bool msb1 = A & 128;                        //The signed overflow flag (V) depends on the most significant bits
    bool msb2 = value & 128;
    bool msb3 = sum + 128;

    A = setflags(sum);
    SR[V] = (msb1 && msb2 && !msb3);

    return;
}

void tm8::mos6502::SBC(const uint8_t value){
    uint16_t sum = A - value - (uint16_t)!(bool)SR[C];
    bool msb1 = A & 128;
    bool msb2 = value & 128;
    bool msb3 = sum + 128;

    A = setflags(sum);
    SR[V] = (msb1 && msb2 && !msb3);

    return;
}



