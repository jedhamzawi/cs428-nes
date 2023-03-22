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
    uint8_t operand = getOperand(opcode.getAddressingMode(), pageBoundaryCost);

    return {opcode, operand, pageBoundaryCost};
}

int NesCpu::execute(const Instruction &instruction) {
    // TODO: IMPORTANT, move PC in each instruction (I think the Opcode::getBytes() will tell you how much)
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


/**
 * Retrieves the operand. The addressing mode determines how to use the address following 
 * the opcode in the retrieval. Sometimes that address may actually point to the operand,
 * other times it may point to the operands address, etc.
 *
 * Addressing modes:
 * - Implied: There is no operand, the opcode is sufficient.
 * - Immediate: Operand is the value after the opcode.
 * - Absolute: Operand is the value at the absolute address. This address is specified by
 *             the word (little endian) that follows the opcode.
 * - Absolute X: Operand is the value at the absolute address, offset by the X register. 
 *               May require an extra cycle if a page boundary is crossed.
 * - Absolute Y: Operand is the value at the absolute address, offset by the Y register. 
 *               May require an extra cycle if a page boundary is crossed.
 * - Zero page: Operand is the value at the zero page address. This address is calculated 
 *              by using the value after the opcode as the low byte and $00 (page 0) as 
 *              the high byte, thus somewhere $0000 <-> $00FF.
 * - Zero page X: Operand is the value at the zero page address, offset by the X register.
 *                May require an extra cycle if a page boundary is crossed.
 * - Zero page Y: Operand is the value at the zero page address, offset by the Y register.
 *                May require an extra cycle if a page boundary is crossed.
 * - Indirect: Only used by JMP. The word (little endian) following the opcode is the
 *             indirect address. This indirect address points to the target address value.
 *             Due to little endian addressing, it points to the LSB of the target address.
 *             The operand is the full target address (where to jump to).
 * - Indirect X: The byte after the opcode, when converted to a zero page address ($00--)
 *               and offset by regX, is location of the LSB of the address of the operand. 
 *               The operand value represents an address (target address).
 * - Indirect Y: The byte after the opcode, when converted to a zero page address ($00--),
 *               is the location of the LSB of a temporary address. When this temporary 
 *               address is offset by regY, it points to the LSB of the operand. The operand
 *               value represents an address (target address).
 * 
 **/
uint8_t NesCpu::getOperand(AddressingMode mode, short& pageBoundaryCost) {
    uint8_t operand;
    uint16_t addressAfterOpcode = this->programCounter + 1;

    switch (mode) {
        case AddressingMode::IMPLIED:
            operand = NULL;
            break;
        case AddressingMode::IMMEDIATE:
            operand = read(addressAfterOpcode);
            break;
        case AddressingMode::ABSOLUTE:
            uint16_t absoluteAddress = readWordToBigEndian(addressAfterOpcode);
            operand = read(absoluteAddress);
            break;
        case AddressingMode::ABSOLUTE_X:
            uint16_t absoluteAddress = readWordToBigEndian(addressAfterOpcode);
            uint16_t effectiveAddress = absoluteAddress + this->regX;

            if (isPageBoundaryCrossed(absoluteAddress, effectiveAddress)) {
                pageBoundaryCost = 1;
            }

            operand = read(effectiveAddress);
            break;
        case AddressingMode::ABSOLUTE_Y:
            uint16_t absoluteAddress = readWordToBigEndian(addressAfterOpcode);
            uint16_t effectiveAddress = absoluteAddress + this->regY;

            if (isPageBoundaryCrossed(absoluteAddress, effectiveAddress)) {
                pageBoundaryCost = 1;
            }

            operand = read(effectiveAddress);
            break;
        case AddressingMode::ZERO_PAGE:
            uint8_t zeroPageAddress = read(addressAfterOpcode);
            operand = read(zeroPageAddress);
            break;
        case AddressingMode::ZERO_PAGE_X:
            uint8_t zeroPageAddress = read(addressAfterOpcode);
            uint16_t effectiveAddress = zeroPageAddress + this->regX;

            if (isPageBoundaryCrossed(zeroPageAddress, effectiveAddress)) {
                effectiveAddress -= 0x0100;         // Zero page wrap
                pageBoundaryCost = 1;
            }

            operand = read(effectiveAddress);
            break;
        case AddressingMode::ZERO_PAGE_Y: 
            uint8_t zeroPageAddress = read(addressAfterOpcode);
            uint16_t effectiveAddress = zeroPageAddress + this->regY;

            if (isPageBoundaryCrossed(zeroPageAddress, effectiveAddress)) {
                effectiveAddress -= 0x0100;         // Zero page wrap
                pageBoundaryCost = 1;
            }

            operand = read(effectiveAddress);
            break;
        case AddressingMode::INDIRECT:
            uint16_t indirectAddress = readWordToBigEndian(addressAfterOpcode);
            uint16_t targetAddress = readWordToBigEndian(indirectAddress);
            operand = targetAddress;
            break;

        case AddressingMode::INDIRECT_X:
            uint16_t zeroPageAddress = read(addressAfterOpcode);
            uint16_t indexedAddress = zeroPageAddress + this->regX;
            
            if (this->isPageBoundaryCrossed(zeroPageAddress, indexedAddress)) {
                indexedAddress -= 0x0100;       // Zero page wrap
                pageBoundaryCost = 1;
            }
            uint16_t targetAddress = readWordToBigEndian(indirectAddress);

            operand = targetAddress;
            break;
        case AddressingMode::INDIRECT_Y:
            uint16_t zeroPageAddress = read(addressAfterOpcode);
            uint16_t tempAddress = readWordToBigEndian(zeroPageAddress);
            uint16_t targetAddress = tempAddress + this->regY;

            if (this->isPageBoundaryCrossed(tempAddress, targetAddress)) {
                targetAddress -= 0x0100;        // Zero page wrap
                pageBoundaryCost = 1;
            }

            operand = targetAddress;
            break;
        default:
            // TODO: error handling
            break;
    }
    return operand;
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

uint16_t NesCpu::readWordToBigEndian(uint16_t addr) {
    uint16_t lowByte = read(addr);
    uint16_t highByte = read(addr + 1);
    return (highByte << 8) | lowByte;
}

void NesCpu::write(uint16_t addr, uint8_t val) {
    memory[addr] = val;
}

void NesCpu::writeWordToLittleEndian(uint16_t addr, uint16_t val) {
    uint8_t lowByte = val & 0x00FF;
    uint8_t highByte = val >> 8;
    write(addr, lowByte);
    write(addr + 1, highByte);
}
