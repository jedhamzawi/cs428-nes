#include "OpcodeTable.h"

const std::unordered_map<uint8_t, Opcode> OpcodeTable::opcodeTable = {
    {0x00, Opcode("BRK", AddressingMode::IMPLIED, 1, 7)},
    {0x01, Opcode("ORA", AddressingMode::INDIRECT_X, 2, 6)},
    // add more opcodes here...
};

const Opcode& OpcodeTable::getOpcode(uint8_t opcode) {
    return opcodeTable.at(opcode);
}