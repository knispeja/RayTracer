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
	printf("---------------------------------------\n");
	printf("Materials:\n");
	for (int i = 0; i < this->materials.size(); i++)
	{
		Vector3 ka = this->materials[i]->ka;
		printf("Material %d ka = [%f %f %f]\n", i, ka.c[0], ka.c[1], ka.c[2]);
	}

	printf("---------------------------------------\n");
	printf("Camera:\n");
	this->camera->print();

	printf("---------------------------------------\n");
	printf("Geometries:\n");
	for (int i = 0; i < (this->objects.size()); i++)
	{
		this->objects[i]->print();
	}
}

void Scene::addMaterial(Material* mat)
{
	printf("added material %d with ka %f %f %f\n", this->materials.size(), mat->ka.c[0], mat->ka.c[1], mat->ka.c[2]);
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
	HitPoint hp;

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