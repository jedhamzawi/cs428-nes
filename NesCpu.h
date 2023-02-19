#pragma once
#include "AbstractClockable.h"

class NesCpu : public AbstractClockable {
private:
	const uint8_t STACK_POINTER_START = 0xFD;  	// Check documentation, should be $FF, but power-on/reset decrements 3?
	uint8_t regAccumulator = 0;					// (A)
	uint8_t regX = 0;							// (X)
	uint8_t regY = 0;							// (Y)
	uint8_t regStatus = 0;						// (P)
	uint8_t stackPointer = 0xFD;				// (S) Stack is stored top -> bottom ($01FF -> $0100)
	uint16_t programCounter = 0; 				// (PC)
	uint16_t addressBus;
public:
	NesCpu() = default; 	// default constructor
	void step();
};