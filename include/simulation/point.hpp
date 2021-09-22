#ifndef POINT_H
#define POINT_H

#include <SFML/Graphics.hpp>
#include <list>
#include <memory>

#include "physics/vector2d.hpp"
#include "simulation/config.hpp"

struct Point
{
public:
	Point(SWVector2D::Vector2D pos);
	~Point() {}

	// Center
	SWVector2D::Vector2D position, prevPosition;
	bool bLocked = false;
	const float& Radius() const { return this->_radius; }

	void LockUnlock();

	static float Distance( const Point& obj1, const Point& obj2);
	float Distance(const Point& obj2) const;

	void drawPointSFMLWindow(sf::RenderTarget& target) const;

private:
	float _radius = 20;
	static std::list<std::unique_ptr<Point>> pointObjects;
	void addPoint2StaticStorage(const Point& p) const;
};

Point::Point(SWVector2D::Vector2D pos)
{
	this->position = pos;
	this->prevPosition = SWVector2D::Vector2D::Zero();

//	Point::pointObjects.push_back(std::make_unique<Point>(this));
}

void Point::drawPointSFMLWindow(sf::RenderTarget &target) const
{
	sf::Sprite sprite;
	sprite.setTexture(*Config::POINT_TEXTURE);
	sprite.setColor(sf::Color::Red);
	sprite.setPosition(this->position.x-60, this->position.y-60);
	target.draw(sprite);
}

void Point::LockUnlock()
{
	this->bLocked = !this->bLocked;
}

float Point::Distance( const Point& obj1, const Point& obj2)
{
	return SWVector2D::Vector2D::Distance(obj1.position, obj2.position) - (obj1.Radius() + obj2.Radius());
}

float Point::Distance(const Point& obj2) const
{
	return SWVector2D::Vector2D::Distance(this->position, obj2.position) - (this->Radius() + obj2.Radius());
}

void Point::addPoint2StaticStorage(const Point &p) const
{
	auto buffer = std::make_unique<Point>(p);
}


#endif // POINT_H
