#include <mapper.hpp>
//test_1

Mapper::Mapper(u8 noPRGBanks, u8 noCHRBanks)
{
	this->noPRGBanks = noPRGBanks;	
	this->noCHRBanks = noCHRBanks;
}

Mapper::~Mapper()
{
}
