#include <figure.h>


/**
Função que dado o nome de um ficheiro constroi a figura nele representada
*/
Figure getFigure(const char *name){
	Figure f;
	f.set_values(getTriangles(getPoints(name)));
	printf("a retornar figura\n");
	return f;
}

/**
Fun‹o que constrói uma lista de tri‰ngulos consoante a lista de pontos que recebe como par‰metro
*/
vector<Triangle> getTriangles(vector<Point> points) {	
	vector<Triangle> triangles;
	Point pts[3];
	int i = 0;
	int counter=0;
	for (vector<Point>::const_iterator it = points.begin(); it != points.end(); ++it) {

		if (i == 3) i = 0;
		
		pts[i] = (*it);

		if (i == 2) { // ver se Ž o 3o ponto e formar triangulo
			Triangle t;
			t.set_values(pts[0], pts[1], pts[2]);
			triangles.push_back(t);
			printf("adicionei %d triangulo\n",counter++);
		}

		i++;
	}
	return triangles;
}

	

/**
Fun‹o que, partindo de um ficheiro gerado pelo programa 'generator', devolve a lista dos pontos existentes nesse ficheiro.
*/
vector<Point> getPoints(const char *name) {
	string point;
	ifstream file;
	printf("vou tentar abrir ficheiro %s\n", name);
	file.open(name);

	string delimiter = ",";
	int delim_len = delimiter.length();
	vector<Point> points;
	int count=0;
    
	while (!file.eof()) { // ler ficheiro completo
		printf("a consultar ficheiro\n");
		getline(file, point); // ler uma linha
        if(!point.compare("")){ printf("linha vazia\n"); break;} // ultima linha do ficheiro Ž vazia, n‹o deve ser processada
		else printf("linha nao vazia\n");
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
		printf("a adicionar um ponto: %d\n",count++);
		points.push_back(p);//adicona novo elemento no fim do vector
		
	}
	file.close();
	printf("a retornar vetor com %d pontos\n", points.size());
	return points;
}
