#include <bus.hpp>
#include <cpu6502.hpp>

CPU6502::CPU6502(){

    using a = CPU6502;

    lookup = {
		{ "BRK", &a::BRK, &a::IMM, 7 },{ "ORA", &a::ORA, &a::IZX, 6 },{ "???", &a::XXX, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 8 },{ "NOP", &a::NOP, &a::IMP, 3 },{ "ORA", &a::ORA, &a::ZP0, 3 },{ "ASL", &a::ASL, &a::ZP0, 5 },{ "???", &a::XXX, &a::IMP, 5 },{ "PHP", &a::PHP, &a::IMP, 3 },{ "ORA", &a::ORA, &a::IMM, 2 },{ "ASL", &a::ASL, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 2 },{ "NOP", &a::NOP, &a::IMP, 4 },{ "ORA", &a::ORA, &a::ABS, 4 },{ "ASL", &a::ASL, &a::ABS, 6 },{ "???", &a::XXX, &a::IMP, 6 },
		{ "BPL", &a::BPL, &a::REL, 2 },{ "ORA", &a::ORA, &a::IZY, 5 },{ "???", &a::XXX, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 8 },{ "NOP", &a::NOP, &a::IMP, 4 },{ "ORA", &a::ORA, &a::ZPX, 4 },{ "ASL", &a::ASL, &a::ZPX, 6 },{ "???", &a::XXX, &a::IMP, 6 },{ "CLC", &a::CLC, &a::IMP, 2 },{ "ORA", &a::ORA, &a::ABY, 4 },{ "NOP", &a::NOP, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 7 },{ "NOP", &a::NOP, &a::IMP, 4 },{ "ORA", &a::ORA, &a::ABX, 4 },{ "ASL", &a::ASL, &a::ABX, 7 },{ "???", &a::XXX, &a::IMP, 7 },
		{ "JSR", &a::JSR, &a::ABS, 6 },{ "AND", &a::AND, &a::IZX, 6 },{ "???", &a::XXX, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 8 },{ "BIT", &a::BIT, &a::ZP0, 3 },{ "AND", &a::AND, &a::ZP0, 3 },{ "ROL", &a::ROL, &a::ZP0, 5 },{ "???", &a::XXX, &a::IMP, 5 },{ "PLP", &a::PLP, &a::IMP, 4 },{ "AND", &a::AND, &a::IMM, 2 },{ "ROL", &a::ROL, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 2 },{ "BIT", &a::BIT, &a::ABS, 4 },{ "AND", &a::AND, &a::ABS, 4 },{ "ROL", &a::ROL, &a::ABS, 6 },{ "???", &a::XXX, &a::IMP, 6 },
		{ "BMI", &a::BMI, &a::REL, 2 },{ "AND", &a::AND, &a::IZY, 5 },{ "???", &a::XXX, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 8 },{ "NOP", &a::NOP, &a::IMP, 4 },{ "AND", &a::AND, &a::ZPX, 4 },{ "ROL", &a::ROL, &a::ZPX, 6 },{ "???", &a::XXX, &a::IMP, 6 },{ "SEC", &a::SEC, &a::IMP, 2 },{ "AND", &a::AND, &a::ABY, 4 },{ "NOP", &a::NOP, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 7 },{ "NOP", &a::NOP, &a::IMP, 4 },{ "AND", &a::AND, &a::ABX, 4 },{ "ROL", &a::ROL, &a::ABX, 7 },{ "???", &a::XXX, &a::IMP, 7 },
		{ "RTI", &a::RTI, &a::IMP, 6 },{ "EOR", &a::EOR, &a::IZX, 6 },{ "???", &a::XXX, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 8 },{ "NOP", &a::NOP, &a::IMP, 3 },{ "EOR", &a::EOR, &a::ZP0, 3 },{ "LSR", &a::LSR, &a::ZP0, 5 },{ "???", &a::XXX, &a::IMP, 5 },{ "PHA", &a::PHA, &a::IMP, 3 },{ "EOR", &a::EOR, &a::IMM, 2 },{ "LSR", &a::LSR, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 2 },{ "JMP", &a::JMP, &a::ABS, 3 },{ "EOR", &a::EOR, &a::ABS, 4 },{ "LSR", &a::LSR, &a::ABS, 6 },{ "???", &a::XXX, &a::IMP, 6 },
		{ "BVC", &a::BVC, &a::REL, 2 },{ "EOR", &a::EOR, &a::IZY, 5 },{ "???", &a::XXX, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 8 },{ "NOP", &a::NOP, &a::IMP, 4 },{ "EOR", &a::EOR, &a::ZPX, 4 },{ "LSR", &a::LSR, &a::ZPX, 6 },{ "???", &a::XXX, &a::IMP, 6 },{ "CLI", &a::CLI, &a::IMP, 2 },{ "EOR", &a::EOR, &a::ABY, 4 },{ "NOP", &a::NOP, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 7 },{ "NOP", &a::NOP, &a::IMP, 4 },{ "EOR", &a::EOR, &a::ABX, 4 },{ "LSR", &a::LSR, &a::ABX, 7 },{ "???", &a::XXX, &a::IMP, 7 },
		{ "RTS", &a::RTS, &a::IMP, 6 },{ "ADC", &a::ADC, &a::IZX, 6 },{ "???", &a::XXX, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 8 },{ "NOP", &a::NOP, &a::IMP, 3 },{ "ADC", &a::ADC, &a::ZP0, 3 },{ "ROR", &a::ROR, &a::ZP0, 5 },{ "???", &a::XXX, &a::IMP, 5 },{ "PLA", &a::PLA, &a::IMP, 4 },{ "ADC", &a::ADC, &a::IMM, 2 },{ "ROR", &a::ROR, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 2 },{ "JMP", &a::JMP, &a::IND, 5 },{ "ADC", &a::ADC, &a::ABS, 4 },{ "ROR", &a::ROR, &a::ABS, 6 },{ "???", &a::XXX, &a::IMP, 6 },
		{ "BVS", &a::BVS, &a::REL, 2 },{ "ADC", &a::ADC, &a::IZY, 5 },{ "???", &a::XXX, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 8 },{ "NOP", &a::NOP, &a::IMP, 4 },{ "ADC", &a::ADC, &a::ZPX, 4 },{ "ROR", &a::ROR, &a::ZPX, 6 },{ "???", &a::XXX, &a::IMP, 6 },{ "SEI", &a::SEI, &a::IMP, 2 },{ "ADC", &a::ADC, &a::ABY, 4 },{ "NOP", &a::NOP, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 7 },{ "NOP", &a::NOP, &a::IMP, 4 },{ "ADC", &a::ADC, &a::ABX, 4 },{ "ROR", &a::ROR, &a::ABX, 7 },{ "???", &a::XXX, &a::IMP, 7 },
		{ "NOP", &a::NOP, &a::IMP, 2 },{ "STA", &a::STA, &a::IZX, 6 },{ "NOP", &a::NOP, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 6 },{ "STY", &a::STY, &a::ZP0, 3 },{ "STA", &a::STA, &a::ZP0, 3 },{ "STX", &a::STX, &a::ZP0, 3 },{ "???", &a::XXX, &a::IMP, 3 },{ "DEY", &a::DEY, &a::IMP, 2 },{ "NOP", &a::NOP, &a::IMP, 2 },{ "TXA", &a::TXA, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 2 },{ "STY", &a::STY, &a::ABS, 4 },{ "STA", &a::STA, &a::ABS, 4 },{ "STX", &a::STX, &a::ABS, 4 },{ "???", &a::XXX, &a::IMP, 4 },
		{ "BCC", &a::BCC, &a::REL, 2 },{ "STA", &a::STA, &a::IZY, 6 },{ "???", &a::XXX, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 6 },{ "STY", &a::STY, &a::ZPX, 4 },{ "STA", &a::STA, &a::ZPX, 4 },{ "STX", &a::STX, &a::ZPY, 4 },{ "???", &a::XXX, &a::IMP, 4 },{ "TYA", &a::TYA, &a::IMP, 2 },{ "STA", &a::STA, &a::ABY, 5 },{ "TXS", &a::TXS, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 5 },{ "NOP", &a::NOP, &a::IMP, 5 },{ "STA", &a::STA, &a::ABX, 5 },{ "???", &a::XXX, &a::IMP, 5 },{ "???", &a::XXX, &a::IMP, 5 },
		{ "LDY", &a::LDY, &a::IMM, 2 },{ "LDA", &a::LDA, &a::IZX, 6 },{ "LDX", &a::LDX, &a::IMM, 2 },{ "???", &a::XXX, &a::IMP, 6 },{ "LDY", &a::LDY, &a::ZP0, 3 },{ "LDA", &a::LDA, &a::ZP0, 3 },{ "LDX", &a::LDX, &a::ZP0, 3 },{ "???", &a::XXX, &a::IMP, 3 },{ "TAY", &a::TAY, &a::IMP, 2 },{ "LDA", &a::LDA, &a::IMM, 2 },{ "TAX", &a::TAX, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 2 },{ "LDY", &a::LDY, &a::ABS, 4 },{ "LDA", &a::LDA, &a::ABS, 4 },{ "LDX", &a::LDX, &a::ABS, 4 },{ "???", &a::XXX, &a::IMP, 4 },
		{ "BCS", &a::BCS, &a::REL, 2 },{ "LDA", &a::LDA, &a::IZY, 5 },{ "???", &a::XXX, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 5 },{ "LDY", &a::LDY, &a::ZPX, 4 },{ "LDA", &a::LDA, &a::ZPX, 4 },{ "LDX", &a::LDX, &a::ZPY, 4 },{ "???", &a::XXX, &a::IMP, 4 },{ "CLV", &a::CLV, &a::IMP, 2 },{ "LDA", &a::LDA, &a::ABY, 4 },{ "TSX", &a::TSX, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 4 },{ "LDY", &a::LDY, &a::ABX, 4 },{ "LDA", &a::LDA, &a::ABX, 4 },{ "LDX", &a::LDX, &a::ABY, 4 },{ "???", &a::XXX, &a::IMP, 4 },
		{ "CPY", &a::CPY, &a::IMM, 2 },{ "CMP", &a::CMP, &a::IZX, 6 },{ "NOP", &a::NOP, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 8 },{ "CPY", &a::CPY, &a::ZP0, 3 },{ "CMP", &a::CMP, &a::ZP0, 3 },{ "DEC", &a::DEC, &a::ZP0, 5 },{ "???", &a::XXX, &a::IMP, 5 },{ "INY", &a::INY, &a::IMP, 2 },{ "CMP", &a::CMP, &a::IMM, 2 },{ "DEX", &a::DEX, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 2 },{ "CPY", &a::CPY, &a::ABS, 4 },{ "CMP", &a::CMP, &a::ABS, 4 },{ "DEC", &a::DEC, &a::ABS, 6 },{ "???", &a::XXX, &a::IMP, 6 },
		{ "BNE", &a::BNE, &a::REL, 2 },{ "CMP", &a::CMP, &a::IZY, 5 },{ "???", &a::XXX, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 8 },{ "NOP", &a::NOP, &a::IMP, 4 },{ "CMP", &a::CMP, &a::ZPX, 4 },{ "DEC", &a::DEC, &a::ZPX, 6 },{ "???", &a::XXX, &a::IMP, 6 },{ "CLD", &a::CLD, &a::IMP, 2 },{ "CMP", &a::CMP, &a::ABY, 4 },{ "NOP", &a::NOP, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 7 },{ "NOP", &a::NOP, &a::IMP, 4 },{ "CMP", &a::CMP, &a::ABX, 4 },{ "DEC", &a::DEC, &a::ABX, 7 },{ "???", &a::XXX, &a::IMP, 7 },
		{ "CPX", &a::CPX, &a::IMM, 2 },{ "SBC", &a::SBC, &a::IZX, 6 },{ "NOP", &a::NOP, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 8 },{ "CPX", &a::CPX, &a::ZP0, 3 },{ "SBC", &a::SBC, &a::ZP0, 3 },{ "INC", &a::INC, &a::ZP0, 5 },{ "???", &a::XXX, &a::IMP, 5 },{ "INX", &a::INX, &a::IMP, 2 },{ "SBC", &a::SBC, &a::IMM, 2 },{ "NOP", &a::NOP, &a::IMP, 2 },{ "???", &a::SBC, &a::IMP, 2 },{ "CPX", &a::CPX, &a::ABS, 4 },{ "SBC", &a::SBC, &a::ABS, 4 },{ "INC", &a::INC, &a::ABS, 6 },{ "???", &a::XXX, &a::IMP, 6 },
		{ "BEQ", &a::BEQ, &a::REL, 2 },{ "SBC", &a::SBC, &a::IZY, 5 },{ "???", &a::XXX, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 8 },{ "NOP", &a::NOP, &a::IMP, 4 },{ "SBC", &a::SBC, &a::ZPX, 4 },{ "INC", &a::INC, &a::ZPX, 6 },{ "???", &a::XXX, &a::IMP, 6 },{ "SED", &a::SED, &a::IMP, 2 },{ "SBC", &a::SBC, &a::ABY, 4 },{ "NOP", &a::NOP, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 7 },{ "NOP", &a::NOP, &a::IMP, 4 },{ "SBC", &a::SBC, &a::ABX, 4 },{ "INC", &a::INC, &a::ABX, 7 },{ "???", &a::XXX, &a::IMP, 7 },
	};
    
}

