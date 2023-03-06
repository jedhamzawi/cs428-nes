#include "OpcodeTable.h"

const std::unordered_map<uint8_t, Opcode> OpcodeTable::opcodeTable = {

    // Load and Store Operations
        // LDA
        {0xA9, Opcode("LDA", AddressingMode::IMMEDIATE, 2, 2)},
        {0xA5, Opcode("LDA", AddressingMode::ZERO_PAGE, 2, 3)},
        {0xB5, Opcode("LDA", AddressingMode::ZERO_PAGE_X, 2, 4)},
        {0xAD, Opcode("LDA", AddressingMode::ABSOLUTE, 3, 4)},
        {0xBD, Opcode("LDA", AddressingMode::ABSOLUTE_X, 3, 4)},    // +1 cycle if page crossed
        {0xB9, Opcode("LDA", AddressingMode::ABSOLUTE_Y, 3, 4)},    // +1 cycle if page crossed
        {0xA1, Opcode("LDA", AddressingMode::INDIRECT_X, 2, 6)},
        {0xB1, Opcode("LDA", AddressingMode::INDIRECT_Y, 2, 5)},    // +1 cycle if page crossed

        // LDX
        {0xA2, Opcode("LDX", AddressingMode::IMMEDIATE, 2, 2)},
        {0xA6, Opcode("LDX", AddressingMode::ZERO_PAGE, 2, 3)},
        {0xB6, Opcode("LDX", AddressingMode::ZERO_PAGE_Y, 2, 4)},
        {0xAE, Opcode("LDX", AddressingMode::ABSOLUTE, 3, 4)},
        {0xBE, Opcode("LDX", AddressingMode::ABSOLUTE_Y, 3, 4)},    // +1 cycle if page crossed

        // LDY
        {0xA0, Opcode("LDY", AddressingMode::IMMEDIATE, 2, 2)},
        {0xA4, Opcode("LDY", AddressingMode::ZERO_PAGE, 2, 3)},
        {0xB4, Opcode("LDY", AddressingMode::ZERO_PAGE_X, 2, 4)},
        {0xAC, Opcode("LDY", AddressingMode::ABSOLUTE, 3, 4)},
        {0xBC, Opcode("LDY", AddressingMode::ABSOLUTE_X, 3, 4)},    // +1 cycle if page crossed

        // STA
        {0x85, Opcode("STA", AddressingMode::ZERO_PAGE, 2, 3)},
        {0x95, Opcode("STA", AddressingMode::ZERO_PAGE_X, 2, 4)},
        {0x8D, Opcode("STA", AddressingMode::ABSOLUTE, 3, 4)},
        {0x9D, Opcode("STA", AddressingMode::ABSOLUTE_X, 3, 5)},
        {0x99, Opcode("STA", AddressingMode::ABSOLUTE_Y, 3, 5)},
        {0x81, Opcode("STA", AddressingMode::INDIRECT_X, 2, 6)},
        {0x91, Opcode("STA", AddressingMode::INDIRECT_Y, 2, 6)},

        // STX
        {0x86, Opcode("STX", AddressingMode::ZERO_PAGE, 2, 3)},
        {0x96, Opcode("STX", AddressingMode::ZERO_PAGE_Y, 2, 4)},
        {0x8E, Opcode("STX", AddressingMode::ABSOLUTE, 3, 4)},

        // STY
        {0x84, Opcode("STY", AddressingMode::ZERO_PAGE, 2, 3)},
        {0x94, Opcode("STY", AddressingMode::ZERO_PAGE_X, 2, 4)},
        {0x8C, Opcode("STY", AddressingMode::ABSOLUTE, 3, 4)},
    
    // Register Transfers
        // TAX
        {0xAA, Opcode("TAX", AddressingMode::IMPLIED, 1, 2)},

        // TAY
        {0xA8, Opcode("TAY", AddressingMode::IMPLIED, 1, 2)},

        // TXA
        {0x8A, Opcode("TXA", AddressingMode::IMPLIED, 1, 2)},

        // TYA
        {0x98, Opcode("TYA", AddressingMode::IMPLIED, 1, 2)},
    
    // Stack Operations
        // TSX
        {0xBA, Opcode("TSX", AddressingMode::IMPLIED, 1, 2)},

        // TXS
        {0x9A, Opcode("TXS", AddressingMode::IMPLIED, 1, 2)},

        // PHA
        {0x48, Opcode("PHA", AddressingMode::IMPLIED, 1, 3)},

        // PHP
        {0x08, Opcode("PHP", AddressingMode::IMPLIED, 1, 3)},

        // PLA
        {0x68, Opcode("PLA", AddressingMode::IMPLIED, 1, 4)},

        // PLP
        {0x28, Opcode("PLP", AddressingMode::IMPLIED, 1, 4)},

    // Logical
        // AND
        {0x29, Opcode("AND", AddressingMode::IMMEDIATE, 2, 2)},
        {0x25, Opcode("AND", AddressingMode::ZERO_PAGE, 2, 3)},
        {0x35, Opcode("AND", AddressingMode::ZERO_PAGE_X, 2, 4)},
        {0x2D, Opcode("AND", AddressingMode::ABSOLUTE, 3, 4)},
        {0x3D, Opcode("AND", AddressingMode::ABSOLUTE_X, 3, 4)},    // +1 cycle if page crossed
        {0x39, Opcode("AND", AddressingMode::ABSOLUTE_Y, 3, 4)},    // +1 cycle if page crossed
        {0x21, Opcode("AND", AddressingMode::INDIRECT_X, 2, 6)},
        {0x31, Opcode("AND", AddressingMode::INDIRECT_Y, 2, 5)},    // +1 cycle if page crossed

        // EOR
        {0x49, Opcode("EOR", AddressingMode::IMMEDIATE, 2, 2)},
        {0x45, Opcode("EOR", AddressingMode::ZERO_PAGE, 2, 3)},
        {0x55, Opcode("EOR", AddressingMode::ZERO_PAGE_X, 2, 4)},
        {0x4D, Opcode("EOR", AddressingMode::ABSOLUTE, 3, 4)},
        {0x5D, Opcode("EOR", AddressingMode::ABSOLUTE_X, 3, 4)},    // +1 cycle if page crossed
        {0x59, Opcode("EOR", AddressingMode::ABSOLUTE_Y, 3, 4)},    // +1 cycle if page crossed
        {0x41, Opcode("EOR", AddressingMode::INDIRECT_X, 2, 6)},
        {0x51, Opcode("EOR", AddressingMode::INDIRECT_Y, 2, 5)},    // +1 cycle if page crossed

        // ORA
        {0x09, Opcode("ORA", AddressingMode::IMMEDIATE, 2, 2)},
        {0x05, Opcode("ORA", AddressingMode::ZERO_PAGE, 2, 3)},
        {0x15, Opcode("ORA", AddressingMode::ZERO_PAGE_X, 2, 4)},
        {0x0D, Opcode("ORA", AddressingMode::ABSOLUTE, 3, 4)},
        {0x1D, Opcode("ORA", AddressingMode::ABSOLUTE_X, 3, 4)},    // +1 cycle if page crossed
        {0x19, Opcode("ORA", AddressingMode::ABSOLUTE_Y, 3, 4)},    // +1 cycle if page crossed
        {0x01, Opcode("ORA", AddressingMode::INDIRECT_X, 2, 6)},
        {0x11, Opcode("ORA", AddressingMode::INDIRECT_Y, 2, 5)},    // +1 cycle if page crossed

        // BIT
        {0x24, Opcode("BIT", AddressingMode::ZERO_PAGE, 2, 3)},
        {0x2C, Opcode("BIT", AddressingMode::ABSOLUTE, 3, 4)},

    // Arithmetic
        // ADC
        {0x69, Opcode("ADC", AddressingMode::IMMEDIATE, 2, 2)},
        {0x65, Opcode("ADC", AddressingMode::ZERO_PAGE, 2, 3)},
        {0x75, Opcode("ADC", AddressingMode::ZERO_PAGE_X, 2, 4)},
        {0x6D, Opcode("ADC", AddressingMode::ABSOLUTE, 3, 4)},
        {0x7D, Opcode("ADC", AddressingMode::ABSOLUTE_X, 3, 4)},    // +1 cycle if page crossed
        {0x79, Opcode("ADC", AddressingMode::ABSOLUTE_Y, 3, 4)},    // +1 cycle if page crossed
        {0x61, Opcode("ADC", AddressingMode::INDIRECT_X, 2, 6)},
        {0x71, Opcode("ADC", AddressingMode::INDIRECT_Y, 2, 5)},    // +1 cycle if page crossed

        // SBC
        {0xE9, Opcode("SBC", AddressingMode::IMMEDIATE, 2, 2)},
        {0xE5, Opcode("SBC", AddressingMode::ZERO_PAGE, 2, 3)},
        {0xF5, Opcode("SBC", AddressingMode::ZERO_PAGE_X, 2, 4)},
        {0xED, Opcode("SBC", AddressingMode::ABSOLUTE, 3, 4)},
        {0xFD, Opcode("SBC", AddressingMode::ABSOLUTE_X, 3, 4)},    // +1 cycle if page crossed
        {0xF9, Opcode("SBC", AddressingMode::ABSOLUTE_Y, 3, 4)},    // +1 cycle if page crossed
        {0xE1, Opcode("SBC", AddressingMode::INDIRECT_X, 2, 6)},
        {0xF1, Opcode("SBC", AddressingMode::INDIRECT_Y, 2, 5)},    // +1 cycle if page crossed

        // CMP
        {0xC9, Opcode("CMP", AddressingMode::IMMEDIATE, 2, 2)},
        {0xC5, Opcode("CMP", AddressingMode::ZERO_PAGE, 2, 3)},
        {0xD5, Opcode("CMP", AddressingMode::ZERO_PAGE_X, 2, 4)},
        {0xCD, Opcode("CMP", AddressingMode::ABSOLUTE, 3, 4)},
        {0xDD, Opcode("CMP", AddressingMode::ABSOLUTE_X, 3, 4)},    // +1 cycle if page crossed
        {0xD9, Opcode("CMP", AddressingMode::ABSOLUTE_Y, 3, 4)},    // +1 cycle if page crossed
        {0xC1, Opcode("CMP", AddressingMode::INDIRECT_X, 2, 6)},
        {0xD1, Opcode("CMP", AddressingMode::INDIRECT_Y, 2, 5)},    // +1 cycle if page crossed

        // CPX
        {0xE0, Opcode("CPX", AddressingMode::IMMEDIATE, 2, 2)},
        {0xE4, Opcode("CPX", AddressingMode::ZERO_PAGE, 2, 3)},
        {0xEC, Opcode("CPX", AddressingMode::ABSOLUTE, 3, 4)},

        // CPY
        {0xC0, Opcode("CPY", AddressingMode::IMMEDIATE, 2, 2)},
        {0xC4, Opcode("CPY", AddressingMode::ZERO_PAGE, 2, 3)},
        {0xCC, Opcode("CPY", AddressingMode::ABSOLUTE, 3, 4)},

    // Increments and Decrements
        // INC
        {0xE6, Opcode("INC", AddressingMode::ZERO_PAGE, 2, 5)},
        {0xF6, Opcode("INC", AddressingMode::ZERO_PAGE_X, 2, 6)},
        {0xEE, Opcode("INC", AddressingMode::ABSOLUTE, 3, 6)},
        {0xFE, Opcode("INC", AddressingMode::ABSOLUTE_X, 3, 7)},
        
        // INX
        {0xE8, Opcode("INX", AddressingMode::IMPLIED, 1, 2)},
        
        // INY
        {0xC8, Opcode("INY", AddressingMode::IMPLIED, 1, 2)},

        // DEC
        {0xC6, Opcode("DEC", AddressingMode::ZERO_PAGE, 2, 5)},
        {0xD6, Opcode("DEC", AddressingMode::ZERO_PAGE_X, 2, 6)},
        {0xCE, Opcode("DEC", AddressingMode::ABSOLUTE, 3, 6)},
        {0xDE, Opcode("DEC", AddressingMode::ABSOLUTE_X, 3, 7)},

        // DEX
        {0xCA, Opcode("DEX", AddressingMode::IMPLIED, 1, 2)},

        // DEY
        {0x88, Opcode("DEY", AddressingMode::IMPLIED, 1, 2)},

    // Shifts
        // ASL
        {0x0A, Opcode("ASL", AddressingMode::ACCUMULATOR, 1, 2)},
        {0x06, Opcode("ASL", AddressingMode::ZERO_PAGE, 2, 5)},
        {0x16, Opcode("ASL", AddressingMode::ZERO_PAGE_X, 2, 6)},
        {0x0E, Opcode("ASL", AddressingMode::ABSOLUTE, 3, 6)},
        {0x1E, Opcode("ASL", AddressingMode::ABSOLUTE_X, 3, 7)},

        // LSR
        {0x4A, Opcode("LSR", AddressingMode::ACCUMULATOR, 1, 2)},
        {0x46, Opcode("LSR", AddressingMode::ZERO_PAGE, 2, 5)},
        {0x56, Opcode("LSR", AddressingMode::ZERO_PAGE_X, 2, 6)},
        {0x4E, Opcode("LSR", AddressingMode::ABSOLUTE, 3, 6)},
        {0x5E, Opcode("LSR", AddressingMode::ABSOLUTE_X, 3, 7)},

        // ROL
        {0x2A, Opcode("ROL", AddressingMode::ACCUMULATOR, 1, 2)},
        {0x26, Opcode("ROL", AddressingMode::ZERO_PAGE, 2, 5)},
        {0x36, Opcode("ROL", AddressingMode::ZERO_PAGE_X, 2, 6)},
        {0x2E, Opcode("ROL", AddressingMode::ABSOLUTE, 3, 6)},
        {0x3E, Opcode("ROL", AddressingMode::ABSOLUTE_X, 3, 7)},

        // ROR
        {0x6A, Opcode("ROR", AddressingMode::ACCUMULATOR, 1, 2)},
        {0x66, Opcode("ROR", AddressingMode::ZERO_PAGE, 2, 5)},
        {0x76, Opcode("ROR", AddressingMode::ZERO_PAGE_X, 2, 6)},
        {0x6E, Opcode("ROR", AddressingMode::ABSOLUTE, 3, 6)},
        {0x7E, Opcode("ROR", AddressingMode::ABSOLUTE_X, 3, 7)},

    // Jumps and Calls
        // JMP
        {0x4C, Opcode("JMP", AddressingMode::ABSOLUTE, 3, 3)},
        {0x6C, Opcode("JMP", AddressingMode::INDIRECT, 3, 5)},

        // JSR
        {0x20, Opcode("JSR", AddressingMode::ABSOLUTE, 3, 6)},

        // RTS
        {0x60, Opcode("RTS", AddressingMode::IMPLIED, 1, 6)},

    // Branches
        // BCC
        {0x90, Opcode("BCC", AddressingMode::RELATIVE, 2, 2)},      // +1 cycle if branch succeeds
                                                                    // +2 if to a new page
        // BCS
        {0xB0, Opcode("BCS", AddressingMode::RELATIVE, 2, 2)},      // +1 cycle if branch succeeds
                                                                    // +2 if to a new page
        // BEQ
        {0xF0, Opcode("BEQ", AddressingMode::RELATIVE, 2, 2)},      // +1 cycle if branch succeeds
                                                                    // +2 if to a new page
        // BMI
        {0x30, Opcode("BMI", AddressingMode::RELATIVE, 2, 2)},      // +1 cycle if branch succeeds
                                                                    // +2 if to a new page
        // BNE
        {0xD0, Opcode("BNE", AddressingMode::RELATIVE, 2, 2)},      // +1 cycle if branch succeeds
                                                                    // +2 if to a new page
        // BPL
        {0x10, Opcode("BPL", AddressingMode::RELATIVE, 2, 2)},      // +1 cycle if branch succeeds
                                                                    // +2 if to a new page
        // BVC
        {0x50, Opcode("BVC", AddressingMode::RELATIVE, 2, 2)},      // +1 cycle if branch succeeds
                                                                    // +2 if to a new page
        // BVS
        {0x70, Opcode("BVS", AddressingMode::RELATIVE, 2, 2)},      // +1 cycle if branch succeeds
                                                                    // +2 if to a new page
    // Status Flag Changes
        // CLC
        {0x18, Opcode("CLC", AddressingMode::IMPLIED, 1, 2)},
        // CLD
        {0xD8, Opcode("CLD", AddressingMode::IMPLIED, 1, 2)},
        // CLI
        {0x58, Opcode("CLI", AddressingMode::IMPLIED, 1, 2)},
        // CLV
        {0xB8, Opcode("CLV", AddressingMode::IMPLIED, 1, 2)},
        // SEC
        {0x38, Opcode("SEC", AddressingMode::IMPLIED, 1, 2)},
        // SED
        {0xF8, Opcode("SED", AddressingMode::IMPLIED, 1, 2)},
        // SEI
        {0x78, Opcode("SEI", AddressingMode::IMPLIED, 1, 2)},

    // System Functions
        // BRK
        {0x00, Opcode("BRK", AddressingMode::IMPLIED, 1, 7)},
        // NOP
        {0xEA, Opcode("NOP", AddressingMode::IMPLIED, 1, 2)},
        // RTI
        {0x40, Opcode("RTI", AddressingMode::IMPLIED, 1, 6)}
};

const Opcode& OpcodeTable::getOpcode(uint8_t opcode) {
    return opcodeTable.at(opcode);
}