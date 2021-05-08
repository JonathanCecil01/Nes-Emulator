# Addressing Modes
There are a total of 12 Addressing Modes that the 6502 uses to fetch data from  
different parts of the memory.  

### Basic Overview

Each Address function takes in no input and sets the addr_abs (Address Absolute) and the addr_rel (Address Relative) to the specific values, which is then used by the instruction to get the data in the addr_abs of the memory and act on it.


### Addressing Modes - 12

- IMP - Implied
- IMM - Immediate
- ZP0 - Zero Page
- ZPX - Zero Page with X Register offset
- ZPY - Zero Page with Y Register offset
- REL - Relative
- ABS - Absolute
- ABX - Absolute with X Register offset
- ABY - Absolute with Y Register offset
- IND - Indirect
- IZX - Indexed Indirect
- IZY - Indirect Indexed

## Detailed Overview



### REL - Relative Addressing Mode

Used by branch instruction to conditional or unconditional jump to a location that is within the range of -127 to +128.

The relative address is stored at the program counter
which is read as a 8-bit number and stored a 16-bit number in the variable addr_rel.

The addr_rel is what gets added to the program counter when branch instructions are executed.

#### Note :
As the number is being read as a 8-bit number and stored as a 16-bit number, the higher 8-bits are set to 1s for a 8-bit negative number in its 16-bit representation.

#### Example :

8-bit 4  : 0000 0100
8-bit -4 : 1111 1100
16-bit -4 : 1111 1111 1111 1100

We can see that all the higher bits are set to 1.