#include "World.hpp"
#include "HitRecord.hpp"

world::~world()
{
	for (auto o : m_objects)
	{
		delete o;
	}
}

bool world::hit(const ray& r, float t_min, float t_max, hit_record& out_record)
{
	hit_record temp_record;
	bool hitAny = false;

	double closes_so_far = t_max;

	for (auto o : m_objects)
	{
		if (o->hit(r, t_min, closes_so_far, temp_record))
		{
			hitAny = true;
			closes_so_far = temp_record.t;
			out_record = temp_record;
		}
	}

	return hitAny;
}

void world::add_object(hitable* o)
{
	m_objects.push_back(o);
}