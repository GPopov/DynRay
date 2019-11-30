#include "randomspheres.hpp"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
namespace DynRay
{
	namespace Demo
	{

		Engine::Frame GenerateRandomSpheresFrame(std::random_device& rd)
		{
			Engine::Frame frame;
			frame.m_Scene.m_Omnis.push_back(DynRay::Engine::OmniLight(glm::vec4(0, 10.2f, -19, 1.f), glm::vec4(1.f, 1.f, 1.f, 1.f), 15.f));
			frame.m_Scene.m_Omnis.push_back(DynRay::Engine::OmniLight(glm::vec4(-30.f, 10.f, 2.f, 1.f), glm::vec4(1.f, 1.f, 1.f, 1.f), 22.2f));
			frame.m_Scene.m_Omnis.push_back(DynRay::Engine::OmniLight(glm::vec4(1.5f, -2.6f, -20.f, 1.f), glm::vec4(1.f, 1.f, 1.f, 1.f), 4.2f));

			std::mt19937 gen(rd());
			std::uniform_real_distribution<float> disPos(-10.f, 10.f);
			std::uniform_real_distribution<float> disDistance(-100.f, -1.f);
			std::uniform_real_distribution<float> disSize(0.f, 2.f);
			std::uniform_real_distribution<float> disColor(0.f, 1.f);
			std::uniform_real_distribution<float> diceRoll(0.f, 100.f);

			int generatedSpheres = 0;
			while (generatedSpheres < 100)
			{
				auto sphere = new DynRay::Engine::Sphere();
				if (diceRoll(gen) < 10)
				{
					sphere->m_Center = glm::vec4(disPos(gen), disPos(gen), disDistance(gen), 1.f);
					sphere->m_Radius = disSize(gen);
					sphere->m_Material = std::make_unique<DynRay::Engine::DiffuseMaterial>(DynRay::Engine::DiffuseMaterial(glm::vec4(disColor(gen), disColor(gen), disColor(gen), 1.f)));
					frame.m_Scene.m_Objects.push_back(std::move(std::unique_ptr<DynRay::Engine::Sphere>(sphere)));
					++generatedSpheres;
				}
			}
			{
				auto plane = std::make_unique<DynRay::Engine::Plane>(glm::normalize(glm::vec4(0.f, 1.f, 0.f, 0.f)), glm::vec4(0.f, -3.f, -20.f, 1.f));
				plane->m_Material = std::make_unique<DynRay::Engine::DiffuseMaterial>(glm::vec4(0.f, 0.f, 1.f, 1.f));
				frame.m_Scene.m_Objects.push_back(std::move(plane));
			}
			frame.m_Camera.SetCameraMatrix(glm::lookAt(glm::vec3{ 0.f, 0.f, 0.f }, glm::vec3{ 0.f, 0.f, -1.f }, glm::vec3{ 0.f, 1.f, 0.f }));
			frame.m_Camera.m_VerticalFOV = glm::radians(45.f);
			return frame;
		}

	}
}
