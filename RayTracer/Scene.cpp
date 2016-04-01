#include "Scene.h"

#include <vector>
using namespace std;

Scene::Scene()
{
	this->materials = vector<Material*>();

	this->camera = NULL;
}

Scene::~Scene()
{
	deallocCamera();

	// Dealloc all materials in this->materials
	for (int i = 0; i < (this->materials.size()); i++)
		delete this->materials[i];

	// Dealloc all lights in this->lights
	for (int i = 0; i < (this->lights.size()); i++)
		delete this->lights[i];

	// Dealloc all geometries in the scene
	if (this->objectTree != NULL)
		delete(this->objectTree);

	//for (int i = 0; i < (this->objects.size()); i++) //TODO: dealloc tree?
	//{
	//	if (this->objects[i] != NULL)
	//		delete this->objects[i];
	//	else
	//		printf("Object %d in Scene was NULL for some reason...", i);
	//}
}

void Scene::setCamera(Camera* camera)
{
	deallocCamera();
	this->camera = camera;
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
		printf("Material %d ka = [%f %f %f]\n", i, ka[0], ka[1], ka[2]);
	}

	printf("---------------------------------------\n");
	printf("Geometries:\n");
	//for (int i = 0; i < (this->objects.size()); i++)
	//{
	//	this->objects[i]->print(); TODO: fix
	//}
}

void Scene::addMaterial(Material* mat)
{
	printf("added material %d with ka %f %f %f\n", this->materials.size(), mat->ka[0], mat->ka[1], mat->ka[2]);
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

void Scene::setObjectTreeHead(BVHTreeNode* head)
{
	this->objectTree = head;
	//this->objectTree->print();
}

bool Scene::getFirstRayIntersection(Ray ray, HitPoint& hit)
{
	if (this->objectTree->intersectsWithRay(ray, hit))
	{
		hit.intersectionPoint = (ray.getOrigin() + (ray.getDirection() * hit.dist)) + hit.normal * LIGHT_RAY_JITTER;
		return true;
	}

	return false;
}

Vector3 Scene::colorPointBasedOnShadow(Ray hitRay, HitPoint hp, unsigned int recursiveDepth)
{
	Vector3 returnColor = COLOR_OF_NOTHINGNESS;
	Material* objMat = this->materials[hp.materialID];

	for (unsigned int i = 0; i < this->lights.size(); i++)
	{
		unsigned int distFromLight = this->lights[i]->getPosition().distance(hp.intersectionPoint);
		Material* lightMat = this->materials[this->lights[i]->getMaterialID()];

		Vector3 lightNorm = (this->lights[i]->getPosition() - hp.intersectionPoint).normalize();

		Ray rayToLight = Ray(hp.intersectionPoint, lightNorm);
		float dotProd = lightNorm.dot(hp.normal);
		
		if (dotProd < 0)
			dotProd = 0;

		//Ambient
		Vector3 ambient = lightMat->ka * objMat->ka;
		returnColor += ambient;

		// Continue to next light immediately if in shadow by this light
		HitPoint lightHP = HitPoint(); 
		if (getFirstRayIntersection(rayToLight, lightHP))
			if (lightHP.dist < distFromLight)
				continue;

		//Diffuse
		Vector3 diffuse = objMat->kd * (dotProd)* lightMat->kd;
		returnColor += diffuse;

		//Specular
		Vector3 lightReflectVector = 2 * dotProd * hp.normal - rayToLight.getDirection();
		Vector3 vecToCamera = (this->camera->getOrigin() - rayToLight.getOrigin()).normalize();

		Vector3 specular = objMat->ks * pow(vecToCamera.dot(lightReflectVector), objMat->shiny) * lightMat->ks;
		returnColor += specular;
	}

	return traceReflection(hitRay, hp, returnColor, recursiveDepth);
}

Vector3 Scene::traceReflection(Ray reflectRay, HitPoint reflectPt, Vector3 colorWOReflection, unsigned int recursiveDepth)
{
	Material* objMat = this->materials[reflectPt.materialID];

	// Return if the surface is not reflective or if we've reached the maximum allowable recursion depth
	if (objMat->reflect == 0 || recursiveDepth > MAX_REFLECTION_RECURSION_DEPTH)
		return colorWOReflection;

	Vector3 reflectedRayDir = reflectRay.getDirection().reflect(reflectPt.normal);
	Ray reflectedRay = Ray(reflectPt.intersectionPoint, reflectedRayDir);

	Vector3 reflectColor = COLOR_OF_NOTHINGNESS;
	HitPoint hp = HitPoint();
	if (getFirstRayIntersection(reflectedRay, hp))
		reflectColor = colorPointBasedOnShadow(reflectedRay, hp, recursiveDepth + 1);

	return (colorWOReflection * (1 - objMat->reflect)) + (reflectColor * objMat->reflect);
}

unsigned int Scene::getNumObjectsInScene()
{
	return -1; //TODO: fix
	//return this->objects.size();
}