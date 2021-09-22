#ifndef RENDERER_H
#define RENDERER_H

#include <SFML/Graphics.hpp>

#include "simulation/RenderObjectsContainer.hpp"
#include "simulation/point.hpp"

using RenObjCon = RenderObjectsContainers;

struct Renderer
{
	Renderer()
	{

	}

	~Renderer()
	{}

	void render(sf::RenderTarget& target, RenObjCon& objCon);
};

void Renderer::render(sf::RenderTarget& target, RenObjCon& objCon)
{
	for(const Point & point : objCon.PointObjects)
	{
		point.drawPointSFMLWindow(target);
	}
}
//	const sf::RenderStates& rs = vp_handler.getRenderState();
//	// Draw background;
//	sf::RectangleShape ground(sf::Vector2f(world.size.x, world.size.y));
//	ground.setFillColor(sf::Color::Black);
//	target.draw(ground, rs);
//	// Draw world
//	world.render(target, rs);
//	// Draw ants and colonies
//	for (ColonyRenderer& colony : colonies) {
//		if (render_ants) {
//			colony.renderAnts(target, rs);
//		}
//		colony.render(target, rs);
//	}
//	// Render UI elements
//	for (ColonyRenderer& colony : colonies) {
//		colony.render_charts(target);
//	}

#endif // RENDERER_H
