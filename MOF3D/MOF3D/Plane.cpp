#include <cmath>

#include "Plane.h"

int sign(double a)
{
	return a < 0 ? -1 : a > 0 ? 1 : 0;
}
Plane::Plane() : A(0.0), B(0.0), C(0.0), D(0.0), dist_eps(1e-8)
{
}
Plane::Plane(double _A, double _B, double _C, double _D) : A(_A), B(_B), C(_C), D(_D), dist_eps(1e-8)
{
}
Plane::Plane(const vectors::Vector3 &_a, const vectors::Vector3 &_b, const vectors::Vector3 &_c)
{
	vectors::Vector3 a = _a, b = _b, c = _c;
	vectors::Vector3 first  = b - a;
	vectors::Vector3 second = c - a;

	vectors::Vector3 normal = vectors::vector_product(first, second);
	this->A = normal.get_x();
	this->B = normal.get_y();
	this->C = normal.get_z();
	a *= -1;
	this->D = vectors::dot_product(normal, a);

	dist_eps = 1e-8;
}
Plane::Plane(const Plane &p)
{
	this->A = p.A;
	this->B = p.B;
	this->C = p.C;
	this->D = p.D;
	this->dist_eps = p.dist_eps;
}
bool Plane::point_is_in_plane(vectors::Vector3 &point)
{
	return fabs(A*point.get_x() + B*point.get_y() + C*point.get_z() + D) < dist_eps;
}
bool Plane::the_same_point_orientation(vectors::Vector3 &base_point, vectors::Vector3 &check_point)
{
	double base_point_belong  = A*base_point.get_x()  + B*base_point.get_y()  + C*base_point.get_z()  + D;
	double check_point_belong = A*check_point.get_x() + B*check_point.get_y() + C*check_point.get_z() + D;
	return ( sign(base_point_belong) == sign(check_point_belong) ) || fabs(check_point_belong) < this->dist_eps;
}
void Plane::set_A(double _A)
{
	this->A = _A;
}
void Plane::set_B(double _B)
{
	this->B = _B;
}
void Plane::set_C(double _C)
{
	this->C = _C;
}
void Plane::set_D(double _D)
{
	this->D = _D;
}
void Plane::set_params(double _A, double _B, double _C, double _D)
{
	this->A = _A;
	this->B = _B;
	this->C = _C;
	this->D = _D;
}

double Plane::get_A()
{
	return A;
}
double Plane::get_B()
{
	return B;
}
double Plane::get_C()
{
	return C;
}
double Plane::get_D()
{
	return D;
}
void Plane::get_params(double &_A, double &_B, double &_C, double &_D)
{
	_A = A;
	_B = B;
	_C = C;
	_D = D;
}

vectors::Vector3 Plane::normal()
{
	return vectors::Vector3(A, B, C);
}

bool Plane::operator == (const Plane &other)
{
	return !(*this != other);
}
bool Plane::operator != (const Plane &other)
{
	double temp1 = A + B + C + D;
	double temp2 = other.A + other.B + other.C + other.D;

	double a1 = A, b1 = B, c1 = C, d1 = D;
	double a2 = other.A, b2 = other.B, c2 = other.C, d2 = other.D;

	a1 /= temp1;
	b1 /= temp1;
	c1 /= temp1;
	d1 /= temp1;

	a2 /= temp2;
	b2 /= temp2;
	c2 /= temp2;
	d2 /= temp2;

	return (a1 != a2) || (b1 != b2) || (c1 != c2) || (d1 != d2);
}