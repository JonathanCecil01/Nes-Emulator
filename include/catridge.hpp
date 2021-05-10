#ifndef CATRIDGE_HPP
#define CATRIDGE_HPP

#include "header.hpp"
#include "mapper_000.hpp"

class Catridge {


private:

	std::vector<u8> PRGMEM;
	std::vector<u8> CHRMEM;

	u8 mapperID = 0;
	u8 noPRGbanks = 0;
	u8 noCHRbanks = 0;

	std::shared_ptr<Mapper> mapper;

public:
	Catridge(const std::string& fileName);
	Catridge();
	~Catridge();

	// Connecting Catridge to the CPU Bus
	bool CPUWrite(u16 addr, u8 data);
	bool CPURead(u16 addr, u8 &data);

	// Connecting Catridge to the PPU Bus
	bool PPUWrite(u16 addr, u8 data);
	bool PPURead(u16 addr, u8 &data);

public:
	bool ImageValid();

	enum MIRROR
	{
		HORIZONTAL,
		VERTICAL,
		ONESCREEN_LO,
		ONESCREEN_HI,
	} mirror = HORIZONTAL;

private:
	bool bImageValid = false;

};

#endif // !CATRIDGE_HPP
