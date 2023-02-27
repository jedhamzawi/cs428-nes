#pragma once
#include "NesCpu.h"
#include "NesPpu.h"
#include "NesApu.h"

class NesSystem {
private:
	int masterClock;
	NesCpu cpu = NesCpu();
	NesPpu ppu = NesPpu();
	NesApu apu = NesApu();

	void tick();

public:
	const int TICKS_PER_FRAME = 357954; 	// (21,477,272 ticks/sec)  /  (60 frames/sec)
	void run();
};