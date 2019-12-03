#pragma once
#include <string>
#include <random>
namespace DynRay
{
namespace Engine
{
	struct Frame;
}

namespace Demo
{

	Engine::Frame GetDemoFrame(const std::string& demoName, std::random_device& rd);
	bool ValidateDemoName(const std::string& demoName);
}
}