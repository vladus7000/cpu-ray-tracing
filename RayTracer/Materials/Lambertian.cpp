#include "Lambertian.hpp"
#include "../HitRecord.hpp"
#include "../MathTools.hpp"
#include "../Ray.hpp"

lambertian::lambertian(const vec3& albedo_in) : m_albedo(albedo_in)
{
}

bool lambertian::scatter(const ray& r_in, const hit_record& h_rec, vec3& out_attenuation, ray& out_ray)
{
	out_attenuation = m_albedo;
	vec3 target = h_rec.point + h_rec.normal + random_in_unit_sphere();
	out_ray = ray(h_rec.point, target - h_rec.point);
	return true;
}