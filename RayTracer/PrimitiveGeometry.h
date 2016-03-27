#pragma once

#include "Material.h"
#include "HitPoint.h"
#include "Ray.h"

class PrimitiveGeometry
{
public:	
	virtual char* getGeometryTypeName() const = 0;
	virtual void printOtherData() const = 0;
	virtual HitPoint intersectWithRay(Ray ray) const = 0;
	virtual Vector3 getCenter() const = 0;

	void print()
	{
		printf("%s (", getGeometryTypeName());
		printOtherData();
		printf(")\n");
	}

	unsigned int getMaterialID()
	{
		return this->materialID;
	}

	float distanceBetween(const PrimitiveGeometry& other)
	{
		return getCenter().distance(other.getCenter());
	}

protected:
	unsigned int materialID;
};