CPU6502::~CPU6502(){}

void CPU6502::ConnectBus(Bus *bus){
    this->bus = bus;
}

uint8_t CPU6502::read(uint16_t a){
    return bus->read(a, false);
}

void CPU6502::write(uint16_t a, uint8_t d){
    bus->write(a, d);
}

uint8_t CPU6502::getFlag(FLAGS f){
	return ((status & f) > 0) ? 1 : 0;
}

void CPU6502::setFlag(FLAGS f, bool v){
	if (v)
		status |= f;
	else
		status &= ~f;
}

void CPU6502::reset(){
    
    a = 0x00;
    x = 0x00;
    y = 0x00;
    SP = 0xFD;
    status = 0x00 | U;

    addr = 0xFFFC;
    uint16_t lo = read(addr + 0);
    uint16_t hi = read(addr + 1);

    PC = (hi << 8) | lo;

    addr = 0x0000;
    addr_rel = 0x0000;
    fetched = 0x00;

    cycles = 8;

}

void CPU6502::irq(){

    if(getFlag(I) == 0){

        write(0x0100 + SP, (PC >> 8) & 0x00FF);
        SP--;

        write(0x0100 + SP, PC & 0x00FF);
        SP--;

        setFlag(B, 0);
        setFlag(U, 1);
        setFlag(I, 1);

        write(0x0100 + SP, status);
        SP--;

        addr = 0xFFFE;

        uint16_t lo = read(addr + 0);
        uint16_t hi = read(addr + 1);

        PC = (hi << 8) | lo;

        cycles = 7;

    }

}

