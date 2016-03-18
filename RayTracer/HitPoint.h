#include "libs\vector\GenVector.h"

struct HitPoint {
	HitPoint() : normal(Vector3()), dist(-1){}

	unsigned int materialID;
	Vector3 normal;
	float dist;
};