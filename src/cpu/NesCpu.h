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

    // Flags
    // byte = Negative, Overflow, _, BreakCommand, DecimalMode, InterruptDisable, Zero, Carry
    bool carryFlag = false;
    bool zeroFlag = false;
    bool interruptFlag = false;
    // bool decimalFlag = 0;                            // Ricoh modded the chip so NES doesn't have decimal mode
    bool breakFlag = false;
    // unused bit
    bool overflowFlag = false;
    bool negativeFlag = false;

	uint8_t regAccumulator = 0;								// (A)
	uint8_t regX = 0;										// (X)
	uint8_t regY = 0;										// (Y)
	uint8_t regStatus = 0;									// (P)		byte = Negative, Overflow, _, Break, Decimal, Interrupt, Zero, Carry
	uint8_t stackPointer = STACK_POINTER_START;				// (S) Stack is stored top -> bottom ($01FF -> $0100)
	uint16_t programCounter = 0; 							// (PC)
	uint8_t* memory;										// pointer to NesSystem memory

	Instruction fetch();									// Fetches instruction (opcode) from memory pointed at by PC
	int execute(const Instruction &instruction);			// Returns CPU cycle (step) cost of instruction

	uint8_t read(uint16_t addr);
	uint16_t readWordToBigEndian(uint16_t addr);			// Reads low then high and returns reordered ($00 $80 => $8000)
	void write(uint16_t addr, uint8_t val);
	void writeWordToLittleEndian(uint16_t addr, uint16_t val);

	uint8_t getOperand(AddressingMode mode, short& pageBoundaryCost);
	static bool isPageBoundaryCrossed(uint16_t addr1, uint16_t addr2);
	static bool hasOverflow(uint8_t input1, uint8_t input2, uint8_t result);


	// Load/Store Operations
	int lda();      // LDA - load accumulator
	int ldx();      // LDX - load X
	int ldy();      // LDY - load Y
	int sta();      // STA - store accumulator
	int stx();      // STX - store X
	int sty();      // STY - store Y

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
	int anda();      // AND - and (with accumulator)
	int eor();      // EOR - exclusive or (with accumulator)
	int ora();      // ORA - or with accumulator
	int bit();      // BIT - bit test

	// Arithmetic
	int adc(const uint8_t &operand);      // ADC - add with carry
	int sbc(const uint8_t &operand);      // SBC - subtract with carry
	int cmp(const uint8_t &operand);      // CMP - compare (with accumulator)
	int cpx(const uint8_t &operand);      // CPX - compare with X
	int cpy(const uint8_t &operand);      // CPY - compare with Y

	// Increments and Decrements
	int inc();      // INC - increment
	int inx();      // INX - increment X
	int iny();      // INY - increment Y
	int dec();      // DEC - decrement
	int dex();      // DEX - decrement X
	int dey();      // DEY - decrement Y

	// Shifts
	int asl();      // ASL - arithmetic shift left
	int lsr();      // LSR - logical shift right
	int rol();      // ROL - rotate left
	int ror();      // ROR - rotate right

	// Jumps and Calls
	int jmp();      // JMP - jump
	int jsr();      // JSR - jump subroutine
	int rts();      // RTS - return from subroutine

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
	int cld();      // CLD - clear decimal
	int cli();      // CLI - clear interrupt disable
	int clv();      // CLV - clear overflow
	int sec();      // SEC - set carry
	int sed();      // SED - set decimal
	int sei();      // SEI - set interrupt disable

	// System Functions
	int brk();      // BRK - break / interrupt
	int nop();      // NOP - no operation
	int rti();      // RTI - return from interrupt

    void incProgramCounter(uint8_t opSize);

public:
	NesCpu(uint8_t* memory);
	~NesCpu();

	void step();

    void initProgramCounter();
};