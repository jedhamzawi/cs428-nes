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
        std::cout << "  " << instruction.getOpcode().getMnemonicString();
        uint8_t operand = getOperand(instruction.getOperandAddress());
        if (operand != '\0') {
            std::cout << " 0x" << 0u + operand;
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

    return {opcode, operandAddress, pageBoundaryCost};
}

int NesCpu::execute(const Instruction &instruction) {
    // TODO: IMPORTANT, move PC in each instruction (I think the Opcode::getNumBytes() will tell you how much)
    bool jumped = false;

    switch(instruction.getOpcode().getMnemonic()) {

        case Mnemonic::LDA:
            lda(getOperand(instruction.getOperandAddress()));
            break;
        case Mnemonic::LDX:
            ldx(getOperand(instruction.getOperandAddress()));
            break;
        case Mnemonic::LDY:
            ldy(getOperand(instruction.getOperandAddress()));
            break;
        case Mnemonic::STA:
            sta(instruction.getOperandAddress());
            break;
        case Mnemonic::STX:
            stx(instruction.getOperandAddress());
            break;
        case Mnemonic::STY:
            sty(instruction.getOperandAddress());
            break;

        case Mnemonic::TAX:
            tax();
            break;
        case Mnemonic::TAY:
            tay();
            break;
        case Mnemonic::TXA:
            txa();
            break;
        case Mnemonic::TYA:
            tya();
            break;

        case Mnemonic::TSX:
            tsx();
            break;
        case Mnemonic::TXS:
            txs();
            break;
        case Mnemonic::PHA:
            pha();
            break;
        case Mnemonic::PHP:
            php();
            break;
        case Mnemonic::PLA:
            pla();
            break;
        case Mnemonic::PLP:
            plp();
            break;

        case Mnemonic::AND:
            anda(getOperand(instruction.getOperandAddress()));
            break;
        case Mnemonic::EOR:
            eor(getOperand(instruction.getOperandAddress()));
            break;
        case Mnemonic::ORA:
            ora(getOperand(instruction.getOperandAddress()));
            break;
        case Mnemonic::BIT:
            bit(getOperand(instruction.getOperandAddress()));
            break;

        case Mnemonic::ADC:
            adc(getOperand(instruction.getOperandAddress()));
            break;
        case Mnemonic::SBC:
            sbc(getOperand(instruction.getOperandAddress()));
            break;

        case Mnemonic::CMP:
            cmp(getOperand(instruction.getOperandAddress()));
            break;
        case Mnemonic::CPX:
            cpx(getOperand(instruction.getOperandAddress()));
            break;
        case Mnemonic::CPY:
            cpy(getOperand(instruction.getOperandAddress()));
            break;

        case Mnemonic::INC:
            inc(instruction.getOperandAddress());
            break;
        case Mnemonic::INX:
            inx();
            break;
        case Mnemonic::INY:
            iny();
            break;
        case Mnemonic::DEC:
            dec(instruction.getOperandAddress());
            break;
        case Mnemonic::DEX:
            dex();
            break;
        case Mnemonic::DEY:
            dey();
            break;

        case Mnemonic::ASL:
            if (instruction.getOpcode().getAddressingMode() == AddressingMode:: ACCUMULATOR) {
                asla();
                break;
            }
            asl(instruction.getOperandAddress());
            break;
        case Mnemonic::LSR:
            if (instruction.getOpcode().getAddressingMode() == AddressingMode:: ACCUMULATOR) {
                lsra();
                break;
            }
            lsr(instruction.getOperandAddress());
            break;
        case Mnemonic::ROL:
            if (instruction.getOpcode().getAddressingMode() == AddressingMode:: ACCUMULATOR) {
                rola();
                break;
            }
            rol(instruction.getOperandAddress());
            break;
        case Mnemonic::ROR:
            if (instruction.getOpcode().getAddressingMode() == AddressingMode:: ACCUMULATOR) {
                rora();
                break;
            }
            ror(instruction.getOperandAddress());
            break;

        case Mnemonic::JMP:
            jmp(instruction.getOperandAddress());
            jumped = true;
            break;
        case Mnemonic::JSR:
            jsr(instruction.getOperandAddress());
            jumped = true;
            break;
        case Mnemonic::RTS:
            rts();
            jumped = true;
            break;

        // Other instructions...

        // Status Flags
        case Mnemonic::CLC:
            clc();
            break;
        case Mnemonic::CLD:
            cld();
            break;
        case Mnemonic::CLI:
            cli();
            break;
        case Mnemonic::CLV:
            clv();
            break;
        case Mnemonic::SEC:
            sec();
            break;
        case Mnemonic::SED:
            sed();
            break;
        case Mnemonic::SEI:
            sei();
            break;

        // TODO: set jumped flag if performed JMP, BRN, RET or other jump operation
        default:
            // Unknown opcode, handle error here
            break;
    }

    if (!jumped) {
        incProgramCounter(instruction.getOpcode().getNumBytes());
    }

    return instruction.getOpcode().getNumCycles() + instruction.getPageBoundaryCost();
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

uint8_t NesCpu::pullFromStack() {
    // TODO: On pull when reached end, should "wrap around" to 0x00"?
    uint8_t value = memory[stackPointer];
    stackPointer++;
    return value;
}

void NesCpu::pushToStack(uint8_t value) {
    // TODO: Use read/write functions rather than explicitly manipulating memory array
    memory[stackPointer] = value;
    stackPointer--;
}

/**
 * Retrieves the operand address. The addressing mode determines how to use the address following
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
uint16_t NesCpu::getOperandAddress(AddressingMode mode, short& pageBoundaryCost) {
    // FIXME: Something is wrong with addressing modes (likely having to do with little/big endian)
    uint16_t operandAddressLocation = this->programCounter + 1;
    uint16_t operandAddress = '\0';

    switch (mode) {
        case AddressingMode::IMMEDIATE: {
            operandAddress = operandAddressLocation;
            break;
        }
        case AddressingMode::ABSOLUTE: {
            uint16_t absoluteAddress = readWordToBigEndian(operandAddressLocation);
            operandAddress = absoluteAddress;
            break;
        }
        case AddressingMode::ABSOLUTE_X: {
            uint16_t absoluteAddress = readWordToBigEndian(operandAddressLocation);
            uint16_t effectiveAddress = absoluteAddress + this->regX;

            if (isPageBoundaryCrossed(absoluteAddress, effectiveAddress)) {
                pageBoundaryCost = 1;
            }

            operandAddress = effectiveAddress;
            break;
        }
        case AddressingMode::ABSOLUTE_Y: {
            uint16_t absoluteAddress = readWordToBigEndian(operandAddressLocation);
            uint16_t effectiveAddress = absoluteAddress + this->regY;

            if (isPageBoundaryCrossed(absoluteAddress, effectiveAddress)) {
                pageBoundaryCost = 1;
            }

            operandAddress = effectiveAddress;
            break;
        }
        case AddressingMode::ZERO_PAGE: {
            uint8_t zeroPageAddress = read(operandAddressLocation);
            operandAddress = (uint16_t)zeroPageAddress;
            break;
        }
        case AddressingMode::ZERO_PAGE_X: {
            uint8_t zeroPageAddress = read(operandAddressLocation);
            uint16_t effectiveAddress = zeroPageAddress + this->regX;

            if (isPageBoundaryCrossed(zeroPageAddress, effectiveAddress)) {
                effectiveAddress -= 0x0100;         // Zero page wrap
                pageBoundaryCost = 1;
            }

            operandAddress = effectiveAddress;
            break;
        }
        case AddressingMode::ZERO_PAGE_Y: {
            uint8_t zeroPageAddress = read(operandAddressLocation);
            uint16_t effectiveAddress = zeroPageAddress + this->regY;

            if (isPageBoundaryCrossed(zeroPageAddress, effectiveAddress)) {
                effectiveAddress -= 0x0100;         // Zero page wrap
                pageBoundaryCost = 1;
            }

            operandAddress = effectiveAddress;
            break;
        }
        case AddressingMode::INDIRECT: {
            uint16_t indirectAddress = readWordToBigEndian(operandAddressLocation);
            operandAddress = readWordToBigEndian(indirectAddress);
            break;
        }
        case AddressingMode::INDIRECT_X: {
            uint16_t zeroPageAddress = read(operandAddressLocation);
            uint16_t indirectAddress = zeroPageAddress + this->regX;

            if (isPageBoundaryCrossed(zeroPageAddress, indirectAddress)) {
                indirectAddress -= 0x0100;       // Zero page wrap
                pageBoundaryCost = 1;
            }

            operandAddress = readWordToBigEndian(indirectAddress);
            break;
        }
        case AddressingMode::INDIRECT_Y: {
            uint16_t zeroPageAddress = read(operandAddressLocation);
            uint16_t tempAddress = readWordToBigEndian(zeroPageAddress);
            uint16_t targetAddress = tempAddress + this->regY;

            if (isPageBoundaryCrossed(tempAddress, targetAddress)) {
                targetAddress -= 0x0100;        // Zero page wrap
                pageBoundaryCost = 1;
            }

            operandAddress = targetAddress;
            break;
        }
        default:
            break;
    }
    return operandAddress;
}

uint8_t NesCpu::getOperand(const uint16_t &operandAddress) {
    if (operandAddress != '\0') {
        return read(operandAddress);
    }
    return '\0';
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
    this->programCounter = memory[0xFFFD] * 256 + memory[0xFFFC];
}

void NesCpu::incProgramCounter(uint8_t opSize) {
    this->programCounter += opSize;
}


// ======================== INSTRUCTIONS ======================== //

// Load/Store
int NesCpu::lda(const uint8_t &operand) {
    setZeroFlag(operand == 0);
    setNegativeFlag(operand & 0x80);

    this->regAccumulator = operand;
}

int NesCpu::ldx(const uint8_t &operand) {
    setZeroFlag(operand == 0);
    setNegativeFlag(operand & 0x80);

    this->regX = operand;
}

int NesCpu::ldy(const uint8_t &operand) {
    setZeroFlag(operand == 0);
    setNegativeFlag(operand & 0x80);

    this->regY = operand;
}

int NesCpu::sta(const uint16_t &operandAddress) {
    this->memory[operandAddress] = this->regAccumulator;
}

int NesCpu::stx(const uint16_t &operandAddress) {
    this->memory[operandAddress] = this->regX;
}

int NesCpu::sty(const uint16_t &operandAddress) {
    this->memory[operandAddress] = this->regY;
}

// Transfer Registers
int NesCpu::tax() {
    setZeroFlag(this->regAccumulator == 0);
    setNegativeFlag(this->regAccumulator & 0x80);

    this->regX = this->regAccumulator;
}

int NesCpu::tay() {
    setZeroFlag(this->regAccumulator == 0);
    setNegativeFlag(this->regAccumulator & 0x80);

    this->regY = this->regAccumulator;
}

int NesCpu::txa() {
    setZeroFlag(this->regX == 0);
    setNegativeFlag(this->regX & 0x80);

    this->regAccumulator = this->regX;
}

int NesCpu::tya() {
    setZeroFlag(this->regY == 0);
    setNegativeFlag(this->regY & 0x80);

    this->regAccumulator = this->regY;
}

// Stack Operations
int NesCpu::tsx() {
    this->regX = this->stackPointer;

    setZeroFlag(this->regX == 0);
    setNegativeFlag(this->regX & 0x80);
}

int NesCpu::txs() {
    this->stackPointer = this->regX;
}

int NesCpu::pha() {
    pushToStack(regAccumulator);
}

int NesCpu::php() {
    pushToStack(regStatus);
}

int NesCpu::pla() {
    this->regAccumulator = pullFromStack();

    setZeroFlag(this->regAccumulator == 0);
    setNegativeFlag(this->regAccumulator & 0x80);
}

int NesCpu::plp() {
    this->regStatus = pullFromStack();
}

// Logical
int NesCpu::anda(const uint8_t &operand) {
    uint8_t result = this->regAccumulator & operand;
    setZeroFlag(result == 0);
    setNegativeFlag(result & 0x80);

    this->regAccumulator = result;
}

int NesCpu::eor(const uint8_t &operand) {
    uint8_t result = this->regAccumulator ^ operand;
    setZeroFlag(result == 0);
    setNegativeFlag(result & 0x80);

    this->regAccumulator = result;
}

int NesCpu::ora(const uint8_t &operand) {
    uint8_t result = this->regAccumulator | operand;
    setZeroFlag(result == 0);
    setNegativeFlag(result & 0x80);

    this->regAccumulator = result;
}

int NesCpu::bit(const uint8_t &operand) {
    setNegativeFlag(operand & 0x80);
    setOverflowFlag(operand & 0x40);
    setZeroFlag(this->regAccumulator & operand);
}

// Arithmetic
int NesCpu::adc(const uint8_t &operand) {
    uint16_t result = this->regAccumulator + operand + isCarryFlag();
   
    setCarryFlag(result > 0xFF);
    setZeroFlag((result & 0xFF) == 0);
    setOverflowFlag(hasOverflow(this->regAccumulator, operand, result));
    setNegativeFlag(result & 0x80);

    this->regAccumulator = (uint8_t)result;
}

int NesCpu::sbc(const uint8_t &operand) {
    uint8_t result = this->regAccumulator - operand - !isCarryFlag();

    setCarryFlag(!(result & 0x100));
    setZeroFlag(result == 0);
    setOverflowFlag((this->regAccumulator ^ result) & (~operand ^ result) & 0x80);
    this->regAccumulator = result;
}

// Compare
int NesCpu::cmp(const uint8_t &operand) {
    uint16_t result = this->regAccumulator - operand;

    setCarryFlag(!(result & 0x100));
    setZeroFlag(result == 0);
    setNegativeFlag(result & 0x80);
}

int NesCpu::cpx(const uint8_t &operand) {
    uint16_t result = this->regX - operand;

    setCarryFlag(!(result & 0x100));
    setZeroFlag(result == 0);
    setNegativeFlag(result & 0x80);
}

int NesCpu::cpy(const uint8_t &operand) {
    uint16_t result = this->regY - operand;

    setCarryFlag(!(result & 0x100));
    setZeroFlag(result == 0);
    setNegativeFlag(result & 0x80);
}

int NesCpu::inc(const uint16_t &operandAddress) {
    uint8_t result = this->memory[operandAddress] + 1;
    setZeroFlag(result == 0);
    setNegativeFlag(result & 0x80);

    this->memory[operandAddress] = result;
}

// Increments/Decrements
int NesCpu::inx() {
    this->regX++;
    setZeroFlag(this->regX == 0);
    setNegativeFlag(this->regX & 0x80);
}

int NesCpu::iny() {
    this->regY++;
    setZeroFlag(this->regY == 0);
    setNegativeFlag(this->regY & 0x80);
}

int NesCpu::dec(const uint16_t &operandAddress) {
    uint8_t result = this->memory[operandAddress] - 1;
    setZeroFlag(result == 0);
    setNegativeFlag(result & 0x80);

    this->memory[operandAddress] = result;
}

int NesCpu::dex() {
    this->regX--;
    setZeroFlag(this->regX == 0);
    setNegativeFlag(this->regX & 0x80);
}

int NesCpu::dey() {
    this->regY--;
    setZeroFlag(this->regY == 0);
    setNegativeFlag(this->regY & 0x80);
}

// Shifts/Rotations
int NesCpu::asl(const uint16_t &operandAddress) {
    uint8_t operand = this->memory[operandAddress];
    setCarryFlag(operand & 0x80);
    operand = operand << 1;
    setZeroFlag(operand == 0);
    setNegativeFlag(operand & 0x80);

    this->memory[operandAddress] = operand;
}

int NesCpu::asla() {;
    setCarryFlag(this->regAccumulator & 0x80);
    this->regAccumulator = this->regAccumulator << 1;
    setZeroFlag(this->regAccumulator == 0);
    setNegativeFlag(this->regAccumulator & 0x80);
}

int NesCpu::lsr(const uint16_t &operandAddress) {
    uint8_t operand = this->memory[operandAddress];
    setCarryFlag(operand & 0x1);
    operand = operand >> 1;
    setZeroFlag(operand == 0);
    setNegativeFlag(false);

    this->memory[operandAddress] = operand;
}

int NesCpu::lsra() {
    setCarryFlag(this->regAccumulator & 0x1);
    this->regAccumulator = this->regAccumulator >> 1;
    setZeroFlag(this->regAccumulator == 0);
    setNegativeFlag(false);
}

int NesCpu::rol(const uint16_t &operandAddress) {
    bool carryFlag = isCarryFlag();
    uint8_t operand = this->memory[operandAddress];
    setCarryFlag(operand & 0x80);
    operand = operand << 1;
    if (carryFlag) {
        operand | 0x1;
    }
    setZeroFlag(operand == 0);
    setNegativeFlag(operand & 0x80);

    this->memory[operandAddress] = operand;
}

int NesCpu::rola() {
    bool carryFlag = isCarryFlag();
    setCarryFlag(this->regAccumulator & 0x80);
    this->regAccumulator = this->regAccumulator << 1;
    if (carryFlag) {
        this->regAccumulator | 0x1;
    }
    setZeroFlag(this->regAccumulator == 0);
    setNegativeFlag(this->regAccumulator & 0x80);
}

int NesCpu::ror(const uint16_t &operandAddress) {
    bool carryFlag = isCarryFlag();
    uint8_t operand = this->memory[operandAddress];
    setCarryFlag(operand & 0x1);
    operand = operand >> 1;
    if (carryFlag) {
        operand | 0x80;
    }
    setZeroFlag(operand == 0);
    setNegativeFlag(carryFlag);

    this->memory[operandAddress] = operand;
}

int NesCpu::rora() {
    bool carryFlag = isCarryFlag();
    setCarryFlag(this->regAccumulator & 0x1);
    this->regAccumulator = this->regAccumulator >> 1;
    if (carryFlag) {
        this->regAccumulator | 0x80;
    }
    setZeroFlag(this->regAccumulator == 0);
    setNegativeFlag(carryFlag);
}

// Jumps/Subroutines
int NesCpu::jmp(const uint16_t &address) {
    programCounter = address;
}

int NesCpu::jsr(const uint16_t &address) {
    pushToStack((uint8_t)(programCounter >> 8));
    pushToStack((uint8_t)programCounter);
    programCounter = address;
}

int NesCpu::rts() {
    uint8_t pcLow = pullFromStack();
    uint8_t pcHigh = pullFromStack();
    programCounter = ((uint16_t)pcHigh << 8 | pcLow) + 1;
}

// Status Flag Changes
int NesCpu::clc() {
    setCarryFlag(false);
}

int NesCpu::cld() {
    setDecimalFlag(false);
}

int NesCpu::cli() {
    setInterruptFlag(false);
}

int NesCpu::clv() {
    setOverflowFlag(false);
}

int NesCpu::sec() {
    setCarryFlag(true);
}

int NesCpu::sed() {
    setDecimalFlag(true);
}

int NesCpu::sei() {
    setInterruptFlag(true);
}

// Other instructions...

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

void NesCpu::setInterruptFlag(bool flag) {
    if (flag) {
        regStatus |= INTERRUPT_DISABLE_MASK;
    } else {
        regStatus &= ~INTERRUPT_DISABLE_MASK;
    }
}

bool NesCpu::isInterruptFlag() {
    return (regStatus & INTERRUPT_DISABLE_MASK) != 0;
}

void NesCpu::setDecimalFlag(bool flag) {
    if (flag) {
        regStatus |= DECIMAL_MODE_MASK;
    } else {
        regStatus &= ~DECIMAL_MODE_MASK;
    }
}

bool NesCpu::isDecimalFlag() {
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
