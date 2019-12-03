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
#include "demo/demos.hpp"

#include <gflags/gflags.h>
DEFINE_uint32(width, 640, "Horizontal resolution of the result image, in pixels");
DEFINE_uint32(height, 480, "Vertical resolution of the result image, in pixels");
DEFINE_string(demo, "", "Run one of the predefined demos");
static bool ValidateDemo(const char* flagname, const std::string& value)
{
	return DynRay::Demo::ValidateDemoName(value);
}
DEFINE_validator(demo, &ValidateDemo);

int main(int argc, char *argv[])
{
	gflags::ParseCommandLineFlags(&argc, &argv, true);
	DynRay::Engine::RenderOptions RENDER_OPTIONS(FLAGS_width, FLAGS_height);
    SDL_Init(SDL_INIT_VIDEO);
    DynRay::Visualizer::SDL_WindowPtr window(SDL_CreateWindow(
        "DynRay Visualizer",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
		FLAGS_width,
		FLAGS_height,
        SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL));

    DynRay::Visualizer::SDL_RendererPtr renderer(SDL_CreateRenderer(window.get(), -1, SDL_RENDERER_ACCELERATED));
    SDL_SetRenderDrawColor(renderer.get(), 0, 0, 0, SDL_ALPHA_OPAQUE);
    auto visualizer = DynRay::Visualizer::Visualizer(renderer.get(), FLAGS_width, FLAGS_height);

	std::random_device rd;
	DynRay::Engine::Frame frame = DynRay::Demo::GetDemoFrame(FLAGS_demo, rd);
	
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