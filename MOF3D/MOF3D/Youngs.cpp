#include "Youngs.h"

#define vcon(index) vcon[index-1];

// ќбъемные концентрации упор€дочены как в статье янгса
// юго-западна€ €чейка из нижнего сло€ €вл€етс€ первой
// северо-восточна€ €чейка из верхнего сло€ последней (27)
// -------------		// ----------------		// ----------------
// | 7 | 8 | 9 |		// | 16 | 17 | 18 |		// | 25 | 26 | 27 |
// -------------		// ----------------		// ----------------
// | 4 | 5 | 6 |		// | 13 | 14 | 15 |		// | 22 | 23 | 24 |
// -------------		// ----------------		// ----------------
// | 1 | 2 | 3 |		// | 10 | 11 | 12 |		// | 19 | 20 | 21 |
// -------------		// ----------------		// ----------------
void define_normal(double *vcon, double dx, double dy, double dz, int material_index, vectors::Vector3 &normal)
{
	double est = 0.0;
	double west = 0.0;
	double south = 0.0;
	double north = 0.0;
	double top = 0.0;
	double below = 0.0;

	double gamma = 4.0;
	double betta = 2.0;

	double temp = vcon(6) + vcon(24) + vcon(18) + vcon(12);
	temp *= betta;
	est = gamma*vcon(15) + vcon(9) + vcon(3) + vcon(27) + vcon(21) + temp;

	temp = vcon(4) + vcon(10) + vcon(16) + vcon(22);
	temp *= betta;
	west = gamma*vcon(13) + vcon(1) + vcon(7) + vcon(19) + vcon(25) + temp;

	temp = vcon(8) + vcon(16) + vcon(18) + vcon(26);
	temp *= betta;
	north = gamma*vcon(17) + vcon(7) + vcon(9) + vcon(25) + vcon(27) + temp;

	temp = vcon(2) + vcon(10) + vcon(12) + vcon(20);
	temp *= betta;
	south = gamma*vcon(11) + vcon(1) + vcon(3) + vcon(19) + vcon(21) + temp;

	temp = vcon(20) + vcon(22) + vcon(24) + vcon(26);
	temp *= betta;
	top = gamma*vcon(23) + vcon(19) + vcon(21) + vcon(25) + vcon(27) + temp;

	temp = vcon(2) + vcon(4) + vcon(6) + vcon(8);
	temp *= betta;
	below = gamma*vcon(5) + vcon(1) + vcon(3) + vcon(7) + vcon(9) + temp;

	normal = vectors::Vector3((est - west) / (2.0*dx), (north - south) / (2.0*dy), (top - below) / (2.0*dz));
	normal *= -1;
	normal.normalize();
}
