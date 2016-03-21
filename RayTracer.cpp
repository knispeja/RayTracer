//Hard code resolution for now
#define RES 100
#define _USE_MATH_DEFINES //This enables math constants in Windows

#include <math.h> //Math functions and some constants

#include "RayTracer/Ray.h"
#include "RayTracer/RayGenerator.h"
#include "RayTracer/Camera.h"
#include "RayTracer/Scene.h"

#include "RayTracer/libs/png/simplePNG.h"
#include "Buffer.h"

#include "RayTracer/SceneLoader.h"

int main(int argc, char ** argv)
{
	//Create buffer
	Buffer<Color> buffer = Buffer<Color>(RES, RES);
	Buffer<Vector3> floatbuffer = Buffer<Vector3>(RES, RES);

	//Need at least two arguments (*.obj input, *.png output)
	if (argc < 3)
	{
		printf("Usage %s input.obj output.png\n", argv[0]);
		exit(0);
	}

	//Create and add objects to the scene
	Scene scene = Scene();
	loadScene(&scene, argv[1]);
	scene.printObjects(); // Print everything in the scene for testing

	//Create a ray generator for the camera
	RayGenerator generator = RayGenerator(scene.getCamera(), RES, RES);

	//Test ray generator by changing pixel colors

	float maxComponent = -1;
	for (unsigned int y = 0; y < RES; y++)
	{
		for (unsigned int x = 0; x < RES; x++)
		{
			Ray r = generator.getRay(x, y);
			HitPoint hp = scene.getFirstRayIntersection(r);
			Vector3 c;
			if (hp.dist < 0)
				c = Vector3(0, 0, 0);
			else
				c = scene.colorPointBasedOnShadow(hp);

			// Keeping track of the maximum component for tone mapping later
			if (maxComponent < c.maxComponent())
				maxComponent = c.maxComponent();

			floatbuffer.at(x, y) = c;
		}
	}

	// Scaling/tone mapping
	for (unsigned int y = 0; y < RES; y++)
	{
		for (unsigned int x = 0; x < RES; x++)
		{
			for (unsigned int i = 0; i < 3; i++)
				floatbuffer.at(x, y).c[i] *= (255.0f / maxComponent);

			buffer.at(x, y) = Color(floatbuffer.at(x, y).c[0], floatbuffer.at(x, y).c[1], floatbuffer.at(x, y).c[2]);
		}
	}

	//Write output buffer to file argv2
	simplePNG_write(argv[2], buffer.getWidth(), buffer.getHeight(), (unsigned char*)&buffer.at(0, 0));
	
	return 0;
}