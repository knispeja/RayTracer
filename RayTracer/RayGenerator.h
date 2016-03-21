#pragma once

#include "Ray.h"
#include "Camera.h"

class RayGenerator
{
public:
	Camera* camera;
	float w;
	float h;

	RayGenerator()
	{
		this->camera = NULL;
		this->w = 0;
		this->h = 0;
	}

	RayGenerator(Camera* camera, unsigned int w, unsigned int h)
	{
		this->camera = camera;
		this->w = w;
		this->h = h;
	}

	~RayGenerator()
	{
		// Don't delete the camera because it is deleted by its associated Scene
	}

	Ray getRay(float x, float y)
	{
		Vector3 w = this->camera->getLook();
		Vector3 u = this->camera->getUp().cross(this->camera->getLook());
		Vector3 v = this->camera->getUp();

		float normx = (-1 * (x / this->w) + 0.5f) * 2;
		float normy = (-1 * (y / this->h) + 0.5f) * 2;
		Vector3 rayDir = (w + (u * normx) + (v * normy));

		return Ray(this->camera->getOrigin(), rayDir);
	}
};