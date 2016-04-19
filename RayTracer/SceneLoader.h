#include "libs\vector\GenVector.h"
#include "libs\objload\objLoader.h"
#include "Scene.h"
#include "Sphere.h"
#include "Triangle.h"
#include "Light.h"

Vector3 objToGenVec(obj_vector const * objVec)
{
	Vector3 v;
	v[0] = objVec->e[0];
	v[1] = objVec->e[1];
	v[2] = objVec->e[2];
	return v;
}

Vector3 materialArrayToVec(double arr[3])
{
	return Vector3(arr[0], arr[1], arr[2]);
}

BVHTreeNode* setupBVHTree(PrimitiveGeometry** primArray, unsigned int size)
{
	if (size == 0)
		return NULL;
	if (size == 1)
		return new BVHTreeNode(primArray[0]);

	AABB* bigBB = new AABB(primArray, size);

	// Find dimension to split on
	unsigned int splitI = (bigBB->bbMax - bigBB->bbMin).maxMagnitudeComponent();

	// Split is going to be the average
	float split = (bigBB->bbMax[splitI] + bigBB->bbMin[splitI]) / 2.0f;

	// Split array
	PrimitiveGeometry** leftArr = new PrimitiveGeometry*[size]();
	PrimitiveGeometry** rightArr = new PrimitiveGeometry*[size]();
	unsigned int leftI = 0;
	unsigned int rightI = 0;
	for (unsigned int i = 0; i < size; i++)
	{
		if (primArray[i]->getCenter()[splitI] < split)
			leftArr[leftI++] = primArray[i];
		else
			rightArr[rightI++] = primArray[i];
	}

	// Handle the case where all of the objects got put on one side
	if (leftI == 0)
	{
		rightI--;
		leftArr[0] = rightArr[rightI];
		leftI++;
	}
	else if (rightI == 0)
	{
		leftI--;
		rightArr[0] = leftArr[leftI];
		rightI++;
	}

	// Create and return node
	BVHTreeNode* thisNode = new BVHTreeNode(bigBB);
	thisNode->setLeft(setupBVHTree(leftArr, leftI));
	thisNode->setRight(setupBVHTree(rightArr, rightI));

	return thisNode;
}

void loadScene(Scene* scene, char* file)
{
	//Load *.obj from file argv1
	objLoader objData = objLoader();
	objData.load(file);

	bool missingCamera = objData.camera == NULL;
	if (!missingCamera)
	{
		//Create a camera object
		Vector3 camOrigin = Vector3(objData.vertexList[objData.camera->camera_pos_index]->e[0],
			objData.vertexList[objData.camera->camera_pos_index]->e[1],
			objData.vertexList[objData.camera->camera_pos_index]->e[2]
			);
		Vector3 camLook = Vector3(objData.vertexList[objData.camera->camera_look_point_index]->e[0],
			objData.vertexList[objData.camera->camera_look_point_index]->e[1],
			objData.vertexList[objData.camera->camera_look_point_index]->e[2]
			);
		Vector3 camUp = Vector3(objData.normalList[objData.camera->camera_up_norm_index]->e[0],
			objData.normalList[objData.camera->camera_up_norm_index]->e[1],
			objData.normalList[objData.camera->camera_up_norm_index]->e[2]
			);
		scene->setCamera(new Camera(camOrigin, camLook, camUp));
	}

	//Create materials
	scene->addMaterial(new Material()); // Default material
	for (int i = 0; i < objData.materialCount; i++)
	{
		obj_material* objMat = objData.materialList[i];

		Material* material = new Material(objMat->shiny, objMat->reflect);

		material->ka = materialArrayToVec(objMat->amb);
		material->kd = materialArrayToVec(objMat->diff);
		material->ks = materialArrayToVec(objMat->spec);

		scene->addMaterial(material);
	}

	//Add lights to scene
	for (int i = 0; i < objData.lightPointCount; i++)
	{
		obj_light_point* objLight = objData.lightPointList[i];

		Vector3 lightPos = objToGenVec(objData.vertexList[objLight->pos_index]);
		unsigned int materialID = objLight->material_index + 1;

		scene->addLight(new Light(lightPos, materialID));
	}

	//Gather geometry primitives into an array
	unsigned int numObjects = objData.sphereCount + objData.faceCount;
	PrimitiveGeometry** objects = new PrimitiveGeometry*[numObjects]();

	for (int i = 0; i < objData.sphereCount; i++) // Add spheres to array...
	{
		Vector3 spherePosVector = objToGenVec(objData.vertexList[objData.sphereList[i]->pos_index]);
		Vector3 sphereUpVector = objToGenVec(objData.normalList[objData.sphereList[i]->up_normal_index]);

		objects[i] = new Sphere(objData.sphereList[i]->material_index + 1, spherePosVector, sphereUpVector.length());
	}

	for (int i = 0; i < objData.faceCount; i++) // Add triangles to array...
	{
		int* vertices = objData.faceList[i]->vertex_index;
		Vector3 v0 = objToGenVec(objData.vertexList[vertices[0]]);
		Vector3 v1 = objToGenVec(objData.vertexList[vertices[1]]);
		Vector3 v2 = objToGenVec(objData.vertexList[vertices[2]]);

		objects[i + objData.sphereCount] = new Triangle(objData.faceList[i]->material_index + 1, v0, v1, v2);
	}

	// Create a BVH tree from the array 
	printf("Building BVH tree...\n");

	scene->setObjectTreeHead(setupBVHTree(objects, numObjects));
	printf("Finished. Number of nodes: %d\n", scene->getNumNodes());

	// Handle missing camera/light
	bool noLight = objData.lightPointCount == 0;
	if (missingCamera || noLight)
	{
		AABB sceneBounds = AABB(objects, numObjects);

		if (missingCamera)
		{
			printf("WARNING: Camera missing from *.obj file, inserting default camera...\n");
			Vector3 camLook = sceneBounds.getCenter();
			Vector3 camLocation = sceneBounds.getCenter() - ((sceneBounds.getMaxBound(2) * 1.6f) * Vector3(0, 0, 1)) - ((sceneBounds.getMaxBound(0) * 0.5f) * Vector3(1, 0, 0));

			scene->setCamera(new Camera(camLocation, camLook, Vector3(0, 1, 0)));
		}

		if (noLight)
		{
			printf("WARNING: No light sources in *.obj file, inserting default light sources...\n");

			// Add light material
			Vector3 ka = Vector3(1.8f, 1.5f, 0.9f);
			Vector3 kd = Vector3(14.4f, 12.0f, 7.2f);
			Vector3 ks = Vector3(2.0f, 2.0f, 2.0f);
			scene->addMaterial(new Material(ka, kd, ks));

			scene->addLight(new Light(sceneBounds.getCenter(), objData.materialCount+1));
			scene->addLight(new Light(scene->getCamera()->getOrigin(), objData.materialCount + 1));
		}
	}
}