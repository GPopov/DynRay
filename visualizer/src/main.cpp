#include "SDL.h"
#include "SDLWrappers.h"
#include "Visualizer.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include <cstdint>
#include <memory>
#include <random>
#include <iostream>
#include <chrono>
#include "engine/scene.hpp"
#include "engine/renderer.hpp"
#include "engine/camera.hpp"
#include "engine/material.hpp"


constexpr uint32_t WIDTH = 640;
constexpr uint32_t HEIGHT = 480;

void RenderScene()
{

}

int main(int argc, char *argv[])
{
    SDL_Init(SDL_INIT_VIDEO);
    DynRay::Visualizer::SDL_WindowPtr window(SDL_CreateWindow(
        "DynRay Visualizer",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        WIDTH,
        HEIGHT,
        SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL));

    DynRay::Visualizer::SDL_RendererPtr renderer(SDL_CreateRenderer(window.get(), -1, SDL_RENDERER_ACCELERATED));
    SDL_SetRenderDrawColor(renderer.get(), 0, 0, 0, SDL_ALPHA_OPAQUE);
    auto visualizer = DynRay::Visualizer::Visualizer(renderer.get(), WIDTH, HEIGHT);

    DynRay::Engine::Scene scene;
	{
		scene.m_Omnis.push_back(DynRay::Engine::OmniLight(glm::vec4(0, 10.2f, -19, 1.f), glm::vec4(1.f, 1.f, 1.f, 1.f), 15.f));
		scene.m_Omnis.push_back(DynRay::Engine::OmniLight(glm::vec4(-30.f, 10.f, 2.f, 1.f), glm::vec4(1.f, 1.f, 1.f, 1.f), 22.2f));
		scene.m_Omnis.push_back(DynRay::Engine::OmniLight(glm::vec4(1.5f, -2.6f, -20.f, 1.f), glm::vec4(1.f, 1.f, 1.f, 1.f), 4.2f));
	}

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> disPos(-10.f, 10.f);
    std::uniform_real_distribution<float> disDistance(-100.f, -1.f);
    std::uniform_real_distribution<float> disSize(0.f, 2.f);
    std::uniform_real_distribution<float> disColor(0.f, 1.f);
    std::uniform_real_distribution<float> diceRoll(0.f, 100.f);
    int generatedSpheres = 0;
    while(generatedSpheres < 100)
    {
        auto sphere = new DynRay::Engine::Sphere();
        if (diceRoll(gen) < 10)
        {
            sphere->m_Center = glm::vec4(disPos(gen), disPos(gen), disDistance(gen), 1.f);
            sphere->m_Radius = disSize(gen);
            sphere->m_Material = std::make_unique<DynRay::Engine::DiffuseMaterial>(DynRay::Engine::DiffuseMaterial(glm::vec4(disColor(gen), disColor(gen), disColor(gen), 1.f)));
            scene.m_Objects.push_back(std::move(std::unique_ptr<DynRay::Engine::Sphere>(sphere)));
            ++generatedSpheres;
        }
    }
    {
		auto plane = std::make_unique<DynRay::Engine::Plane>(glm::normalize(glm::vec4(0.f, 1.f, 0.f, 0.f)), glm::vec4(0.f, -3.f, -20.f, 1.f));
		plane->m_Material = std::make_unique<DynRay::Engine::DiffuseMaterial>(glm::vec4(0.f, 0.f, 1.f, 1.f));
		scene.m_Objects.push_back(std::move(plane));
	}
    DynRay::Engine::Camera camera;
    camera.SetCameraMatrix(glm::lookAt(glm::vec3{0.f, 0.f, 0.f}, glm::vec3{0.f, 0.f, -1.f}, glm::vec3{0.f, 1.f, 0.f}));
    camera.m_VerticalFOV = glm::radians(45.f);

	for (uint32_t i = 0; i < 1; ++i)
	{
		auto startTime = std::chrono::system_clock::now();
		DynRay::Engine::Renderer::Render(scene, camera, WIDTH, HEIGHT, visualizer.GetPixelData());
		auto endTime = std::chrono::system_clock::now();
		auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime);

		std::cout << "Render time: " << elapsed.count() << std::endl;
	}


    while (1)
    {
        visualizer.UpdateTexture();

        SDL_Event e;
        if (SDL_PollEvent(&e))
        {
            if (e.type == SDL_QUIT)
            {
                break;
            }
            if (e.type == SDL_KEYDOWN)
            {
                glm::vec4 offset(0.f, 0.f, 0.f, 0.f);
                switch (e.key.keysym.sym)
                {
                case SDLK_LEFT:
                    offset.x -= .01f;
                    break;
                case SDLK_RIGHT:
                    offset.x += .01f;
                    break;
                case SDLK_UP:
                    offset.z += .01f;
                    break;
                case SDLK_DOWN:
                    offset.z -= .01f;
                    break;
                default:
                    break;
                }

				glm::vec3 cameraPos = glm::vec3(camera.m_ToWorldMatrix[3] + offset);
				camera.SetCameraMatrix(glm::lookAt(cameraPos, glm::vec3{ 0.f, 0.f, -1.f }, glm::vec3(0, 1, 0)));

                //camera.m_ToWorld[3] += offset;
                //std::cout << "CAM POS: (" << camera.m_ToWorld[3].x << ", " << camera.m_ToWorld[3].y << ", " << camera.m_ToWorld[3].z << ")" << std::endl;
                DynRay::Engine::Renderer::Render(scene, camera, WIDTH, HEIGHT, visualizer.GetPixelData());
            }
			if (e.type == SDL_MOUSEBUTTONUP)
			{
				if (e.button.button == 1)
				{
                    auto startTime = std::chrono::system_clock::now();
                    DynRay::Engine::Renderer::RenderSinglePixel(scene, camera, WIDTH, HEIGHT, visualizer.GetPixelData(), e.button.x, e.button.y);
                    auto endTime = std::chrono::system_clock::now();
                    auto elapsed = std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime);
                    std::cout << "Render single pixel time:" << elapsed.count() << "us" << std::endl;
                }
			}
        }

        SDL_RenderClear(renderer.get());
        SDL_RenderCopy(renderer.get(), visualizer.GetTexture(), nullptr, nullptr);
        SDL_RenderPresent(renderer.get());
    }

    SDL_Quit();

    return 0;
}