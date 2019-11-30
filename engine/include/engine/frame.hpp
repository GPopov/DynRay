#pragma once
#include "scene.hpp"
#include "camera.hpp"
namespace DynRay
{
namespace Engine
{
	struct Frame
	{
		Camera m_Camera;
		Scene m_Scene;
	};
};
}