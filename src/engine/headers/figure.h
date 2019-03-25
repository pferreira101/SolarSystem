#ifndef FIGURE
#define FIGURE

#include <vector>
#include <string>
#include <fstream>
#include <stdio.h>
using namespace std;

/**
Classe que guarda as coordenadas X, Y, Z de um ponto
*/
class Point {
	float x, y, z;
public:

	void set_values(double a, double b, double c) {
		x = a;
		y = b;
		z = c;
	}
	double getX() {
		return x;
	}
	double getY() {
		return y;
	}
	double getZ() {
		return z;
	}
};

/**
Classe que guarda os trs pontos de um tri‰ngulo
*/
class Triangle {
	Point one, two, three;

public:

	void set_values(Point x, Point y, Point z) {
		one = x;
		two = y;
		three = z;
	}
	Point getOne() {
		return one;
	}
	Point getTwo() {
		return two;
	}
	Point getThree() {
		return three;
	}
};


/**
Classe que guarda a lista de tri‰ngulos que comp›em uma figura
*/
class Figure {
	std::vector<Triangle> triangles;
public:

	void set_values(std::vector<Triangle> ts) {
		triangles = ts;
	}

	std::vector<Triangle> get_triangles() {
		return triangles;
	}
};


Figure getFigure(const string& name);
vector<Triangle> getTriangles(vector<Point> points);
vector<Point> getPoints(const string& name);

#endif