#include "NesSystem.h"

void NesCpu::step() {
    // Check if starting instruction
    if (this->clock == 0) {
        // Fetch instruction
        // Decode instruction
        // Execute instruction
            //int instructionCost = ?
        // Set internal clock to instruction's step cost
            this->clock += instructionCost;
    }
    // Wait until instruction's step cost is paid
    this->clock--;
}