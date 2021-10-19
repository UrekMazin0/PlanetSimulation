#ifndef CONFIG_H
#define CONFIG_H

#include <memory>
#include <SFML/Graphics.hpp>

struct Config
{
	static float gravity;

	static std::shared_ptr<sf::Texture> POINT_TEXTURE;
	static std::shared_ptr<sf::Texture> STICK_TEXTURE;
	static std::shared_ptr<sf::Texture> BACKGROUND_TEXTURE;
	static sf::Color COLOR[8];
	static uint32_t USE_FULLSCREEN;

	static uint16_t WINDOW_HEIGHT;
	static uint16_t WINDOW_WIDTH;

	static void loadTetures()
	{
		Config::POINT_TEXTURE = std::make_shared<sf::Texture>();
		Config::POINT_TEXTURE->loadFromFile("res/1.png");
		Config::POINT_TEXTURE->setSmooth(true);

		Config::BACKGROUND_TEXTURE = std::make_shared<sf::Texture>();
		Config::BACKGROUND_TEXTURE->loadFromFile("res/background.png");
		Config::BACKGROUND_TEXTURE->setSmooth(true);

		Config::STICK_TEXTURE = std::make_shared<sf::Texture>();

	}

	static void freeTextures()
	{
		Config::POINT_TEXTURE = nullptr;
		Config::STICK_TEXTURE = nullptr;
	}
};

float Config::gravity = 9.8;

std::shared_ptr<sf::Texture> Config::POINT_TEXTURE;
std::shared_ptr<sf::Texture> Config::STICK_TEXTURE;
std::shared_ptr<sf::Texture> Config::BACKGROUND_TEXTURE;

uint16_t Config::WINDOW_WIDTH = 1680;
uint16_t Config::WINDOW_HEIGHT = 1050;

sf::Color Config::COLOR[8] = {sf::Color::Red, sf::Color::Blue, sf::Color::Yellow, sf::Color(50, 255, 255)};

uint32_t Config::USE_FULLSCREEN = 1;

#endif // CONFIG_H
