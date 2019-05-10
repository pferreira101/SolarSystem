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
	vector<Point> texture;
	string texPath;

public:

	void set_values(std::vector<Point> pts, std::vector<Point> nms, std::vector<Point> txs, string path) {
		points = pts;
		normals = nms;
		texture = txs;
		texPath = path;
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

	int getNumTextures() {
		return texture.size();
	}

	vector<Point> getTexture() {
		return texture;
	}

	string getTexPath() {
		return texPath;
	}

};


Figure getFigure(const string& name, string path);


#endif