#ifndef XML_HANDLER
#define XML_HANDLER

#include <tinyxml2.h>
#include <vector>
#include <figure.h>
#include <operation.h>
#include <group.h>
#include <hash.h>
#include <translate.h>
#include <scale.h>
#include <rotate.h>
#include <iostream>
#include <light.h>

using namespace std;
using namespace tinyxml2;

int readXML(const char *filename, vector<Group>* groups, vector<Light*>* lights);
int readGroup(XMLElement* element, vector<Figure> *fig, vector<Operation*>*ops, vector<Group> *subGroups);
int readModels(XMLElement * models, vector<Figure>* fig);
Light* readLight(XMLElement* light_element);

string getDirectory(const string& name);

#endif