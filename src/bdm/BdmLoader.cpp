
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
}
