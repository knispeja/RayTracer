#pragma once
#include "PrimitiveGeometry.h"

class Sphere : public PrimitiveGeometry
{
public:
	Sphere()
	{
		this->center = NULL;
		this->radius = 0;
	}

	Sphere(Vector3 center, float radius)
	{
		this->center = center;
		this->radius = radius;
	}

	~Sphere()
	{
		//Nothing to delete
	}

	virtual char* getGeometryTypeName()
	{
		return "Sphere";
	}

	virtual void printOtherData()
	{
		printf("center: (%0.2f %0.2f %0.2f)", this->center.c[0], this->center.c[1], this->center.c[2]);
		printf(", radius: %0.2f", this->radius);
	}

	virtual float distanceRayIntersectsGeometry(Ray ray)
	{
		Vector3 d = ray.getDirection();
		Vector3 e = ray.getOrigin();
		Vector3 c = this->center;

		float discriminant = pow(d.dot(e - c), 2) - (d.dot(d))*((e-c).dot(e-c)-(pow(this->radius, 2)));
		if (discriminant < 0)
			return -1;
		
		//float postop = ((d*-1).dot(e - c) + sqrt(discriminant));
		float negtop = ((d*-1).dot(e - c) - sqrt(discriminant));
		float bot = (d.dot(d));

		if (discriminant > 0)
			return negtop / bot;
		
		// Discriminant = 0, tangent, but return the same
		return negtop / bot;
	}

private:
	Vector3 center;
	float radius;
};