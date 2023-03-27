#pragma once

#include <cstdint>
#include <string>
#include "AbstractClockable.h"
#include "OpcodeTable.h"
#include "Instruction.h"


// NOTE: The 6502 is little endian, the least significant byte comes first
class NesCpu : public AbstractClockable {
private:
	static constexpr uint8_t STACK_POINTER_START = 0xFD;  	// Check documentation, should be $FF, but power-on/reset decrements 3?

    const uint8_t CARRY_FLAG_MASK = 		0b00000001;
    const uint8_t ZERO_FLAG_MASK = 			0b00000010;
    const uint8_t INTERRUPT_DISABLE_MASK = 	0b00000100;
    const uint8_t DECIMAL_MODE_MASK = 		0b00001000;
    const uint8_t BREAK_COMMAND_MASK = 		0b00010000;
    //const uint8_t UNUSED_MASK = 			0b00100000;
    const uint8_t OVERFLOW_FLAG_MASK = 		0b01000000;
    const uint8_t NEGATIVE_FLAG_MASK =		0b10000000;

	uint8_t regAccumulator = 0;								// (A)
	uint8_t regX = 0;										// (X)
	uint8_t regY = 0;										// (Y)
	uint8_t regStatus = 0b00000000;							// (P) byte = Negative, Overflow, _, Break, Decimal, Interrupt, Zero, Carry
	uint8_t stackPointer = STACK_POINTER_START;				// (S) Stack is stored top -> bottom ($01FF -> $0100)
	uint16_t programCounter = 0; 							// (PC)
	uint8_t* memory;										// pointer to NesSystem memory

	Instruction fetch();									// Fetches instruction (opcode) from memory pointed at by PC
	int execute(const Instruction &instruction);			// Returns CPU cycle (step) cost of instruction

	uint8_t read(uint16_t addr);
	uint16_t readWordToBigEndian(uint16_t addr);			// Reads low then high and returns reordered ($00 $80 => $8000)
	void write(uint16_t addr, uint8_t val);
	void writeWordToLittleEndian(uint16_t addr, uint16_t val);
    uint8_t pullFromStack();
    void pushToStack(uint8_t value);

	uint16_t getOperandAddress(AddressingMode mode, short& pageBoundaryCost);
    uint8_t getOperand(const uint16_t &operandAddress);
	static bool isPageBoundaryCrossed(uint16_t addr1, uint16_t addr2);
	static bool hasOverflow(uint8_t input1, uint8_t input2, uint8_t result);

	// Load/Store Operations
    int lda(const uint8_t &operand);      // LDA - load accumulator
	int ldx(const uint8_t &operand);      // LDX - load X
	int ldy(const uint8_t &operand);      // LDY - load Y
	int sta(const uint16_t &operandAddress);      // STA - store accumulator
	int stx(const uint16_t &operandAddress);      // STX - store X
	int sty(const uint16_t &operandAddress);      // STY - store Y

	// Register Transfers
	int tax();      // TAX - transfer accumulator to X
	int tay();      // TAY - transfer accumulator to Y
	int txa();      // TXA - transfer X to accumulator
	int tya();      // TYA - transfer Y to accumulator

	// Stack Operations
	int tsx();      // TSX - transfer stack pointer to X
	int txs();      // TXS - transfer X to stack pointer
	int pha();      // PHA - push accumulator
	int php();      // PHP - push processor status (SR)
	int pla();      // PLA - pull accumulator
	int plp();      // PLP - pull processor status (SR)

	// Logical
	int anda(const uint8_t &operand);     // AND - and (with accumulator)
	int eor(const uint8_t &operand);      // EOR - exclusive or (with accumulator)
	int ora(const uint8_t &operand);      // ORA - or with accumulator
	int bit(const uint8_t &operand);      // BIT - bit test

	// Arithmetic
	int adc(const uint8_t &operand);      // ADC - add with carry
	int sbc(const uint8_t &operand);      // SBC - subtract with carry

    // Compare
	int cmp(const uint8_t &operand);      // CMP - compare (with accumulator)
	int cpx(const uint8_t &operand);      // CPX - compare with X
	int cpy(const uint8_t &operand);      // CPY - compare with Y

	// Increments and Decrements
	int inc(const uint16_t &operandAddress);      // INC - increment
	int inx();                            // INX - increment X
	int iny();                            // INY - increment Y
	int dec(const uint16_t &operandAddress);      // DEC - decrement
	int dex();                            // DEX - decrement X
	int dey();                            // DEY - decrement Y

	// Shifts
    int asl(const uint16_t &operandAddress);      // ASL - arithmetic shift left (memory)
    int asla();                                   // ASL - arithmetic shift left (accumulator)
	int lsr(const uint16_t &operandAddress);      // LSR - logical shift right (memory)
    int lsra();                                   // LSR - logical shift right (accumulator)
	int rol(const uint16_t &operandAddress);      // ROL - rotate left (memory)
    int rola();                                   // ROL - rotate left (accumulator)
	int ror(const uint16_t &operandAddress);      // ROR - rotate right
    int rora();                                   // ROR - rotate right (accumulator)

	// Jumps and Calls
	int jmp(const uint16_t &address);      // JMP - jump
	int jsr(const uint16_t &address);      // JSR - jump subroutine
	int rts();                            // RTS - return from subroutine

	// Branches
	int bcc();      // BCC - branch on carry clear
	int bcs();      // BCS - branch on carry set
	int beq();      // BEQ - branch on equal (zero set)
	int bmi();      // BMI - branch on minus (negative set)
	int bne();      // BNE - branch on not equal (zero clear)
	int bpl();      // BPL - branch on plus (negative clear)
	int bvc();      // BVC - branch on overflow clear
	int bvs();      // BVS - branch on overflow set

	// Status Flag Changes
	int clc();      // CLC - clear carry
	int cld();      // CLD - clear decimal (decimal flag unused in NES)
	int cli();      // CLI - clear interrupt disable
	int clv();      // CLV - clear overflow
	int sec();      // SEC - set carry
	int sed();      // SED - set decimal (decimal flag unused in NES)
	int sei();      // SEI - set interrupt disable

	// System Functions
	int brk();      // BRK - break / interrupt
	int nop();      // NOP - no operation
	int rti();      // RTI - return from interrupt

    // Status Flag operations
    void setCarryFlag(bool flag);
    bool isCarryFlag();
    void setZeroFlag(bool flag);
    bool isZeroFlag();
    void setInterruptFlag(bool flag);
    bool isInterruptFlag();
    void setDecimalFlag(bool flag);
    bool isDecimalFlag();
    void setBreakCommand(bool flag);
    bool isBreakCommand();
    void setOverflowFlag(bool flag);
    bool isOverflowFlag();
    void setNegativeFlag(bool flag);
    bool isNegativeFlag();

    void incProgramCounter(uint8_t opSize);

public:
	NesCpu(uint8_t* memory);
	~NesCpu();

	void step();

    void initProgramCounter();
};