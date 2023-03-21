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
    }
    // Wait until instruction's step cost is paid
    this->clock--;
}

Instruction NesCpu::fetch() {
    uint8_t opcodeByte = read(this->programCounter);
    Opcode opcode = OpcodeTable::getOpcode(opcodeByte);

    short pageBoundaryCost = 0;
    uint16_t operandAddress = getOperandAddress(opcode.getAddressingMode(), pageBoundaryCost);
    uint8_t operand = read(operandAddress);

    return {opcode, operand, pageBoundaryCost};
}

int NesCpu::execute(const Instruction &instruction) {
    // TODO: IMPORTANT, move PC in each instruction
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


// ======================== INSTRUCTIONS ======================== //

int NesCpu::adc(uint8_t operand) {
    uint16_t result = this->regAccumulator + operand + isCarryFlag();
   
    this->flags.setCarryFlag(result > 0xFF);
    this->flags.setZeroFlag((result & 0xFF) == 0);
    this->flags.setOverflowFlag(hasOverflow(this->regAccumulator, operand, result));
    this->flags.setNegativeFlag(result & 0x80);

    this->regAccumulator = (uint8_t)result;
}

int NesCpu::sbc(uint8_t operand) {
    adc(~operand);      // A - B = A + (-B)
}


// Other instructions...


// ======================== ADDRESSING MODES ======================== //

uint16_t NesCpu::getOperandAddress(AddressingMode mode, short& pageBoundaryCost) {
    uint16_t addressOfInstructionValue = this->programCounter + 1;    // Address of value after opcode
    uint16_t address = 0;

    uint16_t absoluteAddress;
    uint8_t zeroPageAddress;
    uint16_t indirectAddress;
    switch (mode) {
        case AddressingMode::IMPLIED:
            // TODO: maybe fix how we handle getting operands, because implicit doesn't need one
            //       but it will set operand to value at address 0 by default.
            break;
        case AddressingMode::IMMEDIATE:
            address = addressOfInstructionValue;
            break;
        case AddressingMode::ABSOLUTE:
            address = read2Bytes(addressOfInstructionValue);
            break;
        case AddressingMode::ABSOLUTE_X:
            absoluteAddress = read2Bytes(addressOfInstructionValue);
            address = absoluteAddress + this->regX;

            if (this->isPageBoundaryCrossed(absoluteAddress, address)) {
                pageBoundaryCost = 1;
            }

            break;
        case AddressingMode::ABSOLUTE_Y:
            absoluteAddress = read2Bytes(addressOfInstructionValue);
            address = absoluteAddress + this->regY;
            
            if (this->isPageBoundaryCrossed(absoluteAddress, address)) {
                pageBoundaryCost = 1;
            }
            
            break;
        case AddressingMode::ZERO_PAGE:
            address = read(addressOfInstructionValue);   // Cast uint8_t to uint16_t which is like byte $xx + zero page $0000 = $00xx
            break;
        case AddressingMode::ZERO_PAGE_X:
            zeroPageAddress = read(addressOfInstructionValue);
            address = (uint8_t)(zeroPageAddress + this->regX);   // uint8_t handles the wrapping before uint16_t assignment
            break;
        case AddressingMode::ZERO_PAGE_Y:
            zeroPageAddress = read(addressOfInstructionValue);
            address = (uint8_t)(zeroPageAddress + this->regY);   // uint8_t handles the wrapping before uint16_t assignment
            break;
        case AddressingMode::INDIRECT_X:
            zeroPageAddress = read(addressOfInstructionValue);
            indirectAddress = (uint8_t)(zeroPageAddress + this->regX);   // uint8_t handles the wrapping before uint16_t assignment
            address = read2Bytes(indirectAddress);
            break;
        case AddressingMode::INDIRECT_Y:
            zeroPageAddress = read(addressOfInstructionValue);
            indirectAddress = read2Bytes(zeroPageAddress);
            address = indirectAddress + regY;

            if (this->isPageBoundaryCrossed(indirectAddress, address)) {
                pageBoundaryCost = 1;
            }
            break;
        default:
            // TODO: error handling
            break;
    }
    return address;
}


// ======================== HELPERS ======================== //

bool NesCpu::isPageBoundaryCrossed(uint16_t addr1, uint16_t addr2) {    
    // Comparing the high byte of old and new address
    return (addr1 & 0xFF00) != (addr2 & 0xFF00);
}

bool NesCpu::hasOverflow(uint8_t input1, uint8_t input2, uint8_t result) {
    bool input1Negative = input1 & 0x80;
    bool input2Negative = input2 & 0x80;
    bool resultNegative = result & 0x80;
    return (input1Negative == input2Negative) && (input1Negative != resultNegative);
}

void NesCpu::initProgramCounter() {
    // Set program start location based on RESET vector
    programCounter = memory[0xFFFD] * 256 + memory[0xFFFC];
}

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
