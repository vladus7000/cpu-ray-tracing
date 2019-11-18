#pragma once

#include "Math.hpp"

class ray;
class world;

vec3 color(const ray& r, world& w, int depth);