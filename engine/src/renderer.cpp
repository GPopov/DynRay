#include "renderer.hpp"
#include "scene.hpp"
#include "object.hpp"
#include "camera.hpp"
#include <limits>
namespace DynRay
{
namespace Engine
{
    namespace
    {
        uint32_t QuantizeColor(const glm::vec4& color)
        {
            return uint32_t(color.a * 255) << 24 |
                   uint32_t(color.r * 255) << 16 |
                   uint32_t(color.g * 255) << 8 |
                   uint32_t(color.b * 255);
        }
    }
    void Renderer::Render(const Scene &scene, const Camera& camera, uint32_t width, uint32_t height, uint32_t *outBuffer)
    {
        const glm::vec4& rayOrigin = camera.GetPosition();
        for (uint32_t y = 0; y < height; ++y)
        {
            for (uint32_t x = 0; x < width; ++x)
            {
                glm::vec4 rayDirection = camera.GeneratePrimaryRayDirection(width, height, x, y);

                uint32_t pixelColor = 0;
                float minDistance = std::numeric_limits<float>::infinity();
                Object* closestObject = nullptr;
                for (const auto& object : scene.m_Objects)
                {
                    glm::vec4 intersectionPoint;
                    float distance = object->Intersect(rayOrigin, rayDirection);
                    if (distance > 0.f && distance < minDistance)
                    {
                        minDistance = distance;
                        closestObject = object.get();
                    }
                }

                if (closestObject)
                {
                    glm::vec4 intersectionPoint = rayOrigin + rayDirection * minDistance;

                    glm::vec4 normal;
                    glm::vec2 texCoords;
                    closestObject->GetSurfaceDataAt(intersectionPoint, normal, texCoords);
                    glm::vec4 color = closestObject->GetColorAt(texCoords) * glm::dot(normal, rayDirection) * 0.5f;

                    pixelColor = QuantizeColor(color);
                }

                outBuffer[y * width + x] = pixelColor;
            }
        }

    }
}
}