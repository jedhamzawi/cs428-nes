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
    void lda(const uint8_t &operand);              // LDA - load accumulator
	void ldx(const uint8_t &operand);              // LDX - load X
	void ldy(const uint8_t &operand);              // LDY - load Y
	void sta(const uint16_t &operandAddress);      // STA - store accumulator
	void stx(const uint16_t &operandAddress);      // STX - store X
	void sty(const uint16_t &operandAddress);      // STY - store Y

	// Register Transfers
    void tax();      // TAX - transfer accumulator to X
	void tay();      // TAY - transfer accumulator to Y
	void txa();      // TXA - transfer X to accumulator
	void tya();      // TYA - transfer Y to accumulator

	// Stack Operations
    void tsx();      // TSX - transfer stack pointer to X
	void txs();      // TXS - transfer X to stack pointer
	void pha();      // PHA - push accumulator
	void php();      // PHP - push processor status (SR)
	void pla();      // PLA - pull accumulator
	void plp();      // PLP - pull processor status (SR)

	// Logical
    void anda(const uint8_t &operand);             // AND - and (with accumulator)
	void eor(const uint8_t &operand);              // EOR - exclusive or (with accumulator)
	void ora(const uint8_t &operand);              // ORA - or with accumulator
	void bit(const uint8_t &operand);              // BIT - bit test

	// Arithmetic
    void adc(const uint8_t &operand);              // ADC - add with carry
	void sbc(const uint8_t &operand);              // SBC - subtract with carry

    // Compare
    void cmp(const uint8_t &operand);              // CMP - compare (with accumulator)
	void cpx(const uint8_t &operand);              // CPX - compare with X
	void cpy(const uint8_t &operand);              // CPY - compare with Y

	// Increments and Decrements
    void inc(const uint16_t &operandAddress);      // INC - increment
	void inx();                                    // INX - increment X
	void iny();                                    // INY - increment Y
	void dec(const uint16_t &operandAddress);      // DEC - decrement
	void dex();                                    // DEX - decrement X
	void dey();                                    // DEY - decrement Y

	// Shifts
    void asl(const uint16_t &operandAddress);      // ASL - arithmetic shift left (memory)
    void asla();                                   // ASL - arithmetic shift left (accumulator)
	void lsr(const uint16_t &operandAddress);      // LSR - logical shift right (memory)
    void lsra();                                   // LSR - logical shift right (accumulator)
	void rol(const uint16_t &operandAddress);      // ROL - rotate left (memory)
    void rola();                                   // ROL - rotate left (accumulator)
	void ror(const uint16_t &operandAddress);      // ROR - rotate right
    void rora();                                   // ROR - rotate right (accumulator)

	// Jumps and Calls
    void jmp(const uint16_t &address);             // JMP - jump
	void jsr(const uint16_t &address);             // JSR - jump subroutine
	void rts();                                    // RTS - return from subroutine

	// Branches
    bool bcc(const int8_t &offset);                // BCC - branch on carry clear
	bool bcs(const int8_t &offset);                // BCS - branch on carry set
	bool beq(const int8_t &offset);                // BEQ - branch on equal (zero set)
	bool bmi(const int8_t &offset);                // BMI - branch on minus (negative set)
	bool bne(const int8_t &offset);                // BNE - branch on not equal (zero clear)
	bool bpl(const int8_t &offset);                // BPL - branch on plus (negative clear)
	bool bvc(const int8_t &offset);                // BVC - branch on overflow clear
	bool bvs(const int8_t &offset);                // BVS - branch on overflow set

	// Status Flag Changes
    void clc();      // CLC - clear carry
	void cld();      // CLD - clear decimal (decimal flag unused in NES)
	void cli();      // CLI - clear interrupt disable
	void clv();      // CLV - clear overflow
	void sec();      // SEC - set carry
	void sed();      // SED - set decimal (decimal flag unused in NES)
	void sei();      // SEI - set interrupt disable

	// System Functions
    void brk();      // BRK - break / interrupt
	//void nop();      // NOP - no operation
	void rti();      // RTI - return from interrupt

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