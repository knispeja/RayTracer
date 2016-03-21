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

	// Dealloc all materials in this->materials
	for (int i = 0; i < (this->materials.size()); i++)
	{
		delete this->materials[i];
	}

	// Dealloc all lights in this->lights
	for (int i = 0; i < (this->lights.size()); i++)
	{
		delete this->lights[i];
	}

	// Dealloc all geometries in this->objects
	for (int i = 0; i < (this->objects.size()); i++)
	{
		if (this->objects[i] != NULL)
			delete this->objects[i];
		else
			printf("Object %d in Scene was NULL for some reason...", i);
	}
}

void Scene::setCamera(Camera* camera)
{
	deallocCamera();
	this->camera = camera;
}

void Scene::addObject(PrimitiveGeometry* obj)
{
	this->objects.push_back(obj);
}

void Scene::printObjects()
{
	printf("---------------------------------------\n");
	printf("Camera:\n");
	this->camera->print();

	printf("---------------------------------------\n");
	printf("Lights:\n");
	for (int i = 0; i < this->lights.size(); i++)
	{
		this->lights[i]->print();
	}

	printf("---------------------------------------\n");
	printf("Materials:\n");
	for (int i = 0; i < this->materials.size(); i++)
	{
		Vector3 ka = this->materials[i]->ka;
		printf("Material %d ka = [%f %f %f]\n", i, ka.c[0], ka.c[1], ka.c[2]);
	}

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

void Scene::addLight(Light* light)
{
	this->lights.push_back(light);
}

void Scene::printLights()
{
	for (int i = 0; i < this->lights.size(); i++)
	{
		this->lights[i]->print();
	}
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

	if (minDist != -1)
		hp.intersectionPoint = (ray.getOrigin() + (ray.getDirection() * hp.dist));

	return hp;
}

Vector3 Scene::colorPointBasedOnShadow(HitPoint hp)
{
	Vector3 returnColor = Vector3(0, 0, 0); //Black
	Material* objMat = this->materials[hp.materialID];

	for (unsigned int i = 0; i < this->lights.size(); i++)
	{
		unsigned int distFromLight = this->lights[i]->getPosition().distance(hp.intersectionPoint);
		Material* lightMat = this->materials[this->lights[i]->getMaterialID()];

		Vector3 lightNorm = (this->lights[i]->getPosition() - hp.intersectionPoint).normalize();

		Ray rayToLight = Ray(hp.intersectionPoint + LIGHT_RAY_JITTER*lightNorm, lightNorm);
		float dotProd = lightNorm.dot(hp.normal);
		
		if (dotProd < 0)
			dotProd = 0;

		//Ambient
		Vector3 ambient = lightMat->ka * objMat->ka;
		returnColor += ambient;

		if (getFirstRayIntersection(rayToLight).dist < distFromLight)
			continue;

		//Diffuse
		Vector3 diffuse = objMat->kd * (dotProd)* lightMat->kd; // TODO Times light intesnity
		returnColor += diffuse;

		//Specular
		Vector3 lightReflectVector = 2 * dotProd * hp.normal - rayToLight.getDirection();
		Vector3 vecToCamera = (this->camera->getOrigin() - rayToLight.getOrigin()).normalize();

		Vector3 specular = objMat->ks * pow(vecToCamera.dot(lightReflectVector), objMat->shiny) * lightMat->ks; // TODO times light intensity
		returnColor += specular;
	}

	return returnColor;
}

unsigned int Scene::getNumObjectsInScene()
{
	return this->objects.size();
}