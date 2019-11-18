#pragma once

#include "Hitables/Hitable.hpp"
#include <vector>

class world : public hitable
{
public:
	world() {}
	~world();

	virtual bool hit(const ray& r, float t_min, float t_max, hit_record& out_record) override;
	void add_object(hitable* o);
private:
	std::vector<hitable*> m_objects;
};