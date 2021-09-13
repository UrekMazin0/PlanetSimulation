#ifndef VECTOR2D_H
#define VECTOR2D_H

#include <memory>
#include <math.h>

class Vector2D
{
public:
	Vector2D(float x = 0, float y = 0);
	~Vector2D() {}

	static Vector2D Zero();
	static float Distance( const Vector2D& obj1, const Vector2D& obj2);
	float Distance(const Vector2D& obj2) const;

	void Rotate(const float angle);
	float Magnitude() const;
	float Normalize();
	float DotProduct( const Vector2D& v2 ) const;
	float CrossProduct( const Vector2D& v2 ) const;

	Vector2D& operator= ( const Vector2D& obj2 );

	Vector2D& operator+= ( const Vector2D& obj2 );
	Vector2D& operator-= ( const Vector2D& obj2 );
	Vector2D& operator*= ( const float scalar);
	Vector2D& operator/= ( const float scalar);

	const Vector2D operator+( const Vector2D &obj2) const;
	const Vector2D operator-( const Vector2D &obj2) const;
	const Vector2D operator*( const float scalar ) const;
	const Vector2D operator/( const float scalar ) const;

	bool operator==( const Vector2D &obj2) const;
	bool operator!=( const Vector2D &obj2) const;

public:
	float x, y;
};


Vector2D::Vector2D( float x, float y )
{
	this->x = x;
	this->y = y;
}

float Vector2D::Distance( const Vector2D& obj1, const Vector2D& obj2)
{
	return sqrtf( pow((obj2.x - obj1.x), 2 ) + pow((obj2.y - obj1.y), 2) );
}

float Vector2D::Distance(const Vector2D &obj2) const
{
	return sqrtf( pow((obj2.x - this->x), 2) + pow((obj2.y - this->y), 2) );
}

void Vector2D::Rotate( const float angle )
{
	float xt = (x * cosf(angle)) - (y * sinf(angle));
	float yt = (y * cosf(angle)) + (x * sinf(angle));
	x = xt;
	y = yt;
}

float Vector2D::Magnitude() const
{
	return sqrtf(x * x + y * y);
}

float Vector2D::Normalize()
{
	float mag = Magnitude();

	if(mag != 0.0)
	{
		x /= mag;
		y /= mag;
	}

	return mag;
}

float Vector2D::DotProduct( const Vector2D &v2 ) const
{
	return (x * v2.x) + (y * v2.y);
}

float Vector2D::CrossProduct( const Vector2D &v2 ) const
{
	return (x * v2.y) - (y * v2.x);
}

Vector2D Vector2D::Zero()
{
	return Vector2D(0, 0);
}

Vector2D& Vector2D::operator= ( const Vector2D& obj2 )
{
	if (this == &obj2)
		return *this;

	x = obj2.x;
	y = obj2.y;

	return *this;
}

Vector2D& Vector2D::operator+= ( const Vector2D& obj2 )
{
	x += obj2.x;
	y += obj2.y;

	return *this;
}

Vector2D& Vector2D::operator-= ( const Vector2D& obj2 )
{
	x -= obj2.x;
	y -= obj2.y;

	return *this;
}

Vector2D& Vector2D::operator*= ( const float scalar )
{
	x *= scalar;
	y *= scalar;

	return *this;
}

Vector2D& Vector2D::operator/= ( const float scalar )
{
	x /= scalar;
	y /= scalar;

	return *this;
}

const Vector2D Vector2D::operator+( const Vector2D &ovj2 ) const
{
	return Vector2D(*this) += ovj2;
}

const Vector2D Vector2D::operator-( const Vector2D &obj2 ) const
{
	return Vector2D(*this) -= obj2;
}

const Vector2D Vector2D::operator*( const float scalar ) const
{
	return Vector2D(*this) *= scalar;
}

const Vector2D Vector2D::operator/( const float scalar ) const
{
	return Vector2D(*this) /= scalar;
}

bool Vector2D::operator== ( const Vector2D& obj2 ) const
{
	return ((x == obj2.x) && (y == obj2.y));
}

bool Vector2D::operator!= ( const Vector2D& obj2 ) const
{
	return !((x == obj2.x) && (y == obj2.y));
}

#endif // VECTOR2D_H

