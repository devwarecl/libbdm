/** 
 * 'Join or Die' model format reader.
 */

#include <cstdint>
#include <iostream>
#include <fstream>
#include <string>

#include "BdmLoader.hpp"

const int BDM_TEXTURENAME_SEPARATOR = 0x0A;    // New line character

typedef struct {
    std::uint16_t texture_count;
    std::uint16_t unknown_02;
    std::uint16_t unknown_03;
    std::uint16_t unknown_04;
    std::uint16_t unknown_05;
} BDMHEADER;

int main(int argc, char **argv) {
    const std::string filename = argv[1];

    std::fstream fs_bdm;

    // file open
    fs_bdm.open(filename.c_str(), std::ios_base::binary|std::ios_base::in);
    if (!fs_bdm.is_open()) {
        std::cout << "Cannot open file '" << filename << "'" << std::endl;
        return -1;
    }

    // output known header data
    BDMHEADER header = {0};
    fs_bdm.read((char*)&header, sizeof(BDMHEADER));

    std::cout << "File: " << filename << std::endl;
    std::cout << "Texture count: " << header.texture_count << std::endl;

    // output texture filenames
    for (int i=0; i<header.texture_count; ++i) {
        bool done = false;
        std::string textureName = "";

        while (!done) {
            int character = fs_bdm.get();

            if (character == BDM_TEXTURENAME_SEPARATOR) {
                done = true;
            } else {
                textureName += static_cast<char>(character);
            }
        }

        std::cout << "Texture " << (i + 1) << ": " << textureName << std::endl;
    }

    return 0;
}
