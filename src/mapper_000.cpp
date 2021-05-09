#include <mapper_000.hpp>

Mapper_000::Mapper_000(u8 prgBanks, u8 chrBanks)
:Mapper(prgBanks, chrBanks)
{}

Mapper_000::~Mapper_000()
{
}

bool Mapper_000::cpuMapRead(u16 addr, u32& mapped_addr)
{
	if (addr >= 0x8000 && addr <= 0xFFFF) {
		mapped_addr = addr & (noPRGBanks > 1 ? 0x7FFF : 0x3FFF);
		return true;
	}
	return false;
}

bool Mapper_000::cpuMapWrite(u16 addr, u32& mapped_addr)
{
	if (addr >= 0x8000 && addr <= 0xFFFF) {
		mapped_addr = addr & (noPRGBanks > 1 ? 0x7FFF : 0x3FFF);
		return true;
	}
	return false;
}

bool Mapper_000::ppuMapRead(u16 addr, u32& mapped_addr)
{
	if (addr >= 0x0000 && addr <= 0x1FFF) {
		mapped_addr = addr;
		return true;
	}
	return false;
}

bool Mapper_000::ppuMapWrite(u16 addr, u32& mapped_addr)
{
	if (addr >= 0x0000 && addr <= 0x1FFF)
	{
		if (noCHRBanks == 0)
		{
			// Treat as RAM
			mapped_addr = addr;
			return true;
		}
	}
	return false;
}
