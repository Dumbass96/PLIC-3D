#include <iostream>

#include "cell.h"
#include "Vector3.h"
#include "Plane.h"
#include "SLAU.h"

using namespace std;

int main()
{
	std::vector<vectors::Vector3> nodes(8);

	int index = 0;
	for (int i = 0; i < 2; i++)
		for (int j = 0; j < 2; j++)
			for (int k = 0; k < 2; k++)
			{
				nodes[index] = vectors::Vector3(i, j, k);
				index++;
			}

	cell c(nodes);
	c.define_convex_hull();
	/*std::cout << "Volume = " << c.volume() << std::endl;
	std::cout << "VolumeMK = " << c.volumeMK() << std::endl;
	vectors::Vector3 a1(0.0, 0.0, 0.0);
	vectors::Vector3 b1(0.0, 1.0, 0.0);
	vectors::Vector3 c1(0.0, 1.0, 1.0);

	vectors::Vector3 a2(0.0, 0.0, 0.5);
	vectors::Vector3 b2(0.0, 0.5, 0.5);
	vectors::Vector3 c2(0.5, 0.5, 0.5);

	Plane cut_plane(a2, b2, c2);
	cell result_section;
	c.compute_section(result_section, cut_plane);*/
	vectors::Vector3 centroid = c.centroid();
	std::cout << "Centroid =" << centroid.get_x() << "; " << centroid.get_y() << "; " << centroid.get_z() << std::endl;

	return 0;
}
