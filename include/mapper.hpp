#ifndef MAPPER_HPP
#define MAPPER_HPP

#include "header.hpp"

class Mapper {

public:
	Mapper(u8 noPRGBanks, u8 noCHRBanks);
	~Mapper();

public:

	// Transform CPU bus address into PRG ROM offset
	virtual bool cpuMapRead(u16 addr, u32& mapped_addr) = 0;
	virtual bool cpuMapWrite(u16 addr, u32& mapped_addr) = 0;

	// Transform PPU bus address into CHR ROM offset
	virtual bool ppuMapRead(u16 addr, u32& mapped_addr) = 0;
	virtual bool ppuMapWrite(u16 addr, u32& mapped_addr) = 0;

protected:
	// These are stored locally as many of the mappers require this information
	u8 noPRGBanks = 0;
	u8 noCHRBanks = 0;

};



#endif // !MAPPER_HPP
