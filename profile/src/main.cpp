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
       //sphere.m_Material = DynRay::Engine::DiffuseMaterial(glm::vec4(disColor(gen), disColor(gen), disColor(gen), 1.f));
       scene.AddObject(std::move(sphere));
       ++generatedSpheres;
   }
   {
       auto plane = DynRay::Engine::Plane(glm::normalize(glm::vec4(0.f, 1.f, 0.f, 0.f)), glm::vec4(0.f, -3.f, -20.f, 1.f));
       //plane.m_Material = DynRay::Engine::DiffuseMaterial(glm::vec4(0.f, 0.f, 1.f, 1.f));
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
}

static void BM_Trace(benchmark::State &state)
{
   auto scene = PrepareScene();
   auto camera = PrepareCamera();
   constexpr uint32_t WIDTH = 1024;
   constexpr uint32_t HEIGHT = 768;
   auto buffer = std::make_unique<std::array<uint32_t, WIDTH * HEIGHT>>();

   std::random_device rd;
   std::mt19937 gen(rd());
   std::uniform_int_distribution<uint32_t> disX(0, WIDTH - 1);
   std::uniform_int_distribution<uint32_t> disY(0, HEIGHT - 1);
   

   // Perform setup here
   for (auto _ : state)
   {
       glm::vec4 rayDirection = camera.GeneratePrimaryRayDirection(WIDTH, HEIGHT, disX(gen), disY(gen));
       scene.Trace(camera.GetPosition(), rayDirection, 0.f);
   }
}
 //Register the function as a benchmark
BENCHMARK(BM_Trace);

BENCHMARK_MAIN();