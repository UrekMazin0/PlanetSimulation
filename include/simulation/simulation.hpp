#ifndef SIMULATION_H
#define SIMULATION_H

#include <SFML/Graphics.hpp>
#include <list>
#include <functional>
#include <iostream>
#include <memory>

#include "simulation/point.hpp"
#include "common/event_handler.hpp"
#include "physics/vector2d.hpp"
#include "simulation/RenderObjectsContainer.hpp"
#include "render/renderer.hpp"

using PointList = std::list<Planet>;
using RenObjCon = RenderObjectsContainers;

class Simulation
{
public:

	Simulation(sf::Window& window);

	~Simulation(){}

	sfev::EventManager ev_manager;
	sf::Window& win;
	RenObjCon objContainer;
	Renderer renderer;

	void initEventCallbacks();

	void addPoint(sf::Vector2i vector, float m = 10);
	bool checkMousePointCollision(sf::Vector2i mousePos);

	void processEvents();

	void render(sf::RenderTarget& target);
	void update(float dt);

private:

//	Point* _mouseBoundPoint = nullptr;
	void _moveBoundPoint(sf::Vector2i mousePos);

	bool pause = false;
};

Simulation::Simulation(sf::Window &window)
	: ev_manager(window, true)
	, win(window)
	, renderer()
	, objContainer()
{
//	addPoint();
	initEventCallbacks();
}

void Simulation::initEventCallbacks()
{
	ev_manager.addMousePressedCallback(sf::Mouse::Left, [&](sfev::CstEv) {
		addPoint(sf::Mouse::getPosition(win));
	});

//	ev_manager.addMousePressedCallback(sf::Mouse::Right, [&](sfev::CstEv) {
//		if(checkMousePointCollision(sf::Mouse::getPosition(win))){
//			ev_manager.addEventCallback(sf::Event::MouseMoved, [&](sfev::CstEv) {
//				_moveBoundPoint(sf::Mouse::getPosition());
//			});
//		}
//	});

//	ev_manager.addMouseReleasedCallback(sf::Mouse::Right, [&](sfev::CstEv) {
//		_mouseBoundPoint = nullptr;
//		ev_manager.removeCallback(sf::Event::MouseMoved);
//	});

	ev_manager.addKeyPressedCallback(sf::Keyboard::Space, [&](sfev::CstEv) {
		objContainer.clearObjects();
	});

	ev_manager.addEventCallback(sf::Event::Closed, [this](sfev::CstEv) {
		ev_manager.getWindow().close();
	});

	ev_manager.addKeyPressedCallback(sf::Keyboard::Escape, [this](sfev::CstEv) {
		ev_manager.getWindow().close();
	});

	ev_manager.addKeyPressedCallback(sf::Keyboard::B, [&](sfev::CstEv) {
		addPoint(sf::Mouse::getPosition(win), 10000);
	});
}

void Simulation::addPoint(sf::Vector2i mousePos, float m)
{
	this->objContainer.PlanetsObjects.push_back(Planet(SWVector2D::Vector2D(mousePos), m));
}

//bool Simulation::checkMousePointCollision(sf::Vector2i mousePos)
//{
//	for(auto &point : objContainer.PointObjects)
//	{
//		if(point->checkVectorCollision(SWVector2D::Vector2D(mousePos)))
//		{
//			_mouseBoundPoint = &point;
//			return true;
//		}
//	}
//	return false;
//}

void Simulation::render(sf::RenderTarget& target)
{
	renderer.render(target, this->objContainer);
}

void Simulation::update(float dt)
{
	if(this->pause)
		return;

	for(auto i = 0; i < objContainer.PlanetsObjects.size(); i++)
	{
		Planet &p1 = objContainer.PlanetsObjects[i];

		if(p1.mass >= 10000)
			continue;

		SWVector2D::Vector2D vec = SWVector2D::Vector2D::Zero();
		bool collision = false;

		for(auto j = 0; j <objContainer.PlanetsObjects.size(); j++)
		{
			const Planet &p2 = objContainer.PlanetsObjects[j];

			if(i == j)
				continue;

			float d = Planet::Distance(p1, p2);

			if( d > p1.Radius())
			{
				vec.x += (0.03 * p2.mass / (d*d) * (p2.position.x - p1.position.x)/d)*5;
				vec.y += (0.03 * p2.mass / (d*d) * (p2.position.y - p1.position.y)/d)*5;
			}
			else
			{
				collision = true;
			}
		}

		if(!collision)
		{
			std::cout << vec.x << ":" << vec.y << std::endl;
			p1.move(vec);
		}
		else
			objContainer.PlanetsObjects.erase(objContainer.PlanetsObjects.begin()+i);
	}
}

//void Simulation::_moveBoundPoint(sf::Vector2i mousePos)
//{
//	if(_mouseBoundPoint != nullptr)
//		_mouseBoundPoint->setPosition(SWVector2D::Vector2D(mousePos));
//}

void Simulation::processEvents()
{
	ev_manager.processEvents();
}

#endif // SIMULATION_H
