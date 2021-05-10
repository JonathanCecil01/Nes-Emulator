#ifndef CPU6502_HPP
#define CPU6502_HPP

#include "header.hpp"
#include "bus.hpp"

class Bus;

class CPU6502
{

public:

    enum class FLAGS {
        C = (1 << 0), // Carry
        Z = (1 << 1), // Zero
        I = (1 << 2), // Disable Interrupts
        D = (1 << 3), // Decimal Mode (Unused)
        B = (1 << 4), // Break
        U = (1 << 5), // Unused
        V = (1 << 6), // Overflow
        N = (1 << 7)  // Negative
    };

    u8 status; // Status Register
    u8 a;      // Accumulator Register
    u8 x;      // X Register
    u8 y;      // Y Register
    u8 SP;     // Stack Pointer
    u8 PC;    // Program Counter

public:
    CPU6502();
    ~CPU6502();

    void reset();	// Resets the CPU to default
	void irq();		// Interrupt Request - Executes an instruction at a specific location
	void nmi();		// Non-Maskable Interrupt Request - As above, but cannot be disabled
	void clock();   // Performs a clock cycle

    void ConnectBus(Bus *bus);
    
#ifdef HELPER_FUNCTIONS

    bool complete();
    std::map<uint16_t, std::string> disassemble(uint16_t nStart, uint16_t nStop);   
    
#endif

private:
    
    Bus *bus = nullptr;

    u8 read(u16 a);
    void write(u16 a, u8 d);

    void setFlag(FLAGS f, bool v);
    u8 getFlag(FLAGS f);

    u8 fetched;
    u16 temp;
    u16 addr;
    u16 addr_rel;
    u8 opcode;
    u8 cycles;
    u8 cycles_count;

    u8 fetch(); // Fetches the memory of a address given by addr

    struct INSTRUCTION
	{
		std::string name;		
        u8(CPU6502::*op)(void) = nullptr;
        u8(CPU6502::*ad)(void) = nullptr;
        u8     cycles = 0;
	};

	std::vector<INSTRUCTION> lookup;

private:

    // Addressing Modes - 12
    u8 IMP();
    u8 IMM();
    u8 ZP0();
    u8 ZPX();
    u8 ZPY();
    u8 REL();
    u8 ABS();
    u8 ABX();
    u8 ABY();
    u8 IND();
    u8 IZX();
    u8 IZY();

private:

    // Instruction Set - 56

    // Load / Store Operations - 6
    u8 LDA();
    u8 LDX();
    u8 LDY();
    u8 STA();
    u8 STX();
    u8 STY();

    // Resgister Transfers - 4
    u8 TAX();
    u8 TAY();
    u8 TXA();
    u8 TYA();

    // Stack Operations - 6
    u8 TSX();
    u8 TXS();
    u8 PHA();
    u8 PHP();
    u8 PLA();
    u8 PLP();

    // Logical - 4
    u8 AND();
    u8 EOR();
    u8 ORA();
    u8 BIT();

    // Arithmetic - 5
    u8 ADC();
    u8 SBC();
    u8 CMP();
    u8 CPX();
    u8 CPY();

    // Increments & Decrements - 6
    u8 INC();
    u8 INX();
    u8 INY();
    u8 DEC();
    u8 DEX();
    u8 DEY();

    // Shifts - 4
    u8 ASL();
    u8 LSR();
    u8 ROL();
    u8 ROR();

    // Jumps & Calls - 3
    u8 JMP();
    u8 JSR();
    u8 RTS();

    // Branches - 8
    u8 BCC();
    u8 BCS();
    u8 BEQ();
    u8 BMI();
    u8 BNE();
    u8 BPL();
    u8 BVC();
    u8 BVS();

    // Status Flag Changes - 7
    u8 CLC();
    u8 CLD();
    u8 CLI();
    u8 CLV();
    u8 SEC();
    u8 SED();
    u8 SEI();

    // System Functions - 3
    u8 BRK();
    u8 NOP();
    u8 RTI();

    // Capturing all others
    u8 XXX();

};

#endif