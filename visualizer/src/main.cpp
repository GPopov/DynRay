#include "SDL.h"
#include "SDL_image.h"
#include "SDLWrappers.h"
#include "Visualizer.h"
#include <cstdint>
#include <random>
constexpr uint32_t WIDTH = 320;
constexpr uint32_t HEIGHT = 240;
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

    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist(0, WIDTH * HEIGHT - 1);
    std::uniform_int_distribution<std::mt19937::result_type> colorDist(0, 255);

    while (1)
    {
        visualizer.GetPixelData()[dist(rng)] = (colorDist(rng) << 16) | (colorDist(rng) << 8) | colorDist(rng);
        visualizer.UpdateTexture();

        SDL_Event e;
        if (SDL_PollEvent(&e))
        {
            if (e.type == SDL_QUIT)
            {
                break;
            }
        }

        SDL_RenderClear(renderer.get());
        SDL_RenderCopy(renderer.get(), visualizer.GetTexture(), nullptr, nullptr);
        SDL_RenderPresent(renderer.get());
    }

    SDL_Quit();

    return 0;
}