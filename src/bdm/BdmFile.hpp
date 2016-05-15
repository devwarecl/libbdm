
#pragma once
#ifndef __bdm_bdmfile_hpp__
#define __bdm_bdmfile_hpp__

#include "BdmLoader.hpp"
#include <iostream>

namespace bdm {

    class BdmFile {
    public:
        explicit BdmFile(std::istream &is) {
            parse(is);
        }

        explicit BdmFile(const char *file);

        const std::vector<bdm::Vertex>& vertices() const  {
            return m_vertices;
        }

        const std::vector<bdm::TexCoord>& texcoords() const {
            return m_texcoords;
        }

        const std::vector<std::string>& textures() const {
            return m_textures;
        }

        const std::vector<bdm::Face>& faces() const {
            return m_faces;
        }

    protected:
        void parse(std::istream &is);

    private:
        std::vector<bdm::Vertex>    m_vertices;
        std::vector<bdm::Face>      m_faces;
        std::vector<bdm::TexCoord>  m_texcoords;
        std::vector<std::string>    m_textures;
    };
}

#endif 
