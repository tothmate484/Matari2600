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
    address_bus = address;
    
    return;
}

void tm8::mos6502::LDX(const uint8_t value){
    X = value;
    setflags(X);

    return;
}

void tm8::mos6502::STX(const uint16_t address){
    bus[address] = X;
    address_bus = address;
    
    return;
}

void tm8::mos6502::LDY(const uint8_t value){
    Y = value;
    setflags(Y);

    return;
}

void tm8::mos6502::STY(const uint16_t address){
    bus[address] = Y;
    address_bus = address;
    
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
    push(static_cast<uint8_t> (SR.to_ulong()));
    
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
    uint16_t sum = A + value + static_cast<uint16_t>(SR[C]);
    bool msb1 = extractbit(A, 7);       //The signed overflow flag (V) depends on the most significant bits
    bool msb2 = extractbit(value, 7);
    bool msb3 = extractbit(static_cast<uint8_t>(sum), 7);

    A = setflags(sum);
    SR[V] = (msb1 && msb2 && !msb3);

    return;
}

void tm8::mos6502::SBC(const uint8_t value){
    uint16_t sum = A - value - static_cast<uint16_t>(!static_cast<bool>(SR[C]));
    bool msb1 = extractbit(A, 7);
    bool msb2 = extractbit(value, 7);
    bool msb3 = extractbit(static_cast<uint8_t>(sum), 7);

    A = setflags(sum);
    SR[V] = (msb1 && msb2 && !msb3);

    return;
}

void tm8::mos6502::AND(const uint8_t value){
    A = A & value;

    setflags(A);
    return;
}

void tm8::mos6502::ORA(const uint8_t value){
    A = A | value;

    setflags(A);
    return;
}

void tm8::mos6502::EOR(const uint8_t value){
    A = A^value;

    setflags(A);
    return;
}

void tm8::mos6502::ASL(uint8_t & value){
    uint16_t outcome = value;
    outcome <<= 1;

    value = setflags(A);
    return;
}

void tm8::mos6502::LSR(uint8_t & value){
    SR[C] = extractbit(value, 0);

    value >>= 1;

    SR[N] = 0;
    SR[Z] = (value == 0);

    return;
}

void tm8::mos6502::ROL(uint8_t& value){
    bool carry = extractbit(value, 7);
    value <<= 1;
    value += static_cast<uint8_t>(carry);

    setflags(value);
    SR[C] = carry;

    return; 
}
        
void tm8::mos6502::ROR(uint8_t& value){
    bool carry = extractbit(value, 0);
    value >>= 1;
    value += 128*static_cast<uint8_t>(carry);

    setflags(value);
    SR[C] = carry;

    return; 
}

void tm8::mos6502::CMP(const uint8_t value){
    uint8_t difference = A - value;

    if(A < value){
        SR[Z] = 0;
        SR[C] = 0;
        SR[N] = extractbit(difference, 7);
    }
    else if(A == value){
        SR[Z] = 1;
        SR[C] = 1;
        SR[N] = 0;
    }
    else if(A > value){
        SR[Z] = 0;
        SR[C] = 1;
        SR[N] = extractbit(difference, 7);
    }

    return;
}

void tm8::mos6502::CPX(const uint8_t value){
    uint8_t difference = X - value;

    if(X < value){
        SR[Z] = 0;
        SR[C] = 0;
        SR[N] = extractbit(difference, 7);
    }
    else if(X == value){
        SR[Z] = 1;
        SR[C] = 1;
        SR[N] = 0;
    }
    else if(X > value){
        SR[Z] = 0;
        SR[C] = 1;
        SR[N] = extractbit(difference, 7);
    }

    return;
}
void tm8::mos6502::CPY(const uint8_t value){
    uint8_t difference = Y - value;

    if(Y < value){
        SR[Z] = 0;
        SR[C] = 0;
        SR[N] = extractbit(difference, 7);
    }
    else if(Y == value){
        SR[Z] = 1;
        SR[C] = 1;
        SR[N] = 0;
    }
    else if(Y > value){
        SR[Z] = 0;
        SR[C] = 1;
        SR[N] = extractbit(difference, 7);
    }

    return;
}

void tm8::mos6502::BCC(const uint8_t value){
    if(!SR[C]){
        PC += static_cast<int8_t>(value);
    }
}

void tm8::mos6502::BCS(const uint8_t value){
    if(SR[C]){
        PC += static_cast<int8_t>(value);
    }
}

void tm8::mos6502::BEQ(const uint8_t value){
    if(SR[Z]){
       PC += static_cast<int8_t>(value);
    }
}

void tm8::mos6502::BNE(const uint8_t value){
    if(!SR[Z]){
        PC += static_cast<int8_t>(value);
    }
}

void tm8::mos6502::BMI(const uint8_t value){
    if(SR[N]){
        PC += static_cast<int8_t>(value);
    }
}

void tm8::mos6502::BPL(const uint8_t value){
    if(!SR[N]){
        PC += static_cast<int8_t>(value);
    }
}

void tm8::mos6502::BVC(const uint8_t value){
    if(!SR[V]){
        PC += static_cast<int8_t>(value);
    }
}

void tm8::mos6502::BVS(const uint8_t value){
    if(SR[V]){
        PC += static_cast<int8_t>(value);
    }
}

void tm8::mos6502::JMP(const uint16_t address){
    PC = address;
}

void tm8::mos6502::JSR(const uint16_t address){
    uint16_t PC_old = PC - 3; //the instruction decode will automatically increase the PC by 3, as every absolute instruction uses 3 bytes, but I need the address of the instruction itself 
    uint16_t topush = PC; //I will fracture the 16 bit address into 2 8 bit parts, I need to cpoy the original one not to destroy it
    push(static_cast<uint8_t>(topush)); //pushes low byte of the address into the stack
    topush >>= 8; //pushes the high byte in place of the low btye, so casting to 8 bits will return it
    push(static_cast<uint8_t>(topush)); //pushes the original hifh byte into the stack

    PC = createaddress(bus[PC_old + 1] , bus[PC_old + 2], 0); //modifies the PC to the absolute address of the subroutine

    return;
}

void tm8::mos6502::RTS(void){
    uint8_t hb = pop();
    uint8_t lb = pop();

    PC = createaddress(lb, hb, 0);

    return;
}

void tm8::mos6502::BRK(void){
    return; //irrelevant for the working of the program, may be intplemented in the future
}

void tm8::mos6502::RTI(void){
    return; //same as BRK
}

void tm8::mos6502::BIT(const uint8_t value){
    SR[N] = extractbit(value, 7); //0b10000000 = bit 7
    SR[V] = extractbit(value, 6); //0b01000000 = bit 6
    SR[Z] = !(value & A);

    return;
}

void tm8::mos6502::NOP(void){
    return; //just a syntax placeholder
}