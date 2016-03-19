#pragma once
#include "PrimitiveGeometry.h"

class Sphere : public PrimitiveGeometry
{
public:
	Sphere()
	{
		this->materialID = 0;
		this->center = NULL;
		this->radius = 0;
	}

	Sphere(Vector3 center, float radius)
	{
		this->materialID = 0;
		this->center = center;
		this->radius = radius;
	}

	Sphere(unsigned int materialID, Vector3 center, float radius)
	{
		this->materialID = materialID;
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
		printf(", assigned material #%d", this->materialID);
	}

	virtual HitPoint intersectWithRay(Ray ray)
	{
		HitPoint hp = HitPoint();
		hp.materialID = this->materialID;

		Vector3 d = ray.getDirection();
		Vector3 e = ray.getOrigin();
		Vector3 c = this->center;

		float discriminant = pow(d.dot(e - c), 2) - (d.dot(d))*((e-c).dot(e-c)-(pow(this->radius, 2)));
		if (discriminant < 0)
		{
			hp.dist = -1;
			return hp;
		}
		
		//float postop = ((d*-1).dot(e - c) + sqrt(discriminant)); // TODO: Far point of intersection, for translucent spheres (unused)
		float negtop = ((d*-1).dot(e - c) - sqrt(discriminant));
		float bot = (d.dot(d));

		if (discriminant > 0)
			hp.dist = negtop / bot;
		
		// Discriminant = 0, tangent, but return the same
		hp.dist = negtop / bot;

		// Get normal vector from sphere center to intersection point
		Vector3 intersectionPoint = ray.getOrigin() + (ray.getDirection() * hp.dist);
		hp.normal = (intersectionPoint - this->center).normalize();
		return hp;
	}

private:
	Vector3 center;
	float radius;
};