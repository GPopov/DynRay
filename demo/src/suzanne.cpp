#include "suzanne.hpp"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/quaternion.hpp"
#include "tiny_obj_loader.h"
#include <iostream> //DONOTSUBMIT
#include <filesystem>
namespace DynRay
{
    namespace Demo
    {
        DynRay::Engine::Frame DynRay::Demo::GenerateSuzanneScene(std::random_device& rd)
        {
            auto frame = DynRay::Engine::Frame{};
            std::string inputfile = "..\\..\\ExampleScenes\\Suzanne.obj";
            tinyobj::attrib_t attrib;
            std::vector<tinyobj::shape_t> shapes;
            std::vector<tinyobj::material_t> materials;

            std::string warn;
            std::string err;
            std::cout << "cwd: " << std::filesystem::current_path();
            bool ret = tinyobj::LoadObj(&attrib, &shapes, &materials, &warn, &err, inputfile.c_str());

            if (!warn.empty()) {
                std::cout << warn << std::endl;
            }

            if (!err.empty()) {
                std::cerr << err << std::endl;
            }

            if (!ret) {
                exit(1);
            }

            // Loop over shapes
            for (size_t s = 0; s < shapes.size(); s++) {
                // Loop over faces(polygon)
                size_t index_offset = 0;
                for (size_t f = 0; f < shapes[s].mesh.num_face_vertices.size(); f++) {
                    int fv = shapes[s].mesh.num_face_vertices[f];

                    // Loop over vertices in the face.
                    for (size_t v = 0; v < fv; v++) {
                        // access to vertex
                        tinyobj::index_t idx = shapes[s].mesh.indices[index_offset + v];
                        tinyobj::real_t vx = attrib.vertices[3 * idx.vertex_index + 0];
                        tinyobj::real_t vy = attrib.vertices[3 * idx.vertex_index + 1];
                        tinyobj::real_t vz = attrib.vertices[3 * idx.vertex_index + 2];
                        tinyobj::real_t nx = attrib.normals[3 * idx.normal_index + 0];
                        tinyobj::real_t ny = attrib.normals[3 * idx.normal_index + 1];
                        tinyobj::real_t nz = attrib.normals[3 * idx.normal_index + 2];
                        tinyobj::real_t tx = attrib.texcoords[2 * idx.texcoord_index + 0];
                        tinyobj::real_t ty = attrib.texcoords[2 * idx.texcoord_index + 1];
                        // Optional: vertex colors
                        // tinyobj::real_t red = attrib.colors[3*idx.vertex_index+0];
                        // tinyobj::real_t green = attrib.colors[3*idx.vertex_index+1];
                        // tinyobj::real_t blue = attrib.colors[3*idx.vertex_index+2];
                    }
                    index_offset += fv;

                    // per-face material
                    shapes[s].mesh.material_ids[f];
                }
            }
            {
                glm::quat cameraRotation{ 0.780f, 0.484f,0.209f, 0.337f };
                glm::mat4 rotMatrix = glm::toMat4(cameraRotation);
                glm::mat4 tranlationMatrix = glm::translate(glm::mat4(1.f), glm::vec3{ 7.f, -6.f, 5.f });
                auto cameraMatrix = tranlationMatrix * rotMatrix;
                frame.m_Camera.SetCameraMatrix(cameraMatrix);
                frame.m_Camera.m_VerticalFOV = glm::radians(45.f);
            }
            {
                frame.m_Scene.m_Omnis.push_back(DynRay::Engine::OmniLight(glm::vec4(4.f, 1.f, 5.9f, 1.f), glm::vec4(1.f, 1.f, 1.f, 1.f), 15.f));
            }
            {
                auto theSphere = Engine::Sphere();
                theSphere.m_Center = glm::vec4(0.f, 2.5f, 1.2f, 1.f);
                theSphere.m_Radius = 1.5f;
                theSphere.m_Material = DynRay::Engine::DiffuseMaterial(glm::vec4(0.5f, 0.f, 0.f, 1.f));
                frame.m_Scene.AddObject(std::move(theSphere));
            }
            return frame;
        }
    }
}


