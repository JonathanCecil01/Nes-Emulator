#ifndef CATRIDGE_HPP
#define CATRIDGE_HPP

#include "header.hpp"
#include "mapper_000.hpp"

class Catridge {


private:

	std::vector<u8> PRGMEM;
	std::vector<u8> CHRMEM;

	u8 mapperID;
	u8 noPRGbanks;
	u8 noCHRbanks;

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

};

#endif // !CATRIDGE_HPP
