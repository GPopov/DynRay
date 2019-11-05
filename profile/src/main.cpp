#include <benchmark/benchmark.h>
#include <random>
#include <array>
#include <iostream>
#include "engine/scene.hpp"
#include "engine/renderer.hpp"
#include "engine/camera.hpp"
#include "engine/material.hpp"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
namespace
{
DynRay::Engine::Scene PrepareScene()
{
   DynRay::Engine::Scene scene;
   {
      scene.m_Omnis.push_back(DynRay::Engine::OmniLight(glm::vec4(0, 10.2f, -19, 1.f), glm::vec4(1.f, 1.f, 1.f, 1.f), 15.f));
      scene.m_Omnis.push_back(DynRay::Engine::OmniLight(glm::vec4(-30.f, 10.f, 2.f, 1.f), glm::vec4(1.f, 1.f, 1.f, 1.f), 22.2f));
      scene.m_Omnis.push_back(DynRay::Engine::OmniLight(glm::vec4(1.5f, -2.6f, -20.f, 1.f), glm::vec4(1.f, 1.f, 1.f, 1.f), 4.2f));
   }

   std::random_device rd;
   std::mt19937 gen(rd());
   std::uniform_real_distribution<float> disPos(-10.f, 10.f);
   std::uniform_real_distribution<float> disDistance(-100.f, -1.f);
   std::uniform_real_distribution<float> disSize(0.f, 2.f);
   std::uniform_real_distribution<float> disColor(0.f, 1.f);
   std::uniform_real_distribution<float> diceRoll(0.f, 100.f);
   int generatedSpheres = 0;
   while (generatedSpheres < 100)
   {
       auto sphere = DynRay::Engine::Sphere();
       sphere.m_Center = glm::vec4(disPos(gen), disPos(gen), disDistance(gen), 1.f);
       sphere.m_Radius = disSize(gen);
       sphere.m_Material = DynRay::Engine::DiffuseMaterial(glm::vec4(disColor(gen), disColor(gen), disColor(gen), 1.f));
       scene.AddObject(std::move(sphere));
       ++generatedSpheres;
   }
   {
       auto plane = DynRay::Engine::Plane(glm::normalize(glm::vec4(0.f, 1.f, 0.f, 0.f)), glm::vec4(0.f, -3.f, -20.f, 1.f));
       plane.m_Material = DynRay::Engine::DiffuseMaterial(glm::vec4(0.f, 0.f, 1.f, 1.f));
       scene.AddObject(std::move(plane));
   }

   return scene;
}
DynRay::Engine::Camera PrepareCamera()
{
   DynRay::Engine::Camera camera;
   camera.SetCameraMatrix(glm::lookAt(glm::vec3{0.f, 0.f, 0.f}, glm::vec3{0.f, 0.f, -1.f}, glm::vec3{0.f, 1.f, 0.f}));
   camera.m_VerticalFOV = glm::radians(45.f);
   return camera;
}

class Fixture : public benchmark::Fixture
{
public:
    static constexpr uint32_t WIDTH = 1024;
    static constexpr uint32_t HEIGHT = 768;
    DynRay::Engine::Scene m_Scene;
    DynRay::Engine::Camera m_Camera;
    std::array < uint32_t, WIDTH * HEIGHT> m_Buffer;
    std::mt19937 m_rng;
    std::uniform_int_distribution<uint32_t> m_DisX{ 0, WIDTH - 1 };
    std::uniform_int_distribution<uint32_t> m_DisY{ 0, HEIGHT - 1 };

    void SetUp(const ::benchmark::State& state) override {
        m_Scene = PrepareScene();
        m_Camera = PrepareCamera();
        std::random_device rd;
        m_rng.seed(rd());
    }
};
}

BENCHMARK_DEFINE_F(Fixture, RenderWholeScene_NoHeapAlloc)(benchmark::State& state)
{
    for (auto _ : state)
    {
        DynRay::Engine::Renderer::Render(m_Scene, m_Camera, WIDTH, HEIGHT, m_Buffer.data());
    }
}

BENCHMARK_DEFINE_F(Fixture, TraceSingleRay_NoHeapAlloc)(benchmark::State& state)
{
    for (auto _ : state)
    {
        glm::vec4 rayDir = m_Camera.GeneratePrimaryRayDirection(WIDTH, HEIGHT, m_DisX(m_rng), m_DisY(m_rng));
        m_Scene.Trace(m_Camera.GetPosition(), rayDir, 0.f);
    }
}

BENCHMARK_DEFINE_F(Fixture, RenderSinglePixel_NoHeapAlloc)(benchmark::State& state)
{
    for (auto _ : state)
    {
        DynRay::Engine::Renderer::RenderSinglePixel(m_Scene, m_Camera, WIDTH, HEIGHT, m_Buffer.data(), m_DisX(m_rng), m_DisY(m_rng));
    }
}

BENCHMARK_REGISTER_F(Fixture, RenderWholeScene_NoHeapAlloc)->Unit(benchmark::kMillisecond);
BENCHMARK_REGISTER_F(Fixture, TraceSingleRay_NoHeapAlloc);
BENCHMARK_REGISTER_F(Fixture, RenderSinglePixel_NoHeapAlloc);


BENCHMARK_MAIN();