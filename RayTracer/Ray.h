#pragma once

#include "stdio.h"
#include "libs/vector/GenVector.h"

class Ray
{
public:
	Ray()
	{
		this->origin = NULL;
		this->direction = NULL;
	}

	Ray(Vector3 origin, Vector3 direction)
	{
		this->origin = origin;
		this->direction = direction;
		this->direction.normalize();
	}

	~Ray()
	{
		// Nothing to delete
	}

	//TODO: PointatParameter()?

	Vector3 getOrigin()
	{
		return this->origin;
	}

	Vector3 getDirection()
	{
		return this->direction;
	}

private:
	Vector3 origin;
	Vector3 direction;
};

