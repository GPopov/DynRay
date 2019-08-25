#ifndef DYNRAY_OBJECT_HPP
#define DYNRAY_OBJECT_HPP
#include "glm/glm.hpp"
#include <memory>
namespace DynRay
{
namespace Engine
{
	struct Material;
    struct Object
    {
		Object();
		virtual ~Object();
		Object(Object&&);
		Object& operator=(Object&&);
        
        virtual void GetSurfaceDataAt(const glm::vec4& point, glm::vec4& outNormal, glm::vec2& outTexCoords) = 0;
        glm::vec4 GetColorAt(const glm::vec2& texCoords, const glm::vec4& hitNormal) const;
        virtual float Intersect(const glm::vec4& rayOrigin, const glm::vec4& rayDirection) const = 0;

		glm::vec4 m_Color;
		std::unique_ptr<Material> m_Material;

    };

    struct Sphere : public Object
    {
        glm::vec4 GetNormal(const glm::vec4& point) const;
        void GetSurfaceDataAt(const glm::vec4& point, glm::vec4& outNormal, glm::vec2& outTexCoords) override;

        float Intersect(const glm::vec4& rayOrigin, const glm::vec4& rayDirection) const override;
        
        glm::vec4 m_Center;
        float m_Radius;
    };

	struct Plane : public Object
	{
		Plane(const glm::vec4& normal, const glm::vec4& pos);
		void GetSurfaceDataAt(const glm::vec4& point, glm::vec4& outNormal, glm::vec2& outTexCoords) override;

		float Intersect(const glm::vec4& rayOrigin, const glm::vec4& rayDirection) const override;

		glm::vec4 m_u;
		glm::vec4 m_v;
		glm::vec4 m_Normal;
		glm::vec4 m_Pos;
	};

} // namespace Engine
} // namespace DynRay
#endif //DYNRAY_OBJECT_HPP