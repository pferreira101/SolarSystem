
#include <stdio.h>
#include <iostream>
#include <fstream>
#include "tinyxml2.h"
#include<string>
using namespace std;
using namespace tinyxml2;

class Point {
	int x, y, z;
public:
	void set_values(int, int, int);
};

void Point::set_values(int a, int b, int c) {
	x = a;
	y = b;
	z = c;
}

class Triangle {
	Point one, Point two, Point three;
public:
	void set_values(Point, Point, Point);
};

void Triangle::set_values(Point x, Point y, Point z) {
	one = x;
	two = y;
	three = z;
}

class Figure {
	std::vector<Triangle> triangles;
public:
	void set_values(std::vector<Triangle>);
};

void Figure::set_values(std::vector<Triangle> ts) {
	triangles = ts;
}

std::vector<Point> getPoints(const char *name) {
	string point;
	ifstream file;
	file.open(name);

	string delimiter = ",";

	std::vector<Point> points;
	

	while (!file.eof) // To get you all the lines.
	{
		getline(file, point); // Saves the line in STRING.

		size_t pos = 0;
		string token;
		int coord[3];
		int i = 0;

		while ((pos = point.find(delimiter)) != std::string::npos) {
			token = point.substr(0, pos);
			coord[i++] = stof(token);
			point.erase(0, pos + delimiter.length());
		}

		Point p;
		p.set_values(p[0], p[1], p[2]);
		points.push_back(p);
		
	}
	file.close();

	return points;
}

std::vector<Triangle> getTriangles(std::vector<Point> points) {
	
	std::vector<Triangle> triangles;
	Point[3] pts;
	int i = 0;

	for (std::vector<Point>::iterator it = points.begin(); it != points.end(); ++it) {
		(if i == 3) {
			Triangle t;
			t.set_values(Point[0], Point[1], Point[2]);
			triangles.push_back(t);
			i = 0;
		}
		pts[i] = *it;
		i++;
	}

	return triangles;
}

void drawModel(const char *file) {
	return;
}

int readXML(const char *filename) {
	XMLDocument doc;
	XMLError error = doc.LoadFile(filename);
	if (error != XML_SUCCESS) { printf("Error: %i\n", error); return error; }

	XMLNode * scene = doc.FirstChild();
	if (scene == nullptr) return XML_ERROR_FILE_READ_ERROR;

	XMLElement *models = doc.FirstChildElement("model");

	while (models != nullptr) {

		const char * fileName = nullptr;
		fileName = models->Attribute("file");

		if (fileName == nullptr) return XML_ERROR_PARSING_ATTRIBUTE;
		
		drawModel(fileName);

		models = models->NextSiblingElement("model");
	}

	return XML_SUCCESS;
}


int main(int argc, char** argv) {

	readXML(argv[1]);

	return 0;
}
