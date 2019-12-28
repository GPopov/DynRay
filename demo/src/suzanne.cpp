#include "suzanne.hpp"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/quaternion.hpp"
#include "objloader/objloader.hpp"
namespace DynRay
{
    namespace Demo
    {
        DynRay::Engine::Frame DynRay::Demo::GenerateSuzanneScene(std::random_device& rd)
        {
            auto frame = DynRay::Engine::Frame{};
            std::string inputfile = "..\\..\\ExampleScenes\\suzanne.obj";
            OBJLoader::LoadOBJMeshes(inputfile, frame.m_Scene.m_Meshes);
            {
                frame.m_Camera.SetCameraMatrix(glm::lookAt(glm::vec3{ 7.f, -6.f, 5.f }, glm::vec3{ 5.69688f, -4.77166f, 4.10946f }, glm::vec3{ 0, 0, 1 }));
                frame.m_Camera.m_VerticalFOV = glm::radians(35.f);
            }
            {
                frame.m_Scene.m_Omnis.push_back(DynRay::Engine::OmniLight(glm::vec4(4.07625, 1.00545, 5.90386, 1.f), glm::vec4(1.f, 1.f, 1.f, 1.f), 50.f));
                frame.m_Scene.m_Omnis.push_back(DynRay::Engine::OmniLight(glm::vec4(0, -5, 0, 1.f), glm::vec4(1.f, 1.f, 1.f, 1.f), 5.f));
            }

            return frame;
        }
    }
}


