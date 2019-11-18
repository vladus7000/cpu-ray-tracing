#pragma once

#include <random>
#include "Math.hpp"

inline vec3 reflect(const vec3& v, const vec3& n)
{
	return v - 2.0f * dot(v, n)*n;
}

inline vec3 unit_vector(vec3 v) {
	return v / v.length();
}

inline bool refract(const vec3& v, const vec3& n, float ni_over_nt, vec3& refracted)
{
	vec3 uv = unit_vector(v);
	float dt = dot(uv, n);
	float discriminant = 1.0f - ni_over_nt * ni_over_nt * (1.0f - dt * dt);
	if (discriminant > 0.0f)
	{
		refracted = ni_over_nt * (uv - n * dt) - n * sqrt(discriminant);
		return true;
	}
	return false;
}

inline vec3 random_in_unit_sphere()
{
	std::random_device rd;
	std::mt19937 e2(rd());
	std::uniform_real_distribution<> dist(0.0f, 1.0f);
	vec3 p;

	do
	{
		p = 2.0f * vec3(dist(e2), dist(e2), dist(e2)) - vec3(1.0f, 1.0f, 1.0f);
	} while (p.squared_length() >= 1.0f);
	return p;
}

inline float schlick(float cosine, float ref_idx)
{
	float r0 = (1.0f - ref_idx) / (1.0f + ref_idx);
	r0 = r0 * r0;
	return r0 + (1.0f - r0) * pow((1.0f - cosine), 5.0f);
}

inline vec3 random_in_unit_disk()
{
	std::random_device rd;
	std::mt19937 e2(rd());
	std::uniform_real_distribution<> dist(0.0f, 1.0f);

	vec3 p;
	do
	{
		p = 2.0f * vec3(dist(e2), dist(e2), 0.0f) - vec3(1.0f, 1.0f, 0.0f);
	} while (dot(p, p) >= 1.0f);
	return p;
}