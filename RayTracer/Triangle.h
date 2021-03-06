#pragma once
#include "PrimitiveGeometry.h"
#include "AABB.h"

class Triangle : public PrimitiveGeometry
{
public:
	Triangle()
	{
		this->materialID = 0;
		this->v0 = NULL;
		this->v1 = NULL;
		this->v2 = NULL;
	}

	Triangle(Vector3 v0, Vector3 v1, Vector3 v2)
	{
		this->materialID = 0;
		this->v0 = v0;
		this->v1 = v1;
		this->v2 = v2;
	}

	Triangle(unsigned int materialID, Vector3 v0, Vector3 v1, Vector3 v2)
	{
		this->materialID = materialID;
		this->v0 = v0;
		this->v1 = v1;
		this->v2 = v2;
	}

	~Triangle()
	{
		//Nothing to delete
	}

	virtual char* getGeometryTypeName() const
	{
		return "Triangle";
	}

	virtual void printOtherData() const
	{
		printf("vtx0: (%0.2f, %0.2f, %0.2f)", this->v0.c[0], this->v0.c[1], this->v0.c[2]);
		printf(", vtx1: (%0.2f, %0.2f, %0.2f)", this->v1.c[0], this->v1.c[1], this->v1.c[2]);
		printf(", vtx2: (%0.2f, %0.2f, %0.2f)", this->v2.c[0], this->v2.c[1], this->v2.c[2]);
		printf(", assigned material #%d", this->materialID);
	}

	virtual bool intersectsWithRay(Ray ray, HitPoint& hit) const
	{
		// Does the ray intersect the plane this triangle is in?
		Vector3 n = getSurfaceNormal();

		float bot = (ray.getDirection().dot(n));
		if (bot == 0) 
			return false;

		float top = (this->v0 - ray.getOrigin()).dot(n);

		float distIntWithPlane = top / bot; // TODO abs
		if (distIntWithPlane <= 0)
			return false;

		// The ray intersects the triangle's plane, so check for true intersection
		Vector3 x = ray.getOrigin() + (ray.getDirection() * distIntWithPlane);
		
		// TODO: distance I'm returning may be wrong
		bool b0 = ((this->v1 - this->v0).cross(x - this->v0)).dot(n) > 0;
		bool b1 = ((this->v2 - this->v1).cross(x - this->v1)).dot(n) > 0;
		bool b2 = ((this->v0 - this->v2).cross(x - this->v2)).dot(n) > 0;
		if (b0 && b1 && b2)
			hit.dist = abs(distIntWithPlane); // TODO no abs?
		else
			return false;

		hit.materialID = this->materialID;
		hit.normal = n; // The hitpoint normal will be the surface normal
		return true;
	}

	virtual Vector3 getCenter() const
	{
		return (this->v0 + this->v1 + this->v2) / 3;
	}

	virtual float getMinBound(unsigned int dim)
	{
		return min(min(this->v0[dim], this->v1[dim]), this->v2[dim]);
	}

	virtual float getMaxBound(unsigned int dim)
	{
		return max(max(this->v0[dim], this->v1[dim]), this->v2[dim]);
	}

private:
	Vector3 v0;
	Vector3 v1;
	Vector3 v2;

	Vector3 getSurfaceNormal() const
	{
		return (this->v1 - this->v0).cross(this->v2 - this->v0).normalize();
	}
};