void CPU6502::nmi(){
        
    write(0x0100 + SP, (PC >> 8) & 0x00FF);
    SP--;

    write(0x0100 + SP, PC & 0x00FF);
    SP--;

    setFlag(B, 0);
    setFlag(U, 1);
    setFlag(I, 1);

    write(0x0100 + SP, status);
    SP--;

    addr = 0xFFFA;

    uint16_t lo = read(addr + 0);
    uint16_t hi = read(addr + 1);

    PC = (hi << 8) | lo;

    cycles = 8;

}

void CPU6502::Clock(){

    if(cycles == 0){

        // Read the current Instruction
        opcode = read(PC);
        PC++;

        cycles = lookup[opcode].cycles;

        // Address Mode
        uint8_t additionalCycles1 = (this->*lookup[opcode].ad)();

        // Operation Mode
        uint8_t additionalCycles2 = (this->*lookup[opcode].op)();

        cycles += (additionalCycles1 & additionalCycles2);

    }

    cycles--;
}

// Implementing Address Modes

uint8_t CPU6502::IMP(){

    // Gets the accumulator
    fetched = a;

    return 0;
}

uint8_t CPU6502::IMM(){

    addr = PC++;
    return 0;

}

uint8_t CPU6502::ZP0(){

    addr = read(PC++);
    addr &= 0x00FF;

    return 0;
}

