#ifndef TM8_MOS6502_H
#define TM8_MOS6502_H

#include <cstdint>
#include <iostream>
#include <vector>
#include <cmath>
#include <bitset>

namespace tm8{

    class mos6502{ //beginning of class
    private:
        uint8_t A;
        uint8_t X;
        uint8_t Y;
        
        uint8_t SP;
        uint16_t PC;

        enum flags{
            C, Z, I, D, B, i, V, N
        };

        std::bitset<8> SR;
        uint16_t adress_width; //13 by Atari, 16 by everyone else
        std::vector<uint8_t>& bus;
        uint16_t& trigger;

        mos6502(const uint8_t adress_width_in, std::vector<uint8_t>& bus_in, uint16_t& trigger_in, const uint16_t reset_vector) : bus(bus_in), trigger(trigger_in) {

            adress_width = pow(2.0, (long double)adress_width_in);

            trigger = 0xFFFF;

            PC = reset_vector;
            A = 0;
            X = 0;
            Y = 0;
        }

        uint16_t createadress(const uint8_t lb, const uint8_t hb, const uint8_t offset){ 
        uint16_t adress = hb;
        adress <<= 8;
        adress += lb;
        adress += offset;

        adress = (adress & adress_width);

        return adress;
        }

        uint8_t setflags(const uint16_t obj){
            if(obj > 255) SR[C] = 1 ;
            else SR[C] = 0;
            if(obj == 0) SR[Z] = 1;
            else SR[Z] = 0;
            if(obj >=128) SR[N] = 1;
            else SR[N] = 0;

            return static_cast<uint8_t> (obj);
        }

        void push(uint8_t data){
            bus[SP] = data;
            SP--;

            return;
        }

        uint8_t pop(void){
            SP++;
            
            return bus[SP];
        }

        //beginning of ALU function definitions

        void SEI(void);
        void CLI(void);
        void CLC(void);
        void SEC(void);
        void CLV(void);
        void SED(void);
        void CLD(void);

        void LDA(const uint8_t value);
        void STA(const uint16_t address);
        void LDX(const uint8_t value);
        void STX(const uint16_t address);
        void LDY(const uint8_t value);
        void STY(const uint16_t address);
        void TAX(void);
        void TXA(void);
        void TAY(void);
        void TYA(void);
        void TSX(void);
        void TXS(void);

        void PHA(void);
        void PLA(void);
        void PHP(void);
        void PLP(void);

        void INX(void);
        void DEX(void);
        void INY(void);
        void DEY(void);
        void INC(const uint16_t address);
        void DEC(const uint16_t address);

        void ADC(const uint8_t value);
        void SBC(const uint8_t value);

        void AND(const uint8_t value);
        void OR(const uint8_t value);
        void EOR(const uint8_t value);

        void ASL(uint8_t& value);
        void LSR(uint8_t& value);
        void ROL(uint8_t& value);
        void ROR(uint8_t& value);

        void CMP(const uint8_t value);
        void CPX(const uint8_t value);
        void CPY(const uint8_t value);

        void BCC(const uint8_t value);
        void BCS(const uint8_t value);
        void BEQ(const uint8_t value);
        void BNE(const uint8_t value);
        void BMI(const uint8_t value);
        void BPL(const uint8_t value);
        void BVC(const uint8_t value);
        void BVS(const uint8_t value);

        void JMP(const uint16_t address);
        void JSR(const uint16_t address);
        void RTS(void);

        void BRK(void);
        void RTI(void);

        void BIT(const uint8_t value);
        void NOP(void);

        //end of ALU function definitions
    
    }; //End of class
}

#endif