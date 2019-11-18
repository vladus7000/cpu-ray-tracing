#include "Dielectric.hpp"
#include "../HitRecord.hpp"
#include "../MathTools.hpp"
#include "../Ray.hpp"

dielectric::dielectric(float r) : m_refr_idx(r)
{
}

bool dielectric::scatter(const ray& r_in, const hit_record& h_rec, vec3& out_attenuation, ray& out_ray)
{
	vec3 outward_n;
	vec3 reflected = reflect(r_in.direction(), h_rec.normal);
	float ni_over_nt;
	float cosine;
	float refr_probe;
	out_attenuation = vec3(1.0f, 1.0f, 1.0f);
	vec3 refracted;
	if (dot(r_in.direction(), h_rec.normal) > 0.0f)
	{
		outward_n = -h_rec.normal;
		ni_over_nt = m_refr_idx;
		cosine = m_refr_idx * dot(r_in.direction(), h_rec.normal) / r_in.direction().length();
	}
	else
	{
		outward_n = h_rec.normal;
		ni_over_nt = 1.0f / m_refr_idx;
		cosine = -dot(r_in.direction(), h_rec.normal) / r_in.direction().length();
	}

	if (refract(r_in.direction(), outward_n, ni_over_nt, refracted))
	{
		refr_probe = schlick(cosine, m_refr_idx);
	}
	else
	{
		refr_probe = 1.0f;
	}
	std::random_device rd;
	std::mt19937 e2(rd());
	std::uniform_real_distribution<> dist(0.0f, 1.0f);

	if (dist(e2) < refr_probe)
	{
		out_ray = ray(h_rec.point, reflected);
	}
	else
	{
		out_ray = ray(h_rec.point, refracted);
	}

	return true;
}