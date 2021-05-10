#ifndef BUS_HPP
#define BUS_HPP

#include "header.hpp"
#include "cpu6502.hpp"
#include "ppu2C02.hpp"
#include "catridge.hpp"

class Bus
{
private:

public:
    Bus();
    ~Bus();

    // devices
    CPU6502 cpu; // CPU
    PPU2C02 ppu; // PPU
    u8 CPURam[2 * 1024]; // RAM
    std::shared_ptr<Catridge> cart; // Catridge

    void CPUWrite(u16 addr, u8 data);
    u8 CPURead(u16 addr, bool readOnly = false);

    // Functions of NES
    void insertCatridge(const std::shared_ptr<Catridge>& catridge);
    void reset();
    void clock();

private:
    int noSystemTicks = 0;

};

#endif