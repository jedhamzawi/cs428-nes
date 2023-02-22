#include "RomParser.h"
#include "INESHeader.h"
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <bitset>

int main()
{
    RomParser myParser = RomParser();

    myParser.parseHeader("smb.nes");

}



