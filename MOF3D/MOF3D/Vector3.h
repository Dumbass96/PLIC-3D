#ifndef VECTOR3_H
#define VECTOR3_H
#pragma once

namespace vectors
{

	class Vector3
	{
	public:

		///Конструкторы
		Vector3(double x = 0.0, double y = 0.0, double z = 0.0);
		Vector3(const Vector3 &vec);
		~Vector3();

		/// Функции доступа
		void set_x(double &_x);
		void set_y(double &_y);
		void set_z(double &_z);

		double get_x();
		double get_y();
		double get_z();

		/// Функции
		double length();
		double square_length();
		vectors::Vector3 normal();
		void normalize();

		/// операторы
		Vector3 operator / (const double a);
		Vector3 operator * (const double a);
		Vector3 operator + (const Vector3 &vec);
		Vector3 operator - (const Vector3 &vec);

		Vector3 operator += (const Vector3 &vec);
		Vector3 operator -= (const Vector3 &vec);
		Vector3 operator *= (const double a);
		Vector3 operator /= (const double a);

		Vector3 operator = (const Vector3 &vec);
		bool operator == (const Vector3 &vec);
		bool operator != (const Vector3 &vec);

	private:
		double x, y, z;
	};

	double dot_product(const Vector3 &first, const Vector3 &second);
	double mixed_product(const Vector3 &first, const Vector3 &second, const Vector3 &third);
	Vector3 vector_product(const Vector3 &first, const Vector3 &second);
	void rotate(Vector3 &vec, double angle);

	Vector3 ZERO(0.0, 0.0, 0.0);
}
#endif