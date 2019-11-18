#pragma once

#include "Material.hpp"
#include "../Math.hpp"

class lambertian : public material
{
public:
	lambertian(const vec3& albedo_in);

	virtual bool scatter(const ray& r_in, const hit_record& h_rec, vec3& out_attenuation, ray& out_ray) override;
private:
	vec3 m_albedo;
};
