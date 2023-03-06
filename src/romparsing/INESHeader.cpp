#include <bitset>
#include "INESHeader.h"


INESHeader::INESHeader()
{

}

INESHeader::INESHeader(char nesString[], uint8_t fileFormatIdent, uint8_t numPrgRom, uint8_t numChrRom,
                       uint8_t romControlOne, uint8_t romControlTwo, uint8_t numRAM, uint8_t reservedBuffer[]) {
    for (int x = 0; x < 3; x++) {
        this->nesString[x] = nesString[x];
    }
    this->fileFormatIdent = fileFormatIdent;
    this->numPrgRom = numPrgRom;
    this->numChrRom = numChrRom;
    this->romControlOne = romControlOne;
    this->romControlTwo = romControlTwo;
    if (numRAM == 0) {
        this->numRAM = 1;
    }
    else {
        this->numRAM = numRAM;
    }
    if (reservedBuffer != NULL) {
        for (int x = 0; x < 7; x++) {
            this->reservedBuffer[x] = reservedBuffer[x];
        }
    }
    else {
        for (int x = 0; x < 7; x++) {
            this->reservedBuffer[x] = NULL;
        }
    }

    uint8_t tempMapperNumber = romControlTwo << 4;
    uint8_t mapperNumberPtTwo = (romControlOne >> 4) & 0b00001111;
    tempMapperNumber = tempMapperNumber | mapperNumberPtTwo;
    this->headerMapper = static_cast<mapper>(tempMapperNumber);





}


bool INESHeader::printHeaderInformation()
{
    std::cout << "First string is :" << this->nesString << std::endl;
    std::bitset<8> bits(this->fileFormatIdent);

    //std::cout << bits.to_string() << " " << std::endl;
    std::cout << "1A value is: " << bits.to_string() << std::endl;
}

uint8_t INESHeader::getNumPrgRom() const
{
    return numPrgRom;
}

uint8_t INESHeader::getNumChrRom() const
{
    return numChrRom;
}

uint8_t INESHeader::getRomControlOne() const
{
    return romControlOne;
}

uint8_t INESHeader::getRomControlTwo() const
{
    return romControlTwo;
}

uint8_t INESHeader::getNumRam() const
{
    return numRAM;
}

const uint8_t *INESHeader::getReservedBuffer() const
{
    return reservedBuffer;
}

mapper INESHeader::getHeaderMapper() const
{
    return headerMapper;
}



