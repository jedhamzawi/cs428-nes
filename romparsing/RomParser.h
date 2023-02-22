#pragma once
#include "INESHeader.h"







class RomParser
{
    private:
        INESHeader romHeader; // all the header data of the ROM

    public:
        bool parseHeader(std::string fileName); //this function will be used to read in the header and then send it to the INESHeader class to be parsed and checked properly

        RomParser();



};