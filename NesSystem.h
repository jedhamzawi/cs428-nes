#pragma once

class NesSystem {
private:
	int master_clock;

	void step(int t_master_clock);

public:
	void run();
};