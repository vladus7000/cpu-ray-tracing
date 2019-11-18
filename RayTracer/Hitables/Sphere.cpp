#include "Sphere.hpp"
#include "../Ray.hpp"
#include "../HitRecord.hpp"
#include <math.h>

sphere::sphere(const vec3& cen, float r, material* m)
	: m_center(cen)
	, m_radius(r)
	, m_material(m)
{

}

sphere::~sphere()
{
	delete m_material;
}

bool sphere::hit(const ray& r, float t_min, float t_max, hit_record& out_record)
{
	vec3 oc = r.origin() - m_center;
	float a = dot(r.direction(), r.direction());
	float b = 2.0f*dot(oc, r.direction());
	float c = dot(oc, oc) - m_radius * m_radius;
	float d = b * b - 4 * a*c;

	if (d > 0.0f)
	{
		float temp = (-b - sqrt(d)) / (2.0f*a);

		if (temp < t_max && temp > t_min)
		{
			out_record.t = temp;
			out_record.point = r.point_at_parameter(temp);
			out_record.normal = (out_record.point - m_center) / m_radius;
			out_record.mat = m_material;
			return true;
		}

		temp = (-b + sqrt(d)) / (2.0f *a);
		if (temp < t_max && temp > t_min)
		{
			out_record.t = temp;
			out_record.point = r.point_at_parameter(temp);
			out_record.normal = (out_record.point - m_center) / m_radius;
			out_record.mat = m_material;
			return true;
		}
	}
	return false;
}