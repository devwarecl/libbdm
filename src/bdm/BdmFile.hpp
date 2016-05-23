
#pragma once
#ifndef __bdm_bdmfile_hpp__
#define __bdm_bdmfile_hpp__

#include "BdmLoader.hpp"
#include <iostream>

namespace bdm {

    struct Mesh {
        std::vector<std::string> textures;
        std::vector<bdm::Vertex> vertices;
        std::vector<bdm::Face> faces;
        std::vector<bdm::TexCoord> texcoords;
    };

    class BdmFile {
    public:
        explicit BdmFile(std::istream &is) {
            parse(is);
        }

        explicit BdmFile(const char *file);

        const std::vector<Mesh>& meshes() const  {
            return m_meshes;
        }

    protected:
        void parse(std::istream &is);

    private:
        std::vector<Mesh> m_meshes;
    };
}

#endif 
