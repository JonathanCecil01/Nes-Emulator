#include <iostream>
#include <bus.hpp>

Bus::Bus()
{
    for(uint8_t &i : ram) i = 0x00;
    cpu.ConnectBus(this);
}

Bus::~Bus()
{

}

uint8_t Bus::read(uint16_t addr, bool readOnly){

    if(addr >= 0x0000 && addr <= 0xFFFF)
        return ram[addr];

    return 0x00;

}

void Bus::write(uint16_t addr, uint8_t data){
    if(addr >= 0x0000 && addr <= 0xFFFF)
        ram[addr] = data;
}

