#pragma once
#include <string>
#include <unordered_set>

#include "AddressingMode.h"

class Opcode {
private:
    std::string mnemonic;
    AddressingMode mode;
    uint8_t bytes;
    uint8_t cycles;
public:
    Opcode(std::string  mnemonic, AddressingMode mode, uint8_t bytes, uint8_t cycles);

    std::string getMnemonic() const;
    AddressingMode getAddressingMode() const;
    uint8_t getBytes() const;
    uint8_t getCycles() const;
};