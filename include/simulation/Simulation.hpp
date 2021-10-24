#ifndef SIMULATION_H
#define SIMULATION_H

#include <SFML/Graphics.hpp>
#include <list>
#include <functional>
#include <iostream>
#include <memory>

#include "simulation/Planet.hpp"
#include "common/EventHandler.hpp"
#include "physics/Vector2d.hpp"
#include "simulation/RenderObjectsContainer.hpp"
#include "render/Renderer.hpp"

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

	void addPoint(sf::Vector2i vector, float m = 10,
				  std::shared_ptr<sf::Texture> t = Config::PLANET_1_TEXTURE);
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
//	ev_manager.addMousePressedCallback(sf::Mouse::Left, [&](sfev::CstEv) {
//		addPoint(sf::Mouse::getPosition(win));
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

	ev_manager.addKeyPressedCallback(sf::Keyboard::Num1, [&](sfev::CstEv) {
		addPoint(sf::Mouse::getPosition(win), 1000, Config::PLANET_1_TEXTURE);
	});

	ev_manager.addKeyPressedCallback(sf::Keyboard::Num2, [&](sfev::CstEv) {
		addPoint(sf::Mouse::getPosition(win), 500, Config::PLANET_2_TEXTURE);
	});

	ev_manager.addKeyPressedCallback(sf::Keyboard::Num3, [&](sfev::CstEv) {
		addPoint(sf::Mouse::getPosition(win), 1000, Config::PLANET_3_TEXTURE);
	});

	ev_manager.addKeyPressedCallback(sf::Keyboard::Num4, [&](sfev::CstEv) {
		addPoint(sf::Mouse::getPosition(win), 5000, Config::PLANET_4_TEXTURE);
	});

	ev_manager.addKeyPressedCallback(sf::Keyboard::Num5, [&](sfev::CstEv) {
		addPoint(sf::Mouse::getPosition(win), 100, Config::PLANET_5_TEXTURE);
	});

	ev_manager.addKeyPressedCallback(sf::Keyboard::Num6, [&](sfev::CstEv) {
		addPoint(sf::Mouse::getPosition(win), 1000, Config::PLANET_6_TEXTURE);
	});

	ev_manager.addKeyPressedCallback(sf::Keyboard::Num7, [&](sfev::CstEv) {
		addPoint(sf::Mouse::getPosition(win), 20000, Config::BLACK_HOLE_TEXTURE);
	});
}

void Simulation::addPoint(sf::Vector2i mousePos, float m, std::shared_ptr<sf::Texture> t)
{
	this->objContainer.PlanetsObjects.push_back(Planet(SWVector2D::Vector2D(mousePos), t, m));
}

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

		// heavy planet
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
//				p1.velocity.x = (0.03 * p2.mass / (d*d) * (p2.position.x - p1.position.x)/d)*5;
//				p2.velocity.y = (0.03 * p2.mass / (d*d) * (p2.position.y - p1.position.y)/d)*5;
				vec.x += (0.03 * p2.mass / (d*d) * (p2.position.x - p1.position.x)/d)*5;
				vec.y += (0.03 * p2.mass / (d*d) * (p2.position.y - p1.position.y)/d)*5;
			}
			else
			{
				collision = true;
			}
		}

//		if(!collision)
//		{
			p1.update(vec);
			p1.move();
//		}
//		else
//			objContainer.PlanetsObjects.erase(objContainer.PlanetsObjects.begin()+i);
	}
}

void Simulation::processEvents()
{
	ev_manager.processEvents();
}

#endif // SIMULATION_H
