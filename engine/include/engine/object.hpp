#ifndef DYNRAY_OBJECT_HPP
#define DYNRAY_OBJECT_HPP
#include "glm/glm.hpp"
#include <memory>
#include <string>
namespace DynRay
{
namespace Engine
{
	struct Material;
	struct Scene;
    struct Object
    {
		Object();
		virtual ~Object();
		Object(Object&&);
		Object& operator=(Object&&);
        
        virtual void GetSurfaceDataAt(const glm::vec4& point, glm::vec4& outNormal, glm::vec2& outTexCoords) const = 0;
        glm::vec4 GetColorAt(const glm::vec4& point, const Scene& scene) const;
        virtual float Intersect(const glm::vec4& rayOrigin, const glm::vec4& rayDirection) const = 0;
		std::string m_Name;
		std::unique_ptr<Material> m_Material;

    };

    struct Sphere : public Object
    {
        glm::vec4 GetNormal(const glm::vec4& point) const;
        void GetSurfaceDataAt(const glm::vec4& point, glm::vec4& outNormal, glm::vec2& outTexCoords) const override;

        float Intersect(const glm::vec4& rayOrigin, const glm::vec4& rayDirection) const override;
        
        glm::vec4 m_Center;
        float m_Radius;
    };

	struct Plane : public Object
	{
		Plane(const glm::vec4& normal, const glm::vec4& pos);
		void GetSurfaceDataAt(const glm::vec4& point, glm::vec4& outNormal, glm::vec2& outTexCoords) const override;

		float Intersect(const glm::vec4& rayOrigin, const glm::vec4& rayDirection) const override;

		glm::vec4 m_u;
		glm::vec4 m_v;
		glm::vec4 m_Normal;
		glm::vec4 m_Pos;
	};

} // namespace Engine
} // namespace DynRay
#endif //DYNRAY_OBJECT_HPP