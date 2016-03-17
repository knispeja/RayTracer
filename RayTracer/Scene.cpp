#include "Scene.h"

#include <vector>
using namespace std;

Scene::Scene()
{
	this->objects = vector<PrimitiveGeometry*>();

	this->materials = vector<Material*>();

	this->camera = NULL;
}

Scene::~Scene()
{
	deallocCamera();

	// Dealloc all geometries in this->objects
	for (int i = 0; i < (this->objects.size()); i++)
	{
		if (this->objects[i] != NULL)
			delete this->objects[i];
		else
			printf("Object %d in Scene was NULL for some reason...", i);
	}

	// Dealloc all materials in this->materials
	for (int i = 0; i < (this->materials.size()); i++)
	{
		delete this->materials[i];
	}
}

void Scene::setCamera(Camera* camera)
{
	deallocCamera();
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

void Scene::addMaterial(Material* mat)
{
	this->materials.push_back(mat);
}

Material* Scene::getMaterial(unsigned int matIndex)
{
	return this->materials[matIndex];
}

Camera* Scene::getCamera()
{
	return this->camera;
}

HitPoint Scene::getFirstRayIntersection(Ray ray)
{
	int minDist = -1;
	HitPoint hp = HitPoint();

	for (int i = 0; i < (this->objects.size()); i++)
	{
		HitPoint hit = this->objects[i]->intersectWithRay(ray);
		int dist = hit.dist;

		if (dist >= 0)
		{
			if (minDist == -1 || dist < minDist)
			{
				minDist = dist;
				hp = hit;
			}
		}
	}

	return hp;
}

unsigned int Scene::getNumObjectsInScene()
{
	return this->objects.size();
}