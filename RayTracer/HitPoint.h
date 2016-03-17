#include "libs\vector\GenVector.h"

struct HitPoint {
	HitPoint() : normal(Vector3()), dist(-1){}

	Material* material;
	Vector3 normal;
	float dist;
};