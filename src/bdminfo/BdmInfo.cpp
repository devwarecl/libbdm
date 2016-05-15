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
    std::cout << "\nVertices" << std::endl;
    auto vertices = bdm::read<bdm::Vertex>(fs_bdm, header.vertexCount);
    for (auto vertex : vertices) {
        std::cout << vertex << std::endl;
    }

    // output face data
    std::cout << "\nFaces" << std::endl;
    auto faces = bdm::read<bdm::Face>(fs_bdm, header.faceCount);
    for (auto face : faces) {
        std::cout << face << std::endl;
    }

    // 
    std::cout << "\nPoints (?)" << std::endl;
    auto unknowns = bdm::read<bdm::Vertex>(fs_bdm, 1000000);
    for (auto value : unknowns) {
        std::cout << value << std::endl;
    }

    // output texture coordinates
    // std::cout << "\nTex Coords (?)" << std::endl;
    // auto texcoords = bdm::read<bdm::Array<float, 4>>(fs_bdm, header.vertexCount);
    // for (auto texcoord : texcoords) {
    //     std::cout << texcoord << std::endl;
    // }

    return 0;
}
