#pragma once

#include "Ray.h"
#include "Camera.h"

class RayGenerator
{
public:
	Camera* camera;
	unsigned int w;
	unsigned int h;

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

	Ray getRay(unsigned int x, unsigned int y)
	{
		Vector3 leftRelativeToView = this->camera->getUp().cross(this->camera->getLook());
		Vector3 imagePlaneOrigin = (this->camera->getImagePlaneCenter() + (this->camera->getUp() * (this->h / 2)) + (leftRelativeToView * (this->w / 2)));
		Vector3 rayDir = (imagePlaneOrigin - (leftRelativeToView * x) - (this->camera->getUp() * y));

		return Ray(this->camera->getOrigin(), rayDir);
	}
};