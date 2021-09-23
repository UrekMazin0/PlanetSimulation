#ifndef SIMULATION_H
#define SIMULATION_H

#include <SFML/Graphics.hpp>
#include <list>
#include <functional>
#include <iostream>

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
	bool checkMousePointCollision(sf::Vector2i mousePos);

	void processEvents();

	void render(sf::RenderTarget& target);

private:

	Point* _mouseBoundPoint = nullptr;
	void _moveBoundPoint(sf::Vector2i mousePos);
};

void Simulation::initEventCallbacks()
{
	ev_manager.addMousePressedCallback(sf::Mouse::Left, [&](sfev::CstEv) {
		this->addPoint(sf::Mouse::getPosition(win));
	});

	ev_manager.addMousePressedCallback(sf::Mouse::Right, [&](sfev::CstEv) {
		if(checkMousePointCollision(sf::Mouse::getPosition(win))){
			ev_manager.addEventCallback(sf::Event::MouseMoved, [&](sfev::CstEv) {
				_moveBoundPoint(sf::Mouse::getPosition());
			});
		}
	});

	ev_manager.addMouseReleasedCallback(sf::Mouse::Right, [&](sfev::CstEv) {
		_mouseBoundPoint = nullptr;
		ev_manager.removeCallback(sf::Event::MouseMoved);
	});

	ev_manager.addKeyPressedCallback(sf::Keyboard::Space, [&](sfev::CstEv) {
		objContainer.clearObjects();
	});

	ev_manager.addEventCallback(sf::Event::Closed, [this](sfev::CstEv) {
		ev_manager.getWindow().close();
	});

	ev_manager.addKeyPressedCallback(sf::Keyboard::Escape, [this](sfev::CstEv) {
		ev_manager.getWindow().close();
	});
}

void Simulation::addPoint(sf::Vector2i mousePos)
{
	this->objContainer.PointObjects.push_back(SWVector2D::Vector2D(mousePos));
}

bool Simulation::checkMousePointCollision(sf::Vector2i mousePos)
{
	for(Point &point : objContainer.PointObjects)
	{
		if(point.checkVectorCollision(SWVector2D::Vector2D(mousePos)))
		{
			_mouseBoundPoint = &point;
			return true;
		}
	}
	return false;
}

void Simulation::processEvents()
{
	ev_manager.processEvents();
}

void Simulation::render(sf::RenderTarget& target)
{
	renderer.render(target, this->objContainer);
}

void Simulation::_moveBoundPoint(sf::Vector2i mousePos)
{
	if(_mouseBoundPoint != nullptr)
		_mouseBoundPoint->setPosition(SWVector2D::Vector2D(mousePos));
}

#endif // SIMULATION_H
