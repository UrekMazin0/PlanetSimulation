#ifndef POINT_H
#define POINT_H

#include <SFML/Graphics.hpp>
#include <list>
#include <memory>

#include "physics/Vector2d.hpp"
#include "simulation/config.hpp"
#include "render/IDrawing.h"

class Planet : public IDrawing
{
public:
	Planet(SWVector2D::Vector2D pos, std::shared_ptr<sf::Texture> texture, float m = 10, float radius = 10);
	~Planet() {}

	// Center
	SWVector2D::Vector2D position, prevPosition;

	SWVector2D::Vector2D velocity = SWVector2D::Vector2D::Zero();
	SWVector2D::Vector2D acceleration = SWVector2D::Vector2D::Zero();

	bool bLocked = false;
	float mass;

	const float& Radius() const { return this->_radius; }
	void LockUnlock();

	static float Distance( const Planet& obj1, const Planet& obj2);
	float Distance(const Planet& obj2) const;

	void move();
	void move(SWVector2D::Vector2D vector);
	void update(SWVector2D::Vector2D a);

	void setPosition(SWVector2D::Vector2D newPosition);
	void Draw(sf::RenderTarget& target) const;
	bool checkVectorCollision(SWVector2D::Vector2D vector) const;

	bool operator==( const Planet &obj2) const;
	bool operator!=( const Planet &obj2) const;

private:
	float _radius;
	float _sprite_scale = 0.5f;

	std::shared_ptr<sf::Texture> _texture;
};

Planet::Planet(SWVector2D::Vector2D pos, std::shared_ptr<sf::Texture> texture, float m, float radius)
	:position(pos)
	,prevPosition(SWVector2D::Vector2D::Zero())
	,mass(m)
	,_texture(texture)
	,_radius(radius)
{

}

void Planet::Draw(sf::RenderTarget &target) const
{
	sf::Sprite sprite;
	sprite.setTexture(*this->_texture);
	sprite.setScale(sf::Vector2f(_sprite_scale, _sprite_scale));
	sprite.setPosition(position.x - sprite.getTexture()->getSize().x / 4,
					   position.y - sprite.getTexture()->getSize().y / 4);
	target.draw(sprite);
}

bool Planet::checkVectorCollision(SWVector2D::Vector2D vector) const
{
	return SWVector2D::Vector2D::Distance(this->position, vector) <= _radius*_sprite_scale ?
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

void Planet::move()
{
	prevPosition = position;
	position += velocity * Config::dt;
}

void Planet::move(SWVector2D::Vector2D vector)
{
	prevPosition = position;

	position += vector;
}

void Planet::update(SWVector2D::Vector2D a)
{
	velocity += a;
}

#endif // POINT_H
