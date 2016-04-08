#pragma once
#include "PrimitiveGeometry.h"

#include <algorithm>

class AABB : public PrimitiveGeometry
{
public:
	const unsigned int VEC_DIM = 3;

	Vector3 bbMin;
	Vector3 bbMax;

	AABB()
	{
		this->bbMin = Vector3(0, 0, 0);
		this->bbMax = Vector3(0, 0, 0);
	}

	AABB(PrimitiveGeometry** geomsToSurround, int size)
	{
		PrimitiveGeometry* firstGeom = geomsToSurround[0];
		this->bbMax = Vector3(firstGeom->getMaxBound(0), firstGeom->getMaxBound(1), firstGeom->getMaxBound(2));
		this->bbMin = Vector3(firstGeom->getMinBound(0), firstGeom->getMinBound(1), firstGeom->getMinBound(2));

		for (int i = 1; i < size; i++)
		{
			for (int j = 0; j < VEC_DIM; j++)
			{
				this->bbMin[j] = min(this->bbMin[j], geomsToSurround[i]->getMinBound(j));
				this->bbMax[j] = max(this->bbMax[j], geomsToSurround[i]->getMaxBound(j));
			}
		}
	}

	~AABB()
	{
		//Nothing to delete
	}

	virtual char* getGeometryTypeName() const
	{
		return "AABB";
	}

	virtual void printOtherData() const
	{
		printf("\n---- (min  max)\n");
		printf("x: (%0.2f, %0.2f)\n", bbMin[0], bbMax[0]);
		printf("y: (%0.2f, %0.2f)\n", bbMin[1], bbMax[1]);
		printf("z: (%0.2f, %0.2f)\n", bbMin[2], bbMax[2]);
	}

	virtual bool intersectsWithRay(Ray ray, HitPoint& hit) const
	{
		//we want to find the farthest entrance and closest exit to the box
		//if the exit is closer than the entrance, there is no hit
		float entrance = -1.0f * (FLT_MAX - 1.0f);
		float exit = FLT_MAX;
		Vector3 normal = Vector3(0, 0, 0);

		for (int i = 0; i<VEC_DIM; i++)
		{
			float slabA = this->bbMin[i];
			float slabB = this->bbMax[i];
			float invDir = 1.0f / ray.getDirection()[i];
			float origin = ray.getOrigin()[i];

			float closestHit = (slabA - origin) * invDir;
			float farthestHit = (slabB - origin) * invDir;

			if (farthestHit < closestHit)
				std::swap(closestHit, farthestHit);

			bool tooClose = farthestHit < entrance;
			bool tooFar = closestHit > exit;

			if (tooClose || tooFar)
				return false;

			bool foundNewEntrance = closestHit > entrance;
			entrance = foundNewEntrance ? closestHit : entrance;

			bool foundNewExit = farthestHit < exit;
			exit = foundNewExit ? farthestHit : exit;

			if (foundNewEntrance)
			{
				normal = Vector3(0, 0, 0);
				normal[i] = ray.getDirection()[i] * -1;
				normal.normalize();
			}
		}

		hit.normal = normal;
		hit.materialID = 0; // TODO: Fixme
		hit.dist = entrance;

		return true;
	}

	virtual Vector3 getCenter() const
	{
		Vector3 center = Vector3();
		for (int i = 0; i < VEC_DIM; i++)
			center[i] = (this->bbMax[i] + this->bbMin[i])/2;

		return center;
	}

	virtual float getMinBound(unsigned int dim)
	{
		return this->bbMin[dim];
	}

	virtual float getMaxBound(unsigned int dim)
	{
		return this->bbMax[dim];
	}
};

