#include <iostream>
#include <fstream>
#include <bitset>
#include <array>

#include "RomParser.h"
//#include "Opcode.h"
//#include "OpcodeTable.h"

/*
 * This function does pretty much all the work of reading in NES ROM files and interpreting them into a usable state
 *
 * All information about header data can be found in the INESHeader.h file
 * after reading in the header the parser currently just goes in and assigns the program roms and character roms as
 * 2d arrays, with the first value representing the rom number and the second the byte.
 * When I better understand how we are actually storing opcodes I can update this to match.
 *
 */
Rom* RomParser::parseROM(const std::string &filePath) {
    std::ifstream infile(filePath, std::ios::binary);

    if (infile) {
        char byte;

        //BEGIN HEADER READ IN
        //read the first three bytes in as chars
        char nesIDENT[3];
        for (char & x : nesIDENT) {
            infile.get(byte);
            // TODO: Remove demo or log
            std::cout << byte << std::endl; //check that these first three are the right chars for testing purposes
            x = byte;
        }

        //read in the "1A" hex code
        infile.get(byte);
        auto fileFormatIdent = static_cast<uint8_t>(byte);//cast this into a useful format

        //just pull in the rom numbers and turn them into ints for processing
        infile.get(byte);
        auto numPrgRom = static_cast<uint8_t>(byte);
        infile.get(byte);
        auto numChrRom = static_cast<uint8_t>(byte);
        infile.get(byte);
        auto  romControlOne = static_cast<uint8_t>(byte);
        infile.get(byte);
        auto  romControlTwo = static_cast<uint8_t>(byte);
        infile.get(byte);
        auto numRAM = static_cast<uint8_t>(byte);

        INESHeader romHeader = INESHeader(nesIDENT, fileFormatIdent, numPrgRom, numChrRom, romControlOne, romControlTwo, numRAM, nullptr);

        //we should read in the trainer data just in case
        for (int i = 0; i < 7; i++)
        {
            infile.get(byte);
        }
        //END HEADER READ IN


        //this->romHeader.printHeaderInformation();
        // TODO: Remove demo or log
        std::cout << "BEGIN PARSING PRG ROMS" << std::endl;
        auto *programROMS = new std::array<std::array<uint8_t, PRG_ROM_SIZE>, MAX_ROM_BANKS>; //This is an array of all the program rom stored as single bytes.
        //This loop is where we need to store all of the PRG-ROM data into banks
        for (int x = 0; x < romHeader.getNumPrgRom(); x++) {
            for (int y = 0; y < PRG_ROM_SIZE; y++) {
                infile.get(byte);
                programROMS->at(x)[y] = static_cast<uint8_t>(byte);
                std::bitset<8> bits(byte);

                // TODO: Remove demo or log
                //std::cout << bits.to_string() << " " << std::endl;
            }
        }
        // TODO: Remove demo or log
        std::cout << "FINISHED PRG ROMS" << std::endl;


        //This loop is where we need to store all of the CHR-ROM data into banks
        // TODO: Remove demo or log
        std::cout << "BEGIN PARSING CHR ROMS" << std::endl;
        auto* characterROMS = new std::array<std::array<uint8_t, PRG_ROM_SIZE>, MAX_ROM_BANKS>{};
        for (int x = 0; x < romHeader.getNumChrRom(); x++) {
            for (int y = 0; y < CHR_ROM_SIZE; y++)
            {
                infile.get(byte);
                characterROMS->at(x)[y] = static_cast<uint8_t>(byte);
                std::bitset<8> bits(byte);

                //std::cout << bits.to_string() << " " << std::endl;
            }
        }
        // TODO: Remove demo or log
        std::cout << "FINISHED CHR ROMS" << std::endl << std::endl;


        //Cleaning up any additonal data for the time being
        while (infile.get(byte)) {
            std::bitset<8> bits(byte);

            std::cout << bits.to_string() << " " << std::endl;
        }
        infile.close();
        return new Rom(romHeader, programROMS, characterROMS);
    }
    else {
        // TODO: Log
        std::cerr << "Unable to open file: " << filePath << std::endl;
        return nullptr;
    }
}
