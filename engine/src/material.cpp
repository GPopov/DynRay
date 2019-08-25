#include "material.hpp"

namespace DynRay
{
namespace Engine
{
	Material::Material() = default;
	Material::~Material() = default;
	Material::Material(const Material&) = default;
	Material::Material(Material&&) = default;
	Material& Material::operator=(const Material&) = default;
	Material& Material::operator=(Material&&) = default;

}
}