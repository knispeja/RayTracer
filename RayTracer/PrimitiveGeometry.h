#pragma once

#include "Material.h"
#include "HitPoint.h"
#include "Ray.h"

class PrimitiveGeometry
{
public:	
	virtual char* getGeometryTypeName() = 0;
	virtual void printOtherData() = 0;
	virtual HitPoint intersectWithRay(Ray ray) = 0;

	void print()
	{
		printf("%s (", getGeometryTypeName());
		printOtherData();
		printf(")\n");
	}

	unsigned int getMaterial()
	{
		return this->materialID;
	}

protected:
	unsigned int materialID;
};

