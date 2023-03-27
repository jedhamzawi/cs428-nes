#include "OpcodeTable.h"

const std::unordered_map<uint8_t, Opcode> OpcodeTable::opcodeTable = {

    // Load and Store Operations
        // LDA
        {0xA9, Opcode(Mnemonic(LDA), AddressingMode::IMMEDIATE, 2, 2)},
        {0xA5, Opcode(Mnemonic(LDA), AddressingMode::ZERO_PAGE, 2, 3)},
        {0xB5, Opcode(Mnemonic(LDA), AddressingMode::ZERO_PAGE_X, 2, 4)},
        {0xAD, Opcode(Mnemonic(LDA), AddressingMode::ABSOLUTE, 3, 4)},
        {0xBD, Opcode(Mnemonic(LDA), AddressingMode::ABSOLUTE_X, 3, 4)},    // +1 cycle if page crossed
        {0xB9, Opcode(Mnemonic(LDA), AddressingMode::ABSOLUTE_Y, 3, 4)},    // +1 cycle if page crossed
        {0xA1, Opcode(Mnemonic(LDA), AddressingMode::INDIRECT_X, 2, 6)},
        {0xB1, Opcode(Mnemonic(LDA), AddressingMode::INDIRECT_Y, 2, 5)},    // +1 cycle if page crossed

        // LDX
        {0xA2, Opcode(Mnemonic(LDX), AddressingMode::IMMEDIATE, 2, 2)},
        {0xA6, Opcode(Mnemonic(LDX), AddressingMode::ZERO_PAGE, 2, 3)},
        {0xB6, Opcode(Mnemonic(LDX), AddressingMode::ZERO_PAGE_Y, 2, 4)},
        {0xAE, Opcode(Mnemonic(LDX), AddressingMode::ABSOLUTE, 3, 4)},
        {0xBE, Opcode(Mnemonic(LDX), AddressingMode::ABSOLUTE_Y, 3, 4)},    // +1 cycle if page crossed

        // LDY
        {0xA0, Opcode(Mnemonic(LDY), AddressingMode::IMMEDIATE, 2, 2)},
        {0xA4, Opcode(Mnemonic(LDY), AddressingMode::ZERO_PAGE, 2, 3)},
        {0xB4, Opcode(Mnemonic(LDY), AddressingMode::ZERO_PAGE_X, 2, 4)},
        {0xAC, Opcode(Mnemonic(LDY), AddressingMode::ABSOLUTE, 3, 4)},
        {0xBC, Opcode(Mnemonic(LDY), AddressingMode::ABSOLUTE_X, 3, 4)},    // +1 cycle if page crossed

        // STA
        {0x85, Opcode(Mnemonic(STA), AddressingMode::ZERO_PAGE, 2, 3)},
        {0x95, Opcode(Mnemonic(STA), AddressingMode::ZERO_PAGE_X, 2, 4)},
        {0x8D, Opcode(Mnemonic(STA), AddressingMode::ABSOLUTE, 3, 4)},
        {0x9D, Opcode(Mnemonic(STA), AddressingMode::ABSOLUTE_X, 3, 5)},
        {0x99, Opcode(Mnemonic(STA), AddressingMode::ABSOLUTE_Y, 3, 5)},
        {0x81, Opcode(Mnemonic(STA), AddressingMode::INDIRECT_X, 2, 6)},
        {0x91, Opcode(Mnemonic(STA), AddressingMode::INDIRECT_Y, 2, 6)},

        // STX
        {0x86, Opcode(Mnemonic(STX), AddressingMode::ZERO_PAGE, 2, 3)},
        {0x96, Opcode(Mnemonic(STX), AddressingMode::ZERO_PAGE_Y, 2, 4)},
        {0x8E, Opcode(Mnemonic(STX), AddressingMode::ABSOLUTE, 3, 4)},

        // STY
        {0x84, Opcode(Mnemonic(STY), AddressingMode::ZERO_PAGE, 2, 3)},
        {0x94, Opcode(Mnemonic(STY), AddressingMode::ZERO_PAGE_X, 2, 4)},
        {0x8C, Opcode(Mnemonic(STY), AddressingMode::ABSOLUTE, 3, 4)},
    
    // Register Transfers
        // TAX
        {0xAA, Opcode(Mnemonic(TAX), AddressingMode::IMPLIED, 1, 2)},

        // TAY
        {0xA8, Opcode(Mnemonic(TAY), AddressingMode::IMPLIED, 1, 2)},

        // TXA
        {0x8A, Opcode(Mnemonic(TXA), AddressingMode::IMPLIED, 1, 2)},

        // TYA
        {0x98, Opcode(Mnemonic(TYA), AddressingMode::IMPLIED, 1, 2)},
    
    // Stack Operations
        // TSX
        {0xBA, Opcode(Mnemonic(TSX), AddressingMode::IMPLIED, 1, 2)},

        // TXS
        {0x9A, Opcode(Mnemonic(TXS), AddressingMode::IMPLIED, 1, 2)},

        // PHA
        {0x48, Opcode(Mnemonic(PHA), AddressingMode::IMPLIED, 1, 3)},

        // PHP
        {0x08, Opcode(Mnemonic(PHP), AddressingMode::IMPLIED, 1, 3)},

        // PLA
        {0x68, Opcode(Mnemonic(PLA), AddressingMode::IMPLIED, 1, 4)},

        // PLP
        {0x28, Opcode(Mnemonic(PLP), AddressingMode::IMPLIED, 1, 4)},

    // Logical
        // AND
        {0x29, Opcode(Mnemonic(AND), AddressingMode::IMMEDIATE, 2, 2)},
        {0x25, Opcode(Mnemonic(AND), AddressingMode::ZERO_PAGE, 2, 3)},
        {0x35, Opcode(Mnemonic(AND), AddressingMode::ZERO_PAGE_X, 2, 4)},
        {0x2D, Opcode(Mnemonic(AND), AddressingMode::ABSOLUTE, 3, 4)},
        {0x3D, Opcode(Mnemonic(AND), AddressingMode::ABSOLUTE_X, 3, 4)},    // +1 cycle if page crossed
        {0x39, Opcode(Mnemonic(AND), AddressingMode::ABSOLUTE_Y, 3, 4)},    // +1 cycle if page crossed
        {0x21, Opcode(Mnemonic(AND), AddressingMode::INDIRECT_X, 2, 6)},
        {0x31, Opcode(Mnemonic(AND), AddressingMode::INDIRECT_Y, 2, 5)},    // +1 cycle if page crossed

        // EOR
        {0x49, Opcode(Mnemonic(EOR), AddressingMode::IMMEDIATE, 2, 2)},
        {0x45, Opcode(Mnemonic(EOR), AddressingMode::ZERO_PAGE, 2, 3)},
        {0x55, Opcode(Mnemonic(EOR), AddressingMode::ZERO_PAGE_X, 2, 4)},
        {0x4D, Opcode(Mnemonic(EOR), AddressingMode::ABSOLUTE, 3, 4)},
        {0x5D, Opcode(Mnemonic(EOR), AddressingMode::ABSOLUTE_X, 3, 4)},    // +1 cycle if page crossed
        {0x59, Opcode(Mnemonic(EOR), AddressingMode::ABSOLUTE_Y, 3, 4)},    // +1 cycle if page crossed
        {0x41, Opcode(Mnemonic(EOR), AddressingMode::INDIRECT_X, 2, 6)},
        {0x51, Opcode(Mnemonic(EOR), AddressingMode::INDIRECT_Y, 2, 5)},    // +1 cycle if page crossed

        // ORA
        {0x09, Opcode(Mnemonic(ORA), AddressingMode::IMMEDIATE, 2, 2)},
        {0x05, Opcode(Mnemonic(ORA), AddressingMode::ZERO_PAGE, 2, 3)},
        {0x15, Opcode(Mnemonic(ORA), AddressingMode::ZERO_PAGE_X, 2, 4)},
        {0x0D, Opcode(Mnemonic(ORA), AddressingMode::ABSOLUTE, 3, 4)},
        {0x1D, Opcode(Mnemonic(ORA), AddressingMode::ABSOLUTE_X, 3, 4)},    // +1 cycle if page crossed
        {0x19, Opcode(Mnemonic(ORA), AddressingMode::ABSOLUTE_Y, 3, 4)},    // +1 cycle if page crossed
        {0x01, Opcode(Mnemonic(ORA), AddressingMode::INDIRECT_X, 2, 6)},
        {0x11, Opcode(Mnemonic(ORA), AddressingMode::INDIRECT_Y, 2, 5)},    // +1 cycle if page crossed

        // BIT
        {0x24, Opcode(Mnemonic(BIT), AddressingMode::ZERO_PAGE, 2, 3)},
        {0x2C, Opcode(Mnemonic(BIT), AddressingMode::ABSOLUTE, 3, 4)},

    // Arithmetic
        // ADC
        {0x69, Opcode(Mnemonic(ADC), AddressingMode::IMMEDIATE, 2, 2)},
        {0x65, Opcode(Mnemonic(ADC), AddressingMode::ZERO_PAGE, 2, 3)},
        {0x75, Opcode(Mnemonic(ADC), AddressingMode::ZERO_PAGE_X, 2, 4)},
        {0x6D, Opcode(Mnemonic(ADC), AddressingMode::ABSOLUTE, 3, 4)},
        {0x7D, Opcode(Mnemonic(ADC), AddressingMode::ABSOLUTE_X, 3, 4)},    // +1 cycle if page crossed
        {0x79, Opcode(Mnemonic(ADC), AddressingMode::ABSOLUTE_Y, 3, 4)},    // +1 cycle if page crossed
        {0x61, Opcode(Mnemonic(ADC), AddressingMode::INDIRECT_X, 2, 6)},
        {0x71, Opcode(Mnemonic(ADC), AddressingMode::INDIRECT_Y, 2, 5)},    // +1 cycle if page crossed

        // SBC
        {0xE9, Opcode(Mnemonic(SBC), AddressingMode::IMMEDIATE, 2, 2)},
        {0xE5, Opcode(Mnemonic(SBC), AddressingMode::ZERO_PAGE, 2, 3)},
        {0xF5, Opcode(Mnemonic(SBC), AddressingMode::ZERO_PAGE_X, 2, 4)},
        {0xED, Opcode(Mnemonic(SBC), AddressingMode::ABSOLUTE, 3, 4)},
        {0xFD, Opcode(Mnemonic(SBC), AddressingMode::ABSOLUTE_X, 3, 4)},    // +1 cycle if page crossed
        {0xF9, Opcode(Mnemonic(SBC), AddressingMode::ABSOLUTE_Y, 3, 4)},    // +1 cycle if page crossed
        {0xE1, Opcode(Mnemonic(SBC), AddressingMode::INDIRECT_X, 2, 6)},
        {0xF1, Opcode(Mnemonic(SBC), AddressingMode::INDIRECT_Y, 2, 5)},    // +1 cycle if page crossed

    // Comparison
        // CMP
        {0xC9, Opcode(Mnemonic(CMP), AddressingMode::IMMEDIATE, 2, 2)},
        {0xC5, Opcode(Mnemonic(CMP), AddressingMode::ZERO_PAGE, 2, 3)},
        {0xD5, Opcode(Mnemonic(CMP), AddressingMode::ZERO_PAGE_X, 2, 4)},
        {0xCD, Opcode(Mnemonic(CMP), AddressingMode::ABSOLUTE, 3, 4)},
        {0xDD, Opcode(Mnemonic(CMP), AddressingMode::ABSOLUTE_X, 3, 4)},    // +1 cycle if page crossed
        {0xD9, Opcode(Mnemonic(CMP), AddressingMode::ABSOLUTE_Y, 3, 4)},    // +1 cycle if page crossed
        {0xC1, Opcode(Mnemonic(CMP), AddressingMode::INDIRECT_X, 2, 6)},
        {0xD1, Opcode(Mnemonic(CMP), AddressingMode::INDIRECT_Y, 2, 5)},    // +1 cycle if page crossed

        // CPX
        {0xE0, Opcode(Mnemonic(CPX), AddressingMode::IMMEDIATE, 2, 2)},
        {0xE4, Opcode(Mnemonic(CPX), AddressingMode::ZERO_PAGE, 2, 3)},
        {0xEC, Opcode(Mnemonic(CPX), AddressingMode::ABSOLUTE, 3, 4)},

        // CPY
        {0xC0, Opcode(Mnemonic(CPY), AddressingMode::IMMEDIATE, 2, 2)},
        {0xC4, Opcode(Mnemonic(CPY), AddressingMode::ZERO_PAGE, 2, 3)},
        {0xCC, Opcode(Mnemonic(CPY), AddressingMode::ABSOLUTE, 3, 4)},

    // Increments and Decrements
        // INC
        {0xE6, Opcode(Mnemonic(INC), AddressingMode::ZERO_PAGE, 2, 5)},
        {0xF6, Opcode(Mnemonic(INC), AddressingMode::ZERO_PAGE_X, 2, 6)},
        {0xEE, Opcode(Mnemonic(INC), AddressingMode::ABSOLUTE, 3, 6)},
        {0xFE, Opcode(Mnemonic(INC), AddressingMode::ABSOLUTE_X, 3, 7)},
        
        // INX
        {0xE8, Opcode(Mnemonic(INX), AddressingMode::IMPLIED, 1, 2)},
        
        // INY
        {0xC8, Opcode(Mnemonic(INY), AddressingMode::IMPLIED, 1, 2)},

        // DEC
        {0xC6, Opcode(Mnemonic(DEC), AddressingMode::ZERO_PAGE, 2, 5)},
        {0xD6, Opcode(Mnemonic(DEC), AddressingMode::ZERO_PAGE_X, 2, 6)},
        {0xCE, Opcode(Mnemonic(DEC), AddressingMode::ABSOLUTE, 3, 6)},
        {0xDE, Opcode(Mnemonic(DEC), AddressingMode::ABSOLUTE_X, 3, 7)},

        // DEX
        {0xCA, Opcode(Mnemonic(DEX), AddressingMode::IMPLIED, 1, 2)},

        // DEY
        {0x88, Opcode(Mnemonic(DEY), AddressingMode::IMPLIED, 1, 2)},

    // Shifts
        // ASL
        {0x0A, Opcode(Mnemonic(ASL), AddressingMode::ACCUMULATOR, 1, 2)},
        {0x06, Opcode(Mnemonic(ASL), AddressingMode::ZERO_PAGE, 2, 5)},
        {0x16, Opcode(Mnemonic(ASL), AddressingMode::ZERO_PAGE_X, 2, 6)},
        {0x0E, Opcode(Mnemonic(ASL), AddressingMode::ABSOLUTE, 3, 6)},
        {0x1E, Opcode(Mnemonic(ASL), AddressingMode::ABSOLUTE_X, 3, 7)},

        // LSR
        {0x4A, Opcode(Mnemonic(LSR), AddressingMode::ACCUMULATOR, 1, 2)},
        {0x46, Opcode(Mnemonic(LSR), AddressingMode::ZERO_PAGE, 2, 5)},
        {0x56, Opcode(Mnemonic(LSR), AddressingMode::ZERO_PAGE_X, 2, 6)},
        {0x4E, Opcode(Mnemonic(LSR), AddressingMode::ABSOLUTE, 3, 6)},
        {0x5E, Opcode(Mnemonic(LSR), AddressingMode::ABSOLUTE_X, 3, 7)},

        // ROL
        {0x2A, Opcode(Mnemonic(ROL), AddressingMode::ACCUMULATOR, 1, 2)},
        {0x26, Opcode(Mnemonic(ROL), AddressingMode::ZERO_PAGE, 2, 5)},
        {0x36, Opcode(Mnemonic(ROL), AddressingMode::ZERO_PAGE_X, 2, 6)},
        {0x2E, Opcode(Mnemonic(ROL), AddressingMode::ABSOLUTE, 3, 6)},
        {0x3E, Opcode(Mnemonic(ROL), AddressingMode::ABSOLUTE_X, 3, 7)},

        // ROR
        {0x6A, Opcode(Mnemonic(ROR), AddressingMode::ACCUMULATOR, 1, 2)},
        {0x66, Opcode(Mnemonic(ROR), AddressingMode::ZERO_PAGE, 2, 5)},
        {0x76, Opcode(Mnemonic(ROR), AddressingMode::ZERO_PAGE_X, 2, 6)},
        {0x6E, Opcode(Mnemonic(ROR), AddressingMode::ABSOLUTE, 3, 6)},
        {0x7E, Opcode(Mnemonic(ROR), AddressingMode::ABSOLUTE_X, 3, 7)},

    // Jumps and Calls
        // JMP
        {0x4C, Opcode(Mnemonic(JMP), AddressingMode::ABSOLUTE, 3, 3)},
        {0x6C, Opcode(Mnemonic(JMP), AddressingMode::INDIRECT, 3, 5)},

        // JSR
        {0x20, Opcode(Mnemonic(JSR), AddressingMode::ABSOLUTE, 3, 6)},

        // RTS
        {0x60, Opcode(Mnemonic(RTS), AddressingMode::IMPLIED, 1, 6)},

    // Branches
        // BCC
        {0x90, Opcode(Mnemonic(BCC), AddressingMode::RELATIVE, 2, 2)},      // +1 cycle if branch succeeds
                                                                    // +2 if to a new page
        // BCS
        {0xB0, Opcode(Mnemonic(BCS), AddressingMode::RELATIVE, 2, 2)},      // +1 cycle if branch succeeds
                                                                    // +2 if to a new page
        // BEQ
        {0xF0, Opcode(Mnemonic(BEQ), AddressingMode::RELATIVE, 2, 2)},      // +1 cycle if branch succeeds
                                                                    // +2 if to a new page
        // BMI
        {0x30, Opcode(Mnemonic(BMI), AddressingMode::RELATIVE, 2, 2)},      // +1 cycle if branch succeeds
                                                                    // +2 if to a new page
        // BNE
        {0xD0, Opcode(Mnemonic(BNE), AddressingMode::RELATIVE, 2, 2)},      // +1 cycle if branch succeeds
                                                                    // +2 if to a new page
        // BPL
        {0x10, Opcode(Mnemonic(BPL), AddressingMode::RELATIVE, 2, 2)},      // +1 cycle if branch succeeds
                                                                    // +2 if to a new page
        // BVC
        {0x50, Opcode(Mnemonic(BVC), AddressingMode::RELATIVE, 2, 2)},      // +1 cycle if branch succeeds
                                                                    // +2 if to a new page
        // BVS
        {0x70, Opcode(Mnemonic(BVS), AddressingMode::RELATIVE, 2, 2)},      // +1 cycle if branch succeeds
                                                                    // +2 if to a new page
    // Status Flag Changes
        // CLC
        {0x18, Opcode(Mnemonic(CLC), AddressingMode::IMPLIED, 1, 2)},
        // CLD
        {0xD8, Opcode(Mnemonic(CLD), AddressingMode::IMPLIED, 1, 2)},
        // CLI
        {0x58, Opcode(Mnemonic(CLI), AddressingMode::IMPLIED, 1, 2)},
        // CLV
        {0xB8, Opcode(Mnemonic(CLV), AddressingMode::IMPLIED, 1, 2)},
        // SEC
        {0x38, Opcode(Mnemonic(SEC), AddressingMode::IMPLIED, 1, 2)},
        // SED
        {0xF8, Opcode(Mnemonic(SED), AddressingMode::IMPLIED, 1, 2)},
        // SEI
        {0x78, Opcode(Mnemonic(SEI), AddressingMode::IMPLIED, 1, 2)},

    // System Functions
        // BRK
        {0x00, Opcode(Mnemonic(BRK), AddressingMode::IMPLIED, 1, 7)},
        // NOP
        {0xEA, Opcode(Mnemonic(NOP), AddressingMode::IMPLIED, 1, 2)},
        // RTI
        {0x40, Opcode(Mnemonic(RTI), AddressingMode::IMPLIED, 1, 6)}
};

const Opcode& OpcodeTable::getOpcode(uint8_t opcode) {
    return opcodeTable.at(opcode);
}