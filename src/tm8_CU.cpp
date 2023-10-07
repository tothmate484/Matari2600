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
