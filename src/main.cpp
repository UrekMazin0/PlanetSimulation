#include <SFML/Graphics.hpp>

#include "physics/vector2d.hpp"
#include "simulation/simulation.hpp"
#include "simulation/config.hpp"

using namespace std;

int main()
{
	Config::loadTetures();

	sf::ContextSettings settings;
	settings.antialiasingLevel = 1;
	int32_t window_style = Config::USE_FULLSCREEN ? sf::Style::Fullscreen : sf::Style::Default;
	sf::RenderWindow window(sf::VideoMode(Config::WINDOW_WIDTH, Config::WINDOW_HEIGHT), "PointStickSimulation", window_style, settings);
	window.setFramerateLimit(60);

	float dt = 0.016;
	Simulation simulation(window);

	while (window.isOpen()) {

		simulation.processEvents();

		simulation.render(window);

		simulation.update(dt);

		window.display();

	}
	// Free textures
	Config::freeTextures();

	return 0;
}
