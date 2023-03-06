#pragma once

class AbstractClockable {
public:
	virtual void step() = 0;

protected:
	int clock = 0;
};
