#include "StatusFlags.h"

StatusFlags::StatusFlags(bool carryFlag, bool zeroFlag, bool interruptFlag, 
            bool breakFlag, bool overflowFlag, bool negativeFlag)
    : carryFlag(carryFlag), zeroFlag(zeroFlag), 
        interruptFlag(interruptFlag), breakFlag(breakFlag), 
        overflowFlag(overflowFlag), negativeFlag(negativeFlag) {}
StatusFlags::StatusFlags(uint8_t byte) {
    setFlags(byte);
};
StatusFlags::StatusFlags() {};
StatusFlags::~StatusFlags() = default;

// =================== Getters/Setters =================== //

bool StatusFlags::hasCarryFlag() {
    return this->carryFlag;
}

void StatusFlags::setCarryFlag(bool flag) {
    this->carryFlag = flag;
}

bool StatusFlags::hasZeroFlag() {
    return this->zeroFlag;
}

void StatusFlags::setZeroFlag(bool flag) {
    this->zeroFlag = flag;
}

bool StatusFlags::hasInterruptFlag() {
    return this->interruptFlag;
}

void StatusFlags::setInterruptFlag(bool flag) {
    this->interruptFlag = flag;
}

bool StatusFlags::hasBreakFlag() {
    return this->breakFlag;
}

void StatusFlags::setBreakFlag(bool flag) {
    this->breakFlag = flag;
}

bool StatusFlags::hasOverflowFlag() {
    return this->overflowFlag;
}

void StatusFlags::setOverflowFlag(bool flag) {
    this->overflowFlag = flag;
}

bool StatusFlags::hasNegativeFlag() {
    return this->negativeFlag;
}

void StatusFlags::setNegativeFlag(bool flag) {
    this->negativeFlag = flag;
}

uint8_t StatusFlags::getFlags() {
    uint8_t result = 0;
    result |= (this->carryFlag << 0);
    result |= (this->zeroFlag << 1);
    result |= (this->interruptFlag << 2);
    // no decimal mode
    result |= (this->breakFlag << 4);
    // unused bit
    result |= (this->overflowFlag << 6);
    result |= (this->negativeFlag << 7);
    return result;
}

void StatusFlags::setFlags(uint8_t byte) {
    this->carryFlag = (byte >> 0) & 0x01;
    this->zeroFlag = (byte >> 1) & 0x01;
    this->interruptFlag = (byte >> 2) & 0x01;
    // no decimal mode
    this->breakFlag = (byte >> 4) & 0x01;
    // unused bit
    this->overflowFlag = (byte >> 6) & 0x01;
    this->negativeFlag = (byte >> 7) & 0x01;
}

void StatusFlags::resetFlags() {
    this->carryFlag = 0;
    this->zeroFlag = 0;
    this->interruptFlag = 0;
    // no decimal mode
    this->breakFlag = 0;
    // unused bit
    this->overflowFlag = 0;
    this->negativeFlag = 0;
}