#pragma once
#include <utility>

#include "Opcode.h"

class Instruction {
private:
    Opcode opcode;
    uint16_t operandAddress;
    short pageBoundaryCost;
public:
    Instruction(Opcode opcode, uint16_t operandAddress, short pageBoundaryCost)
    : opcode(opcode)
    , operandAddress(operandAddress)
    , pageBoundaryCost(pageBoundaryCost) {}

    const Opcode &getOpcode() const {
        return opcode;
    }

    uint16_t getOperandAddress() const {
        return operandAddress;
    }

    short getPageBoundaryCost() const {
        return pageBoundaryCost;
    }
};

