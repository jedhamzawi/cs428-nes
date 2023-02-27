#pragma once
#include "AbstractClockable.h"

class NesApu : public AbstractClockable {

public:
	NesApu() = default; 	// default constructor
	void step();
};