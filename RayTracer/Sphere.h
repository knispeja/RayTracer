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

	virtual char* getGeometryTypeName() const
	{
		return "Sphere";
	}

	virtual void printOtherData() const
	{
		printf("center: (%0.2f %0.2f %0.2f)", this->center.c[0], this->center.c[1], this->center.c[2]);
		printf(", radius: %0.2f", this->radius);
		printf(", assigned material #%d", this->materialID);
	}

	virtual bool intersectsWithRay(Ray ray, HitPoint& hit) const
	{
		Vector3 d = ray.getDirection();
		Vector3 e = ray.getOrigin();
		Vector3 c = this->center;

		float discriminant = pow(d.dot(e - c), 2) - (d.dot(d))*((e-c).dot(e-c)-(pow(this->radius, 2)));
		if (discriminant < 0)
			return false;
		
		//float postop = ((d*-1).dot(e - c) + sqrt(discriminant)); // TODO: Far point of intersection, for translucent spheres (unused)
		float postop = ((d*-1).dot(e - c) + sqrt(discriminant));
		float negtop = ((d*-1).dot(e - c) - sqrt(discriminant));
		float bot = (d.dot(d));

		// Discriminant = 0 = tangent, discriminant > 0 = regular intersect. Return same either way
		float negResult = negtop / bot;
		float posResult = postop / bot;

		if (negResult < 0 && posResult < 0)
			return false;
		else if (negResult < 0)
			hit.dist = posResult;
		else if (posResult < 0)
			hit.dist = negResult;
		else if (negResult > posResult)
			hit.dist = posResult;
		else
			hit.dist = negResult;

		// Get normal vector from sphere center to intersection point
		hit.normal = (ray.getOrigin() - this->center).normalize();
		hit.materialID = this->materialID;
		return true;
	}

	virtual Vector3 getCenter() const
	{
		return this->center;
	}

private:
	Vector3 center;
	float radius;
};