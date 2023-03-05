#include <iostream>
#include <fstream>
#include <bitset>
#include "RomParser.h"



RomParser::RomParser()
{

}


bool RomParser::parseHeader(std::string fileName)
{
    std::string filename = fileName; // Replace with your file name
    std::ifstream infile(filename, std::ios::binary);

    if (infile) {
        char byte;

        //read the first three bytes in as chars
        char nesIDENT[3];
        for (int x = 0; x < 3; x++)
        {
            infile.get(byte);
            std::cout << byte << std::endl; //check that these first three are the right chars for testing purposes
            nesIDENT[x] = byte;
        }

        //read in the "1A" hex code
        infile.get(byte);
        uint8_t fileFormatIdent = static_cast<uint8_t>(byte);//cast this into a useful format

        //just pull in the rom numbers and turn them into ints for processing
        infile.get(byte);
        uint8_t numPrgRom = static_cast<uint8_t>(byte);
        infile.get(byte);
        uint8_t numChrRom = static_cast<uint8_t>(byte);
        infile.get(byte);
        uint8_t  romControlOne = static_cast<uint8_t>(byte);
        infile.get(byte);
        uint8_t  romControlTwo = static_cast<uint8_t>(byte);
        infile.get(byte);
        uint8_t numRAM = static_cast<uint8_t>(byte);

        romHeader = INESHeader(nesIDENT, fileFormatIdent, numPrgRom, numChrRom, romControlOne, romControlTwo, numRAM, NULL);



        while (infile.get(byte)) {
            std::bitset<8> bits(byte);

            std::cout << bits.to_string() << " " << std::endl;
        }
        infile.close();
    }
    else {
        std::cerr << "Unable to open file: " << filename << std::endl;
        return 1;
    }

    return 0;

}

INESHeader RomParser::getHeader()
{
    return romHeader;
}