uint8_t CPU6502::ZPX(){

    addr = read(PC + x);
    PC++;
    addr &= 0x00FF;
    return 0;

}


uint8_t CPU6502::ZPY(){

    addr = read(PC + x);
    PC++;
    addr &= 0x00FF;
    return 0;

}


uint8_t CPU6502::REL(){

    addr_rel = read(PC++);

    // Note
    if(addr_rel & 0x80){
        addr_rel |= 0xFF00;
    }

    return 0;
}

uint8_t CPU6502::ABS(){

    uint8_t lo = read(PC++);
    uint8_t hi = read(PC++);
    addr = (hi << 8) | lo;
    return 0;

}

uint8_t CPU6502::ABX(){

    uint8_t lo = read(PC++);
    uint8_t hi = read(PC++);
    addr = (hi << 8) | lo;
    addr += x;

    if((addr & 0x00FF) != (hi << 8)){
        // Page has changed, so additional clock cycles
        return 1;
    }

    return 0;

}

uint8_t CPU6502::ABY(){

    uint8_t lo = read(PC++);
    uint8_t hi = read(PC++);
    addr = (hi << 8) | lo;
    addr += y;

    if((addr & 0x00FF) != (hi << 8)){
        // Page has changed, so additional clock cycles
        return 1;
    }

    return 0;

}

uint8_t CPU6502::IND(){

    uint8_t lo = read(PC++);
    uint8_t hi = read(PC++);
    uint16_t ptr = (hi << 8) | lo;
    
    // addr = (read(ptr + 1) << 8) | read(ptr);

    if(lo == 0x00FF){
        // Hardware Bug
        addr = (read(ptr & 0xFF00) << 8) | read(ptr);
    }else{
        addr = (read(ptr + 1) << 8) | read(ptr);
    }

    return 0;

}

uint8_t CPU6502::IZX(){

    uint8_t t = read(PC++);

    uint8_t lo = read((((uint16_t)(t + x)) & 0x00FF));
    uint8_t hi = read((((uint16_t)(t + x + 1)) & 0x00FF));

    addr = (hi << 8) | lo;

    return 0;

}

