#pragma once

class ray;
struct hit_record;
class vec3;
class material
{
public:
	virtual bool scatter(const ray& r_in, const hit_record& h_rec, vec3& out_attenuation, ray& out_ray) = 0;
};