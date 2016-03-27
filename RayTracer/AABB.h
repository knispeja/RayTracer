#pragma once
#include "PrimitiveGeometry.h"

#include <algorithm>

class AABB : public PrimitiveGeometry
{
public:
	AABB()
	{
		for (int i = 0; i < VEC_DIM; i++)
		{
			bbMin[i] = 0;
			bbMax[i] = 0;
		}
	}

	AABB(float minX, float maxX, float minY, float maxY, float minZ, float maxZ)
	{
		bbMin[0] = minX;
		bbMax[0] = maxX;

		bbMin[1] = minY;
		bbMax[1] = maxY;

		bbMin[2] = minZ;
		bbMax[2] = maxZ;
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
		printf("---- (min  max)");
		printf("x: (%0.2f, %0.2f)", bbMin[0], bbMax[0]);
		printf("y: (%0.2f, %0.2f)", bbMin[1], bbMax[1]);
		printf("z: (%0.2f, %0.2f)", bbMin[2], bbMax[2]);
	}

	virtual HitPoint intersectWithRay(Ray ray) const
	{
		HitPoint hp = HitPoint();

		//we want to find the farthest entrance and closest exit to the box
		//if the exit is closer than the entrance, there is no hit
		float entrance = 0.0f;
		float exit = hp.dist; // WHAT SHOULD THIS BE???
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
			{
				hp.dist = -1;
				return hp;
			}

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

		hp.normal = normal;
		hp.materialID = 0;
		hp.dist = entrance;

		return hp;
	}

	virtual Vector3 getCenter() const
	{
		Vector3 center = Vector3();
		for (int i = 0; i < VEC_DIM; i++)
			center[i] = this->bbMax[i] - this->bbMin[i];

		return center;
	}

private:
	const size_t VEC_DIM = 3;

	int bbMin[3];
	int bbMax[3];
};

