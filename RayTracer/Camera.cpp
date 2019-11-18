#include "Camera.hpp"
#include "MathTools.hpp"

camera::camera(float vFov, float aspect)
	: lowLeftCorner(-2.0f, -1.0f, -1.0f)
	, horizontal(4.0f, 0.0f, 0.0f)
	, vertical(0.0f, 2.0f, 0.0f)
	, origin(0.0f, 0.0f, 0.0f)
{
	float theta = vFov * 3.141592654f / 180.0f;
	float half_h = tan(theta / 2.0f);
	float half_w = aspect * half_h;
	lowLeftCorner = vec3(-half_w, -half_h, -1.0f);
	horizontal = vec3(2.0f * half_w, 0.0f, 0.0f);
	vertical = vec3(0.0f, 2.0f * half_h, 0.0f);
}

camera::camera(const vec3& lookFrom, const vec3& lookAt, vec3 up, float vFov, float aspect, float apert, float focus_d)
	: lowLeftCorner(-2.0f, -1.0f, -1.0f)
	, horizontal(4.0f, 0.0f, 0.0f)
	, vertical(0.0f, 2.0f, 0.0f)
	, origin(0.0f, 0.0f, 0.0f)
	, lens_radius(apert / 2.0f)
	, focus_dist(focus_d)
{

	float theta = vFov * 3.141592654f / 180.0f;
	float half_h = tan(theta / 2.0f);
	float half_w = aspect * half_h;
	origin = lookFrom;
	w = unit_vector(lookFrom - lookAt);
	u = unit_vector(cross(up, w));
	v = cross(w, u);

	lowLeftCorner = origin - half_w * focus_dist*u - half_h * focus_dist* v - focus_dist * w;
	horizontal = 2.0f * half_w *focus_dist* u;
	vertical = 2.0f * half_h *focus_dist*v;
}

ray camera::getRay(float s, float t)
{
	vec3 rd = lens_radius * random_in_unit_disk();
	vec3 offset = u * rd.x() + v * rd.y();
	return ray(origin + offset, lowLeftCorner + s * horizontal + t * vertical - origin - offset);
}