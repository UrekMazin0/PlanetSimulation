#ifndef RENDERER_H
#define RENDERER_H

#include <SFML/Graphics.hpp>
#include <memory>

#include "simulation/RenderObjectsContainer.hpp"
#include "simulation/Planet.hpp"
#include "IDrawing.h"

using RenObjCon = RenderObjectsContainers;

class Renderer
{
public:
	Renderer()
	{

	}

	~Renderer()
	{}

	void render(sf::RenderTarget& target, RenObjCon& objCon);
	void setScales(std::shared_ptr<sf::Texture> BG_TEXTURE);

private:
	std::shared_ptr<sf::Texture> BACKGROUND_TEXTURE;
	sf::Sprite backgroundSprite;
	float scaleXBackground;
	float scaleYBackground;
};

void Renderer::render(sf::RenderTarget& target, RenObjCon& objCon)
{
	target.draw(backgroundSprite);

	for(const auto & point : objCon.PlanetsObjects)
	{
		point.Draw(target);
	}
}

void Renderer::setScales(std::shared_ptr<sf::Texture> BG_TEXTURE)
{
	this->BACKGROUND_TEXTURE = BG_TEXTURE;

	scaleXBackground = (float)Config::WINDOW_WIDTH / BACKGROUND_TEXTURE->getSize().x;
	scaleYBackground = (float)Config::WINDOW_HEIGHT / BACKGROUND_TEXTURE->getSize().y;

	backgroundSprite.setTexture(*this->BACKGROUND_TEXTURE);
	backgroundSprite.setScale(scaleXBackground, scaleYBackground);
}

#endif // RENDERER_H
