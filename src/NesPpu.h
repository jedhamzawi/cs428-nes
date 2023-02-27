#pragma once
#include "AbstractClockable.h"

class NesPpu : public AbstractClockable {

public:
	NesPpu() = default; 	// default constructor
	void step();
};