#ifndef POINT_H
#define POINT_H

#include <SFML/Graphics.hpp>
#include <list>
#include <memory>

#include "physics/vector2d.hpp"
#include "simulation/config.hpp"
#include "render/IDrawing.h"

class Planet : public IDrawing
{
public:
	Planet(SWVector2D::Vector2D pos, float m = 10);
	~Planet() {}

	// Center
	SWVector2D::Vector2D position, prevPosition;
	bool bLocked = false;
	float mass;

	const float& Radius() const { return this->_radius; }

	void LockUnlock();

	static float Distance( const Planet& obj1, const Planet& obj2);
	float Distance(const Planet& obj2) const;

	void move(SWVector2D::Vector2D vector);

	void setPosition(SWVector2D::Vector2D newPosition);
	void Draw(sf::RenderTarget& target) const;
	bool checkVectorCollision(SWVector2D::Vector2D vector) const;

	bool operator==( const Planet &obj2) const;
	bool operator!=( const Planet &obj2) const;

private:
	float _radius = 10;
	float sprite_scale = 0.5f;
};

Planet::Planet(SWVector2D::Vector2D pos, float m)
	:position(pos)
	,prevPosition(SWVector2D::Vector2D::Zero())
	,mass(m)
{

}

void Planet::Draw(sf::RenderTarget &target) const
{
	sf::Sprite sprite;
	sprite.setTexture(*Config::POINT_TEXTURE);
	sprite.setScale(sf::Vector2f(sprite_scale, sprite_scale));
	sprite.setPosition(position.x - _radius*sprite_scale, position.y - _radius*sprite_scale);
	target.draw(sprite);
}

bool Planet::checkVectorCollision(SWVector2D::Vector2D vector) const
{
	return SWVector2D::Vector2D::Distance(this->position, vector) <= _radius*sprite_scale ?
				true :
				false;
}

bool Planet::operator==(const Planet &obj2) const
{
	return this->position == obj2.position ? true : false;
}

bool Planet::operator!=(const Planet &obj2) const
{
	return this->position != obj2.position ? true : false;
}

void Planet::LockUnlock()
{
	this->bLocked = !this->bLocked;
}

float Planet::Distance( const Planet& obj1, const Planet& obj2)
{
	return SWVector2D::Vector2D::Distance(obj1.position, obj2.position) - (obj1.Radius() + obj2.Radius());
}

float Planet::Distance(const Planet& obj2) const
{
	return SWVector2D::Vector2D::Distance(this->position, obj2.position) - (this->Radius() + obj2.Radius());
}

void Planet::setPosition(SWVector2D::Vector2D newPosition)
{
	this->prevPosition = this->position;
	this->position = newPosition;
}

void Planet::move(SWVector2D::Vector2D vector)
{
	this->prevPosition = this->position;

	this->position += vector;
}


#endif // POINT_H
