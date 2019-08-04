#include "SDL.h"
#include "SDL_image.h"
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


constexpr uint32_t WIDTH = 320;
constexpr uint32_t HEIGHT = 240;

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
        auto sphere = std::make_unique<DynRay::Engine::Sphere>();
        sphere->m_Center = glm::vec4(0.f, 0.f, -20.f, 1.f);
        sphere->m_Radius = 5.f;
        sphere->m_Color = glm::vec4(0.f, 1.f, 0.f, 1.f);
        scene.m_Objects.push_back(std::move(sphere));
    }
    {
        auto sphere = std::make_unique<DynRay::Engine::Sphere>();
        sphere->m_Center = glm::vec4(5.f, 7.f, -20.f, 1.f);
        sphere->m_Radius = 5.f;
        sphere->m_Color = glm::vec4(0.f, 0.f, 1.f, 1.f);
        scene.m_Objects.push_back(std::move(sphere));
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
                //camera.m_ToWorld[3] += offset;
                //std::cout << "CAM POS: (" << camera.m_ToWorld[3].x << ", " << camera.m_ToWorld[3].y << ", " << camera.m_ToWorld[3].z << ")" << std::endl;
                DynRay::Engine::Renderer::Render(scene, camera, WIDTH, HEIGHT, visualizer.GetPixelData());
            }
        }

        SDL_RenderClear(renderer.get());
        SDL_RenderCopy(renderer.get(), visualizer.GetTexture(), nullptr, nullptr);
        SDL_RenderPresent(renderer.get());
    }

    SDL_Quit();

    return 0;
}