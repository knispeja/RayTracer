#pragma once
#include "Light.h"
#include "Camera.h"
#include "PrimitiveGeometry.h"

#include <vector>
using namespace std;

class Scene
{
public:
	Scene();
	~Scene();

	void setCamera(Camera* camera);

	void addObject(PrimitiveGeometry* obj);
	void printObjects();
	
	void addMaterial(Material* mat);
	Material* getMaterial(unsigned int matIndex);

	void addLight(Light* light);
	void printLights();

	Camera* getCamera();
	HitPoint getFirstRayIntersection(Ray ray);
	Vector3 colorPointBasedOnShadow(HitPoint hp);

	unsigned int getNumObjectsInScene();

private:
	const float LIGHT_RAY_JITTER = 0.0001f;

	Camera* camera;
	vector<Material*> materials;
	vector<Light*> lights;
	vector<PrimitiveGeometry*> objects;

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

