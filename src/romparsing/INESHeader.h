#pragma once
#include <iostream>



//This enum maps the number of the mapper type that is stored in the iNES format (*.nes) for use in bank switching (games larger than 32KB)
enum mapper {
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



class INESHeader {
    private:
        //raw variables (straight from the source ROM)
        char nesString[3]; //This is a three character idetnifier that simply has "NES" to identify it as an iNES file
        uint8_t fileFormatIdent; //This is a 1 byte identifier value, should have $1A
        uint8_t numPrgRom; //This is the number of 16 kb PRG-ROM banks (Program ROM)
        uint8_t numChrRom; //This is the number of 8 kb CHR-ROM / VROM banks (used for graphical information)
        uint8_t romControlOne; //This is an 8 bit binary number that indicates different chips and s   
        /*
        Bit 0 - Indicates the type of mirroring used by the game
        where 0 indicates horizontal mirroring, 1 indicates
        vertical mirroring.
        Bit 1 - Indicates the presence of battery-backed RAM at
        memory locations $6000-$7FFF.
        Bit 2 - Indicates the presence of a 512-byte trainer at
        memory locations $7000-$71FF.
        Bit 3 - If this bit is set it overrides bit 0 to indicate fourscreen mirroring should be used.
        Bits 4-7 - Four lower bits of the mapper number. 
        */


        uint8_t romControlTwo;//Second 8-bit binaary number that is used for control modes
        /*
            • Bits 0-3 - Reserved for future usage and should all be 0.
            • Bits 4-7 - Four upper bits of the mapper number. 
        */

        uint8_t numRAM; //The number of 8kb ram banks. For compatabiltiy reasons if this value is 0 it should be assumed to be 1
        uint8_t reservedBuffer[7]; //reserved for future usage and should all be 0


        //derived variables
        mapper headerMapper; // This variable is used to store the mapper type found in the header

    public:

        //constructor
        INESHeader(char nesString[], uint8_t fileFormatIdent, uint8_t numPrgRom, uint8_t numChrRom,
        uint8_t romControlOne, uint8_t romControlTwo, uint8_t numRAM, uint8_t reservedBuffer[]);

        //empty constructor
        INESHeader();

        //bool isValidHeader(); //check that the file given is a valid iNES file


        bool printHeaderInformation(); //A diagnostic print function for us to verify what all the header has

        //char32_t errorMessage[]; //just an error message that can be used to let the user know what is wrong with the header

    uint8_t getNumPrgRom() const;

    uint8_t getNumChrRom() const;

    uint8_t getRomControlOne() const;

    uint8_t getRomControlTwo() const;

    uint8_t getNumRam() const;

    const uint8_t *getReservedBuffer() const;

    mapper getHeaderMapper() const;

};