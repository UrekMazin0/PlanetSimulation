#ifndef SIMULATION_H
#define SIMULATION_H

#include <SFML/Graphics.hpp>
#include <list>

#include "simulation/point.hpp"
#include "common/event_handler.hpp"
#include "physics/vector2d.hpp"
#include "simulation/RenderObjectsContainer.hpp"
#include "render/renderer.hpp"

using PointList = std::list<Point>;
using RenObjCon = RenderObjectsContainers;

class Simulation
{
public:
	sfev::EventManager ev_manager;
	sf::Window& win;
	RenObjCon objContainer;
	Renderer renderer;

	Simulation(sf::Window& window)
		: ev_manager(window, true)
		, win(window)
		, renderer()
		, objContainer()
	{
		initEventCallbacks();
	}

	~Simulation(){}

	void initEventCallbacks();

	void addPoint(sf::Vector2i vector);

	void processEvents();

	void render(sf::RenderTarget& target);
};

void Simulation::initEventCallbacks()
{
	ev_manager.addMouseReleasedCallback(sf::Mouse::Left, [&](sfev::CstEv) {
		this->addPoint(sf::Mouse::getPosition(win));
	});

	ev_manager.addEventCallback(sf::Event::Closed, [this](sfev::CstEv) {
		ev_manager.getWindow().close();
	});

	ev_manager.addKeyPressedCallback(sf::Keyboard::Escape, [this](sfev::CstEv) {
		ev_manager.getWindow().close();
	});
}

void Simulation::addPoint(sf::Vector2i vector)
{
	this->objContainer.PointObjects.push_back(SWVector2D::Vector2D(vector));
}

void Simulation::processEvents()
{
	ev_manager.processEvents();
}

void Simulation::render(sf::RenderTarget& target)
{
	renderer.render(target, this->objContainer);
}

#endif // SIMULATION_H
