#pragma once
#include "Light.h"
#include "Camera.h"
#include "PrimitiveGeometry.h"
#include "BVHTreeNode.h"
#include "AABB.h"

#include <vector>
using namespace std;

class Scene
{
public:
	Scene();
	~Scene();

	void setCamera(Camera* camera);

	void printObjects();
	
	void addMaterial(Material* mat);
	Material* getMaterial(unsigned int matIndex);

	void addLight(Light* light);
	void printLights();

	Camera* getCamera();
	bool getFirstRayIntersection(Ray ray, HitPoint& hit);
	Vector3 colorPointBasedOnShadow(Ray hitRay, HitPoint hp, unsigned int recursiveDepth = 0);
	Vector3 traceReflection(Ray reflectRay, HitPoint reflectPt, Vector3 colorWOReflection, unsigned int recursiveDepth);

	unsigned int getNumObjectsInScene();

	void setObjectTreeHead(BVHTreeNode* head);

private:
	const float LIGHT_RAY_JITTER = 0.0001f;
	const unsigned int MAX_REFLECTION_RECURSION_DEPTH = 10;
	const Vector3 COLOR_OF_NOTHINGNESS = Vector3(0, 0, 0);

	Camera* camera;
	BVHTreeNode* objectTree;
	vector<Material*> materials;
	vector<Light*> lights;

	Color addVector3ToColor(Color c, Vector3 vec)
	{
		Color returnColor = c;
		returnColor.c[0] += vec.c[0];
		returnColor.c[1] += vec.c[1];
		returnColor.c[2] += vec.c[2];

		return returnColor;
	}

	void deallocCamera()
	{
		if (this->camera != NULL)
			delete this->camera;
	}
};

