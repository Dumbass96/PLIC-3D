#ifndef CELL_H
#define CELL_H

#pragma once

#include <iostream>
#include <vector>

#include "Vector3.h"
#include "Plane.h"

class cell
{
public:
	cell();
	cell(std::vector<vectors::Vector3> &_nodes);
	cell(double *x, double *y, double *z, const int amount_nodes);
	cell(const cell &c);
	~cell() {};

	std::vector<vectors::Vector3> &get_nodes();
	std::vector< std::vector<vectors::Vector3> > &get_faces();
	std::vector<Plane> &get_faces_plane();

	bool compute_section(cell &section, const Plane &cut_plane);
	void define_convex_hull();
	void sort_faces_vertices();
	double volume();
	double volumeMK();
	double face_square(const int index);
	bool point_inside_figure(const vectors::Vector3 &point);
	vectors::Vector3 centroid();

	vectors::Vector3 face_normal(const int index);
	vectors::Vector3 face_center(const int index);
	vectors::Vector3 cell_center();

private:
	std::vector<vectors::Vector3> nodes;
	std::vector< std::vector<vectors::Vector3> > faces;
	std::vector<Plane> faces_plane;

};

#endif