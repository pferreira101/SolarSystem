#include "pch.h"
#include <iostream>
#include <string>
#include <fstream>
using namespace std;

//definação dos valores da funcao de hash para as figuras aceitaveis (nao podem ser calculados em run time
// para se puderem usar no switch
#define PLANE 5488
#define BOX 3161
#define SPHERE 7234
#define CONE 4000

int hashF(char* s){
	int r=0;
	for(int i=0; s[i]; i++){
		r += (s[i]*(10^i));
	}
	return r;
}


int fileWriter(string file, string content) {
  ofstream myfile;
  myfile.open(file);
  myfile << content;
  myfile.close();
  return 0;
}

void planeHandler(int size, char* destFile){

	//string s = string("Guardar quadrado com lado ") + std::to_string(size) + ", no ficheiro " + destFile + "\n";
	string s = "<" + to_string(size/2) + ", 0," + to_string(-size/2) + ",\n" +
					 to_string(-size/2) + ", 0," + to_string(-size/2) + ",\n" + 
					 to_string(size/2) + ", 0," + to_string(size/2) + ">\n" + 
			   "<" + to_string(-size/2) + ", 0," + to_string(-size/2) + ",\n" +
					 to_string(-size/2) + ", 0," + to_string(size/2) + ",\n" +
					 to_string(size/2) + ", 0," + to_string(size/2) + ">";

	fileWriter(destFile, s);
}

void boxHandler(int x, int y, int z, int d, char* destFile){
	string s;
	string x_str = to_string(x);
	string y_str = to_string(y);
	string z_str = to_string(z);
	float div = y / d;
	float height = 0;

	// base
	s += "<0, 0, " + z_str + ",\n" +
		 x_str + ", 0, 0,\n" +
		 x_str + ", 0, " + z_str + ">\n" +		 
		"<0, 0, " + z_str + ",\n" + 
		"0, 0, 0,\n" +
		x_str + ", 0, 0>\n";

	// faces
	for (int i = 0; i < d; i++, height += div) {
		string h_str = to_string(height);
		string h2_str = to_string(height + div);

		// frontal
		s += "<triangle>\n\t<point X=0 Y=" + h_str + " Z=" + z_str + "\>\n" +
			"\t<point X=" + x_str + " Y=" + h_str + " Z=" + z_str + "\>\n" +
			"\t<point X=" + x_str + " Y=" + h2_str + " Z=" + z_str + "\>\n" + "</triangle>\n" +
			"<triangle>\n\t<point X=" + x_str + " Y=" + h2_str + " Z=" + z_str + "\>\n" +
			"\t<point X=0 Y=" + h2_str + " Z=" + z_str + "\>\n" +
			"\t<point X=0 Y=" + h_str + " Z=" + z_str + "\>\n" + "</triangle>\n";
			

		// lateral visivel
		s += "<" + x_str + ", " + h_str + ", " + z_str + ",\n" +
			x_str + ", " + h_str + ", 0,\n" +
			x_str + ", " + h2_str + ", 0>\n" +
			"<" + x_str + ", " + h2_str + ", 0,\n" +
			x_str + ", " + h2_str + ", " + z_str + ",\n" +
			x_str + ", " + h_str + ", " + z_str + ">\n";

		// lateral invisivel

		// traseira
	}

	// topo
	s += "<0, " + y_str + ", " + z_str + ",\n" +
		x_str + ", " + y_str + ", " + z_str + ",\n" +
		x_str + ", " + y_str + ", 0>\n" +
		"<0, " + y_str + ", " + z_str + ",\n" +
		x_str + ", " + y_str + ", 0,\n" +
		"0, " + y_str + ", 0>\n";
	/*
	if (d == 0) {
		s = string("Guardar caixa com x ") + x + ", y " + y + " e z " + z + " no ficheiro " + destFile + " \n";
	} 
	else {
		s = string("Guardar caixa com x ") + x + ", y " + y + ", z " + z + " e " + d + " dimensoes  no ficheiro " + destFile + " \n";
	}
	*/

	fileWriter(destFile, s);
}

void sphereHandler(char* r, char* slices, char* stacks, char* destFile){
	string s = string("Guardar esfera com raio ")+ r +", "+ slices +" slices e "+ stacks +" stacks no ficheiro "+ destFile +"\n";
	fileWriter(destFile, s);
}

void coneHandler(char* r, char* h, char* slices, char* stacks, char* destFile){
	string s = string("Guardar cone cujo raio da base é ")+ r +", tem altura "+ h +" com "+ slices +" slices e "+ stacks +" stacks no ficheiro "+ destFile +" \n";
	fileWriter(destFile, s);
} 

int main(int argc, char** argv){
	int error_flag=0;

	if (argc == 1) return -1;

	switch (hashF(argv[1])){
    	case PLANE:
        	if(argc == 4) planeHandler(atoi(argv[2]), argv[3]);
        	else error_flag = 1;
        	break;

    	case BOX:
        	if(argc >= 6){
        		int dim = 1;
				char* fdest = argv[5];
				
				if(argc == 7) { 
					dim = atoi(argv[5]); 
					fdest = argv[6];
				}
				boxHandler(atoi(argv[2]), atoi(argv[3]), atoi(argv[4]), dim, fdest);
        	}
        	else error_flag = 1;
        	break;

    	case SPHERE:
       	 	if(argc == 6) sphereHandler(argv[2], argv[3], argv[4], argv[5]);	
       	 	else error_flag = 1;
        	break;

        case CONE:
       	 	if(argc == 7) coneHandler(argv[2], argv[3], argv[4], argv[5], argv[6]);
       	 	else error_flag = 1;
        	break;

    	default:
       		printf("Por favor, insira um sólido válido. \n");
        	break;
    }

    if(error_flag) printf("Por favor insira todos os parâmetros necessários. \n");

	return 1;

}
