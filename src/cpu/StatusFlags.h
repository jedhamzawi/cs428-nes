#pragma once

#include <cstdint>

class StatusFlags {
private:
    // byte = Negative, Overflow, _, BreakCommand, DecimalMode, InterruptDisable, Zero, Carry
    bool carryFlag = 0;
    bool zeroFlag = 0;
    bool interruptFlag = 0;
    // bool decimalFlag = 0;                            // Ricoh modded the chip so NES doesn't have decimal mode
    bool breakFlag = 0;
    // unused bit
    bool overflowFlag = 0;
    bool negativeFlag = 0;

public:
    StatusFlags(bool carryFlag, bool zeroFlag, bool interruptFlag, 
                bool breakFlag, bool overflowFlag, bool negativeFlag);
    StatusFlags(uint8_t byte);
    StatusFlags();
    ~StatusFlags();

    bool hasCarryFlag();
    void setCarryFlag(bool flag);

    bool hasZeroFlag();
    void setZeroFlag(bool flag);

    bool hasInterruptFlag();
    void setInterruptFlag(bool flag);

    bool hasBreakFlag();
    void setBreakFlag(bool flag);

    bool hasOverflowFlag();
    void setOverflowFlag(bool flag);

    bool hasNegativeFlag();
    void setNegativeFlag(bool flag);

    uint8_t getFlags();
    void setFlags(uint8_t byte);
    
    void resetFlags();
};