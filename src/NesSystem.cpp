#include <chrono>
#include <thread>

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

void NesSystem::run() {
    while(1) {
        this->tick();
        
        // Sync with real time of a frame
        if (this->masterClock == this->TICKS_PER_FRAME) {
            using namespace std::chrono_literals;
            std::this_thread::sleep_for(0.016666666s);       // 1/60th of a sec
        }

        this->masterClock++;
    }
}