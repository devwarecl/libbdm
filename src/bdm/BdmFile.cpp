
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

    struct UnknownField {
        std::uint16_t field1;
        std::uint16_t field2;
        std::uint16_t field3;
        std::uint16_t field4;
        std::uint16_t field5;
        std::uint16_t flag_or_count;

        friend std::ostream& operator<< (std::ostream &os, const UnknownField &uf) {
            
            os << uf.field1 << " " << uf.field2 << " " << uf.field3 << " " << uf.field4 << " " << uf.field5 << std::endl;
            os << "flag_or_count: " << uf.flag_or_count << std::endl;

            return os;
        }
    };

    typedef bdm::Array<std::uint16_t, 34> ConditionalField1;
    
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

            // campo restante 1 (sacar por salida estandar)
            std::cout << "OFFSET: " << std::hex << is.tellg() << std::dec << std::endl;

            // remaining field 1
            std::cout << "remaining field 1" << std::endl;
            auto field1 = bdm::read<UnknownField>(is);

            std::cout << field1 << std::endl;

            if (field1.flag_or_count) {
                auto cf = bdm::read<ConditionalField1>(is);

                std::cout << "remaining conditional field 1" << std::endl;
                std::cout << cf << std::endl;
            }

            // remaining field 2
            std::cout << "remaining field 2" << std::endl;
            auto field2 = bdm::read<bdm::Vertex>(is, header.faceCount);
            for (auto value : field2) {
                std::cout << value << std::endl;
            }
            std::cout << std::endl;

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
