#pragma once

#include "Material.h"
#include "HitPoint.h"
#include "PrimitiveGeometry.h"
#include "Ray.h"

class BVHTreeNode : public PrimitiveGeometry
{
public:
public:
	BVHTreeNode(PrimitiveGeometry* geom)
	{
		this->left = NULL;
		this->right = NULL;
		this->geom = geom;
	}

	~BVHTreeNode()
	{
		//Nothing to delete TODO: delete left/right?
	}

	virtual char* getGeometryTypeName() const
	{
		return "Tree";
	}

	virtual void printOtherData() const
	{
		printf("---- merp");
	}

	virtual HitPoint intersectWithRay(Ray ray) const
	{
		return HitPoint();
	}

	virtual Vector3 getCenter() const
	{
		return Vector3();
	}

private:
	BVHTreeNode* left;
	BVHTreeNode* right;
	PrimitiveGeometry* geom;
};

