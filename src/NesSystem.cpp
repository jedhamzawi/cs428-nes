#include <chrono>
#include <thread>
#include <iterator>
#include <bits/stdc++.h>

#include "NesSystem.h"

void NesSystem::tick() {
        if (this->masterClock % 12 == 0) {
            this->cpu.step();
            // this->apu.step();
        }

        if (this->masterClock % 4 == 0) {
            this->ppu.step();
        }
}

void NesSystem::loadRom(Rom *rom) {
    // TODO: Load all initial memory from ROM for startup (like PRG-ROM below)

    // Fill PRG-ROM starting at #8000
    std::copy(std::begin(rom->getProgramRoms()->at(0)), std::end(rom->getProgramRoms()->at(0)), &memory[0x8000]);
    if (rom->getHeader().getNumPrgRom() > 1) {
        std::copy(std::begin(rom->getProgramRoms()->at(1)), std::end(rom->getProgramRoms()->at(1)), &memory[0xC000]);
    }
    else {
        std::copy(std::begin(rom->getProgramRoms()->at(0)), std::end(rom->getProgramRoms()->at(0)), &memory[0xC000]);
    }
}

[[noreturn]] void NesSystem::run() {
    initCpu();
    // TODO: Remove demo or log
    std::cout << "BEGIN PROGRAM" << std::endl;
    while(true) {
        this->tick();
        
        // Sync with real time of a frame
        if (this->masterClock == this->TICKS_PER_FRAME) {
            using namespace std::chrono_literals;
            std::this_thread::sleep_for(0.016666666s);       // 1/60th of a sec
        }

        this->masterClock++;
    }
}

void NesSystem::initCpu() {
    cpu.initProgramCounter();
}
