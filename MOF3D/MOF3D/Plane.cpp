#include <cmath>
#include <iostream>

#include "Plane.h"
#include "SLAU.h"

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
double Plane::point_position(const vectors::Vector3 &point)
{
	vectors::Vector3 p = point;
	return A*p.get_x() + B*p.get_y() + C*p.get_z() + D;
}
bool Plane::is_plane_intersection(const Plane &other)
{
	vectors::Vector3 n1(A, B, C);
	vectors::Vector3 n2(other.A, other.B, other.C);

	double eps = 1e-8;
	double vector_product = vectors::vector_product(n1, n2).length();

	return fabs(vector_product) < eps ? false : true;// Нормальные векторы плоскостей коллинеарны
}
bool Plane::intersection_with_plane(const Plane &other, vectors::Vector3 &point, vectors::Vector3 &normal)
{
	Plane copy = other;
	vectors::Vector3 n1(A, B, C); n1.normalize();
	vectors::Vector3 n2(other.A, other.B, other.C); n2.normalize();
	vectors::Vector3 n3 = vectors::vector_product(n1, n2);

	double eps = 1e-8;
	double length = n3.square_length();

	if (length < eps)
	{
		return false;
	}
	else
	{
		n3.normalize();
		point = (vectors::vector_product(n3, n2) * D + vectors::vector_product(n1, n3) * copy.get_D()) / length;
		normal = n3;
	}
}
bool Plane::intersection_with_two_plane(const Plane &one, const Plane &two, vectors::Vector3 &point)
{
	Plane copy1 = one;
	Plane copy2 = two;

	double *x = new double[3];
	double y[3];
	double **a;
	a = new double*[3];
	for (int i = 0; i < 3; i++)
	{
		a[i] = new double[3];
	}

	a[0][0] = copy1.get_A();
	a[0][1] = copy1.get_B();
	a[0][2] = copy1.get_C();

	a[1][0] = copy2.get_A();
	a[1][1] = copy2.get_B();
	a[1][2] = copy2.get_C();

	a[2][0] = A;
	a[2][1] = B;
	a[2][2] = C;

	y[0] = -copy1.get_D();
	y[1] = -copy2.get_D();
	y[2] = -D;

	if (gauss(a, y, x, 3))
	{
		for (int i = 0; i < 3; i++)
		{
			std::cout << x[i] << " ";
		}
		std::cout << std::endl;
		point = vectors::Vector3(x[0], x[1], x[2]);
		return true;
	}
	else
	{
		return false;
	}
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