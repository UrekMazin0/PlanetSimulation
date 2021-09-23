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

	void setPosition(SWVector2D::Vector2D newPosition);
	void drawPointSFMLWindow(sf::RenderTarget& target) const;
	bool checkVectorCollision(SWVector2D::Vector2D vector) const;

	bool operator==( const Point &obj2) const;
	bool operator!=( const Point &obj2) const;

private:
	float _radius = 60;
};

Point::Point(SWVector2D::Vector2D pos)
{
	this->position = pos;
	this->prevPosition = SWVector2D::Vector2D::Zero();
}

void Point::drawPointSFMLWindow(sf::RenderTarget &target) const
{
	sf::Sprite sprite;
	sprite.setTexture(*Config::POINT_TEXTURE);
	sprite.setPosition(this->position.x-60, this->position.y-60);
	target.draw(sprite);
}

bool Point::checkVectorCollision(SWVector2D::Vector2D vector) const
{
	return SWVector2D::Vector2D::Distance(this->position, vector) <= this->Radius() ?
				true :
				false;
}

bool Point::operator==(const Point &obj2) const
{
	return this->position == obj2.position ? true : false;
}

bool Point::operator!=(const Point &obj2) const
{
	return this->position != obj2.position ? true : false;
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

void Point::setPosition(SWVector2D::Vector2D newPosition)
{
	this->prevPosition = this->position;
	this->position = newPosition;
}


#endif // POINT_H
