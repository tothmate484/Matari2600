#ifndef TM8_MOS6502_H
#define TM8_MOS6502_H

#include <cstdint>
#include <array>
#include <iostream>
#include <vector>

namespace tm8{

    class sr
    {
    public:
        bool N;
        bool V;
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
        uint16_t trigger;

        mos6502(const uint8_t adress_width, std::vector<uint8_t>& bus){
            this->bus = bus;

            this->adress_width = 1;
            for(int i = 0; i < adress_width-1; i++){
                this->adress_width <<= 1;
                this->adress_width += 1;
            }

            trigger = 0x0000;
        }

        uint16_t createadress(const uint8_t lb, const uint8_t hb, const uint8_t offset){ //creates a 16 bit adress                                                                              //out of 2 8 bit components
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
    
    };//End of class
}

#endif
