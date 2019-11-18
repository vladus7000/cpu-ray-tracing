#include <iostream>
#include <vector>
#include <thread>
#include <sstream>

#include "Math.hpp"
#include "MathTools.hpp"
#include "Hitables/Sphere.hpp"
#include "Hitables/World.hpp"
#include "Materials/Lambertian.hpp"
#include "Materials/Dielectric.hpp"
#include "Materials/Metal.hpp"
#include "Camera.hpp"
#include "ColorFunction.hpp"

int main()
{
	int width = 250;
	int height = 100;
	int ns = 30;
	int nbThreads = 10;
	std::vector<std::ostringstream> threadBuffers(nbThreads);

	world w;

	{
		std::random_device rd;
		std::mt19937 e2(rd());
		std::uniform_real_distribution<> dist(0.0f, 1.0f);

		int n = 500;
		w.add_object(new sphere(vec3(0.0f, -1000.0f, 0.0f), 1000.f, new lambertian(vec3(0.5f, 0.5f, 0.5f))));

		for (int a = -11; a < 11; a++)
		{
			for (int b = -11; b < 11; b++)
			{
				float material = dist(e2);
				vec3 center(a + 0.9f * dist(e2), 0.2f, b + 0.9f * dist(e2));
				if ((center - vec3(4.0f, 0.2f, 0.0f)).length() > 0.9)
				{
					if (material < 0.8f) // diff
					{
						w.add_object(new sphere(center, 0.2f, new lambertian(vec3(dist(e2) * dist(e2), dist(e2) * dist(e2), dist(e2) * dist(e2)))));
					}
					else if (material < 0.95f) // metal
					{
						w.add_object(new sphere(center, 0.2f,
							new metal(vec3(0.5f* (1.0f + dist(e2)), 0.5f* (1.0f + dist(e2)), 0.5f* (1.0f + dist(e2))), 0.5f* dist(e2))
						));
					}
					else // glass
					{
						w.add_object(new sphere(center, 0.2f, new dielectric(1.5f)));
					}
				}
			}
		}

		w.add_object(new sphere(vec3(0.0f, 1.0f, 0.0f), 1.0f, new dielectric(1.5f)));
		w.add_object(new sphere(vec3(-4.0f, 1.0f, 0.0f), 1.0f, new lambertian(vec3(0.4f, 0.2f, 0.1f))));
		w.add_object(new sphere(vec3(4.0f, 1.0f, 0.0f), 1.0f, new metal(vec3(0.7f, 0.6f, 0.5f), 0.0f)));

	}

	auto workload = [&w, width, height, ns, nbThreads, &threadBuffers](int threadID)
	{
		if (threadID == 0)
		{
			threadBuffers[threadID] << "P3\n" << width << " " << height << "\n255\n";
		}
		vec3 lookFrom(13.0f, 2.0f, 3.0f);
		vec3 lookAt(0.0f, 0.0f, -1.0f);
		float aperture = 0.1f;
		float dist_to_focus = 10.0f;// (lookFrom - lookAt).length();
		camera cam(lookFrom, lookAt, vec3(0.0f, 1.0f, 0.0f), 20.0f, (float(width) / float(height)), aperture, dist_to_focus);
		std::random_device rd;
		std::mt19937 e2(rd());
		std::uniform_real_distribution<> dist(0.0f, 1.0f);

		int chunk = height / nbThreads;
		int startFrom = chunk * (nbThreads - threadID);
		int to = startFrom - chunk;
		for (int j = startFrom - 1; j >= to; j--)
		{
			for (int i = 0; i < width; i++)
			{
				vec3 col(0.0f, 0.0f, 0.0f);
				for (int s = 0; s < ns; s++)
				{
					float u = float(i + dist(e2)) / float(width);
					float v = float(j + dist(e2)) / float(height);
					col += color(cam.getRay(u, v), w, 0);
				}

				col /= float(ns);
				col = vec3(sqrt(col[0]), sqrt(col[1]), sqrt(col[2])); // gamma correction
				int ir = int(255.99 * col[0]);
				int ig = int(255.99 * col[1]);
				int ib = int(255.99 * col[2]);

				threadBuffers[threadID] << ir << " " << ig << " " << ib << "\n";
			}
		}
	};

	std::vector<std::thread> threads;
	for (int i = 0; i < nbThreads; i++)
	{
		auto currentW = [i, &workload]()
		{
			workload(i);
		};
		std::thread t(currentW);

		threads.push_back(std::move(t));
	}

	for (auto& t : threads)
	{
		t.join();
	}

	for (auto& buffs : threadBuffers)
	{
		std::string str = buffs.str(); // :D
		std::cout << str;
	}

	return 0;
}