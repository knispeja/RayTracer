#include "Scene.h"

#include <vector>
using namespace std;

Scene::Scene()
{
	this->objects = vector<PrimitiveGeometry*>();
	this->camera = NULL;
}

Scene::~Scene()
{
	delete this->camera;

	for (int i = 0; i < (this->objects.size()); i++)
	{
		delete this->objects[i];
	}
}

void Scene::setCamera(Camera* camera)
{
	if (this->camera != NULL)
		delete this->camera;
	this->camera = camera;
}

void Scene::addObjectToScene(PrimitiveGeometry* obj)
{
	this->objects.push_back(obj);
}

void Scene::printObjectsInScene()
{
	this->camera->print();
	for (int i = 0; i < (this->objects.size()); i++)
	{
		this->objects[i]->print();
	}
}

Camera* Scene::getCamera()
{
	return this->camera;
}

int Scene::getFirstRayIntersectionDist(Ray ray)
{
	int minDist = -1;
	for (int i = 0; i < (this->objects.size()); i++)
	{
		int dist = this->objects[i]->distanceRayIntersectsGeometry(ray);
		if (dist >= 0)
		{
			if (minDist == -1 || dist < minDist)
				minDist = dist;
		}
	}
	return minDist;
}

unsigned int Scene::getNumObjectsInScene()
{
	return this->objects.size();
}
