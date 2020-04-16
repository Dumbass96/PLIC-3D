#include <iostream>

#include "cell.h"
#include "Vector3.h"

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

	return 0;
}
