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
    address_bus = 0xFFFF;
    fetch();
    decode();

    switch (inst_c)
    {
    case 1:
        switch (inst_a)
        {
            case 0:
                ORA(0);

                std::cout << "\tORA\t";
            break;

            case 1:
                AND(0);

                std::cout << "\tAND\t";
            break;

            case 2:
                EOR(0);

                std::cout << "\tORA\t";
            break;

            case 3:
                ADC(0);

                std::cout << "\tADC\t";
            break;

            case 4:
                STA(bus[0]);

                std::cout << "\tSTA\t";
            break;

            case 5:
                LDA(0);

                std::cout << "\tLDA\t";
            break;

            case 6:
                CMP(0);

                std::cout << "\tCMP\t";
            break;

            case 7:
                SBC(0);

                std::cout << "\tORA\t";
            break;
        
            default:
            break;
        }
    break;
    
    case 2:
        switch (inst_a)
        {
            case 0:
                ASL(bus[0]); //ACC

                std::cout << "\tASL\t";
            break;

            case 1:
                ROL(bus[0]); //ACC

                std::cout << "\tROL\t";
            break;

            case 2:
                LSR(bus[0]); //ACC

                std::cout << "\tLSR\t";
            break;

            case 3:
                ROR(bus[0]); //ACC

                std::cout << "\tROR\t";
            break;

            case 4:
                if(inst_b == 2){
                    TXA();

                    std::cout << "\tTXA\t";
                }
                else if(inst_b == 6){
                    TXS();

                    std::cout << "\tTXS\t";
                }
                else{
                    STX(0);

                    std::cout << "\tSTX\t";
                }
            break;

            case 5:
                if(inst_b == 2){
                    TAX();

                    std::cout << "\tTAX\t";
                }
                else if (inst_b == 6){
                    TSX();

                    std::cout << "\tTSX\t";
                }
                else{
                    LDX(0);

                    std::cout << "\tDX\t";
                }
            break;

            case 6:
                if(inst_b == 2){
                    DEX();

                    std::cout << "\tDEX\t";
                }else{
                    DEC(bus[0]);

                    std::cout << "\tDEC\t";
                }
            break;

            case 7:
                if(inst_b == 2){
                    NOP();

                    std::cout << "\tNOP\t";
                }
                else{
                    INC(0);

                    std::cout << "\tINC\t";
                }
            break;

            default:
            break;
        }
    break;

    case 0:
        switch (inst_a)
        {
            case 0:
                if(inst_b == 0){
                    BRK();

                    std::cout << "\tBRK\t";
                }
                else if(inst_b == 2){
                    PHP();

                    std::cout << "\tPHP\t";
                }
                else if(inst_b == 4){
                    BPL(0);

                    std::cout << "\tBPL\t";
                }
                else if(inst_b == 6){
                    CLC();

                    std::cout << "\tCLC\t";
                }
            break;
                
            case 1:
                if(inst_b == 0){
                    JSR(0);

                    std::cout << "\tJSR\t";
                }
                else if(inst_b == 1){
                    BIT(0);

                    std::cout << "\tBIT\t";
                }
                else if(inst_b == 2){
                    PLP();

                    std::cout << "\tPLP\t";
                }
                else if(inst_b == 3){
                    BIT(0);

                    std::cout << "\tBIT\t";
                }
                else if(inst_b == 4){
                    BMI(0);

                    std::cout << "\tBMI\t";
                }
                else if(inst_b == 6){
                    SEC();

                    std::cout << "\tSEC\t";
                }
            break;
        
            default:
            break;
        }
    break;

    default:
        break;
    }
}

//addressing mode implementations
//missing length determination

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
