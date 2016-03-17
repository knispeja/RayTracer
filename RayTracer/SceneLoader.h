#include "libs\vector\GenVector.h"
#include "libs\objload\objLoader.h"
#include "Scene.h"
#include "Sphere.h"
#include "Triangle.h"

Vector3 objToGenVec(obj_vector const * objVec)
{
	Vector3 v;
	v[0] = objVec->e[0];
	v[1] = objVec->e[1];
	v[2] = objVec->e[2];
	return v;
}

void loadScene(Scene* scene, char* file)
{
	//Load *.obj from file argv1
	objLoader objData = objLoader();
	objData.load(file);

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

	//Create materials
	scene->addMaterial(new Material()); // Default material
	for (int i = 0; i < objData.materialCount; i++)
	{
		Material* material = new Material();
		obj_material* objMat = objData.materialList[i];

		// TODO setup material
		//material->ka = objMat->amb;

		scene->addMaterial(material);
	}

	// Add primitives to scene
	for (int i = 0; i < objData.sphereCount; i++) // Add spheres to scene...
	{
		Vector3 spherePosVector = objToGenVec(objData.vertexList[objData.sphereList[i]->pos_index]);
		Vector3 sphereUpVector = objToGenVec(objData.normalList[objData.sphereList[i]->up_normal_index]);

		Material* mat = scene->getMaterial(objData.sphereList[i]->material_index + 1);

		scene->addObjectToScene(new Sphere(mat, spherePosVector, sphereUpVector.length()));
	}

	for (int i = 0; i < objData.faceCount; i++) // Add triangles to scene...
	{
		int* vertices = objData.faceList[i]->vertex_index;
		Vector3 v0 = objToGenVec(objData.vertexList[vertices[0]]);
		Vector3 v1 = objToGenVec(objData.vertexList[vertices[1]]);
		Vector3 v2 = objToGenVec(objData.vertexList[vertices[2]]);

		Material* mat = scene->getMaterial(objData.faceList[i]->material_index + 1);

		scene->addObjectToScene(new Triangle(mat, v0, v1, v2));
	}
}