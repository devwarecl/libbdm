
#include "BdmFile.hpp"

namespace bdm {

    BdmFile::BdmFile(const char *file) {
        std::ifstream is;

        is.open(file, std::ios_base::binary);

        if (!is.is_open()) {
            throw std::runtime_error("");
        }

        parse(is);
    }

    void BdmFile::parse(std::istream &is) {
        bdm::Header header = bdm::read<bdm::Header>(is);

        m_textures = bdm::readTextures(is, header);
        m_vertices = bdm::read<bdm::Vertex>(is, header.vertexCount);
        m_faces = bdm::read<bdm::Face>(is, header.faceCount);
        m_texcoords = bdm::read<bdm::TexCoord>(is, header.faceCount * 3);
    }
}
