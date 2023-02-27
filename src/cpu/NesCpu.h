#pragma once

#include <cstdint>
#include "AbstractClockable.h"


// NOTE: The 6502 is little endian, the least significant byte comes first
class NesCpu : public AbstractClockable {
private:
	static constexpr uint16_t ADDRESS_SPACE_SIZE = 65536;
	static constexpr uint8_t STACK_POINTER_START = 0xFD;  	// Check documentation, should be $FF, but power-on/reset decrements 3?

	enum AddressingMode {
		IMPLIED,         // Implied addressing mode (no operand)
		ACCUMULATOR,     // Accumulator addressing mode (operand is in A register)
		IMMEDIATE,       // Immediate addressing mode (operand is a constant)
		ZERO_PAGE,       // Zero page addressing mode (operand is a memory address in the first 256 bytes of memory)
		ZERO_PAGE_X,     // Zero page,X addressing mode (operand is a memory address in the first 256 bytes of memory, indexed by X)
		ZERO_PAGE_Y,     // Zero page,Y addressing mode (operand is a memory address in the first 256 bytes of memory, indexed by Y)
		RELATIVE,        // Relative addressing mode (operand is a signed 8-bit offset from the program counter)
		ABSOLUTE,        // Absolute addressing mode (operand is a memory address in the full 64K address space)
		ABSOLUTE_X,      // Absolute,X addressing mode (operand is a memory address in the full 64K address space, indexed by X)
		ABSOLUTE_Y,      // Absolute,Y addressing mode (operand is a memory address in the full 64K address space, indexed by Y)
		INDIRECT,        // Indirect addressing mode (operand is a memory address that contains a memory address)
		INDIRECT_X,      // Indirect,X addressing mode (operand is a memory address that is used as an index into the zero page)
		INDIRECT_Y       // Indirect,Y addressing mode (operand is a memory address in the zero page that is indexed by Y)
	};

	uint8_t regAccumulator = 0;								// (A)
	uint8_t regX = 0;										// (X)
	uint8_t regY = 0;										// (Y)
	uint8_t regStatus = 0;									// (P)
	uint8_t stackPointer = STACK_POINTER_START;				// (S) Stack is stored top -> bottom ($01FF -> $0100)
	uint16_t programCounter = 0; 							// (PC)
	uint16_t addressBus;
	uint8_t memory[ADDRESS_SPACE_SIZE];						// $0000 -> $FFFF

	uint8_t read(uint16_t addr);
	void write(uint16_t addr, uint8_t val);

	uint8_t fetch();										// Fetches instruction (opcode) from memory pointed at by PC
	AddressingMode decode(uint8_t opcode);								// Returns addressing mode of opcode
	int execute(uint8_t opcode, AddressingMode mode);
	// Instructions:
	int adc();      // ADC - add with carry
	int and();      // AND - and (with accumulator)
	int asl();      // ASL - arithmetic shift left
	int bcc();      // BCC - branch on carry clear
	int bcs();      // BCS - branch on carry set
	int beq();      // BEQ - branch on equal (zero set)
	int bit();      // BIT - bit test
	int bmi();      // BMI - branch on minus (negative set)
	int bne();      // BNE - branch on not equal (zero clear)
	int bpl();      // BPL - branch on plus (negative clear)
	int brk();      // BRK - break / interrupt
	int bvc();      // BVC - branch on overflow clear
	int bvs();      // BVS - branch on overflow set
	int clc();      // CLC - clear carry
	int cld();      // CLD - clear decimal
	int cli();      // CLI - clear interrupt disable
	int clv();      // CLV - clear overflow
	int cmp();      // CMP - compare (with accumulator)
	int cpx();      // CPX - compare with X
	int cpy();      // CPY - compare with Y
	int dec();      // DEC - decrement
	int dex();      // DEX - decrement X
	int dey();      // DEY - decrement Y
	int eor();      // EOR - exclusive or (with accumulator)
	int inc();      // INC - increment
	int inx();      // INX - increment X
	int iny();      // INY - increment Y
	int jmp();      // JMP - jump
	int jsr();      // JSR - jump subroutine
	int lda();      // LDA - load accumulator
	int ldx();      // LDX - load X
	int ldy();      // LDY - load Y
	int lsr();      // LSR - logical shift right
	int nop();      // NOP - no operation
	int ora();      // ORA - or with accumulator
	int pha();      // PHA - push accumulator
	int php();      // PHP - push processor status (SR)
	int pla();      // PLA - pull accumulator
	int plp();      // PLP - pull processor status (SR)
	int rol();      // ROL - rotate left
	int ror();      // ROR - rotate right
	int rti();      // RTI - return from interrupt
	int rts();      // RTS - return from subroutine
	int sbc();      // SBC - subtract with carry
	int sec();      // SEC - set carry
	int sed();      // SED - set decimal
	int sei();      // SEI - set interrupt disable
	int sta();      // STA - store accumulator
	int stx();      // STX - store X
	int sty();      // STY - store Y
	int tax();      // TAX - transfer accumulator to X
	int tay();      // TAY - transfer accumulator to Y
	int tsx();      // TSX - transfer stack pointer to X
	int txa();      // TXA - transfer X to accumulator
	int txs();      // TXS - transfer X to stack pointer
	int tya();      // TYA - transfer Y to accumulator

public:
	NesCpu();
	~NesCpu();

	void step();
};