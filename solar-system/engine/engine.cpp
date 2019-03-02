#include <stdio.h>
#include <iostream>
#include <fstream>
#include "tinyxml2.h"
#include <string>
#include <vector>
using namespace std;
using namespace tinyxml2;

class Point {
	float x, y, z;
public:

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
	void print(int x) { // testar
		cout << "T" << x << ": " << getOne().getX() << " " << getOne().getY() << " " << getOne().getZ() << "\n";
		cout << "T" << x << ": " << getTwo().getX() << " " << getTwo().getY() << " " << getTwo().getZ() << "\n";
		cout << "T" << x << ": " << getThree().getX() << " " << getThree().getY() << " " << getThree().getZ() << "\n";
	}
};



class Figure {
	vector<Triangle> triangles;
public:

	void set_values(vector<Triangle> ts) {
		triangles = ts;
	}

	vector<Triangle> get_values() {
		return triangles;
	}
};



vector<Point> getPoints(const char *name) {
	string point;
	ifstream file;
	file.open(name);

	string delimiter = ", ";
	int delim_len = delimiter.length();

	int num = 0; // teste

	vector<Point> points;
	

	while (!file.eof()) { // To get you all the lines.

		getline(file, point); // Saves the line in STRING.

		string token;
		float coord[3];
		int i = 0;

		int pos_start = 0,pos_end;

		while (i<3) {
			pos_end = point.find(delimiter, pos_start);
			token = point.substr(pos_start, pos_end-pos_start);
			coord[i++] = stof(token);
			pos_start = pos_end + delim_len;
		}

		Point p;
		p.set_values(coord[0], coord[1], coord[2]);
		points.push_back(p);
		cout << "ponto " << num << ": " << p.getX() << " " << p.getY() << " " << p.getZ() << "\n";
		num++; // teste
		
	}
	file.close();

	cout << num << " pontos\n"; // teste
	return points;
}

vector<Triangle> getTriangles(vector<Point> points) {	
	vector<Triangle> triangles;
	Point pts[3];
	int i = 0;
	int k = 0; // teste : numero do triangulo

	for (vector<Point>::iterator it = points.begin(); it != points.end(); ++it) {

		if (i == 3) { // dividir em triangulos
			Triangle t;
			t.set_values(pts[0], pts[1], pts[2]);
			triangles.push_back(t);
			i = 0;
			t.print(k); // teste
			k++; // teste
		}
		pts[i] = (*it);
		i++;
	}

	return triangles;
}



void drawModel(Figure f) {
	return;
}

vector<Figure> figures;

int readXML(const char *filename) {
	XMLDocument doc;
	XMLError error = doc.LoadFile(filename);
	if (error != XML_SUCCESS) { printf("Error: %i\n", error); return error; }

	XMLNode * scene = doc.FirstChild();
	if (scene == nullptr) return XML_ERROR_FILE_READ_ERROR;

	XMLElement *models = scene->FirstChildElement("model");

	while (models != nullptr) {

		const char * fileName = nullptr;
		fileName = models->Attribute("file");
		cout << fileName << "\n";

		if (fileName == nullptr) return XML_ERROR_PARSING_ATTRIBUTE;
		
		Figure f;
		f.set_values(getTriangles(getPoints(fileName)));
		figures.push_back(f);

		models = models->NextSiblingElement("model");
	}

	return XML_SUCCESS;
}


int main(int argc, char** argv) {

	if (argc == 1) return -1;

	else {
		return readXML(argv[1]);
	}
}
