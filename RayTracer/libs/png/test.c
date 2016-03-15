#include <stdio.h>
#include <stdlib.h>
#include "simplePNG.h"

int main (int argc, const char * argv[]) {
	unsigned int w = 4;
	unsigned int h = 4;
	unsigned char * im;
	im = (unsigned char *) malloc( w * h * 3);
	for(int i=0; i<4; i++)
	{
		for(int j=0; j<4; j++)
		{
			im[i*4*3+j*3+0] = j*80;
			im[i*4*3+j*3+1] = i*80;
			im[i*4*3+j*3+2] = 150;
		}
	}
	simplePNG_write("test.png", w, h, im);
	printf("Writing: test.png\n", argv[0]);
	
    return 0;
}
