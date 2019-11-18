#pragma once

#include "Material.hpp"
#include "../Math.hpp"

class dielectric : public material
{
public:
	dielectric(float refr_idx);

	virtual bool scatter(const ray& r_in, const hit_record& h_rec, vec3& out_attenuation, ray& out_ray) override;
private:
	float m_refr_idx;;
};