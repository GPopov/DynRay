#pragma once
#include "engine/frame.hpp"
#include <random>
namespace DynRay
{
    namespace Demo
    {
        Engine::Frame GenerateSuzanneScene(std::random_device& rd);
    };
}