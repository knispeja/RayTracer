#pragma once

#include "PrimitiveGeometry.h"
#include "Ray.h"

class BVHTreeNode : public PrimitiveGeometry
{
public:
	BVHTreeNode(PrimitiveGeometry* geom)
	{
		this->left = NULL;
		this->right = NULL;
		this->geom = geom;
	}

	~BVHTreeNode()
	{
		if (this->left != NULL)
			delete(this->left);
		if (this->right != NULL)
			delete(this->right);
		delete(this->geom);
	}

	void setLeft(BVHTreeNode* left)
	{
		this->left = left;
	}

	void setRight(BVHTreeNode* right)
	{
		this->right = right;
	}

	virtual char* getGeometryTypeName() const
	{
		return "BVH Tree";
	}

	virtual void printOtherData() const
	{
		printf("BVH:\nObject:");
		this->geom->print();

		if (this->left != NULL)
		{
			printf("\nLeft:");
			this->left->printOtherData();
			printf("\n");
		}
		if (this->right != NULL)
		{
			printf("\nRight:");
			this->right->printOtherData();
			printf("\n");
		}
	}

	virtual bool intersectsWithRay(Ray ray, HitPoint& hit) const
	{
		if (this->geom->intersectsWithRay(ray, hit))
		{
			if (isLeaf())
				return true;

			HitPoint leftHP = HitPoint();
			bool leftSucc = this->left == NULL ? false : this->left->intersectsWithRay(ray, leftHP);

			HitPoint rightHP = HitPoint();
			bool rightSucc = this-> right == NULL ? false : this->right->intersectsWithRay(ray, rightHP);

			if (leftSucc)
			{
				if (rightSucc && leftHP.dist > rightHP.dist)
					hit = rightHP;
				else
					hit = leftHP;

				return true;
			}

			if (rightSucc)
				hit = rightHP;
			return rightSucc;
		}
		return false;
	}

	virtual Vector3 getCenter() const
	{
		return this->geom->getCenter();
	}

	virtual float getMinBound(unsigned int dim)
	{
		return this->geom->getMinBound(dim);
	}

	virtual float getMaxBound(unsigned int dim)
	{
		return this->geom->getMaxBound(dim);
	}

	bool isLeaf() const
	{
		return (this->left == NULL && this->right == NULL);
	}

private:
	BVHTreeNode* left;
	BVHTreeNode* right;
	PrimitiveGeometry* geom;
};

