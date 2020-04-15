#include "Vector3.h"

#include <cmath>
#include <iostream>

namespace vectors
{
	///Конструкторы
	Vector3::Vector3(double _x, double _y, double _z ) : x(_x), y(_y), z(_z)
	{
	}
	Vector3::Vector3(const Vector3 &vec) : x(vec.x), y(vec.y), z(vec.z)
	{
	}
	Vector3::~Vector3() {}

	Vector3 Vector3::operator / (const double a)
	{
		Vector3 temp = *this;
		temp /= a;
		return temp;
	}
	Vector3 Vector3::operator * (const double a)
	{
		Vector3 temp = *this;
		temp *= a;
		return temp;
	}
	Vector3 Vector3::operator + (const Vector3 &vec)
	{
		Vector3 temp = *this;
		temp += vec;
		return temp;
	}
	Vector3 Vector3::operator - (const Vector3 &vec)
	{
		Vector3 temp = *this;
		temp -= vec;
		return temp;
	}

	Vector3 Vector3::operator += (const Vector3 &vec)
	{
		this->x += vec.x;
		this->y += vec.y;
		this->z += vec.z;

		return *this;
	}
	Vector3 Vector3::operator -= (const Vector3 &vec)
	{
		this->x -= vec.x;
		this->y -= vec.y;
		this->z -= vec.z;

		return *this;
	}
	Vector3 Vector3::operator *= (const double a)
	{
		this->x *= a;
		this->y *= a;
		this->z *= a;

		return *this;
	}
	Vector3 Vector3::operator /= (const double a)
	{
		if (a != 0)
		{
			this->x /= a;
			this->y /= a;
			this->z /= a;
		}
		else
		{
			std::cout << "Error : Attempt to divide by zero \n";
		}

		return *this;
	}
	Vector3 Vector3::operator = (const Vector3 &vec)
	{
		if (*this != vec)
		{
			this->x = vec.x;
			this->y = vec.y;
			this->z = vec.z;
		}
		return *this;
	}
	bool Vector3::operator == (const Vector3 &vec)
	{
		return !(*this != vec);
	}
	bool Vector3::operator != (const Vector3 &vec)
	{
		return this->x != vec.x || this->y != vec.y || this->z != vec.z;
	}
	/// Функции доступа
	void Vector3::set_x(double &_x)
	{
		this->x = _x;
	}
	void Vector3::set_y(double &_y)
	{
		this->y = _y;
	}
	void Vector3::set_z(double &_z)
	{
		this->z = _z;
	}
	double Vector3::get_x()
	{
		return this->x;
	}
	double Vector3::get_y()
	{
		return this->y;
	}
	double Vector3::get_z()
	{
		return this->z;
	}
	/// Функции
	double Vector3::length()
	{
		return sqrt(this->square_length());
	}
	double Vector3::square_length()
	{
		return dot_product(*this, *this);
	}
	/// @todo
	vectors::Vector3 Vector3::normal()
	{
		return ZERO;
	}
	void Vector3::normalize()
	{
		*this /= this->length();
	}

	double dot_product(const Vector3 &_first, const Vector3 &_second)
	{
		Vector3 first  = _first;
		Vector3 second = _second;

		return first.get_x()*second.get_x() + first.get_y()*second.get_y() + first.get_z()*second.get_z();
	}
	double mixed_product(const Vector3 &first, const Vector3 &second, const Vector3 &third)
	{
		Vector3 a = first;
		Vector3 b = second;
		Vector3 c = third;

		return a.get_x()*b.get_y()*c.get_z() + a.get_z()*b.get_x()*c.get_y() + a.get_y()*b.get_z()*c.get_x() -
			   a.get_z()*b.get_y()*c.get_x() - a.get_x()*b.get_z()*c.get_y() - a.get_y()*b.get_x()*c.get_z();
	}
	Vector3 vector_product(const Vector3 &_first, const Vector3 &_second)
	{
		Vector3 first  = _first;
		Vector3 second = _second;

		Vector3 temp(first.get_y()*second.get_z() - first.get_z()*second.get_y(),
			first.get_z()*second.get_x() - first.get_x()*second.get_z(),
			first.get_x()*second.get_y() - first.get_y()*second.get_x());

		return temp;
	}
	void rotate(Vector3 &vec, double angle)
	{

	}
}