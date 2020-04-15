#include <iostream>

#include "cell.h"

cell::cell()
{
}
cell::cell(std::vector<vectors::Vector3> &_nodes)
{
	this->nodes = _nodes;
}
cell::cell(double *x, double *y, double *z, const int amount_nodes)
{
	this->nodes.resize(amount_nodes);

	for (int i = 0; i < amount_nodes; i++)
	{
		vectors::Vector3 vec(x[i], y[i], z[i]);
		nodes[i] = vec;
	}
}
cell::cell(const cell &c)
{
	this->nodes = c.nodes;
	this->faces = c.faces;
}

std::vector<vectors::Vector3> &cell::get_nodes()
{
	return this->nodes;
}
std::vector<Plane> &cell::get_faces()
{
	return this->faces;
}

void cell::define_convex_hull()
{
	if (nodes.size())
	{
		for (int inode = 0; inode < nodes.size(); inode++)
		{

		}
	}
	else
	{
		std::cout << "Nodes was not set \n";
	}
}
double cell::volume()
{

}
double cell::face_square(const int index)
{

}

vectors::Vector3 cell::face_normal(const int index)
{

}
vectors::Vector3 cell::face_center(const int index)
{

}
vectors::Vector3 cell::cell_center()
{

}