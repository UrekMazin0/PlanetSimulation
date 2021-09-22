#ifndef ROC
#define ROC

#include <list>

#include "simulation/point.hpp"

struct RenderObjectsContainers
{
	std::list<Point> PointObjects;

	RenderObjectsContainers()
		: PointObjects()
	{

	}

	void clearObjects()
	{
		this->PointObjects.clear();
	}
};

#endif // ROC
