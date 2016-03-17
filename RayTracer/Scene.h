#pragma once
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

	void addObjectToScene(PrimitiveGeometry* obj);
	void printObjectsInScene();
	
	void addMaterial(Material* mat);
	Material* getMaterial(unsigned int matIndex);

	Camera* getCamera();
	HitPoint getFirstRayIntersection(Ray ray);

	unsigned int getNumObjectsInScene();

private:
	Camera* camera;
	vector<Material*> materials;
	vector<PrimitiveGeometry*> objects;

	void deallocCamera()
	{
		if (this->camera != NULL)
			delete this->camera;
	}
};

