#pragma once
#include <utility>

#include "Opcode.h"

class Instruction {
private:
    Opcode opcode;
    uint8_t operand;
    short pageBoundaryCost;
public:
    Instruction(Opcode opcode, uint8_t operand, short pageBoundaryCost)
    : opcode(std::move(opcode))
    , operand(operand)
    , pageBoundaryCost(pageBoundaryCost) {}

    const Opcode &getOpcode() const {
        return opcode;
    }

    uint8_t getOperand() const {
        return operand;
    }

    short getPageBoundaryCost() const {
        return pageBoundaryCost;
    }
};

