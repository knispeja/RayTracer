#pragma once

#include "stdio.h"
#include "libs\vector\GenVector.h"

class Camera
{
public:

	Camera()
	{
		this->distanceFromImagePlane = DEFAULT_DISTANCE_FROM_IMAGE_PLANE;

		this->origin = NULL;
		this->look = NULL;
		this->up = NULL;

		recalculateImagePlaneCenter();
	}

	Camera(Vector3 origin, Vector3 look, Vector3 up)
	{
		this->distanceFromImagePlane = DEFAULT_DISTANCE_FROM_IMAGE_PLANE;

		this->origin = origin;
		this->look = look;
		this->up = up;

		normalizeVectors();
		recalculateImagePlaneCenter();
	}

	~Camera()
	{
		// Nothing to delete
	}

	Vector3 getOrigin()
	{
		return this->origin;
	}

	Vector3 getLook()
	{
		return this->look;
	}

	Vector3 getUp()
	{
		return this->up;
	}

	Vector3 getImagePlaneCenter()
	{
		return this->imagePlaneCenter;
	}

	void increaseFOV()
	{
		this->distanceFromImagePlane++;
		recalculateImagePlaneCenter();
	}

	void decreaseFOV()
	{
		if (distanceFromImagePlane > 1)
		{
			this->distanceFromImagePlane--;
			recalculateImagePlaneCenter();
		}
	}

	void print()
	{
		printf("Camera (pos: (%f, %f, %f))\n", this->origin.c[0], this->origin.c[1], this->origin.c[2]);
	}

private:
	static const unsigned int DEFAULT_DISTANCE_FROM_IMAGE_PLANE = 50;

	unsigned int distanceFromImagePlane;
	Vector3 imagePlaneCenter;
	Vector3 origin;
	Vector3 look;
	Vector3 up;

	void normalizeVectors()
	{
		this->look.normalize();
		this->up.normalize();
	}

	void recalculateImagePlaneCenter()
	{
		this->imagePlaneCenter = (this->origin + (this->look * this->distanceFromImagePlane));
	}
};

