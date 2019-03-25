#include <xmlHandler.h>

/**
Fun‹o que interpreta um cen‡rio gr‡fico em XML
*/
int readXML(const char *filename, vector<Group>* groups){

	XMLDocument doc;
	XMLError error = doc.LoadFile(filename);
	if (error != XML_SUCCESS) { printf("Error: %i\n", error); return error; }

	XMLNode *scene = doc.FirstChild();
	if (scene == nullptr) return XML_ERROR_FILE_READ_ERROR;

	XMLElement *groups_xml = scene->FirstChildElement("group");

	while (groups_xml != nullptr) {
		vector<Operation*> ops;
		vector<Figure> fig;
		vector<Group> subGroups;
		readGroup(groups_xml, &fig, &ops, &subGroups);
		
		Group group; 
		group.set_values(fig, ops, subGroups);
		groups->push_back(group);

		groups_xml = groups_xml->NextSiblingElement("group");
	}

	return XML_SUCCESS;
}


int readGroup(XMLElement* element, vector<Figure>* fig, vector<Operation*>* ops, vector<Group>* subGroups) {
	XMLElement* child;
	int flag = 0;
	for (child = element->FirstChildElement(); child != NULL && flag == 0; child = child->NextSiblingElement())
	{
		vector<Figure> aux;
		vector<Operation*> aux2;
		vector<Group> aux3;
		Group g;

        
		float x = 1, y = 1, z = 1; // Inicializar a 1 por do scale. Caso nao consiga ler Y, Y=0 e tem que ser 1. Daí usar QueryFloatSttribute tambem
		const char* n;
		double angle = 0;
		switch (hashF((char*)child->Value()))
		{
		case TRANSLATE:
			x = child->FloatAttribute("X");
			y = child->FloatAttribute("Y");
			z = child->FloatAttribute("Z");
			printf("deteta translate\n");
			(*ops).push_back(new Translate(x,y,z));
			break;
		case ROTATE:
			angle = child->FloatAttribute("angle");
			x = child->FloatAttribute("axisX");
			y = child->FloatAttribute("axisY");
			z = child->FloatAttribute("axisZ");
			printf("deteta rotate\n");
			(*ops).push_back(new Rotate(angle, x, y, z));
			break;
        case SCALE:
            child->QueryFloatAttribute("X", &x);
            child->QueryFloatAttribute("Y", &y);
            child->QueryFloatAttribute("Z", &z);
			printf("deteta scale\n");
			(*ops).push_back(new Scale(x, y, z));
            break;
		case MODELS:
			readModels(child, fig);
			break;
		case GROUP:
			readGroup(child, &aux, &aux2, &aux3);
			g.set_values(aux,aux2,aux3);
			(*subGroups).push_back(g);
			break;
		default:
			break;
		}
	}

	return XML_SUCCESS;
}


int readModels(XMLElement* models, vector<Figure>* fig) {
	if (models != nullptr) {
		XMLElement *model = models->FirstChildElement("model");
		while (model != nullptr) {
			const char * fileName = nullptr;
			fileName = model->Attribute("file");

			if (fileName == nullptr) return XML_ERROR_PARSING_ATTRIBUTE;

			Figure f = getFigure(fileName);
			(*fig).push_back(f);
			printf("a adicionar figura\n");
			model = model->NextSiblingElement("model");
		}

		models = models->NextSiblingElement("models");
		return XML_SUCCESS;
	}
	return XML_NO_TEXT_NODE;
}
