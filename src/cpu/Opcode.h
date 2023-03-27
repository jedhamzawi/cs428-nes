#pragma once
#include <string>

enum Mnemonic {
    LDA, LDX, LDY, STA, STX, STY, TAX, TAY, TXA,
    TYA, TSX, TXS, PHA, PHP, PLA, PLP, AND, EOR,
    ORA, BIT, ADC, SBC, CMP, CPX, CPY, INC, INX,
    INY, DEC, DEX, DEY, ASL, LSR, ROL, ROR, JMP,
    JSR, RTS, BCC, BCS, BEQ, BMI, BNE, BPL, BVC,
    BVS, CLC, CLD, CLI, CLV, SEC, SED, SEI, BRK,
    NOP, RTI
};

static const char * MNEMONIC_STRINGS[] = {
    "LDA", "LDX", "LDY", "STA", "STX", "STY", "TAX", "TAY", "TXA",
    "TYA", "TSX", "TXS", "PHA", "PHP", "PLA", "PLP", "AND", "EOR",
    "ORA", "BIT", "ADC", "SBC", "CMP", "CPX", "CPY", "INC", "INX",
    "INY", "DEC", "DEX", "DEY", "ASL", "LSR", "ROL", "ROR", "JMP",
    "JSR", "RTS", "BCC", "BCS", "BEQ", "BMI", "BNE", "BPL", "BVC",
    "BVS", "CLC", "CLD", "CLI", "CLV", "SEC", "SED", "SEI", "BRK",
    "NOP", "RTI" };

enum AddressingMode {
    IMPLIED,         // Implied addressing mode (no operand)
    ACCUMULATOR,     // Accumulator addressing mode (operand is in A register)
    IMMEDIATE,       // Immediate addressing mode (operand is a constant)
    ZERO_PAGE,       // Zero page addressing mode (operand is a memory address in the first 256 numBytes of memory)
    ZERO_PAGE_X,     // Zero page,X addressing mode (operand is a memory address in the first 256 numBytes of memory, indexed by X)
    ZERO_PAGE_Y,     // Zero page,Y addressing mode (operand is a memory address in the first 256 numBytes of memory, indexed by Y)
    RELATIVE,        // Relative addressing mode (operand is a signed 8-bit offset from the program counter)
    ABSOLUTE,        // Absolute addressing mode (operand is a memory address in the full 64K address space)
    ABSOLUTE_X,      // Absolute,X addressing mode (operand is a memory address in the full 64K address space, indexed by X)
    ABSOLUTE_Y,      // Absolute,Y addressing mode (operand is a memory address in the full 64K address space, indexed by Y)
    INDIRECT,        // Indirect addressing mode (operand is a memory address that contains a memory address)
    INDIRECT_X,      // Indexed, Indirect. Indirect,X addressing mode (operand is a memory address that is used as an index into the zero page)
    INDIRECT_Y       // Indirect, Indexed. Indirect,Y addressing mode (operand is a memory address in the zero page that is indexed by Y)
};

class Opcode {
private:
    Mnemonic mnemonic;
    AddressingMode mode;
    short numBytes;
    short numCycles;
public:
    Opcode(Mnemonic mnemonic, AddressingMode mode, short numBytes, short numCycles);

    Mnemonic getMnemonic() const;
    std::string getMnemonicString() const;
    AddressingMode getAddressingMode() const;
    short getNumBytes() const;
    short getNumCycles() const;
};