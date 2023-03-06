#include <iostream>

#include "NesCpu.h"
#include "Instruction.h"

NesCpu::NesCpu(uint8_t* memory): memory(memory){}

NesCpu::~NesCpu() = default;

void NesCpu::step() {
    // Check if starting instruction
    if (this->clock == 0) {
        std::cout << "PC: " << std::hex << 0u + this->programCounter;
        Instruction instruction = this->fetch();

        // TODO: Remove demo or log
        std::cout << "  " << instruction.getOpcode().getMnemonic();
        if (instruction.getOperand() != 0) {
            std::cout << " 0x" << 0u + instruction.getOperand();
        }
        std::cout << std::endl;


        int instructionCost = this->execute(instruction);


        // Set internal clock to instruction's step cost
        this->clock += instructionCost;
        incrementProgramCounter();
    }
    // Wait until instruction's step cost is paid
    this->clock--;
}


// ======================== HELPERS ======================== //

uint8_t NesCpu::read(uint16_t addr) {
    return memory[addr];
}

uint16_t NesCpu::read2Bytes(uint16_t addr) {
    uint16_t lowByte = read(addr);
    uint16_t highByte = read(addr + 1);
    return (highByte << 8) | lowByte;
}

void NesCpu::write(uint16_t addr, uint8_t val) {
    memory[addr] = val;
}

Instruction NesCpu::fetch() {
    uint8_t opcodeByte = read(this->programCounter);
    Opcode opcode = OpcodeTable::getOpcode(opcodeByte);
    this->programCounterOffset = 1;

    short pageBoundaryCost = 0;
    uint16_t operandAddress = getOperandAddress(opcode.getAddressingMode(), pageBoundaryCost);
    uint8_t operand = read(operandAddress);

    return {opcode, operand, pageBoundaryCost};
}


// ======================== INSTRUCTIONS ======================== //

int NesCpu::execute(const Instruction &instruction) {

    switch(instruction.getOpcode().getBytes()) {

        // ADC - add with carry
        case 0x61: case 0x65: case 0x69: case 0x6D:
        case 0x71: case 0x75: case 0x79: case 0x7D:
            adc(instruction.getOperand());
            break;

        // SBC - subtract with carry
        case 0xE1: case 0xE5: case 0xE9: case 0xED:
        case 0xF1: case 0xF5: case 0xF9: case 0xFD:
            sbc(instruction.getOperand());
            break;

        // Other instructions...
        
        default:
            // Unknown opcode, handle error here
            break;
    }
    return instruction.getOpcode().getCycles() + instruction.getPageBoundaryCost();
}

int NesCpu::adc(uint8_t operand) {
    uint16_t result = (uint16_t)this->regAccumulator + (uint16_t)operand + (uint16_t)isCarryFlag();
    this->regAccumulator = (uint8_t)result;

    setCarryFlag(result > 0xFF);
    setZeroFlag((result & 0xFF) == 0);
    setOverflowFlag((~((uint16_t)this->regAccumulator ^ (uint16_t)operand) & ((uint16_t)this->regAccumulator ^ (uint16_t)result) & 0x80) != 0);
    setNegativeFlag((result & 0x80) != 0);
}

int NesCpu::sbc(uint8_t operand) {
    
}


// Other instructions...


// ======================== ADDRESSING MODES ======================== //

