#pragma once

#include "stdio.h"
#include "libs\vector\GenVector.h"

class Camera
{
public:

	Camera()
	{
		this->origin = NULL;
		this->look = NULL;
		this->up = NULL;
	}

	Camera(Vector3 origin, Vector3 lookAt, Vector3 up)
	{
		this->imagePlaneCenter = lookAt;
		this->origin = origin;
		this->look = (lookAt - origin).normalize();
		this->up = up;
		this->up.normalize();
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

	float getDistanceFromImagePlane()
	{
		return this->origin.distance(this->imagePlaneCenter);
	}

	void print()
	{
		printf("Camera (pos: (%f, %f, %f) look: (%f, %f, %f))\n", this->origin.c[0], this->origin.c[1], this->origin.c[2], this->look.c[0], this->look.c[1], this->look.c[2]);
	}

private:
	float distanceFromImagePlane;
	Vector3 imagePlaneCenter;
	Vector3 origin;
	Vector3 look;
	Vector3 up;
};

