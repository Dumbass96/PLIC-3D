#ifndef PLANE_H
#define PLANE_H

#include "Vector3.h"

#pragma once
class Plane
{
public:
	Plane();
	Plane(double _A, double _B, double _C, double _D);
	Plane(const vectors::Vector3 &a, const vectors::Vector3 &b, const vectors::Vector3 &c);
	Plane(const Plane &p);
	~Plane() {};

	void set_A(double A);
	void set_B(double B);
	void set_C(double C);
	void set_D(double D);
	void set_params(double A, double B, double C, double D);

	double get_A();
	double get_B();
	double get_C();
	double get_D();
	void get_params(double &A, double &B, double &C, double &D);

	vectors::Vector3 normal();

private:
	double A, B, C, D;
};

#endif