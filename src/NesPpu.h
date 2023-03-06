#pragma once
#include "AbstractClockable.h"

class NesPpu : public AbstractClockable {
private:
	uint8_t* memory;										// pointer to NesSystem memory
public:
	NesPpu(uint8_t* memory): memory(memory) {}
	~NesPpu() {}
	void step() {};
};
