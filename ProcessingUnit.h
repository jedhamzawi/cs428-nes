#pragma once

class ProcessingUnit {
public:
	virtual void step_to(int t_master_clock) = 0;

protected:
	int internal_clock;
};
