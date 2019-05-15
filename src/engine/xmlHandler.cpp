#include <xmlHandler.h>


string cur_dir;


/**
Função que interpreta um cen‡rio gr‡fico em XML
*/

int readXML(const char *filename, vector<Group>* groups , vector<Light*>* lights, float* cam){
	cur_dir = getDirectory(filename);	
	XMLDocument doc;
	XMLError error = doc.LoadFile(filename);
	if (error != XML_SUCCESS) { printf("Error: %i\n", error); return error; }

	XMLNode *scene = doc.FirstChild();
	if (scene == nullptr) return XML_ERROR_FILE_READ_ERROR;

	// CAMERA
	XMLElement *cam_xml = scene->FirstChildElement("camera");
	if (cam_xml != nullptr) {
		cam_xml->QueryFloatAttribute("x", &cam[0]);
		cam_xml->QueryFloatAttribute("y", &cam[1]);
		cam_xml->QueryFloatAttribute("z", &cam[2]);
	}

	// LIGHTS
	XMLElement *lights_xml = scene->FirstChildElement("lights");
	if(lights_xml != nullptr) {	
		XMLElement *light_xml = lights_xml->FirstChildElement("light");
		while (light_xml != nullptr) {
			
			(*lights).push_back(readLight(light_xml));

			light_xml = light_xml->NextSiblingElement("light");
		}	
	}

	// GROUPS
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
	int flag = 0; // PODEMOS RETIRAR ESTAR FLAG NÃO?
	int nr_points = 0;
	for (child = element->FirstChildElement(); child != NULL && flag == 0; child = child->NextSiblingElement())	{
		vector<Figure> aux;
		vector<Operation*> aux2;
		vector<Group> aux3;
		vector<Point> pts;
		Group g;

        
		float time, x = 1, y = 1, z = 1; // Inicializar a 1 por causa do scale. Caso nao consiga ler Y, Y=0 e tem que ser 1. Daí usar QueryFloatSttribute tambem
		double angle = 0;
		switch (hashF((char*)child->Value())){
			case TRANSLATE:
				if (child->FindAttribute("time") != NULL) {
					pts = * new std::vector<Point>;
					time = child->FloatAttribute("time");

					XMLElement* point;
					for (point = child->FirstChildElement(); point != NULL; point = point->NextSiblingElement()) {
						x = point->FloatAttribute("X");
						y = point->FloatAttribute("Y");
						z = point->FloatAttribute("Z");

						pts.push_back(* new Point(x, y, z));

						nr_points++; // para verificar no fim se são 4+
					}

					if (nr_points < 4) return -1;

					(*ops).push_back(new DynamicTranslate(time, pts));
				}
				else {
					x = child->FloatAttribute("X");
					y = child->FloatAttribute("Y");
					z = child->FloatAttribute("Z");

					(*ops).push_back(new Translate(x, y, z));

					
				}
				
				break;

			case ROTATE:
				if (child->FindAttribute("time") != NULL) { 
					time = child->FloatAttribute("time");
					x = child->FloatAttribute("axisX");
					y = child->FloatAttribute("axisY");
					z = child->FloatAttribute("axisZ");

					(*ops).push_back(new DynamicRotate(time, x, y, z));
					

				}
				else {
					angle = child->FloatAttribute("angle");
					x = child->FloatAttribute("axisX");
					y = child->FloatAttribute("axisY");
					z = child->FloatAttribute("axisZ");

					(*ops).push_back(new Rotate(angle, x, y, z));
					
				} 
				
				break;

			case SCALE:
				child->QueryFloatAttribute("X", &x);
				child->QueryFloatAttribute("Y", &y);
				child->QueryFloatAttribute("Z", &z);

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


int readModels(XMLElement* models, vector<Figure>* fig){
	if (models != nullptr) {
		XMLElement *model = models->FirstChildElement("model");
		while (model != nullptr) {
			const char * fileName = nullptr;
			fileName = model->Attribute("file");

			if (fileName == nullptr) return XML_ERROR_PARSING_ATTRIBUTE;
			
			string fname(fileName);
			string path = cur_dir+fname;

			float r = 0;
			float g = 0;
			float b = 0;
			int diff, spec, emi, amb;
			vector<Colour> colours;

			diff = model->QueryFloatAttribute("diffR",&r);
			if (diff != XML_NO_ATTRIBUTE){
				model->QueryFloatAttribute("diffG",&g);
				model->QueryFloatAttribute("diffB",&b);
				Colour colour;
				colour.set_rgb(r, g, b);
				colour.set_type(0);
				colours.push_back(colour);
			}

			spec = model->QueryFloatAttribute("specR",&r);
			if (spec != XML_NO_ATTRIBUTE){
				model->QueryFloatAttribute("specG",&g);
				model->QueryFloatAttribute("specB",&b);
				Colour colour;
				colour.set_rgb(r, g, b);
				colour.set_type(1);
				colours.push_back(colour);
			}

			emi = model->QueryFloatAttribute("emiR",&r);
			if (emi != XML_NO_ATTRIBUTE) {
				model->QueryFloatAttribute("emiG",&g);
				model->QueryFloatAttribute("emiB",&b);
				Colour colour;
				colour.set_rgb(r, g, b);
				colour.set_type(2);
				colours.push_back(colour);
			}

			amb = model->QueryFloatAttribute("ambR",&r);
			if (amb != XML_NO_ATTRIBUTE) {
				model->QueryFloatAttribute("ambG",&g);
				model->QueryFloatAttribute("ambB",&b);
				Colour colour;
				colour.set_rgb(r, g, b);
				colour.set_type(3);
				colours.push_back(colour);
			}

			const char* textureFile = nullptr;
			textureFile = model->Attribute("texture");

			Figure f;

			if (textureFile != nullptr) {
				string texPath = cur_dir + textureFile;

				f = getFigure(path, texPath);
			}

			else f = getFigure(path, "");

			f.set_colours(colours);

			(*fig).push_back(f);

			model = model->NextSiblingElement("model");
		}

		models = models->NextSiblingElement("models");
		return XML_SUCCESS;
	}
	return XML_NO_TEXT_NODE;
}


Light* readLight(XMLElement* light_element) {
	string type = light_element->Attribute("type");

	float *pos = (float*)malloc(sizeof(float) * 4); 
	pos[0] = pos[1] = pos[2] = pos[3] = 0.0f;

	float *diff = (float*)malloc(sizeof(float) * 4); 
	diff[0] = diff[1] = diff[2] = diff[3] = 1.0f;
	
	float *amb = (float*)malloc(sizeof(float) * 4);
	amb[0] = amb[1] = amb[2] = 0.8f; amb[3] = 1.0f;

	float *spec = (float*)malloc(sizeof(float) * 4);
	spec[0] = spec[1] = spec[2] = 0.0f; spec[3] = 1.0f;


	light_element->QueryFloatAttribute("posX", &pos[0]);
	light_element->QueryFloatAttribute("posY", &pos[1]);	
	light_element->QueryFloatAttribute("posZ", &pos[2]);
	pos[3] = 1;

	light_element->QueryFloatAttribute("diffR", &diff[0]);
	light_element->QueryFloatAttribute("diffG", &diff[1]);	
	light_element->QueryFloatAttribute("diffB", &diff[2]);

	light_element->QueryFloatAttribute("ambR", &amb[0]);
	light_element->QueryFloatAttribute("ambG", &amb[1]);
	light_element->QueryFloatAttribute("ambB", &amb[2]);

	light_element->QueryFloatAttribute("specR", &spec[0]);
	light_element->QueryFloatAttribute("specG", &spec[1]);
	light_element->QueryFloatAttribute("specB", &spec[2]);


	if (type.compare("DIRECTIONAL") == 0) {
		pos[3] = 0;

		return new LightDirectional(pos, diff, amb, spec);
	}	
	else if (type.compare("POINT") == 0) {
		float attenuation = 0;

		light_element->QueryFloatAttribute("attenuation", &attenuation);

		return new LightPoint(pos, diff, amb, spec, attenuation);
	}
	else if (type.compare("SPOT") == 0){
		float *dir = (float*)malloc(sizeof(float) * 3);
		dir[0] = dir[1] = dir[2] = 0;

		float angle = 45, exp;

		light_element->QueryFloatAttribute("dirX", &dir[0]);
		light_element->QueryFloatAttribute("dirY", &dir[1]);
		light_element->QueryFloatAttribute("dirZ", &dir[2]);

		light_element->QueryFloatAttribute("angle", &angle);
		light_element->QueryFloatAttribute("exponent", &exp);


		return new LightSpot(pos, diff, amb, spec, dir, angle, exp);
	}
}



string getDirectory(const string& name){
    size_t pos = name.find_last_of("/\\");
    string path = name.substr(0, pos+1);
    return ( pos != string::npos)? path : "";
}
