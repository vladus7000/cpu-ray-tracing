#pragma once
#include "Math.hpp"
#include "Materials/Material.hpp"

struct hit_record
{
	float t;
	vec3 point;
	vec3 normal;
	material* mat;
};
