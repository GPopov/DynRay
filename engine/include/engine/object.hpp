#ifndef DYNRAY_OBJECT_HPP
#define DYNRAY_OBJECT_HPP
#include "glm/glm.hpp"
namespace DynRay
{
namespace Engine
{
    struct Object
    {
        virtual ~Object() = default;
        virtual void GetSurfaceDataAt(const glm::vec4& point, glm::vec4& outNormal, glm::vec2& outTexCoords) = 0;
        virtual glm::vec4 GetColorAt(const glm::vec2& texCoords, const glm::vec4& hitNormal) const = 0;
        virtual float Intersect(const glm::vec4& rayOrigin, const glm::vec4& rayDirection) const = 0;
    };

    struct Sphere : public Object
    {
        glm::vec4 GetNormal(const glm::vec4& point) const;
        void GetSurfaceDataAt(const glm::vec4& point, glm::vec4& outNormal, glm::vec2& outTexCoords) override;

        glm::vec4 GetColorAt(const glm::vec2& texCoords, const glm::vec4& hitNormal) const override;
        float Intersect(const glm::vec4& rayOrigin, const glm::vec4& rayDirection) const override;

        glm::vec4 m_Color;
        glm::vec4 m_Center;
        float m_Radius;
    };

	struct Plane : public Object
	{
		void GetSurfaceDataAt(const glm::vec4& point, glm::vec4& outNormal, glm::vec2& outTexCoords) override;

		glm::vec4 GetColorAt(const glm::vec2& texCoords, const glm::vec4& hitNormal) const override;
		float Intersect(const glm::vec4& rayOrigin, const glm::vec4& rayDirection) const override;

		glm::vec4 m_Normal;
		glm::vec4 m_Pos;
		glm::vec4 m_Color;
	};

} // namespace Engine
} // namespace DynRay
#endif //DYNRAY_OBJECT_HPP