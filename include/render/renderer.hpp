#ifndef RENDERER_H
#define RENDERER_H

#include <SFML/Graphics.hpp>

#include "simulation/RenderObjectsContainer.hpp"
#include "simulation/point.hpp"
#include "IDrawing.h"

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
	sf::Sprite sprite;
	sprite.setTexture(*Config::BACKGROUND_TEXTURE);
//	sprite.setScale(sf::Vector2f(sprite_scale, sprite_scale));
	target.draw(sprite);

	for(const auto & point : objCon.PlanetsObjects)
	{
		point.Draw(target);
	}
}
#endif // RENDERER_H
