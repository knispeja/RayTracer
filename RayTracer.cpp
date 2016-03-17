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
	Buffer buffer = Buffer(RES, RES);

	//Need at least two arguments (*.obj input, *.png output)
	if(argc < 3)
	{
		printf("Usage %s input.obj output.png\n", argv[0]);
		exit(0);
	}

	//Create and add objects to the scene
	Scene scene = Scene();
	loadScene(&scene, argv[1]);
	scene.printObjectsInScene(); // Print everything in the scene for testing

	//Create a ray generator for the camera
	RayGenerator generator = RayGenerator(scene.getCamera(), RES, RES);

	//Test ray generator by changing pixel colors
	for (int y = 0; y<RES; y++)
	{
		for (int x = 0; x<RES; x++)
		{
			Ray r = generator.getRay(x, y);
			HitPoint hp = scene.getFirstRayIntersection(r);

			Vector3 colorVec;
			if (hp.dist < 0)
				colorVec = r.getDirection();
			else
				colorVec = hp.normal;

			Color c;
			Vector3 d = colorVec*255.0f;
			c = Color(abs(d[0]), abs(d[1]), abs(d[2]));
			buffer.at(x, y) = c;
		}
	}

	//Write output buffer to file argv2
	simplePNG_write(argv[2], buffer.getWidth(), buffer.getHeight(), (unsigned char*)&buffer.at(0, 0));
	
	return 0;
}