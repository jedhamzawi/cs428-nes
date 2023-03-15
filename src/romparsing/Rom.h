#pragma once
#include <array>
#include <vector>

#include "INESHeader.h"

static const int MAX_ROM_BANKS = 32;

const int PRG_ROM_SIZE = 16384;
const int CHR_ROM_SIZE = 8192;

class Rom {
private:
    INESHeader header;
    std::vector<std::array<uint8_t, PRG_ROM_SIZE>> *programROMS;
    std::vector<std::array<uint8_t, PRG_ROM_SIZE>> *characterROMS;
public:
    Rom(INESHeader header,
        std::vector<std::array<uint8_t, PRG_ROM_SIZE>> *programROMS,
        std::vector<std::array<uint8_t, PRG_ROM_SIZE>> *characterROMS)
        : header(header)
        , programROMS(programROMS)
        , characterROMS(characterROMS) {}

    ~Rom() {
        delete this->programROMS;
        delete this->characterROMS;
    }

    const INESHeader &getHeader() const {
        return header;
    }

    const std::vector<std::array<uint8_t, PRG_ROM_SIZE>> *getProgramRoms() const {
        return programROMS;
    }

    const std::vector<std::array<uint8_t, PRG_ROM_SIZE>> *getCharacterRoms() const {
        return characterROMS;
    }
};
