#ifndef POINT_H
#define POINT_H

#include <SFML/Graphics.hpp>
#include <list>
#include <memory>

#include "physics/vector2d.hpp"

struct Point
{
public:
	Point(Vector2D pos);
	~Point() {}

	// Center
	Vector2D position, prevPosition;
	bool bLocked = false;
	const float& Radius() const { return this->_radius; }

	void LockUnlock();

	static float Distance( const Point& obj1, const Point& obj2);
	float Distance(const Point& obj2) const;

	void drawPointSFMLWindow(sf::RenderTarget& target);

private:
	float _radius = 20;
	static std::list<std::unique_ptr<Point>> pointObjects;
	void addPoint2StaticStorage(const Point& p) const;
};

Point::Point(Vector2D pos)
{
	this->position = pos;
	this->prevPosition = Vector2D::Zero();

//	Point::pointObjects.push_back(std::make_unique<Point>(this));
}

void Point::LockUnlock()
{
	this->bLocked = !this->bLocked;
}

float Point::Distance( const Point& obj1, const Point& obj2)
{
	return Vector2D::Distance(obj1.position, obj2.position) - (obj1.Radius() + obj2.Radius());
}

float Point::Distance(const Point& obj2) const
{
	return Vector2D::Distance(this->position, obj2.position) - (this->Radius() + obj2.Radius());
}

void Point::addPoint2StaticStorage(const Point &p) const
{
	auto buffer = std::make_unique<Point>(p);
}


#endif // POINT_H