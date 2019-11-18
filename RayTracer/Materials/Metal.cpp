#include "Metal.hpp"
#include "../HitRecord.hpp"
#include "../MathTools.hpp"
#include "../Ray.hpp"

metal::metal(const vec3& albedo_in, float fuzz) : m_albedo(albedo_in), m_fuzz(fuzz) {}

bool metal::scatter(const ray& r_in, const hit_record& h_rec, vec3& out_attenuation, ray& out_ray)
{
	vec3 reflected = reflect(unit_vector(r_in.direction()), h_rec.normal);
	out_attenuation = m_albedo;
	out_ray = ray(h_rec.point, reflected + m_fuzz * random_in_unit_sphere());

	return dot(out_ray.direction(), h_rec.normal) > 0.0f;
}