#include "libs\vector\GenVector.h"

struct HitPoint {
	HitPoint() : materialID(0), normal(Vector3()), dist(-1), intersectionPoint(Vector3()){}

	unsigned int materialID;
	Vector3 normal;
	float dist;
	Vector3 intersectionPoint;
};