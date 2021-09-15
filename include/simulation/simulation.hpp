#ifndef SIMULATION_H
#define SIMULATION_H

#include <SFML/Graphics.hpp>
#include <list>

#include "simulation/point.hpp"
#include "common/event_handler.hpp"
#include "physics/vector2d.hpp"
#include "simulation/RenderObjectsContainer.hpp"

using PointList = std::list<Point>;

class Simulation
{
	sfev::EventManager ev_manager;
	sf::Window& win;
	PointList pointStorage;

	Simulation(sf::Window& window)
		: ev_manager(window, true)
		, win(window)
		, pointStorage()
	{
		initEventCallbacks();
	}

	~Simulation();

	void initEventCallbacks()
	{
		ev_manager.addMouseReleasedCallback(sf::Mouse::Left, [&](sfev::CstEv) {
			this->addPoint(sf::Mouse::getPosition(win));
		});
	}

	void addPoint(sf::Vector2i vector)
	{
		this->pointStorage.push_back(SWVector2D::Vector2D(vector));
	}
};

#endif // SIMULATION_H
