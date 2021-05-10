#ifndef PPU2C02_HPP
#define PPU2C02_HPP

#include "header.hpp"
#include "catridge.hpp"
#include "olc/olcPixelGameEngine.h"

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

private:
	olc::Pixel  palScreen[0x40];
	olc::Sprite sprScreen = olc::Sprite(256, 240);
	olc::Sprite sprNameTable[2] = { olc::Sprite(256, 240), olc::Sprite(256, 240) };
	olc::Sprite sprPatternTable[2] = { olc::Sprite(128, 128), olc::Sprite(128, 128) };

public:
	// Debugging Utilities
	olc::Sprite& GetScreen();
	olc::Sprite& GetNameTable(uint8_t i);
	olc::Sprite& GetPatternTable(uint8_t i);
	bool frame_complete = false;

private:
	int16_t scanline = 0;
	int16_t cycle = 0;
};







#endif // !PPU2C02_HPP
