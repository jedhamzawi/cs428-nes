#pragma once
#include "INESHeader.h"



const int PRG_ROM_SIZE = 16384;
const int CHR_ROM_SIZE = 8192;



class RomParser
{
    private:
        INESHeader romHeader; // all the header data of the ROM




    public:
        bool parseROM(std::string fileName); //this function will be used to read in the header and then send it to the INESHeader class to be parsed and checked properly

        RomParser();

        INESHeader getHeader();

        uint8_t programROMS[30][PRG_ROM_SIZE]; //This is an array of all the program rom stored as single bytes.
        uint8_t characterROMS[30][CHR_ROM_SIZE];



};