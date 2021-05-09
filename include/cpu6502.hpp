#ifndef CPU6502_HPP
#define CPU6502_HPP

#include <cstdint>
#include <string>
#include <vector>
#include <map>

#include "bus.hpp"

class Bus;

class CPU6502
{

public:

    enum FLAGS{
        C = (1 << 0), // Carry
        Z = (1 << 1), // Zero
        I = (1 << 2), // Disable Interrupts
        D = (1 << 3), // Decimal Mode (Unused)
        B = (1 << 4), // Break
        U = (1 << 5), // Unused
        V = (1 << 6), // Overflow
        N = (1 << 7)  // Negative
    };

    uint8_t status; // Status Register
    uint8_t a;      // Accumulator Register
    uint8_t x;      // X Register
    uint8_t y;      // Y Register
    uint8_t SP;     // Stack Pointer
    uint16_t PC;    // Program Counter

public:
    CPU6502();
    ~CPU6502();

    void reset();	// Resets the CPU to default
	void irq();		// Interrupt Request - Executes an instruction at a specific location
	void nmi();		// Non-Maskable Interrupt Request - As above, but cannot be disabled
	void Clock();   // Performs a clock cycle

    void ConnectBus(Bus *bus);
    
#ifdef HELPER_FUNCTIONS

    bool complete();
    std::map<uint16_t, std::string> disassemble(uint16_t nStart, uint16_t nStop);   
    
#endif

private:
    
    Bus *bus = nullptr;

    uint8_t read(uint16_t a);
    void write(uint16_t a, uint8_t d);

    void setFlag(FLAGS f, bool v);
    uint8_t getFlag(FLAGS f);

    uint8_t fetched;
    uint16_t temp;
    uint16_t addr;
    uint16_t addr_rel;
    uint8_t opcode;
    uint8_t cycles;
    uint8_t cycles_count;

    uint8_t fetch(); // Fetches the memory of a address given by addr

    struct INSTRUCTION
	{
		std::string name;		
		uint8_t     (CPU6502::*op)(void) = nullptr;
		uint8_t     (CPU6502::*ad)(void) = nullptr;
		uint8_t     cycles = 0;
	};

	std::vector<INSTRUCTION> lookup;

private:

    // Addressing Modes - 12
    uint8_t IMP();
    uint8_t IMM();
    uint8_t ZP0();
    uint8_t ZPX();
    uint8_t ZPY();
    uint8_t REL();
    uint8_t ABS();
    uint8_t ABX();
    uint8_t ABY();
    uint8_t IND();
    uint8_t IZX();
    uint8_t IZY();

private:

    // Instruction Set - 56

    // Load / Store Operations - 6
    uint8_t LDA();
    uint8_t LDX();
    uint8_t LDY();
    uint8_t STA();
    uint8_t STX();
    uint8_t STY();

    // Resgister Transfers - 4
    uint8_t TAX();
    uint8_t TAY();
    uint8_t TXA();
    uint8_t TYA();

    // Stack Operations - 6
    uint8_t TSX();
    uint8_t TXS();
    uint8_t PHA();
    uint8_t PHP();
    uint8_t PLA();
    uint8_t PLP();

    // Logical - 4
    uint8_t AND();
    uint8_t EOR();
    uint8_t ORA();
    uint8_t BIT();

    // Arithmetic - 5
    uint8_t ADC();
    uint8_t SBC();
    uint8_t CMP();
    uint8_t CPX();
    uint8_t CPY();

    // Increments & Decrements - 6
    uint8_t INC();
    uint8_t INX();
    uint8_t INY();
    uint8_t DEC();
    uint8_t DEX();
    uint8_t DEY();

    // Shifts - 4
    uint8_t ASL();
    uint8_t LSR();
    uint8_t ROL();
    uint8_t ROR();

    // Jumps & Calls - 3
    uint8_t JMP();
    uint8_t JSR();
    uint8_t RTS();

    // Branches - 8
    uint8_t BCC();
    uint8_t BCS();
    uint8_t BEQ();
    uint8_t BMI();
    uint8_t BNE();
    uint8_t BPL();
    uint8_t BVC();
    uint8_t BVS();

    // Status Flag Changes - 7
    uint8_t CLC();
    uint8_t CLD();
    uint8_t CLI();
    uint8_t CLV();
    uint8_t SEC();
    uint8_t SED();
    uint8_t SEI();

    // System Functions - 3
    uint8_t BRK();
    uint8_t NOP();
    uint8_t RTI();

    // Capturing all others
    uint8_t XXX();

};

#endif