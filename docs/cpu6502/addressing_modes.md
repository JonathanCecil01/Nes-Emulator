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

## Page

Conceptual Way of organizing group of address. Normally the first high byte  
is referred as the page and the next byte as an indexing into the page.
So for a 16-bit addresing there are 256 pages with 256 indices.

## Detailed Overview

### IMP - Implied Addressing Mode

When No Data is passed onto to the Instruction, IMP Mode is used.  
Although the accumulator data might get fetched by the instruction.  

### IMM - Immediate Addressing Mode

The Address from which the data must be fetched is given in the next byte  
after the instruction.

### ZP0 - Zero Page Addressing Mode

In Zero Page addressing the page is 0, i.e is the high byte is always zero.  
So it is optimal to read only the lower byte to get the actual zero page address.  

### ZPX - Zero Page (with x-offset) Addressing Mode

The lower byte is offsetted by the `x register`. It can be thought of the arrays in C/C++,  
There is a base address and the index is like the offset from that address.  

### ZPY - Zero Page (with y-offset) Addressing Mode

The lower byte is offsetted by the `y register`. It can be thought of the arrays in C/C++,  
There is a base address and the index is like the offset from that address.  

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

We can see that all the higher bits are set to 1.'

### ABS - Absolute Addressing Mode

In this type of addressing, a 16-bit address in passed with the instruction.  
First the low byte is read and then followed by the high byte.

### ABX - Absolute (with x-offset) Addressing Mode

Absolute Addressing Mode, in which the address is offset by the `x register`.  
Any additional clock cycle is required if the page of the address changes, after adding the offset.

### ABY - Absolute (with y-offset) Addressing Mode

Absolute Addressing Mode, in which the address is offset by the `y register`.  
Any additional clock cycle is required if the page of the address changes, after adding the offset.

### IND - Indirect Addresing Mode

This is how Pointers are implemented in 6502. In this the Suppiled address in used to  
fetch data from another location pointed by the suppiled address.  

#### Bug :

If the low byte is FF that is 255 then adding one (+1) to it effectively changes the page  
of the address, causing an additional clock cycle. But 6502 completely ignores this page  
crossing and just doesn't consider the additional one.

### IZX - Indirect (with zero-page, x-offset) Addressing Mode

Works as the Indirect Addressing Mode. But the Address specified is offset by `x register`  
to get the address of the data.

### IZY - Indirect (with zero-page, x-offset) Addressing Mode

In Previous x and y variants, they were direct opposites of each other. But in this case  
there is a slight change.  

Works as the Indirect Addressing Mode. But the Address specified is **not** offset by `y register`  
Now the address pointing to the data is read and then it is offset by `y register`.  
Any additional clock cycle is required if the page of the address changes, after adding the offset.  