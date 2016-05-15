
#include "BdmLoader.hpp"

namespace bdm {
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
