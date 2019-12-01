#include "SDL.h"
#include "SDLWrappers.h"
#include "Visualizer.h"

#include <cstdint>
#include <random>
#include <iostream>
#include <chrono>
#include "engine/renderer.hpp"
#include "engine/frame.hpp"
#include "engine/renderoptions.hpp"
#include "demo/randomspheres.hpp"

constexpr uint32_t WIDTH = 640;
constexpr uint32_t HEIGHT = 480;
constexpr DynRay::Engine::RenderOptions RENDER_OPTIONS(WIDTH, HEIGHT);

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

	std::random_device rd;
	DynRay::Engine::Frame frame = DynRay::Demo::GenerateRandomSpheresFrame(rd);
	
	for (uint32_t i = 0; i < 1; ++i)
	{
		auto startTime = std::chrono::system_clock::now();
		DynRay::Engine::Renderer::Render(frame, RENDER_OPTIONS, visualizer.GetPixelData());
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
            
			if (e.type == SDL_MOUSEBUTTONUP)
			{
				if (e.button.button == 1)
				{
                    DynRay::Engine::Renderer::RenderSinglePixel(frame, RENDER_OPTIONS, visualizer.GetPixelData(), e.button.x, e.button.y);
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