#include "include/tm8_mos6502.hpp"

void tm8::mos6502::fetch(){
    if(cycles == 0){
        instruction = bus[PC];
        operand1 = bus[PC+1];
        operand2 = bus[PC+2];

        inst_a = instruction & 0b11100000; //parts of the instruction: see instruction layout
        inst_a >>= 5;

        inst_b = instruction & 0b000111000;
        inst_b >>= 2;

        inst_c = instruction & 0b00000011;
    }

    return;
}

void tm8::mos6502::decode(){

}

void tm8::mos6502::execute(){

}

//addressing mode definitions

void tm8::mos6502::impl(){
    address_bus = 0xFFFF;
    PC++;

    return; 
}

void tm8::mos6502::imm(){
    address_bus = static_cast<uint16_t>(PC+1);
    PC += 2;

    return;
}
void tm8::mos6502::abs(){
    address_bus = createaddress(PC+1, PC+2, 0);
    PC += 3;

    return;
}
void tm8::mos6502::abs_X(){
    address_bus = createaddress(PC+1, PC+2, X);
    PC += 2;

    return;
}

void tm8::mos6502::abs_Y(){
    address_bus = createaddress(PC+1, PC+2, Y);
    PC += 2;

    return;
}

void tm8::mos6502::zpg(){
    address_bus = static_cast<uint8_t>(createaddress(PC+1, 0, 0));
    PC++;

    return;
}

void tm8::mos6502::zpg_X(){
    address_bus = static_cast<uint8_t>(createaddress(PC+1, 0, X)); //if it's bigger than 255 it has to be cut down to 8 bits 
    PC++;

    return;
}

void tm8::mos6502::zpg_Y(){
    address_bus = static_cast<uint8_t>(createaddress(PC+1, 0, Y));
    PC++;

    return;
}

void tm8::mos6502::ind(){
    uint16_t preaddress = createaddress(PC+1, PC+2, 0);
    
}

void Acc(); //target: accumulator
void X_ind(); //pre-X-indexed indirect
void Y_ind(); //pre-Y-indexed indirect
void rel(); //relative for conditional jumps
