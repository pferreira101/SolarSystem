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

	string toString(){
		return string(to_string(x)+","+to_string(y)+","+to_string(z)+"\n");
	}
};



/**
Classe que guarda a lista de tri‰ngulos que comp›em uma figura
*/
class Figure {
	vector<Point> points;
	vector<Point> normals;
public:

	void set_values(std::vector<Point> pts, std::vector<Point> nms) {
		points = pts;
		normals = nms;
	}

	int getNumPoints() {
		return points.size();
	}

	vector<Point> getPoints(){
		return points;
	}

	int getNumNormals() {
		return normals.size();
	}

	vector<Point> getNormals() {
		return normals;
	}
};


Figure getFigure(const string& name);


#endif