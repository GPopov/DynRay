#include "demos.hpp"
#include "engine/frame.hpp"
#include "randomspheres.hpp"
#include "suzanne.hpp"
#include <map>
namespace DynRay
{
namespace Demo
{
	using DemoGenerator = Engine::Frame(*)(std::random_device & rd);
	using DemoRepository = std::map<std::string, DemoGenerator>;
	static DemoRepository s_Demos = 
	{
		{"RandomSpheres", &Demo::GenerateRandomSpheresFrame},
		{"SingleSphere", &Demo::GenerateSingleSphereFrame},
        {"Suzanne", &Demo::GenerateSuzanneScene},
	};
	DynRay::Engine::Frame GetDemoFrame(const std::string& demoName, std::random_device& rd)
	{
		auto demo = s_Demos.find(demoName);
		if (demo != s_Demos.end())
		{
			auto [key, generator] = *demo;
			return generator(rd);
		}

		return Engine::Frame{};
	}

	bool ValidateDemoName(const std::string& demoName)
	{
		return demoName == "" || s_Demos.count(demoName) > 0;
	}

}
}