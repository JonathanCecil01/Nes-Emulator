#include <ppu2C02.hpp>

PPU2C02::PPU2C02()
{
}

PPU2C02::~PPU2C02()
{
}

void PPU2C02::CPUWrite(u16 addr, u8 data)
{

	switch (addr) {

	case 0x0000: // Control
		break;
	case 0x0001: // Mask
		break;
	case 0x0002: // Status
		break;
	case 0x0003: // OAM Address
		break;
	case 0x0004: // OAM data
		break;
	case 0x0005: // Scroll
		break;
	case 0x0006: // PPU Address
		break;
	case 0x0007: // PPU data
		break;
	}

}

u8 PPU2C02::CPURead(u16 addr, bool readOnly)
{
	u8 data = 0x00;

	switch (addr) {

	case 0x0000: // Control
		break;
	case 0x0001: // Mask
		break;
	case 0x0002: // Status
		break;
	case 0x0003: // OAM Address
		break;
	case 0x0004: // OAM data
		break;
	case 0x0005: // Scroll
		break;
	case 0x0006: // PPU Address
		break;
	case 0x0007: // PPU data
		break;
	}

	return data;
}

void PPU2C02::PPUWrite(u16 addr, u8 data)
{
	addr &= 0x3FFF;

	if (catridge->PPUWrite(addr, data)) {

	}

}

u8 PPU2C02::PPURead(u16 addr, bool readOnly)
{
	u8 data = 0x00;
	addr &= 0x3FFF;

	if (catridge->PPURead(addr, data)) {

	}

	return data;

}

void PPU2C02::connectCartidge(const std::shared_ptr<Catridge>& catridge)
{
	this->catridge = catridge;
}

void PPU2C02::clock()
{
}