uint8_t CPU6502::IZY(){

    uint8_t t = read(PC++);

    uint8_t lo = read((uint16_t)t & 0x00FF);
    uint8_t hi = read((uint16_t)(t + 1) & 0x00FF);

    addr = (hi << 8) | lo;
    addr += y;

    if((addr & 0xFF00) != (hi << 8)){
        // Crosses Page Boundary
        return 1;
    }

    return 0;

}

// Instructions
uint8_t CPU6502::fetch() {
    
    if (lookup[opcode].ad != &CPU6502::IMP) {
        fetched = read(addr);
    }
    
    return fetched;
}

// Load / Store Operations - 6
uint8_t CPU6502::LDA(){

    fetch();
    a = fetched;

    setFlag(Z, a == 0x00);
    setFlag(N, a & 0x80);

    return 0;

}

uint8_t CPU6502::LDX(){

    fetch();
    x = fetched;

    setFlag(Z, x == 0x00);
    setFlag(N, x & 0x80);

    return 0;

}

uint8_t CPU6502::LDY(){

    fetch();
    y = fetched;

    setFlag(Z, y == 0x00);
    setFlag(N, y & 0x80);

    return 0;

}

uint8_t CPU6502::STA(){
    write(addr, a);
    return 0;
}

uint8_t CPU6502::STX(){
    write(addr, x);
    return 0;
}

uint8_t CPU6502::STY(){
    write(addr, y);
    return 0;
}

// Load / Store Operations

// Resgister Transfers - 4

uint8_t CPU6502::TAX(){
    x = a;
    setFlag(Z, x == 0x00);
	setFlag(N, x & 0x80);
	return 0;
}

uint8_t CPU6502::TAY(){
    y = a;
    setFlag(Z, y == 0x00);
	setFlag(N, y & 0x80);
	return 0;
}

uint8_t CPU6502::TXA(){
    a = x;
    setFlag(Z, a == 0x00);
	setFlag(N, a & 0x80);
	return 0;
}

uint8_t CPU6502::TYA(){
    a = y;
    setFlag(Z, a == 0x00);
	setFlag(N, a & 0x80);
	return 0;
}

// Resgister Transfers

// Stack Operations - 6

uint8_t CPU6502::TSX(){
    x = SP;
    setFlag(Z, x == 0x00);
	setFlag(N, x & 0x80);
	return 0;
}

uint8_t CPU6502::TXS(){
    SP = x;
    return 0;
}

uint8_t CPU6502::PHA(){

    write(0x0100 + SP, a);
    SP--;
    return 0;

}

uint8_t CPU6502::PHP(){

    write(0x0100 + SP, status | B | U);
    SP--;

    setFlag(B, 0);
    setFlag(U, 0);

    return 0;

}

uint8_t CPU6502::PLA(){
    
    SP++;
    a = read(0x0100 + SP);
    setFlag(Z, a == 0x00);
    setFlag(N, a & 0x80);
    return 0;

}

uint8_t CPU6502::PLP(){
    
    SP++;
    status = read(0x0100 + SP);
    setFlag(U, 1);
    return 0;

}
// Stack Operations

// Logical - 4
uint8_t CPU6502::AND() {
    
    fetch();
    a &= fetched;

    setFlag(Z, a == 0x00);
    setFlag(N, a &= 0x80);

    return 1;

}

uint8_t CPU6502::EOR(){

    fetch();

    a ^= fetched;

    setFlag(Z, a == 0x00);
    setFlag(N, a & 0x80);

    return 1;

}

uint8_t CPU6502::ORA(){

    fetch();

    a |= fetched;

    setFlag(Z, a == 0x00);
    setFlag(N, a & 0x80);

    return 1;

}

uint8_t CPU6502::BIT(){

    fetch();

    setFlag(Z, (a & fetched) == 0x00);
    setFlag(N, fetched & 0x80);
    setFlag(V, fetched & 0x70);
    
    return 0;
}

// Logical

// Arithmetic - 5
uint8_t CPU6502::ADC(){
    fetch();
    uint16_t temp = static_cast<uint16_t>(a) + static_cast<uint16_t>(fetched) + static_cast<uint16_t>(getFlag(C));

    setFlag(C, temp > 255);
    setFlag(Z, (temp & 0x00FF) == 0);
    setFlag(V, (
        (
            ~(static_cast<uint16_t>(a) ^ static_cast<uint16_t>(fetched)) & 
            (static_cast<uint16_t>(a) ^ static_cast<uint16_t>(temp))) & 0x0080
        )
    );

    a = temp & 0x00FF;

    return 1;
}

