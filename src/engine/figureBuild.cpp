#include <figure.h>

vector<Point> getFilePoints(const string& name);

/**
Função que dado o nome de um ficheiro constroi a figura nele representada
*/
Figure getFigure(const string& name){
	Figure f;
	f.set_values(getFilePoints(name));
	return f;
}

	

/**
Função que, partindo de um ficheiro gerado pelo programa 'generator', devolve a lista dos pontos existentes nesse ficheiro.
*/
vector<Point> getFilePoints(const string& name) {
	string point;
	ifstream file;
	file.open(name);

	string delimiter = ",";
	int delim_len = delimiter.length();
	vector<Point> points;
    
	while (!file.eof()) { // ler ficheiro completo
		getline(file, point); // ler uma linha
        if(!point.compare("")) break; // ultima linha do ficheiro Ž vazia, n‹o deve ser processada
        string token;
		float coord[3];
		int i = 0;

		int pos_start = 0, pos_end;

		while (i<3) {
			pos_end = point.find(delimiter, pos_start);
            token = point.substr(pos_start, pos_end-pos_start);
			coord[i++] = stof(token);
			pos_start = pos_end + delim_len;
		}

		Point p;
		p.set_values(coord[0], coord[1], coord[2]);

		points.push_back(p);//adicona novo elemento no fim do vector
		
	}
	file.close();
	return points;
}
