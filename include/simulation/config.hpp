#ifndef CONFIG_H
#define CONFIG_H

#include <memory>
#include <SFML/Graphics.hpp>

struct Config
{
	static std::shared_ptr<sf::Texture> POINT_TEXTURE;
	static std::shared_ptr<sf::Texture> STICK_TEXTURE;
	static sf::Color COLOR[8];
	static uint32_t USE_FULLSCREEN;

	static uint16_t WINDOW_HEIGHT = 1050;
	static uint16_t WINDOW_WIDTH = 1680;

	static void loadTetures()
	{
		Config::POINT_TEXTURE = std::make_shared<sf::Texture>();
		Config::POINT_TEXTURE->loadFromFile("res/point.png");
		Config::POINT_TEXTURE->setSmooth(true);

		Config::STICK_TEXTURE = std::make_shared<sf::Texture>();

	}

	static void freeTexture()
	{
		Config::POINT_TEXTURE = nullptr;
		Config::STICK_TEXTURE = nullptr;
	}
};

std::shared_ptr<sf::Texture> Config::POINT_TEXTURE;
std::shared_ptr<sf::Texture> Config::STICK_TEXTURE;

uint16_t Config::WINDOW_WIDTH = 1680;
uint16_t Config::WINDOW_HEIGHT = 1050;

sf::Color Config::COLONY_COLORS[8] = {sf::Color::Red, sf::Color::Blue, sf::Color::Yellow, sf::Color(50, 255, 255)};

uint32_t Config::USE_FULLSCREEN = 1;

#endif // CONFIG_H
