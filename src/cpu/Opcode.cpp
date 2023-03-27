#include "Opcode.h"

#include <utility>

Opcode::Opcode(Mnemonic mnemonic, AddressingMode mode, short numBytes, short numCycles)
    // Initializer List
    : mnemonic(mnemonic)
    , mode(mode)
    , numBytes(numBytes)
    , numCycles(numCycles) {}

Mnemonic Opcode::getMnemonic() const {
    return mnemonic;
}

std::string Opcode::getMnemonicString() const {
    return MNEMONIC_STRINGS[this->mnemonic];
}

AddressingMode Opcode::getAddressingMode() const {
    return mode;
}

short Opcode::getNumBytes() const {
    return numBytes;
}

short Opcode::getNumCycles() const {
    return numCycles;
}