uint8_t CPU6502::SBC(){

    // 2's Complement
    fetch();
    uint16_t complement = ((uint16_t)fetched) ^ 0x00FF;

    uint16_t temp = static_cast<uint16_t>(a) + complement + static_cast<uint16_t>(getFlag(C));

    setFlag(C, temp > 255);
    setFlag(Z, (temp & 0x00FF) == 0);
    setFlag(V, (
        (
            ~(static_cast<uint16_t>(a) ^ static_cast<uint16_t>(fetched)) & 
            (static_cast<uint16_t>(a) ^ static_cast<uint16_t>(temp))) & 0x0080
        )
    );

    a = temp & 0x00FF;

    return 1;
}

uint8_t CPU6502::CMP(){
    
    fetch();
    temp = static_cast<uint16_t>(a) - static_cast<uint16_t>(fetched);
    
    setFlag(C, a >= fetched);
    setFlag(Z, (temp & 0x00FF) == 0x00);
    setFlag(N, temp & 0x80);
    return 1;

}

uint8_t CPU6502::CPX(){
    
    fetch();
    temp = static_cast<uint16_t>(x) - static_cast<uint16_t>(fetched);
    
    setFlag(C, x >= fetched);
    setFlag(Z, (temp & 0x00FF) == 0x00);
    setFlag(N, temp & 0x80);
    return 1;

}

uint8_t CPU6502::CPY(){
    
    fetch();
    temp = static_cast<uint16_t>(y) - static_cast<uint16_t>(fetched);
    
    setFlag(C, y >= fetched);
    setFlag(Z, (temp & 0x00FF) == 0x00);
    setFlag(N, temp & 0x80);
    return 1;

}
// Arthimetic


// Increments & Decrements - 6
uint8_t CPU6502::INC(){

    fetch();
    temp = static_cast<uint16_t>(fetched) + 1;

    setFlag(Z, (temp & 0x00FF) == 0x00);
    setFlag(N, temp & 0x80);

    return 0;

}

uint8_t CPU6502::INX(){
    x++;
    setFlag(Z, x == 0x00);
    setFlag(N, x & 0x80);
    return 0;
}


uint8_t CPU6502::INY(){
    y++;
    setFlag(Z, y == 0x00);
    setFlag(N, y & 0x80);
    return 0;
}

uint8_t CPU6502::DEC(){

    fetch();
    temp = static_cast<uint16_t>(fetched) - 1;
    write(addr, temp & 0x00FF);

    setFlag(Z, (temp & 0x00FF) == 0x00);
    setFlag(N, temp & 0x80);
    return 0;
}

uint8_t CPU6502::DEX(){
    x--;
    setFlag(Z, x == 0x00);
    setFlag(N, x & 0x80);
    return 0;
}

uint8_t CPU6502::DEY(){
    y--;
    setFlag(Z, y == 0x00);
    setFlag(N, y & 0x80);
    return 0;
}

// Increments & Decrements


// Shifts - 4
uint8_t CPU6502::ASL(){
    
    fetch();
    temp = static_cast<uint16_t>(fetched) << 1;

    setFlag(N, temp & 0x80);
    setFlag(Z, (temp & 0x00FF) == 0x00);
    setFlag(C, (temp & 0xFF00) > 0);

    if(lookup[opcode].ad == &CPU6502::IMP){
        a = temp & 0x00FF;
    }else{
        write(addr, temp & 0x00FF);
    }

    return 0;

}

uint8_t CPU6502::LSR(){

    fetch();

    setFlag(C, fetched & 0x0001);

    temp = fetched >> 1;	

    setFlag(Z, (temp & 0x00FF) == 0x00);
	setFlag(N, temp & 0x0080);

    if (lookup[opcode].ad == &CPU6502::IMP)
		a = temp & 0x00FF;
	else
		write(addr, temp & 0x00FF);

    return 0;

}

uint8_t CPU6502::ROL(){
    
    fetch();
    
    temp = (fetched << 1) | getFlag(C);

    setFlag(C, temp & 0xFF00);
    setFlag(Z, (temp & 0x00FF) == 0x00);
    setFlag(N, temp & 0x80);

    if (lookup[opcode].ad == &CPU6502::IMP)
		a = temp & 0x00FF;
	else
		write(addr, temp & 0x00FF);

    return 0;

}

uint8_t CPU6502::ROR(){
    
    fetch();
    
    temp = static_cast<uint16_t>(getFlag(C) << 7) | (fetched >> 1);

    setFlag(C, fetched & 0x0001);
    setFlag(Z, (temp & 0x00FF) == 0x00);
    setFlag(N, temp & 0x80);

    if (lookup[opcode].ad == &CPU6502::IMP)
		a = temp & 0x00FF;
	else
		write(addr, temp & 0x00FF);

    return 0;
}

