#pragma once

#include <cstdint>
#include <unordered_map>
#include "Opcode.h"

class OpcodeTable {
private:
    static const std::unordered_map<uint8_t, Opcode> opcodeTable;
public:
    static const Opcode& getOpcode(uint8_t opcode);
};