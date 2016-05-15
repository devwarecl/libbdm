

#pragma once
#ifndef __bdmloader__
#define __bdmloader__

#include <vector>
#include <list>
#include <fstream>
#include <iostream>

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

    std::vector<std::string> readTextures(std::fstream &fs, const Header &header);

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

    std::vector<Vertex> readVertices(std::fstream &fs, const Header &header);

    std::vector<Face> readFaces(std::fstream &fs, const Header &header);
}


#endif
