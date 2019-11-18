#pragma once

class ray;
struct hit_record;

class hitable
{
public:
	~hitable() {}

	virtual bool hit(const ray& r, float t_min, float t_max, hit_record& out_record) = 0;
};