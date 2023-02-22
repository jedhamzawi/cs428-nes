#pragma once
#include "INESHeader.h"




//This enum maps the number of the mapper type that is stored in the iNES format (*.nes) for use in bank switching (games larger than 32KB)
enum mapper
{
    NROM = 0,
    MMC1 = 1,
    UNROM = 2,
    CNROM = 3,
    MMC3 = 4,
    MMC5 = 5,
    FFE_F4 = 6,
    AOROM = 7,
    FFE_F3 = 8,
    MMC2 = 9,
    MMC4 = 10,
    COLOR_DREAMS = 11,
    FFE_F6 = 12,
    HUNDRED_IN_ONE = 15,
    BANDAI = 16,
    FFE_F8 = 17,
    SS8806 = 18,
    NAMCOT_106 = 19,
    NIN_DSK = 20,
    VRC_4A = 21,
    VRC_2A_1 = 22,
    VRC_2A_2 = 23,
    VRC_6 = 24,
    VRC_4b = 25,
    IREM_G101 = 32,
    TAITOTC = 33,
    SWITCH_32KB_ROM = 34,
    RAMBO_1 = 64,
    IREM_H3001 = 65,
    SWITCH_GN_ROM = 66,
    SUNSOFT_3 = 67,
    SUNSOFT_4 = 68,
    SUNSOFT_5 = 69,
    CAMERICA = 71,
    IREM_74HC161 = 78,
    HK_SF3_PIRATE = 91

};


class RomParser
{
    private:
        INESHEader romHeader; // all the header data of the ROM

    public:
        bool parseHeader(char16_t fileName[]); //this function will be used to read in the header and then send it to the INESHeader class to be parsed and checked properly

};