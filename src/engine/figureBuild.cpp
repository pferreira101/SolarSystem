#include <figure.h>

int getFilePoints(const string& name, std::vector<Point>* pts, std::vector<Point>* nms, std::vector<Point>* txs);

/**
Função que dado o nome de um ficheiro constroi a figura nele representada
*/
Figure getFigure(const string& name, string path){
	Figure f;
	vector<Point> normals;
	vector<Point> texture;
	vector<Point> points;
	int type = getFilePoints(name, &points, &normals, &texture);
	f.set_values(type, points, normals, texture, path);
	return f;
}

	

/**
Função que, partindo de um ficheiro gerado pelo programa 'generator', devolve a lista dos pontos existentes nesse ficheiro.
*/
int getFilePoints(const string& name, std::vector<Point>* points, std::vector<Point>* normals, std::vector<Point>* tex) {
	int type;
	string point;
	ifstream file;
	file.open(name);

	string delimiter = ",";
	int delim_len = delimiter.length();
    
	getline(file, point); // ler uma linha
	sscanf(point.c_str(), "%d", &type);

	while (!file.eof()) { // ler ficheiro completo
		getline(file, point); // ler uma linha
        
		while (point.compare("") != 0) {
			//if (!point.compare("")) break; // ultima linha do ficheiro Ž vazia, n‹o deve ser processada
			
			float x, y, z;

			sscanf(point.c_str(), "%f, %f, %f", &x, &y, &z);		

			Point p;
			p.set_values(x, y, z);

			(*points).push_back(p);//adicona novo elemento no fim do vector

			getline(file, point);
		}

		getline(file, point);
		while (point.compare("") != 0) {
			//if (!point.compare("")) break; // ultima linha do ficheiro Ž vazia, n‹o deve ser processada
			float x, y, z;

			sscanf(point.c_str(), "%f, %f, %f", &x, &y, &z);

			Point p;
			p.set_values(x, y, z);

			(*normals).push_back(p);//adicona novo elemento no fim do vector

			getline(file, point);
		}

		getline(file, point);
		while (point.compare("") != 0) {
			//if (!point.compare("")) break; // ultima linha do ficheiro Ž vazia, n‹o deve ser processada
			float x, y;

			sscanf(point.c_str(), "%f, %f", &x, &y);

			Point p;
			p.set_values(x, y, 0);

			(*tex).push_back(p);//adicona novo elemento no fim do vector

			getline(file, point);
		}

	}
	file.close();

	return type;
}
