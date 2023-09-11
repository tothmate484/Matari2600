#ifndef TM8_MOS6502_H
#define TM8_MOS6502_H

#include <cstdint>
#include <array>
#include <iostream>
#include <vector>
#include <cmath>

#define INST    bus[PC]
#define PARAM1  bus[PC+1]
#define PARAM2  bus[PC+2]

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
    
    };//End of class
}

#endif
