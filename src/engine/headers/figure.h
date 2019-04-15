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
	Point() {
		x = y = z = 0;
	}
	Point(float xx, float yy, float zz) {
		x = xx;
		y = yy;
		z = zz;
	}

	void set_values(float a, float b, float c) {
		x = a;
		y = b;
		z = c;
	}
	float getX() {
		return x;
	}
	float getY() {
		return y;
	}
	float getZ() {
		return z;
	}

};

/**
Classe que guarda os trs pontos de um tri‰ngulo
*/
class Triangle {
	Point one, two, three;

public:

	Triangle(Point x, Point y, Point z) {
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