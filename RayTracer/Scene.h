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
	
	Camera* getCamera();
	int getFirstRayIntersectionDist(Ray ray);

	unsigned int getNumObjectsInScene();

private:
	Camera* camera;
	vector<PrimitiveGeometry*> objects;
};

