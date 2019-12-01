#include <benchmark/benchmark.h>
#include <random>
#include <array>
#include <iostream>
#include "engine/scene.hpp"
#include "engine/renderer.hpp"
#include "engine/camera.hpp"
#include "engine/frame.hpp"
#include "engine/material.hpp"
#include "engine/renderoptions.hpp"
#include "demo/randomspheres.hpp"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
namespace
{

class Fixture : public benchmark::Fixture
{
public:
    static constexpr uint32_t WIDTH = 640;
    static constexpr uint32_t HEIGHT = 480;
	Fixture()
		: m_RenderOptions(WIDTH, HEIGHT)
	{

	}
	DynRay::Engine::Frame m_Frame;
	DynRay::Engine::RenderOptions m_RenderOptions;
    std::array < uint32_t, WIDTH * HEIGHT> m_Buffer;
    std::mt19937 m_rng;
    std::uniform_int_distribution<uint32_t> m_DisX{ 0, WIDTH - 1 };
    std::uniform_int_distribution<uint32_t> m_DisY{ 0, HEIGHT - 1 };

    void SetUp(const ::benchmark::State& state) override {
		std::random_device rd;
		m_rng.seed(rd());
		m_Frame = DynRay::Demo::GenerateRandomSpheresFrame(rd);
    }
};
}

BENCHMARK_DEFINE_F(Fixture, RenderWholeScene_NoHeapAlloc)(benchmark::State& state)
{
    for (auto _ : state)
    {
        DynRay::Engine::Renderer::Render(m_Frame, m_RenderOptions, m_Buffer.data());
    }
}

BENCHMARK_DEFINE_F(Fixture, TraceSingleRay_NoHeapAlloc)(benchmark::State& state)
{
    for (auto _ : state)
    {
        glm::vec4 rayDir = m_Frame.m_Camera.GeneratePrimaryRayDirection(m_RenderOptions, m_DisX(m_rng), m_DisY(m_rng));
		m_Frame.m_Scene.Trace(m_Frame.m_Camera.GetPosition(), rayDir, 0.f);
    }
}

BENCHMARK_DEFINE_F(Fixture, RenderSinglePixel_NoHeapAlloc)(benchmark::State& state)
{
    for (auto _ : state)
    {
        DynRay::Engine::Renderer::RenderSinglePixel(m_Frame, m_RenderOptions, m_Buffer.data(), m_DisX(m_rng), m_DisY(m_rng));
    }
}

BENCHMARK_REGISTER_F(Fixture, RenderWholeScene_NoHeapAlloc)->Unit(benchmark::kMillisecond);
BENCHMARK_REGISTER_F(Fixture, TraceSingleRay_NoHeapAlloc);
BENCHMARK_REGISTER_F(Fixture, RenderSinglePixel_NoHeapAlloc);


BENCHMARK_MAIN();