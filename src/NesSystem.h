#pragma once
#include "NesCpu.h"
#include "NesPpu.h"
#include "NesApu.h"

class NesSystem {
private:
	static constexpr uint16_t ADDRESS_SPACE_SIZE = 65536;
	int masterClock;
	NesCpu cpu;
	NesPpu ppu;
	NesApu apu;

	void tick();

public:
	const int TICKS_PER_FRAME = 357954; 			// (21,477,272 ticks/sec)  /  (60 frames/sec)
	uint8_t memory[ADDRESS_SPACE_SIZE];				// $0000 -> $FFFF

	NesSystem() : cpu(memory), ppu(memory) {} // pass pointer to memory to cpu and ppu

	void run();
};