#ifndef ROC
#define ROC

#include <vector>
#include <memory>

#include "simulation/Planet.hpp"

struct RenderObjectsContainers
{
	std::vector<Planet> PlanetsObjects;

	RenderObjectsContainers()
		: PlanetsObjects()
	{

	}

	void clearObjects()
	{
		this->PlanetsObjects.clear();
	}
};

#endif // ROC
