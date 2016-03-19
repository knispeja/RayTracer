#pragma once

#include "libs\vector\GenVector.h"

class Light
{
public:
	Light(Vector3 position, unsigned int materialID)
	{
		this->position = position;
		this->materialID = materialID;
	}

	~Light()
	{
		//Nothing to dispose
	}

	void print()
	{
		printf("Light at pos (%f %f %f)\n", this->position.c[0], this->position.c[1], this->position.c[2]);
	}

	Vector3 getPosition()
	{
		return this->position;
	}

	unsigned int getMaterialID()
	{
		return this->materialID;
	}

	/*Vector3 getKa()
	{
		return this->ka;
	}

	Vector3 getKd()
	{
		return this->kd;
	}

	Vector3 getKs()
	{
		return this->ks;
	}*/

private:
	Vector3 position;
	unsigned int materialID;
};

