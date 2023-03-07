#include "Opcode.h"

#include <utility>

static const std::unordered_set<std::string> pcOpCodes = {"JMP", "JSR", "BCC", "BCS", "BEQ", "BMI", "BNE", "BPL", "BVC", "BVS", "BRK", "RTI", "RTS"};

Opcode::Opcode(std::string  mnemonic, AddressingMode mode, uint8_t bytes, uint8_t cycles)
    // Initializer List
    : mnemonic(std::move(mnemonic))
    , mode(mode)
    , bytes(bytes)
    , cycles(cycles) {}

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
