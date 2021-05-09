#include <bus.hpp>

Bus::Bus()
{
    for(u8 &i : CPURam) i = 0x00;
    cpu.ConnectBus(this);
}

Bus::~Bus()
{

}

u8 Bus::CPURead(u16 addr, bool readOnly) {

    u8 data = 0x00;

    if (cartidge->CPURead(addr, readOnly)){

    }else if (addr >= 0x0000 && addr <= 0x1FFF)
        data = CPURam[addr & 0x07FF];

    else if (addr >= 0x2000 && addr <= 0x3FFF)
        data = ppu.CPURead(addr & 0x0007, readOnly);
    
    return data;

}

void Bus::CPUWrite(u16 addr, u8 data){

    if (cartidge->CPUWrite(addr, data)) {

    }
    else if (addr >= 0x0000 && addr <= 0x1FFF)
        CPURam[addr & 0x07FF] = data;
    
    else if (addr >= 0x2000 && addr <= 0x3FFF)
        ppu.CPUWrite(addr & 0x0007, data);

}

void Bus::reset()
{

    cpu.reset();
    noSystemTicks = 0;

}

void Bus::clock()
{
    cpu.clock();
    ppu.clock();
}

void Bus::insertCatridge(const std::shared_ptr<Catridge>& catridge)
{
    this->catridge = catridge;
    ppu.connectCartidge(catridge);
}
