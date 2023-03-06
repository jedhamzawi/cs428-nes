#pragma once
#include <array>

#include "INESHeader.h"

const int PRG_ROM_SIZE = 16384;
const int CHR_ROM_SIZE = 8192;
const int MAX_ROM_BANKS = 32;

class Rom {
private:
    INESHeader header;
    std::array<std::array<uint8_t, PRG_ROM_SIZE>, MAX_ROM_BANKS> programROMS;
    std::array<std::array<uint8_t, PRG_ROM_SIZE>, MAX_ROM_BANKS> characterROMS;
public:
    Rom(INESHeader header,
        std::array<std::array<uint8_t, PRG_ROM_SIZE>, MAX_ROM_BANKS> programROMS,
        std::array<std::array<uint8_t, PRG_ROM_SIZE>, MAX_ROM_BANKS> characterROMS):
        header(header),
        programROMS(programROMS),
        characterROMS(characterROMS) {}

    const INESHeader &getHeader() const {
        return header;
    }

    const std::array<std::array<uint8_t, PRG_ROM_SIZE>, MAX_ROM_BANKS> &getProgramRoms() const {
        return programROMS;
    }

    const std::array<std::array<uint8_t, PRG_ROM_SIZE>, MAX_ROM_BANKS> &getCharacterRoms() const {
        return characterROMS;
    }
};
