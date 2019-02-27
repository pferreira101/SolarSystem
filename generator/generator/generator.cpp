#include "pch.h"
#include <iostream>
#include <string>
#include <fstream>

#define _USE_MATH_DEFINES
#include <math.h>
#include <stdio.h>
#include <string>  

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

void planeHandler(char* size, char* destFile){
	string s = string("Guardar quadrado com lado ")+ size +", no ficheiro "+ destFile +"\n";
	fileWriter(destFile, s);
}

void boxHandler(char* x, char* y, char* z, char* d, char* destFile){
	string s;
	if(!d) s = string("Guardar caixa com x ")+ x +", y "+ y +" e z "+ z +" no ficheiro "+ destFile +" \n";
	else s = string("Guardar caixa com x ") + x +", y "+ y +", z "+ z +" e "+ d +" dimensoes  no ficheiro "+ destFile +" \n";
	fileWriter(destFile, s);
}

void sphereHandler(char* r, char* slices, char* stacks, char* destFile){
	string s = string("Guardar esfera com raio ")+ r +", "+ slices +" slices e "+ stacks +" stacks no ficheiro "+ destFile +"\n";
	fileWriter(destFile, s);
}

void buildSlice(int stacks, float r, float h, string s, float a, float stepSide, float hips) {
	float stepUp = (float)(h / stacks);
	float stepInside = sqrt((hips*hips) - (stepUp*stepUp));
	float height = 0;
	for (int i = 0; i < stacks - 1; i++) {
		s.append(to_string(r*cos(a)) + "," + to_string(height) + "," + to_string(r*sin(a)) + "\n");
		s.append(to_string((r - stepInside)*cos(a)) + "," + 
				to_string(height + stepUp) + "," 
					+ to_string((r - stepInside)*sin(a)) + "\n");
		s.append(to_string((r - stepInside)*cos(a + stepSide)) + "," 
				+ to_string(height + stepUp) + "," 
					+ to_string((r - stepInside)*sin(a + stepSide)) + "\n");

		
		s.append(to_string((r - stepInside)*cos(a + stepSide)) + "," 
				+ to_string(height + stepUp) + "," 
					+ to_string((r - stepInside)*sin(a + stepSide)) + "\n");
		s.append(to_string(r*cos(a + stepSide)) + "," 
				+ to_string(height) + ","
					+ to_string(r*sin(a + stepSide)) + "\n");
		s.append(to_string(r*cos(a)) + "," 
				+ to_string(height) + "," 
			+ to_string(r*sin(a)) + "\n");
		
		height += stepUp;
		r -= stepInside;

	}

	s.append("0," + to_string(h) + ",0\n");
	s.append(to_string(r*cos(a + stepSide)) + "," 
		+ to_string(height) + "," 
			+ to_string(r*sin(a + stepSide)) + "\n");
	s.append(to_string(r*cos(a)) + "," 
		+ to_string(height) + "," 
			+ to_string(r*sin(a)) + "\n");
}

void coneHandler(char* r, char* h, char* slices, char* stacks, char* destFile){
	string s;// = string("Guardar cone cujo raio da base é ")+ r +", tem altura "+ h +" com "+ slices +" slices e "+ stacks +" stacks no ficheiro "+ destFile +" \n";
	float raio = atof(r);
	float altura = atof(h);
	int sli = atoi(slices);
	int sta = atoi(stacks);
	float a = 0;
	float step = 2 * M_PI / sli;
	float hip = sqrt((raio*raio) + (altura*altura));
	for (int i = 0; i < sli; i++) {
		s.append("0,0,0\n");
		s.append(to_string(raio*cos(a)) + ",0," + to_string(raio * sin(a)) +"\n");
		s.append(to_string((raio*cos(a + step))) + ",0," + to_string(raio * sin(a + step)) +"\n");
		a += step;
		buildSlice(sta,raio,altura,s,a,step,hip/atoi(stacks));
	}	
	fileWriter(destFile, s);
} 

int main(int argc, char** argv){
	int error_flag=0;

	if (argc == 1) return -1;

	switch (hashF(argv[1])){
    	case PLANE:
        	if(argc == 4) planeHandler(argv[2],argv[3]);
        	else error_flag = 1;
        	break;

    	case BOX:
        	if(argc >= 6){
        		char* dim = NULL;
				char* fdest = argv[5];
				if(argc == 7) { dim = argv[5]; fdest = argv[6];}

				boxHandler(argv[2],argv[3],argv[4],dim,fdest);
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
       		printf("Por favor, insira um sólido válido.\n");
        	break;
    }

    if(error_flag) printf("Por favor insira todos os parâmetros necessários\n");

	return 1;

}
