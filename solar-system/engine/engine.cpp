
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
};

class Triangle {
	Point one, two, three;

public:

	void set_values(Point x, Point y, Point z) {
		one = x;
		two = y;
		three = z;
	}
};



class Figure {
	vector<Triangle> triangles;
public:

	void set_values(vector<Triangle> ts) {
		triangles = ts;
	}
};



vector<Point> getPoints(const char *name) {
	string point;
	ifstream file;
	file.open(name);

	string delimiter = ",";

	vector<Point> points;
	

	while (!file.eof()) { // To get you all the lines.

		getline(file, point); // Saves the line in STRING.
		size_t pos = 0;
		string token;
		float coord[3];
		int i = 0;

		while ((pos = point.find(delimiter)) != std::string::npos) {
			token = point.substr(0, pos);
			coord[i++] = stof(token);
			point.erase(0, pos + delimiter.length());
		}

		cout << coord[0] << " " << coord[1] << " " << coord[2];

		Point p;
		p.set_values(coord[0], coord[1], coord[2]);
		points.push_back(p);
		
	}
	file.close();

	return points;
}

vector<Triangle> getTriangles(vector<Point> points) {	
	vector<Triangle> triangles;
	Point pts[3];
	int i = 0;

	for (vector<Point>::iterator it = points.begin(); it != points.end(); ++it) {
		if (i == 3) {
			Triangle t;
			t.set_values(pts[0], pts[1], pts[2]);
			triangles.push_back(t);
			i = 0;
		}
		pts[i] = *it;
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

	XMLElement *models = doc.FirstChildElement("model");

	while (models != nullptr) {

		const char * fileName = nullptr;
		fileName = models->Attribute("file");

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

	else return readXML(argv[1]);
}
