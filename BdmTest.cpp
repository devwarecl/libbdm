/** 
 * 'Join or Die' model format reader.
 */

#include <cstdint>
#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <vector>

#include "BdmLoader.hpp"

namespace bdm {
    // New line character
    static const int Separator = 0x0A;

    struct Header {
        std::uint16_t textureCount;
        std::uint16_t vertexCount;
        std::uint16_t unknown03;
        std::uint16_t faceCount;
        std::uint16_t unknown05;

        friend std::ostream& operator<< (std::ostream& os, const Header &header) {
            os << "Texture Count: " << header.textureCount << std::endl;
            os << "Vertex Count: " << header.vertexCount << std::endl;
            os << "Unknown03: " << header.unknown03 << std::endl;
            os << "Face Count (?): " << header.faceCount << std::endl;
            os << "Unknown05: " << header.unknown05 << std::endl;

            return os;
        }
    };
    
    template<typename Field>
    Field read(std::fstream &fs) {
        Field field;
        
        fs.read(reinterpret_cast<char*>(&field), sizeof(Field));

        return field;
    }

    std::vector<std::string> readTextures(std::fstream &fs, const Header &header) {
        std::vector<std::string> textures(header.textureCount);
    
        // output texture filenames
        for (int i=0; i<header.textureCount; ++i) {
            bool done = false;
            std::string textureName = "";

            while (!done) {
                int character = fs.get();

                if (character == bdm::Separator) {
                    done = true;
                } else {
                    textureName += static_cast<char>(character);
                }
            }

            textures.push_back(textureName);
        }

        return textures;
    }

    struct Vertex {
        float x, y, z;

        friend std::ostream& operator << (std::ostream &os, const Vertex &v) {
            std::cout << v.x << ", " << v.y << ", " << v.z;

            return os;
        }
    };

    struct Face {
        std::uint16_t v1, v2, v3;

        friend std::ostream& operator << (std::ostream &os, const Face &f) {
            std::cout << f.v1 << ", " << f.v2 << ", " << f.v3;

            return os;
        }
    };

    std::vector<Vertex> readVertices(std::fstream &fs, const Header &header) {
        std::vector<Vertex> floats;

        int total = header.vertexCount;

        while (total-- > 0) {
            Vertex value = read<Vertex>(fs);
            floats.push_back(value);
        }

        return floats;
    }

    std::vector<Face> readFaces(std::fstream &fs, const Header &header) {
        std::vector<Face> faces;

        int total = header.faceCount;

        while (total-- > 0) {
            auto face = read<Face>(fs);
            faces.push_back(face);
        }

        return faces;
    }
}

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
