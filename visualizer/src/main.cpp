#include "SDL.h"
#include "SDLWrappers.h"
#include "Visualizer.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include <cstdint>
#include <memory>
#include <random>
#include <iostream>
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
		scene.m_Omnis.push_back(DynRay::Engine::OmniLight(glm::vec4(0, 10.2f, -19, 1.f), glm::vec4(1.f, 1.f, 1.f, 1.f), 3.f));
		scene.m_Omnis.push_back(DynRay::Engine::OmniLight(glm::vec4(-30.f, 10.f, 2.f, 1.f), glm::vec4(1.f, 1.f, 1.f, 1.f), 4.2f));
		scene.m_Omnis.push_back(DynRay::Engine::OmniLight(glm::vec4(1.5f, -2.6f, -20.f, 1.f), glm::vec4(1.f, 1.f, 1.f, 1.f), 4.2f));
	}
	{
		auto sphere = std::make_unique<DynRay::Engine::Sphere>();
		sphere->m_Center = glm::vec4(5.f, 7.f, -20.f, 1.f);
		sphere->m_Radius = 5.f;
		sphere->m_Material = std::make_unique<DynRay::Engine::DiffuseMaterial>(glm::vec4(0.f, 0.f, 1.f, 1.f));
		sphere->m_Name = "S1";
		scene.m_Objects.push_back(std::move(sphere));
	}
    {
        auto sphere = std::make_unique<DynRay::Engine::Sphere>();
        sphere->m_Center = glm::vec4(0.f, 0.f, -20.f, 1.f);
        sphere->m_Radius = 1.f;
		sphere->m_Material = std::make_unique<DynRay::Engine::DiffuseMaterial>(glm::vec4(0.f, 1.f, 0.f, 1.f));
		sphere->m_Name = "S2";
        scene.m_Objects.push_back(std::move(sphere));
    }
	{
		auto plane = std::make_unique<DynRay::Engine::Plane>(glm::normalize(glm::vec4(0.f, 1.f, 0.f, 0.f)), glm::vec4(0.f, -3.f, -20.f, 1.f));
		plane->m_Material = std::make_unique<DynRay::Engine::DiffuseMaterial>(glm::vec4(0.f, 0.f, 1.f, 1.f));
		scene.m_Objects.push_back(std::move(plane));
	}
    DynRay::Engine::Camera camera;
    camera.SetCameraMatrix(glm::lookAt(glm::vec3{0.f, 0.f, 0.f}, glm::vec3{0.f, 0.f, -1.f}, glm::vec3{0.f, 1.f, 0.f}));
    camera.m_VerticalFOV = glm::radians(45.f);

    DynRay::Engine::Renderer::Render(scene, camera, WIDTH, HEIGHT, visualizer.GetPixelData());


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
					DynRay::Engine::Renderer::RenderSinglePixel(scene, camera, WIDTH, HEIGHT, visualizer.GetPixelData(), e.button.x, e.button.y);
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