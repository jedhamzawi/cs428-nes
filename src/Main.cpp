#include <iostream>
#include "NesSystem.h"
#include "RomParser.h"

const int INVALID_ARGS_CODE = 1;

void usage();



int main(int argc, char **argv) {
    if (argc != 2) {
        std::cerr << "Invalid args!" << std::endl << std::endl;
        usage();
        return INVALID_ARGS_CODE;
    }
    std::string romPath = argv[1];

    NesSystem nesSystem;
    RomParser parser = RomParser();

    Rom *rom = parser.parseROM(romPath);
    if (rom == nullptr) {
        std::cout << "Invalid ROM, or no ROM given. Please reset with a valid ROM." << std::endl;
    }
    else {
        nesSystem.loadRom(rom);
    }
    nesSystem.run();
}

void usage() {
    std::cerr << "Usage:" << std::endl;
    std::cerr << "  simple-nes <path-to-rom-file>" << std::endl;
}
