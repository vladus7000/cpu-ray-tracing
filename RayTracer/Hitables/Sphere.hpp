#pragma once

#include "Hitable.hpp"
#include "../Math.hpp"
#include "../Materials/Material.hpp"

class sphere : public hitable
{
public:
	sphere(const vec3& cen, float r, material* m);
	~sphere();
	virtual bool hit(const ray& r, float t_min, float t_max, hit_record& out_record) override;
private:
	vec3 m_center;
	float m_radius;
	material* m_material;
};