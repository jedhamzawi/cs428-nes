#include "NesCpu.h"

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


uint8_t NesCpu::read(uint16_t addr) {
    return memory[addr];
}

void NesCpu::write(uint16_t addr, uint8_t val) {
    memory[addr] = val;
}

uint8_t NesCpu::fetch() {
    uint8_t opcode = read(this->programCounter);
    this->programCounter++;
    return opcode;
}

NesCpu::AddressingMode NesCpu::decode(uint8_t opcode) {
    // TODO: get addressing mode
}

int NesCpu::execute(uint8_t opcode, NesCpu::AddressingMode mode) {
    switch(opcode) {

        // ADC - add with carry
        case 0x61: case 0x65: case 0x69: case 0x6D:
        case 0x71: case 0x75: case 0x79: case 0x7D:
            return adc();

        // AND - and (with accumulator)
        case 0x21: case 0x25: case 0x29: case 0x2D:
        case 0x31: case 0x35: case 0x39: case 0x3D:
            return and();

        // ASL - arithmetic shift left
        case 0x06: case 0x0A: case 0x0E: case 0x16: case 0x1E:
            return asl();

        // Other instructions...
        
        default:
            // Unknown opcode, handle error here
            break;
    }
}

int NesCpu::adc() {
    // Set base instruction cost (cycles/steps)
    // Do instruction
    // Add +1 to cost if applicable mode and page boundary crossed
    // Return cost
}


