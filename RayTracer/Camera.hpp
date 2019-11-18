#pragma once

#include "Math.hpp"
#include "Ray.hpp"

class camera
{
public:
	camera(float vFov, float aspect);
	camera(const vec3& lookFrom, const vec3& lookAt, vec3 up, float vFov, float aspect, float apert, float focus_d);
	ray getRay(float s, float t);

private:
	vec3 lowLeftCorner;
	vec3 horizontal;
	vec3 vertical;
	vec3 origin;
	float lens_radius;
	float focus_dist;
	vec3 u, v, w;
};
