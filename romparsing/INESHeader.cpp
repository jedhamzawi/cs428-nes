#include "INESHeader.h"


INESHeader::INESHeader()
{

}

INESHeader::INESHeader(char nesString[], uint8_t fileFormatIdent, uint8_t numPrgRom, uint8_t numChrRom,
                       uint8_t romControlOne, uint8_t romControlTwo, uint8_t numRAM, uint8_t reservedBuffer[])
{
    for (int x = 0; x < 2; x++)
    {
        this->nesString[x] = nesString[x];
    }
    this->fileFormatIdent = fileFormatIdent;
    this->numPrgRom = numPrgRom;
    this->numChrRom = numChrRom;
    this->romControlOne = romControlOne;
    this->romControlTwo = romControlTwo;
    this->numRAM = numRAM;
    for (int x = 0; x < 7; x++)
    {
        this->reservedBuffer[x] = reservedBuffer[x];
    }

}

