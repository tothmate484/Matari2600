#include "include/tm8_mos6502.hpp"

void tm8::mos6502::fetch(){
    if(cycles == 0){
        instruction = bus[PC];
        operand1 = bus[PC+1];
        operand2 = bus[PC+2];

        inst_a = instruction & 0b11100000; //parts of the instruction: see instruction layout
        inst_a >>= 5;

        inst_b = instruction & 0b00011100;
        inst_b >>= 2;

        inst_c = instruction & 0b00000011;
    }

    return;
}

void tm8::mos6502::decode(){ //timing not included at the moment
    switch (inst_b)
    {
    case 1:
        zpg();

        std::cout << "zpg\t"; 
    break;

    case 3:
        abs();

        std::cout << "abs\t";
    break;

    case 5:
        if(inst_c != 2){
            zpg_X();
            std::cout << "zpg_X\t";
        }
        else{
            if(inst_a == 4 || inst_a == 5){
                zpg_Y();

                std::cout << "zpg_Y\t";
            }
            else{
                zpg_X();

                std::cout << "zpg_X\t";
            }
        }
    break;

    case 7:
        if(inst_a != 5){
            abs_X();

            std::cout << "abs_X\t";
        }
        else{
            abs_Y();

            std::cout << "abs_Y\t";
        }
    break;

    case 4:
        if(inst_c == 0){
            rel();

            std::cout << "rel\t";
        }
        else if(inst_c == 1){
            ind_Y();

            std::cout << "ind_Y\t";
        }
    break;

    case 6:
        if(inst_c == 1){
            abs_Y();

            std::cout << "abs_Y\t";
        }
        else{
            impl();

            std::cout << "impl\t";
        }
    break;

    case 2:
        if(inst_c == 0){
            impl();

            std::cout << "impl\t";
        }
        else if(inst_c == 1){
            imm();

            std::cout << "imm\t";
        }
        else if(inst_c == 2){
            if(inst_a <= 3){
                acc();

                std::cout << "acc\t";
            }
            else{ //if(inst_a >= 4)
                impl();

                std::cout << "impl\t";
            }
        }
    break;

    case 0:
        if(inst_c == 1){
            X_ind();

            std::cout << "X_ind\t";
        }
        else if(inst_c == 2){
            imm();

            std::cout << "imm\t";
        }
        else if(inst_c == 0){
            if(inst_a >= 4){
                imm();

                std::cout << "abs\t";
            }
            else if(inst_a == 1){
                abs();

                std::cout << "abs\t";
            }
            else{
                impl();

                std::cout << "impl\t";
            }
        }
    break;

    default:
        break;

        std::cout << "unknown addressing mode\t";
    }
}

void tm8::mos6502::execute(){
    
}

//addressing mode implementations
//faulty, uses address instead of value

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
    address_bus = createaddress(operand1, operand2, 0);
    PC += 3;

    return;
}
void tm8::mos6502::abs_X(){
    address_bus = createaddress(operand1, operand2, X);
    PC += 2;

    return;
}

void tm8::mos6502::abs_Y(){
    address_bus = createaddress(operand1, operand2, Y);
    PC += 2;

    return;
}

void tm8::mos6502::zpg(){
    address_bus = static_cast<uint8_t>(createaddress(operand1, 0, 0));
    PC++;

    return;
}

void tm8::mos6502::zpg_X(){
    address_bus = static_cast<uint8_t>(createaddress(operand1, 0, X)); //if it's bigger than 255 it has to be cut down to 8 bits 
    PC++;

    return;
}

void tm8::mos6502::zpg_Y(){
    address_bus = static_cast<uint8_t>(createaddress(operand1, 0, Y));
    PC++;

    return;
}

void tm8::mos6502::ind(){
    uint16_t tmp_address = createaddress(operand1, operand2, 0);

    address_bus = createaddress(bus[tmp_address], bus[tmp_address+1], 0);

    PC += 3;   
}

void tm8::mos6502::acc(){ //target: accumulator
    address_bus = 0xFFFF;
    PC++;

    return;
}

void tm8::mos6502::X_ind(){ //pre-X-indexed indirect
    uint16_t tmp_address = createaddress(operand1, 0, X);

    address_bus = createaddress(bus[tmp_address], bus[tmp_address+1], 0);

    PC += 2;
}

void tm8::mos6502::ind_Y(){ //post-Y-indexed indirect
    uint16_t tmp_address = createaddress(operand1, 0, 0);

    address_bus = createaddress(bus[tmp_address], bus[tmp_address+1], Y);

    PC += 2;
}

void tm8::mos6502::rel(){ //relative for conditional jumps
    address_bus = 0x1FFF;
    rel_address = operand1;

    PC+= 2;
}
