#pragma once
#include "INESHeader.h"
#include "Rom.h"

class RomParser
{
    public:
        RomParser();
        Rom* parseROM(std::string fileName); //this function will be used to read in the header and then send it to the INESHeader class to be parsed and checked properly
};