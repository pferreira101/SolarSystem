#include <figure.h>

vector<Point> getFilePoints(const string& name, std::vector<Point>* nms, std::vector<Point>* txs);

/**
Função que dado o nome de um ficheiro constroi a figura nele representada
*/
Figure getFigure(const string& name, string path){
	Figure f;
	vector<Point> normals;
	vector<Point> texture;
	vector<Point> points = getFilePoints(name, &normals,&texture);
	f.set_values(points, normals,texture,path);
	return f;
}

	

/**
Função que, partindo de um ficheiro gerado pelo programa 'generator', devolve a lista dos pontos existentes nesse ficheiro.
*/
vector<Point> getFilePoints(const string& name, std::vector<Point>* normals, std::vector<Point>* tex) {
	string point;
	ifstream file;
	file.open(name);

	string delimiter = ",";
	int delim_len = delimiter.length();
	vector<Point> points;
    
	while (!file.eof()) { // ler ficheiro completo
		getline(file, point); // ler uma linha
        
		while (point.compare("") != 0) {
			//if (!point.compare("")) break; // ultima linha do ficheiro Ž vazia, n‹o deve ser processada
			
			float x, y, z;

			sscanf(point.c_str(), "%f, %f, %f", &x, &y, &z);		

			Point p;
			p.set_values(x, y, z);

			points.push_back(p);//adicona novo elemento no fim do vector

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

	return points;
}
