#ifndef IDRAWING_H
#define IDRAWING_H

#include <SFML/Graphics.hpp>

class IDrawing
{
protected:
	IDrawing(){}

public:
	~IDrawing(){}

	virtual void Draw(sf::RenderTarget &target) const = 0;
};

#endif // IDRAWING_H