// TODO: handle page crossing when modes like zero page x or absolute y wrap addresses??
uint16_t NesCpu::getOperandAddress(AddressingMode mode, short& pageBoundaryCost) {
    uint16_t addrLoc = this->programCounter + this->programCounterOffset;
    uint16_t address = 0;
    uint16_t absoluteAddress;
    uint8_t zeroPageAddress;
    uint16_t indirectAddress;
    switch (mode) {
        case AddressingMode::IMMEDIATE:
            address = addrLoc;
            this->programCounterOffset++;
            break;
        case AddressingMode::ABSOLUTE:
            address = read2Bytes(addrLoc);
            this->programCounterOffset += 2;
            break;
        case AddressingMode::ABSOLUTE_X:
            absoluteAddress = read2Bytes(addrLoc);
            this->programCounterOffset += 2;
            address = absoluteAddress + this->regX;

            if (this->isPageBoundaryCrossed(absoluteAddress, address)) {
                pageBoundaryCost = 1;
            }

            break;
        case AddressingMode::ABSOLUTE_Y:
            absoluteAddress = read2Bytes(addrLoc);
            this->programCounterOffset += 2;
            address = absoluteAddress + this->regY;
            
            if (this->isPageBoundaryCrossed(absoluteAddress, address)) {
                pageBoundaryCost = 1;
            }
            
            break;
        case AddressingMode::ZERO_PAGE:
            address = read(addrLoc);   // Casted uint8_t to uint16_t which is like byte $xx + zero page $0000 = $00xx
            this->programCounterOffset++;
            break;
        case AddressingMode::ZERO_PAGE_X:
            zeroPageAddress = read(addrLoc);
            address = (uint8_t)(zeroPageAddress + this->regX);   // uint8_t handles the wrapping before uint16_t assignment
            this->programCounterOffset++;
            break;
        case AddressingMode::ZERO_PAGE_Y:
            zeroPageAddress = read(addrLoc);
            address = (uint8_t)(zeroPageAddress + this->regY);   // uint8_t handles the wrapping before uint16_t assignment
            this->programCounterOffset++;
            break;
        case AddressingMode::INDIRECT_X:
            zeroPageAddress = read(addrLoc);
            indirectAddress = (uint8_t)(zeroPageAddress + this->regX);   // uint8_t handles the wrapping before uint16_t assignment
            address = read2Bytes(indirectAddress);
            this->programCounterOffset++;
            break;
        case AddressingMode::INDIRECT_Y:
            zeroPageAddress = read(addrLoc);
            indirectAddress = read2Bytes(zeroPageAddress);
            address = indirectAddress + regY;

            if (this->isPageBoundaryCrossed(indirectAddress, address)) {
                pageBoundaryCost = 1;
            }
            this->programCounterOffset++;
            break;
        default:
        // TODO: error handling
            break;
    }
    return address;
}

bool isPageBoundaryCrossed(uint16_t addr1, uint16_t addr2) {    // Comparing the high byte of old and new address
    return (addr1 & 0xFF00) != (addr2 & 0xFF00);
}


// ======================== STATUS FLAGS ======================== //

void NesCpu::setCarryFlag(bool flag) {
    if (flag) {
        regStatus |= CARRY_FLAG_MASK;
    } else {
        regStatus &= ~CARRY_FLAG_MASK;
    }
}

bool NesCpu::isCarryFlag() {
    return (regStatus & CARRY_FLAG_MASK) != 0;
}

void NesCpu::setZeroFlag(bool flag) {
    if (flag) {
        regStatus |= ZERO_FLAG_MASK;
    } else {
        regStatus &= ~ZERO_FLAG_MASK;
    }
}

bool NesCpu::isZeroFlag() {
    return (regStatus & ZERO_FLAG_MASK) != 0;
}

void NesCpu::setInterruptDisable(bool flag) {
    if (flag) {
        regStatus |= INTERRUPT_DISABLE_MASK;
    } else {
        regStatus &= ~INTERRUPT_DISABLE_MASK;
    }
}

bool NesCpu::isInterruptDisable() {
    return (regStatus & INTERRUPT_DISABLE_MASK) != 0;
}

void NesCpu::setDecimalMode(bool flag) {
    if (flag) {
        regStatus |= DECIMAL_MODE_MASK;
    } else {
        regStatus &= ~DECIMAL_MODE_MASK;
    }
}

bool NesCpu::isDecimalMode() {
    return (regStatus & DECIMAL_MODE_MASK) != 0;
}

void NesCpu::setBreakCommand(bool flag) {
    if (flag) {
        regStatus |= BREAK_COMMAND_MASK;
    } else {
        regStatus &= ~BREAK_COMMAND_MASK;
    }
}

bool NesCpu::isBreakCommand() {
    return (regStatus & BREAK_COMMAND_MASK) != 0;
}

void NesCpu::setOverflowFlag(bool flag) {
    if (flag) {
        regStatus |= OVERFLOW_FLAG_MASK;
    } else {
        regStatus &= ~OVERFLOW_FLAG_MASK;
    }
}

bool NesCpu::isOverflowFlag() {
    return (regStatus & OVERFLOW_FLAG_MASK) != 0;
}

void NesCpu::setNegativeFlag(bool flag) {
    if (flag) {
        regStatus |= NEGATIVE_FLAG_MASK;
    } else {
        regStatus &= ~NEGATIVE_FLAG_MASK;
    }
}

bool NesCpu::isNegativeFlag() {
    return (regStatus & NEGATIVE_FLAG_MASK) != 0;
}

// TODO: Implement
bool NesCpu::isPageBoundaryCrossed(uint16_t addr1, uint16_t addr2) {
    return false;
}

// Set program start location based on RESET vector
void NesCpu::initProgramCounter() {
    programCounter = memory[0xFFFD] * 256 + memory[0xFFFC];
}

void NesCpu::incrementProgramCounter() {
    this->programCounter += this->programCounterOffset;
    this->programCounterOffset = 0;
}
