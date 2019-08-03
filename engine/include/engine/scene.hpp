#ifndef DYNRAY_SCENE_HPP
#define DYNRAY_SCENE_HPP
#include <vector>
#include <memory>
#include "object.hpp"
namespace DynRay
{
namespace Engine
{


struct Scene
{
    std::vector<std::unique_ptr<Object>> m_Objects;
};
} // namespace Engine   
} // namespace DynRay

#endif //DYNRAY_SCENE_HPP