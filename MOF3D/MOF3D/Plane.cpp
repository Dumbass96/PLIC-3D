#include "Plane.h"

Plane::Plane() : A(0.0), B(0.0), C(0.0), D(0.0)
{
}
Plane::Plane(double _A, double _B, double _C, double _D) : A(_A), B(_B), C(_C), D(_D)
{
}
Plane::Plane(const vectors::Vector3 &_a, const vectors::Vector3 &_b, const vectors::Vector3 &_c)
{
	vectors::Vector3 a = _a, b = _b, c = _c;
	vectors::Vector3 first  = b - a;
	vectors::Vector3 second = c - a;

	vectors::Vector3 normal = vectors::vector_product(first, second);
	a *= -1;
	double d = vectors::dot_product(normal, a);
}
Plane::Plane(const Plane &p)
{
	this->A = p.A;
	this->B = p.B;
	this->C = p.C;
	this->D = p.D;
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