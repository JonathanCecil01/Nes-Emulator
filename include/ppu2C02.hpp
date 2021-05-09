#ifndef PPU2C02_HPP
#define PPU2C02_HPP

#include "header.hpp"
#include "catridge.hpp"

class PPU2C02 {


public:
	PPU2C02();
	~PPU2C02();

	// Connecting PPU to the CPU Bus
	void CPUWrite(u16 addr, u8 data);
	u8 CPURead(u16 addr, bool readOnly = false);

	// Connecting PPU to is own Bus
	void PPUWrite(u16 addr, u8 data);
	u8 PPURead(u16 addr, bool readOnly = false);

	void connectCartidge(const std::shared_ptr<Catridge>& catridge);
	void clock();

private:
	std::shared_ptr<Catridge> catridge;

	// devices
	u8 tblName[2][1024];
	u8 tblPalette[32];

};







#endif // !PPU2C02_HPP
