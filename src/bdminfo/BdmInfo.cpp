/** 
 * 'Join or Die' model format reader.
 */

#include <cstdint>
#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <vector>
#include <cmath>

#include "bdm/BdmLoader.hpp"
#include "bdm/BdmFile.hpp"

template<typename Type, int Count>
void export_(std::ostream &os, const bdm::Array<Type, Count> &array_) {
    for (int i=0; i<Count-1; i++) {
        os << array_.values[i] << " ";
    }

    os << array_.values[Count-1];
}

void export_(std::ostream &os, const bdm::BdmFile &model) {
    auto &vertices = model.vertices();

    // export vertices
    for (auto &face : model.faces()) {
        for (auto &index : face.values) {
            auto &vertex = vertices[index];

            os << "v ";
            export_(os, vertex);

            os << std::endl;
        }
    }

    // export vertex normals
    for (auto &face : model.faces()) {

        bdm::Vertex v[3];
        for (int j=0; j<3; j++) {
            v[j] = vertices[face.values[j]];
        }

        // compute v1 and v2
        bdm::Vertex v1, v2;

        for (int j=0; j<3; j++) {
            v1.values[j] = v[1].values[j] - v[0].values[j];
            v2.values[j] = v[2].values[j] - v[0].values[j];    
        }

        // compute cross product
        bdm::Vertex n;
        n.values[0] = v1.values[1]*v2.values[2] - v1.values[2]*v2.values[1];
        n.values[1] = v1.values[2]*v2.values[0] - v1.values[0]*v2.values[2];
        n.values[2] = v1.values[0]*v2.values[1] - v1.values[1]*v2.values[0];

        // normalize the normal vector
        float length = 0.0f;
        for (int j=0; j<3; j++) {
            length += n.values[j]*n.values[j];
        }

        for (int j=0; j<3; j++) {
            n.values[j] /= std::sqrt(length);
        }

        // export the normal
        for (int j=0; j<3; j++){
            os << "vn ";
            export_(os, n);
            os << std::endl;
        }
    }

    // export texture coordinates
    for (auto &texcoord : model.texcoords()) {
        os << "vt ";

        bdm::TexCoord texcoord_ = texcoord;

        texcoord_.values[0] /= 32.0f;
        texcoord_.values[1] /= 64.0f;

        texcoord_.values[0] = texcoord_.values[0];

        export_(os, texcoord_);

        os << std::endl;
    }

    // export face data
    for (size_t i=0; i<model.faces().size(); i++) {
        bdm::Face face;

        for (size_t j=0; j<3; j++) {
            face.values[j] = static_cast<uint16_t>(i*3) + static_cast<uint16_t>(j) + 1;
        }

        os << "f ";

        export_(os, face);

        os << std::endl;
    }
}

void display( const bdm::BdmFile &file) {
    // output texture filenames
    auto textures = file.textures();
    for (auto texture : textures) {
        std::cout << texture << std::endl;
    }

    // output vertex data
    std::cout << "\nVertices" << std::endl;
    auto vertices = file.vertices();
    for (auto vertex : vertices) {
        std::cout << vertex << std::endl;
    }

    // output face data
    std::cout << "\nFaces" << std::endl;
    auto faces = file.faces();
    for (auto face : faces) {
        std::cout << face << std::endl;
    }

    //  output texture coordinate
    std::cout << "\nTexture Coordinate" << std::endl;
    auto texcoords = file.texcoords();
    for (auto value : texcoords) {
        std::cout << value << std::endl;
    }
}

int main(int argc, char **argv) {
    const std::string filename = argv[1];

    bdm::BdmFile file (filename.c_str());

    export_(std::cout, file);

    return 0;
}
