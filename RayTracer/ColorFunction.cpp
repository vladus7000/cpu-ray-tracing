#include "ColorFunction.hpp"
#include "HitRecord.hpp"
#include "Ray.hpp"
#include "Hitables/World.hpp"
#include "MathTools.hpp"
#include <float.h>

vec3 color(const ray& r, world& w, int depth)
{
	hit_record rec;

	if (w.hit(r, 0.001f, FLT_MAX, rec) /*t > 0.0f*/)
	{
		ray scatered;
		vec3 attenuated;

		if (depth < 50 && rec.mat->scatter(r, rec, attenuated, scatered))
		{
			return attenuated * color(scatered, w, depth + 1);
		}
		else
		{
			return vec3(0.0f, 0.0f, 0.0f);
		}
	}

	//Base Color
	float t;
	vec3 unit_dir = unit_vector(r.direction());
	t = 0.5f * (unit_dir.y() + 1.0f);

	return (1.0f - t) * vec3(1.0f, 1.0f, 1.0f) + t * vec3(0.5f, 0.7f, 1.0f);
}