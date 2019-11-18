#pragma once

#include "Material.hpp"
#include "../Math.hpp"

class metal : public material
{
public:
	metal(const vec3& albedo_in, float fuzz);

	virtual bool scatter(const ray& r_in, const hit_record& h_rec, vec3& out_attenuation, ray& out_ray) override;
private:
	vec3 m_albedo;
	float m_fuzz;
};