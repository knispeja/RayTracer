#pragma once

#include "Ray.h"

class PrimitiveGeometry
{
public:	
	virtual char* getGeometryTypeName() = 0;
	virtual void printOtherData() = 0;
	virtual float distanceRayIntersectsGeometry(Ray ray) = 0;

	void print()
	{
		printf("%s (", getGeometryTypeName());
		printOtherData();
		printf(")\n");
	}
};

