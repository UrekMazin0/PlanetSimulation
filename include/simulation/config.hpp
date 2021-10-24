#ifndef CONFIG_H
#define CONFIG_H

#include <memory>
#include <SFML/Graphics.hpp>

struct Config
{
	static float g;
	static float dt;

	static std::shared_ptr<sf::Texture> PLANET_1_TEXTURE;
	static std::shared_ptr<sf::Texture> PLANET_2_TEXTURE;
	static std::shared_ptr<sf::Texture> PLANET_3_TEXTURE;
	static std::shared_ptr<sf::Texture> PLANET_4_TEXTURE;
	static std::shared_ptr<sf::Texture> PLANET_5_TEXTURE;
	static std::shared_ptr<sf::Texture> PLANET_6_TEXTURE;
	static std::shared_ptr<sf::Texture> BLACK_HOLE_TEXTURE;

	static std::shared_ptr<sf::Texture> POINT_TEXTURE;
	static std::shared_ptr<sf::Texture> STICK_TEXTURE;
	static std::shared_ptr<sf::Texture> BACKGROUND_TEXTURE;
	static sf::Color COLOR[8];
	static uint32_t USE_FULLSCREEN;

	static uint16_t WINDOW_HEIGHT;
	static uint16_t WINDOW_WIDTH;

	static void loadTetures()
	{
		Config::PLANET_1_TEXTURE = std::make_shared<sf::Texture>();
		Config::PLANET_1_TEXTURE->loadFromFile("res/1.png");
		Config::PLANET_1_TEXTURE->setSmooth(true);

		Config::PLANET_2_TEXTURE = std::make_shared<sf::Texture>();
		Config::PLANET_2_TEXTURE->loadFromFile("res/2.png");
		Config::PLANET_2_TEXTURE->setSmooth(true);

		Config::PLANET_3_TEXTURE = std::make_shared<sf::Texture>();
		Config::PLANET_3_TEXTURE->loadFromFile("res/3.png");
		Config::PLANET_3_TEXTURE->setSmooth(true);

		Config::PLANET_4_TEXTURE = std::make_shared<sf::Texture>();
		Config::PLANET_4_TEXTURE->loadFromFile("res/4.png");
		Config::PLANET_4_TEXTURE->setSmooth(true);

		Config::PLANET_5_TEXTURE = std::make_shared<sf::Texture>();
		Config::PLANET_5_TEXTURE->loadFromFile("res/5.png");
		Config::PLANET_5_TEXTURE->setSmooth(true);

		Config::PLANET_6_TEXTURE = std::make_shared<sf::Texture>();
		Config::PLANET_6_TEXTURE->loadFromFile("res/6.png");
		Config::PLANET_6_TEXTURE->setSmooth(true);

		Config::BLACK_HOLE_TEXTURE = std::make_shared<sf::Texture>();
		Config::BLACK_HOLE_TEXTURE->loadFromFile("res/BlackHole.png");
		Config::BLACK_HOLE_TEXTURE->setSmooth(true);

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

float Config::g = 39.5;
float Config::dt = 0.008;

std::shared_ptr<sf::Texture> Config::PLANET_1_TEXTURE;
std::shared_ptr<sf::Texture> Config::PLANET_2_TEXTURE;
std::shared_ptr<sf::Texture> Config::PLANET_3_TEXTURE;
std::shared_ptr<sf::Texture> Config::PLANET_4_TEXTURE;
std::shared_ptr<sf::Texture> Config::PLANET_5_TEXTURE;
std::shared_ptr<sf::Texture> Config::PLANET_6_TEXTURE;
std::shared_ptr<sf::Texture> Config::BLACK_HOLE_TEXTURE;

std::shared_ptr<sf::Texture> Config::POINT_TEXTURE;
std::shared_ptr<sf::Texture> Config::STICK_TEXTURE;
std::shared_ptr<sf::Texture> Config::BACKGROUND_TEXTURE;

uint16_t Config::WINDOW_WIDTH = 1680;
uint16_t Config::WINDOW_HEIGHT = 1050;

sf::Color Config::COLOR[8] = {sf::Color::Red, sf::Color::Blue, sf::Color::Yellow, sf::Color(50, 255, 255)};

uint32_t Config::USE_FULLSCREEN = 1;

#endif // CONFIG_H
