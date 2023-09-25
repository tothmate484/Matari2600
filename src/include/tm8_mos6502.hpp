#ifndef TM8_MOS6502_H
#define TM8_MOS6502_H

#include <cstdint>
#include <iostream>
#include <vector>
#include <cmath>

namespace tm8{

    class sr
    {
    public:
        bool N;
        bool V;
        bool i;
        bool B;
        bool D;
        bool I;
        bool Z;
        bool C;
        uint8_t SR;

        sr()
        {
            N = false;
            V = false;
            D = false;
            I = true;
            Z = false;
            C = false;
            SR = 0;
        }
    };

    class mos6502{ //beginning of class
    private:
        uint8_t A;
        uint8_t X;
        uint8_t Y;
        
        uint8_t SP;
        uint16_t PC;
        sr SR;
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
            if(obj > 255) SR.C = true ;
            else SR.C = false;
            if(obj == 0) SR.Z = true;
            else SR.Z = false;

            return static_cast<uint8_t> (obj);
        }

        //beginning of ALU function definitions

        void SEI(void);
        void CLI(void);
        void CLC(void);
        void SEC(void);
        void CLV(void);
        void SED(void);
        void CLD(void);

        void LDA(uint8_t value);
        void STA(uint16_t address);
        void LDX(uint8_t value);
        void STX(uint16_t address);
        void LDY(uint8_t value);
        void STY(uint16_t address);
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
        void INC(uint16_t address);
        void DEC(uint16_t address);

        void ADC(uint8_t value);
        void SBC(uint8_t value);

        void AND(uint8_t value);
        void OR(uint8_t value);
        void EOR(uint8_t value);

        void ASL(void);
        void RSR(void);
        void ROL(void);
        void ROR(void);

        void CMP(uint8_t value);
        void CPX(uint8_t value);
        void CPY(uint8_t value);

        void BCC(uint8_t value);
        void BCS(uint8_t value);
        void BEQ(uint8_t value);
        void BNE(uint8_t value);
        void BMI(uint8_t value);
        void BPL(uint8_t value);
        void BVC(uint8_t value);
        void BVS(uint8_t value);

        void JMP(uint16_t address);
        void JSR(uint16_t address);
        void RTS(void);

        void BRK(void);
        void RTI(void);

        void BIT(uint8_t value);
        void NOP(void);

        //end of ALU function definitions
    
    }; //End of class
}

#endif
