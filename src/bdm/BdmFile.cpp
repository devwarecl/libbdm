
#include "BdmFile.hpp"

namespace bdm {

    BdmFile::BdmFile(const char *file) {
        std::cout << "Opening file: " << file << std::endl;

        std::ifstream is;

        is.open(file, std::ios_base::binary);

        if (!is.is_open()) {
            throw std::runtime_error("Can't open file '" + std::string(file));
        }

        parse(is);
    }

    void BdmFile::parse(std::istream &is) {

        while (is.tellg() >= 0) {
            bdm::Header header = bdm::read<bdm::Header>(is);

            if (m_meshes.size() > 0) {
                 break;
            }
            
            std::cout << header << std::endl;

            bdm::Mesh mesh;
            mesh.textures   = bdm::readTextures(is, header);
            mesh.vertices   = bdm::read<bdm::Vertex>(is, header.vertexCount);
            mesh.faces      = bdm::read<bdm::Face>(is, header.faceCount);
            mesh.texcoords  = bdm::read<bdm::TexCoord>(is, header.faceCount * 3);
            mesh.texturefaces = bdm::read<std::uint16_t>(is, header.faceCount );

            m_meshes.push_back(mesh);
        }

        //std::cout << is.tellg() << std::endl;

        //// remaining field 3
        //std::cout << "remaining field 3" << std::endl;
        //auto field3 = bdm::read<bdm::Vertex>(is, 2);
        //for (auto value : field3) {
        //    std::cout << value << std::endl;
        //}
        //std::cout << std::endl;

        //// remaining field 4
        //std::cout << "remaining field 4" << std::endl;
        //auto field4 = bdm::read<float>(is, 2);
        //for (auto value : field4) {
        //    std::cout << value << std::endl;
        //}
        //std::cout << std::endl;
        //
        //std::cout << is.tellg() << " of " << 427 << std::endl;
        // 427
    }
}
