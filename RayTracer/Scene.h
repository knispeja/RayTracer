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

	unsigned int getNumObjectsInScene();

private:
	Camera* camera;
	vector<Material*> materials;
	vector<Light*> lights;
	vector<PrimitiveGeometry*> objects;

	void deallocCamera()
	{
		if (this->camera != NULL)
			delete this->camera;
	}
};

