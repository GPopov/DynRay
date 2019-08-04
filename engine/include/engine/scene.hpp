#ifndef DYNRAY_SCENE_HPP
#define DYNRAY_SCENE_HPP
#include <vector>
#include <memory>
#include "object.hpp"
#include "light.hpp"
namespace DynRay
{
namespace Engine
{
    struct Scene
    {
        std::vector<std::unique_ptr<Object>> m_Objects;
        std::vector<Light> m_Lights;
    };
} // namespace Engine   
} // namespace DynRay

#endif //DYNRAY_SCENE_HPP