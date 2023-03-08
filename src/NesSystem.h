#pragma once
#include "cpu/NesCpu.h"
#include "NesPpu.h"
#include "NesApu.h"
#include "Rom.h"

class NesSystem {
private:
	static constexpr uint32_t ADDRESS_SPACE_SIZE = 65536;
	int masterClock = 0;
	NesCpu cpu;
	NesPpu ppu;
	NesApu apu;

	void tick();
    void initCpu();

public:
	const int TICKS_PER_FRAME = 357954; 			// (21,477,272 ticks/sec)  /  (60 frames/sec)
	uint8_t memory[ADDRESS_SPACE_SIZE] = {0};		// $0000 -> $FFFF; initialized to 0's

	NesSystem() : cpu(memory), ppu(memory) {} // pass pointer to memory to cpu and ppu

    void loadRom(Rom *rom);
    [[noreturn]] void run();
};