#pragma once
#include <string>
#include <unordered_set>

#include "AddressingMode.h"

class Opcode {
private:
    // The set of OpCodes that manipulate the program counter
    static const std::unordered_set<std::string> pcOpCodes;

    std::string mnemonic;
    AddressingMode mode;
    uint8_t bytes;
    uint8_t cycles;
public:
    Opcode(const std::string& mnemonic, AddressingMode mode, uint8_t bytes, uint8_t cycles);

    const bool manipsPC;

    std::string getMnemonic() const;
    AddressingMode getAddressingMode() const;
    uint8_t getBytes() const;
    uint8_t getCycles() const;
};