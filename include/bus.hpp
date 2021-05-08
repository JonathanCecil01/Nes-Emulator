#ifndef BUS_HPP
#define BUS_HPP

#include <array>
#include <cstdint>
#include <cpu6502.hpp>

class Bus
{
private:

public:
    Bus();
    ~Bus();

    void write(uint16_t addr, uint8_t data);
    uint8_t read(uint16_t addr, bool readOnly = false);

    // devices
    Cpu6502 cpu; // Cpu
    std::array<uint8_t, 64 * 1024> ram; // Ram

};

#endif