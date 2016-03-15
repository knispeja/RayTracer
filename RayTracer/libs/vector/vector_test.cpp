#include "GenVector.h"

int main(int argc, char ** argv)
{
	Vector3 t = Vector3(0,1,0);
	Vector3 s = Vector3(1,0,0);
	Vector3 c = t.cross(s);

	printf("%f %f %f\n", c[0], c[1], c[2]);

	Color r = Color(255, 0, 0);
	Color g = Color(0, 255, 0);
	Color a = r + g;

	printf("%i %i %i\n", a[0], a[1], a[2]);

	return 0;
}
