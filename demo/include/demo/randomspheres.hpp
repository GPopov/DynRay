#pragma once
#include "engine/frame.hpp"
#include <random>
namespace DynRay
{
	namespace Demo
	{
		Engine::Frame GenerateRandomSpheresFrame(std::random_device& rd);
	};
}