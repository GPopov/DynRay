#include "objloader.hpp"
#include "tiny_obj_loader.h"
#include <iostream>
namespace DynRay
{
namespace OBJLoader
{
    void LoadOBJMeshes(const std::string& inputfile, std::vector<Engine::TriangleMesh>& outMeshes)
    {

        tinyobj::attrib_t attrib;
        std::vector<tinyobj::shape_t> shapes;
        std::vector<tinyobj::material_t> materials;

        std::string warn;
        std::string err;
        bool ret = tinyobj::LoadObj(&attrib, &shapes, &materials, &warn, &err, inputfile.c_str());

        if (!warn.empty()) {
            std::cout << warn << std::endl;
        }

        if (!err.empty()) {
            std::cerr << err << std::endl;
        }

        if (!ret)
            return;

        static constexpr uint32_t INVALID_TRIANGLE_INDEX = 0xFFFFFFFF;
        outMeshes.reserve(outMeshes.capacity() + shapes.size());

        // Loop over shapes
        for (size_t s = 0; s < shapes.size(); s++) {

            DynRay::Engine::TriangleMesh mesh;
            std::vector<size_t> remappedVertexIndices(attrib.vertices.size(), INVALID_TRIANGLE_INDEX);

            // Loop over faces(polygon)
            size_t index_offset = 0;
            for (size_t f = 0; f < shapes[s].mesh.num_face_vertices.size(); f++) {
                int fv = shapes[s].mesh.num_face_vertices[f];
                assert(fv == 3); //Only triangles are supported!
                if (fv != 3) {
                    std::cerr << "Face " << f << "is not a triangle! It has " << fv << "vertices!" << std::endl;
                    return;
                }

                // Loop over vertices in the face.
                for (size_t v = 0; v < fv; v++) {

                    // access to vertex
                    tinyobj::index_t idx = shapes[s].mesh.indices[index_offset + v];
                    const size_t objVertexIndex = 3 * idx.vertex_index;
                    size_t newVertexIndex = remappedVertexIndices[objVertexIndex];

                    if (newVertexIndex == INVALID_TRIANGLE_INDEX)
                    {
                        
                        glm::vec3 newVertex = glm::vec3(attrib.vertices[objVertexIndex + 0], 
                                                        attrib.vertices[objVertexIndex + 1], 
                                                        attrib.vertices[objVertexIndex + 2]);

                        mesh.m_Vertices.push_back(newVertex);
                        newVertexIndex = mesh.m_Vertices.size() - 1;
                        remappedVertexIndices[objVertexIndex] = newVertexIndex;
                    }
                    mesh.m_TriangleIndices.push_back(newVertexIndex);

                    tinyobj::real_t nx = attrib.normals[3 * idx.normal_index + 0];
                    tinyobj::real_t ny = attrib.normals[3 * idx.normal_index + 1];
                    tinyobj::real_t nz = attrib.normals[3 * idx.normal_index + 2];
                    mesh.m_VertexNormals.push_back(glm::vec3(nx, ny, nz));

                    tinyobj::real_t tx = attrib.texcoords[2 * idx.texcoord_index + 0];
                    tinyobj::real_t ty = attrib.texcoords[2 * idx.texcoord_index + 1];
                    mesh.m_TextureCoordinates.push_back(glm::vec2(tx, ty));
                }
                index_offset += fv;

            }
            outMeshes.push_back(std::move(mesh));
        }
    }
    
} // namespace OBJLoader
} // namespace DynRay