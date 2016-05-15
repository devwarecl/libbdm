/** 
 * 'Join or Die' model format reader.
 */

#include <cstdint>
#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <vector>

#include "bdm/BdmLoader.hpp"

int main(int argc, char **argv) {

    const std::string filename = argv[1];

    std::fstream fs_bdm;

    // file open
    fs_bdm.open(filename.c_str(), std::ios_base::binary|std::ios_base::in);
    if (!fs_bdm.is_open()) {
        std::cout << "Cannot open file '" << filename << "'" << std::endl;
        return -1;
    }

    bdm::Header header = bdm::read<bdm::Header>(fs_bdm);

    // output known header data
    std::cout << header << std::endl;

    // output texture filenames
    auto textures = bdm::readTextures(fs_bdm, header);
    for (auto texture : textures) {
        std::cout << texture << std::endl;
    }

    // output vertex data
    auto vertices = bdm::readVertices(fs_bdm, header);
    for (auto vertex : vertices) {
        std::cout << vertex << std::endl;
    }

    // output face data
    auto faces = bdm::readFaces(fs_bdm, header);
    for (auto face : faces) {
        std::cout << face << std::endl;
    }

    return 0;
}
