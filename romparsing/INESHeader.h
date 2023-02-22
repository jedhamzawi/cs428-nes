#pragma once
#include <iostream>
#include "RomParser.h"

class INESHEader
{
    private:
        //raw variables (straight from the source ROM)
        char16_t nesString[3]; //This is a three character idetnifier that simply has "NES" to identify it as an iNES file
        int8_t fileFormatIdent; //This is a 1 byte identifier value, should have $1A
        int8_t numPrgRom; //This is the number of 16 kb PRG-ROM banks (Program ROM)
        int8_t numChrRom; //This is the number of 8 kb CHR-ROM / VROM banks (used for graphical information)
        int8_t romControlOne; //This is an 8 bit binary number that indicates different chips and s   
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


        int8_t romControlTwo;//Second 8-bit binaary number that is used for control modes
        /*
            • Bits 0-3 - Reserved for future usage and should all be 0.
            • Bits 4-7 - Four upper bits of the mapper number. 
        */

        int8_t numRAM; //The number of 8kb ram banks. For compatabiltiy reasons if this value is 0 it should be assumed to be 1
        int8_t reservedBuffer[7]; //reserved for future usage and should all be 0



        //derived variables
        mapper headerMapper; // This variable is used to store the mapper type found in the header

        bool assignAndCheckMapper();//This function will be used to assign the mapper type as well as checkign if it is valid.
        //returns false if the mapper is an invalid type

    public:

        //constructor
        INESHEader(char16_t nesString[], int8_t fileFormatIdent, int8_t numPrgRom, int8_t numChrRom,
        int8_t romControlOne, int8_t romControlTwo, int8_t numRAM, int8_t reservedBuffer[]);

        bool isValidHeader(); //check that the file given is a valid iNES file

        char32_t errorMessage[]; //just an error message that can be used to let the user know what is wrogn with the header






};