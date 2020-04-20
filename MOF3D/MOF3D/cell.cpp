#include <algorithm>
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
std::vector< std::vector<vectors::Vector3> > &cell::get_faces()
{
	return this->faces;
}

// Процедура определения наименьшей выпуклой оболочки из набор координат
// оболочка упаковывается в виде набора плоскостей и набора упорядоченных точек (определяющих грань)
void cell::define_convex_hull()
{
	if (nodes.size())
	{
		vectors::Vector3 center = this->cell_center();
		std::vector< std::vector<vectors::Vector3> > temp_faces;

		for (int i = 0; i < nodes.size(); i++)
		{
			vectors::Vector3 a = nodes[i];
			for (int j = i+1; j < nodes.size(); j++)
			{
				vectors::Vector3 b = nodes[j];
				std::vector <vectors::Vector3> face_nodes;

				for (int k = j+1; k < nodes.size(); k++)
				{
					vectors::Vector3 c = nodes[k];
					Plane p(a, b, c);
					bool all_points_inside = true;

					for (int t = 0; t < nodes.size(); t++)
					{
						vectors::Vector3 d = nodes[t];
						if (!p.the_same_point_orientation(center, d))
						{
							all_points_inside = false;
							break;
						}
					}

					if (all_points_inside)
					{
						for (int t = 0; t < nodes.size(); t++)
						{
							vectors::Vector3 d = nodes[t];
							if (p.point_is_in_plane(d))
							{
								face_nodes.push_back(d);
							}
						}
						if (face_nodes.size())
						{
							std::sort(face_nodes.begin(), face_nodes.end());
							temp_faces.push_back(face_nodes);
							face_nodes.clear();
						}
					}
					//break;
				}
			}
		}

		for (int i = 0; i < temp_faces.size(); i++)
		{
			bool all_equal = false;
			for (int j = i + 1; j < temp_faces.size(); j++)
			{
				if (temp_faces[i].size() != temp_faces[j].size())
				{
					continue;
				}
				int amount = 0;
				for (int k = 0; k < temp_faces[i].size(); k++)
				{
					if (temp_faces[i][k] == temp_faces[j][k])
					{
						amount++;
					}
				}
				if (amount == temp_faces[i].size())
				{
					all_equal = true;
					break;
				}
			}
			if (all_equal == false)
			{
				faces.push_back(temp_faces[i]);
			}
		}

		sort_faces_vertices();

		if (this->faces.size())
		{
			// Формирование списка плоскостей граней
			for (int iface = 0; iface < faces.size(); iface++)
			{
				Plane temp(faces[iface][0], faces[iface][1], faces[iface][2]);
				this->faces_plane.push_back(temp);
			}
			
			for (int iface = 0; iface < faces.size(); iface++)
			{
				std::cout << "Face # " << iface << std::endl;
				for (int inode = 0; inode < faces[iface].size(); inode++)
				{
					std::cout << "( " << faces[iface][inode].get_x() << ", " << faces[iface][inode].get_y() << ", " << faces[iface][inode].get_z() << " )" << std::endl;
				}

				std::cout << "========================" << std::endl;
			}
		}
		else
		{
			std::cout << "Convex hull was not found \n";
		}
	}
	else
	{
		std::cout << "Nodes was not set \n";
	}
}
struct nodes_sort
{
	vectors::Vector3 node;
	double angle;
};
bool operator < (const nodes_sort &first, const nodes_sort &second)
{
	return first.angle < second.angle;
}
void cell::sort_faces_vertices()
{
	for (int iface = 0; iface < faces.size(); iface++)
	{
		//Вычислим центр грани
		vectors::Vector3 face_center(vectors::ZERO);

		for (int inode = 0; inode < faces[iface].size(); inode++)
		{
			face_center += faces[iface][inode];
		}
		face_center /= faces[iface].size();
		// Определим вектор начала отсчета углов
		vectors::Vector3 origin = faces[iface][1] - faces[iface][0];

		std::vector<nodes_sort> new_order_of_nodes(faces[iface].size() - 1);
		for (int inode = 1; inode < faces[iface].size(); inode++)
		{
			vectors::Vector3 cur_vec = faces[iface][inode] - face_center;
			double angle = vectors::angle(origin, cur_vec);
			new_order_of_nodes[inode - 1].angle = angle;
			new_order_of_nodes[inode - 1].node = faces[iface][inode];
		}

		std::sort(new_order_of_nodes.begin(), new_order_of_nodes.end());

		for (int inode = 1; inode < faces[iface].size(); inode++)
		{
			faces[iface][inode] = new_order_of_nodes[inode - 1].node;
		}
	}
}
double cell::volume()
{
	double result = 0.0;
	for (int iface = 0; iface < faces.size(); iface++)
	{
		vectors::Vector3 polyhedron_center = this->cell_center();
		vectors::Vector3 face_center(vectors::ZERO);

		for (int inode = 0; inode < faces[iface].size(); inode++)
		{
			face_center += faces[iface][inode];
		}
		face_center /= faces[iface].size();

		double temp = 0.0;
		for (int inode = 0; inode < faces[iface].size(); inode++)
		{
			int index = (inode + 1) % faces[iface].size();
			vectors::Vector3 a = faces[iface][inode] - polyhedron_center;
			vectors::Vector3 b = faces[iface][index] - polyhedron_center;
			vectors::Vector3 c = face_center		 - polyhedron_center;

			temp += fabs(vectors::mixed_product(a, b, c));
		}
		result += 1.0/6.0 * temp;
	}
	return result;
}
double cell::volumeMK()
{
	double result = 0.0;
	int max_point = 100;

	vectors::Vector3 center = this->cell_center();
	double radius = 0.0;
	vectors::Vector3 temp;

	for (int iface = 0; iface < faces.size(); iface++)
	{
		for (int inode = 0; inode < faces[iface].size(); inode++)
		{
			temp = faces[iface][inode] - center;
			double len = temp.length();
			radius = radius > len ? radius : len;
		}
	}

	int inside  = 0;
	for (int i = 0; i < max_point; i++)
	{
		double x = -radius + radius * (rand() % 101) / 50 + center.get_x();
		double y = -radius + radius * (rand() % 101) / 50 + center.get_y();
		double z = -radius + radius * (rand() % 101) / 50 + center.get_z();

		vectors::Vector3 p(x, y, z);
		bool temp = this->point_inside_figure(p);
		if (temp)
		{
			inside++;
		}
	}

	return (double) inside / (double) max_point;
}
bool cell::point_inside_figure(const vectors::Vector3 &point)
{
	vectors::Vector3 copy_point = point;
	vectors::Vector3 polyhedron_center = this->cell_center();
	bool inside = true;
	for (int iface = 0; iface < faces.size(); iface++)
	{
		bool temp = faces_plane[iface].the_same_point_orientation(polyhedron_center, copy_point);
		if (temp == false)
		{
			return false;
		}
	}

	return inside;
}
double cell::face_square(const int index)
{
	return 0;
}
void cell::compute_section(std::vector<vectors::Vector3> &result, const Plane &plane)
{
	Plane copy_plane = plane;
	std::vector<vectors::Vector3> found_points;

	for (int iface = 0; iface < faces.size(); iface++)
	{
		for (int inode = 0; inode < nodes.size(); inode++)
		{

		}
	}
}
vectors::Vector3 cell::face_normal(const int index)
{
	return vectors::ZERO;
}
vectors::Vector3 cell::face_center(const int index)
{
	return vectors::ZERO;
}
vectors::Vector3 cell::cell_center()
{
	vectors::Vector3 center(vectors::ZERO);
	if (nodes.size())
	{
		for (int inode = 0; inode < nodes.size(); inode++)
		{
			center += nodes[inode];
		}
		center /= nodes.size();
	}
	else
	{
		std::cout << "Amount of nodes is equal zero \n";
	}

	return center;
}