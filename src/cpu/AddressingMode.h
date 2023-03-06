#pragma once

enum class AddressingMode {
    IMPLIED,         // Implied addressing mode (no operand)
    ACCUMULATOR,     // Accumulator addressing mode (operand is in A register)
    IMMEDIATE,       // Immediate addressing mode (operand is a constant)
    ZERO_PAGE,       // Zero page addressing mode (operand is a memory address in the first 256 bytes of memory)
    ZERO_PAGE_X,     // Zero page,X addressing mode (operand is a memory address in the first 256 bytes of memory, indexed by X)
    ZERO_PAGE_Y,     // Zero page,Y addressing mode (operand is a memory address in the first 256 bytes of memory, indexed by Y)
    RELATIVE,        // Relative addressing mode (operand is a signed 8-bit offset from the program counter)
    ABSOLUTE,        // Absolute addressing mode (operand is a memory address in the full 64K address space)
    ABSOLUTE_X,      // Absolute,X addressing mode (operand is a memory address in the full 64K address space, indexed by X)
    ABSOLUTE_Y,      // Absolute,Y addressing mode (operand is a memory address in the full 64K address space, indexed by Y)
    INDIRECT,        // Indirect addressing mode (operand is a memory address that contains a memory address)
    INDIRECT_X,      // Indirect,X addressing mode (operand is a memory address that is used as an index into the zero page)
    INDIRECT_Y       // Indirect,Y addressing mode (operand is a memory address in the zero page that is indexed by Y)   
};