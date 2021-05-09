#include <catridge.hpp>

Catridge::Catridge()
{
}

Catridge::Catridge(const std::string& fileName)
{

	struct iNESHeader
	{
		char name[4];
		u8 PRGRomChunks;
		u8 CHRRomChunks;
		u8 mapper1;
		u8 mapper2;
		u8 PRGRamSize;
		u8 TVSys1;
		u8 TVSys2;
		char unused[5];

	}header;

	std::ifstream ifs;
	ifs.open(fileName, std::ifstream::binary);
	if (ifs.is_open()) {
	
		ifs.read((char*)&header, sizeof(iNESHeader));
	
		if (header.mapper1 & 0x04) {
			ifs.seekg(512, std::ios_base::cur);
		}

		mapperID = ((header.mapper2 >> 4) << 4) | (header.mapper1 >> 4);

		u8 fileType = 1;

		if (fileType == 0) {

		}
		else if (fileType == 1) {

			noPRGbanks = header.PRGRomChunks;
			PRGMEM.resize(noPRGbanks * 16 * 1024);
			ifs.read((char*)PRGMEM.data(), PRGMEM.size());

			noCHRbanks = header.CHRRomChunks;
			CHRMEM.resize(noCHRbanks * 8 * 1024);
			ifs.read((char*)CHRMEM.data(), CHRMEM.size());



		}
		else if (fileType == 2) {

		}

		switch (mapperID) {

		case 0:
			mapper = std::make_shared<Mapper_000>(noPRGbanks, noCHRbanks);
			break;

		}

		ifs.close();
	}


}

Catridge::~Catridge()
{
}

bool Catridge::CPUWrite(u16 addr, u8 data)
{
	uint32_t mapped_addr = 0;
	if (mapper->cpuMapRead(addr, mapped_addr))
	{
		PRGMEM[mapped_addr] = data;
		return true;
	}

	return false;
}

bool Catridge::CPURead(u16 addr, u8 &data)
{
	uint32_t mapped_addr = 0;
	if (mapper->cpuMapRead(addr, mapped_addr))
	{
		data = PRGMEM[mapped_addr];
		return true;
	}

	return false;
}

bool Catridge::PPUWrite(u16 addr, u8 data)
{
	uint32_t mapped_addr = 0;
	if (mapper->ppuMapRead(addr, mapped_addr))
	{
		CHRMEM[mapped_addr] = data;
		return true;
	}

	return false;
}

bool Catridge::PPURead(u16 addr, u8 &data)
{

	uint32_t mapped_addr = 0;
	if (mapper->ppuMapRead(addr, mapped_addr))
	{
		data = CHRMEM[mapped_addr];
		return true;
	}

	return false;
}