// Shifts

// Jumps & Calls - 3
uint8_t CPU6502::JMP(){
    PC = addr;
    return 0;
}

uint8_t CPU6502::JSR(){
    
    PC--;

    write(0x0100 + SP, (PC >> 8) & 0x00FF);
    SP--;

    write(0x0100 + SP, PC & 0x00FF);
    SP--;

    PC = addr;
    return 0;

}

uint8_t CPU6502::RTS(){
    
    SP++;
	PC = static_cast<uint16_t>(read(0x0100 + SP));
	SP++;
	PC |= static_cast<uint16_t>(read(0x0100 + SP)) << 8;
	
	PC++;
	
    return 0;
}
// Jumps & Calls

// Branches - 8
uint8_t CPU6502::BCC(){
    if (getFlag(C) == 0) {

        cycles++;

        addr = PC + addr_rel;

        // Page Crossing
        if ((addr & 0xFF00) != (PC & 0xFF00)) {
            cycles++;
        }

        // Branch to that location
        PC = addr;

    }

    return 0;
}

uint8_t CPU6502::BCS() {

    if (getFlag(C) == 1) {

        cycles++;

        addr = PC + addr_rel;

        // Page Crossing
        if ((addr & 0xFF00) != (PC & 0xFF00)) {
            cycles++;
        }

        // Branch to that location
        PC = addr;

    }

    return 0;
}

uint8_t CPU6502::BEQ(){
    if (getFlag(Z) == 0) {

        cycles++;

        addr = PC + addr_rel;

        // Page Crossing
        if ((addr & 0xFF00) != (PC & 0xFF00)) {
            cycles++;
        }

        // Branch to that location
        PC = addr;

    }

    return 0;
}

uint8_t CPU6502::BMI(){
    if (getFlag(N) == 1) {

        cycles++;

        addr = PC + addr_rel;

        // Page Crossing
        if ((addr & 0xFF00) != (PC & 0xFF00)) {
            cycles++;
        }

        // Branch to that location
        PC = addr;

    }

    return 0;
}

uint8_t CPU6502::BNE(){
    if (getFlag(Z) == 0) {

        cycles++;

        addr = PC + addr_rel;

        // Page Crossing
        if ((addr & 0xFF00) != (PC & 0xFF00)) {
            cycles++;
        }

        // Branch to that location
        PC = addr;

    }

    return 0;
}

uint8_t CPU6502::BPL(){
    if (getFlag(N) == 0) {

        cycles++;

        addr = PC + addr_rel;

        // Page Crossing
        if ((addr & 0xFF00) != (PC & 0xFF00)) {
            cycles++;
        }

        // Branch to that location
        PC = addr;

    }

    return 0;
}

uint8_t CPU6502::BVC(){
    if (getFlag(V) == 0) {

        cycles++;

        addr = PC + addr_rel;

        // Page Crossing
        if ((addr & 0xFF00) != (PC & 0xFF00)) {
            cycles++;
        }

        // Branch to that location
        PC = addr;

    }

    return 0;
}

uint8_t CPU6502::BVS(){
    if (getFlag(V) == 1) {

        cycles++;

        addr = PC + addr_rel;

        // Page Crossing
        if ((addr & 0xFF00) != (PC & 0xFF00)) {
            cycles++;
        }

        // Branch to that location
        PC = addr;

    }

    return 0;
}

// Status Flag Changes - 7
uint8_t CPU6502::CLC(){
    setFlag(C, 0);
    return 0;
}

uint8_t CPU6502::CLD(){
    setFlag(D, 0);
    return 0;
}

uint8_t CPU6502::CLI(){
    setFlag(I, 0);
    return 0;
}

uint8_t CPU6502::CLV(){
    setFlag(V, 0);
    return 0;
}

uint8_t CPU6502::SEC(){
    setFlag(C, 1);
    return 0;
}

uint8_t CPU6502::SED(){
    setFlag(D, 1);
    return 0;
}

uint8_t CPU6502::SEI(){
    setFlag(I, 1);
    return 0;
}


// System Functions - 3
uint8_t CPU6502::BRK(){
    
    PC++;

    setFlag(I, 1);

    write(0x0100 + SP, (PC >> 8) & 0x00FF);
    SP--;

    write(0x0100 + SP, PC & 0x00FF);
    SP--;

    setFlag(B, 0);
    write(0x0100 + SP, status);
    SP--;
    setFlag(B, 1);

    uint16_t lo = read(0xFFFE + 0);
    uint16_t hi = read(0xFFFE + 1);

    PC = (hi << 8) | lo;

    return 0;

}

