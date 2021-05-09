#ifndef MAPPER_000_HPP
#define MAPPER_000_HPP

#include "header.hpp"
#include "mapper.hpp"

class Mapper_000 : public Mapper {

public:
	Mapper_000(u8 prgBanks, u8 chrBanks);
	~Mapper_000();

public:
	bool cpuMapRead(u16 addr, u32& mapped_addr) override;
	bool cpuMapWrite(u16 addr, u32& mapped_addr) override;
	bool ppuMapRead(u16 addr, u32& mapped_addr) override;
	bool ppuMapWrite(u16 addr, u32& mapped_addr) override;

};





#endif // !MAPPER_000_HPP
