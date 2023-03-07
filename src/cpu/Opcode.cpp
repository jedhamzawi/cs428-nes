#include "Opcode.h"

static const std::unordered_set<std::string> pcOpCodes = {"JMP", "JSR", "BCC", "BCS", "BEQ", "BMI", "BNE", "BPL", "BVC", "BVS", "BRK", "RTI", "RTS"};

Opcode::Opcode(const std::string& mnemonic, AddressingMode mode, uint8_t bytes, uint8_t cycles)
    // Initializer List
    : mnemonic(mnemonic)
    , mode(mode)
    , bytes(bytes)
    , cycles(cycles)
    , manipsPC(::pcOpCodes.count(mnemonic)){}

std::string Opcode::getMnemonic() const {
    return mnemonic;
}

AddressingMode Opcode::getAddressingMode() const {
    return mode;
}

uint8_t Opcode::getBytes() const {
    return bytes;
}

uint8_t Opcode::getCycles() const {
    return cycles;
}