uint8_t CPU6502::NOP(){

    switch (opcode){

        case 0x1C:
        case 0x3C:
        case 0x5C:
        case 0x7C:
        case 0xDC:
        case 0xFC:
            return 1;
            break;

	}

	return 0;

}

uint8_t CPU6502::RTI(){

    SP++;
    status = read(0x0100 + SP);
    
    setFlag(B, 1);
    setFlag(U, 0);

    SP++;
    PC = read(0x0100 + SP);
    SP++;
    PC |= read(0x0100 + SP) << 8;

    return 0;
}
// System Functions

// Capturing all others
uint8_t CPU6502::XXX(){
    return 0;
}


#ifdef HELPER_FUNCTIONS

bool CPU6502::complete()
{
    return cycles == 0;
}


std::map<uint16_t, std::string> CPU6502::disassemble(uint16_t nStart, uint16_t nStop)
{
    uint32_t address = nStart;
    uint8_t value = 0x00, lo = 0x00, hi = 0x00;
    std::map<uint16_t, std::string> mapLines;
    uint16_t line_addr = 0;

    auto hex = [](uint32_t n, uint8_t d)
    {
        std::string s(d, '0');
        for (int i = d - 1; i >= 0; i--, n >>= 4)
            s[i] = "0123456789ABCDEF"[n & 0xF];
        return s;
    };


    while (address <= (uint32_t)nStop)
    {
        line_addr = address;

        std::string sInst = "$" + hex(address, 4) + ": ";

        uint8_t opcode = bus->read(address, true); address++;
        sInst += lookup[opcode].name + " ";

        if (lookup[opcode].ad == &CPU6502::IMP)
        {
            sInst += " {IMP}";
        }
        else if (lookup[opcode].ad == &CPU6502::IMM)
        {
            value = bus->read(address, true); address++;
            sInst += "#$" + hex(value, 2) + " {IMM}";
        }
        else if (lookup[opcode].ad == &CPU6502::ZP0)
        {
            lo = bus->read(address, true); address++;
            hi = 0x00;
            sInst += "$" + hex(lo, 2) + " {ZP0}";
        }
        else if (lookup[opcode].ad == &CPU6502::ZPX)
        {
            lo = bus->read(address, true); address++;
            hi = 0x00;
            sInst += "$" + hex(lo, 2) + ", X {ZPX}";
        }
        else if (lookup[opcode].ad == &CPU6502::ZPY)
        {
            lo = bus->read(address, true); address++;
            hi = 0x00;
            sInst += "$" + hex(lo, 2) + ", Y {ZPY}";
        }
        else if (lookup[opcode].ad == &CPU6502::IZX)
        {
            lo = bus->read(address, true); address++;
            hi = 0x00;
            sInst += "($" + hex(lo, 2) + ", X) {IZX}";
        }
        else if (lookup[opcode].ad == &CPU6502::IZY)
        {
            lo = bus->read(address, true); address++;
            hi = 0x00;
            sInst += "($" + hex(lo, 2) + "), Y {IZY}";
        }
        else if (lookup[opcode].ad == &CPU6502::ABS)
        {
            lo = bus->read(address, true); address++;
            hi = bus->read(address, true); address++;
            sInst += "$" + hex((uint16_t)(hi << 8) | lo, 4) + " {ABS}";
        }
        else if (lookup[opcode].ad == &CPU6502::ABX)
        {
            lo = bus->read(address, true); address++;
            hi = bus->read(address, true); address++;
            sInst += "$" + hex((uint16_t)(hi << 8) | lo, 4) + ", X {ABX}";
        }
        else if (lookup[opcode].ad == &CPU6502::ABY)
        {
            lo = bus->read(address, true); address++;
            hi = bus->read(address, true); address++;
            sInst += "$" + hex((uint16_t)(hi << 8) | lo, 4) + ", Y {ABY}";
        }
        else if (lookup[opcode].ad == &CPU6502::IND)
        {
            lo = bus->read(address, true); address++;
            hi = bus->read(address, true); address++;
            sInst += "($" + hex((uint16_t)(hi << 8) | lo, 4) + ") {IND}";
        }
        else if (lookup[opcode].ad == &CPU6502::REL)
        {
            value = bus->read(address, true); address++;
            sInst += "$" + hex(value, 2) + " [$" + hex(address + value, 4) + "] {REL}";
        }

        mapLines[line_addr] = sInst;
    }

    return mapLines;
}

#endif // HELPER_FUNCTIONS
