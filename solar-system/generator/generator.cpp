#include "asprintf.h"
#include <fstream>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>

#define _USE_MATH_DEFINES
#include <math.h>

using namespace std;

/**
 Definação dos valores da funcao de hash para as figuras aceitaveis
 - não podem ser calculados em run time para se puderem usar no switch
 */
#define PLANE 5488
#define BOX 3161
#define SPHERE 7234
#define CONE 4000

/**
 Função auxiliar para calcular o valor do argv[1] a usar
 */
int hashF(char* s){
	int r=0;
	for(int i=0; s[i]; i++){
		r += (s[i]*(10^i));
	}
	return r;
}

/**
 Função para realizar escritas no ficheiro passado como argumento
 */
int fileWriter(string file, string content) {
	ofstream myfile;
	myfile.open(file);
	myfile << content;
	myfile.close();
	return 0;
}

/**
Função responsável por calcular os pontos dos dois triângulos que compõem
uma figura do tipo 'plane'
*/
void planeHandler(double size, char* destFile){
    double x1 = size/2;
    double x2 = -1*x1;
    double z1 = size/2;
    double z2 = -1*z1;

    string s = "";
    
    string p1 = to_string(x1) + ",0," + to_string(z2) + "\n";
    string p2 = to_string(x2) + ",0," + to_string(z2) + "\n";
    string p3 = to_string(x1) + ",0," + to_string(z1) + "\n";
    string p4 = to_string(x2) + ",0," + to_string(z1) + "\n";
    
    s.append(p1);
    s.append(p2);
    s.append(p3);
    s.append(p2);
    s.append(p4);
    s.append(p3);
    
	fileWriter(destFile, s);
}

/**
 Função responsável por calcular os pontos dos triângulos que compõem
 uma figura do tipo 'box', centrada na origem
 */
void boxHandler(double x, double y, double z, int d, char* destFile){
	string s="";
	double div = (double) y / d;
	double height = -y/2;
    double x1 = x/2;
    double y1 = y/2;
    double z1 = z/2;
    
    //calcular pontos da base e do topo (diferem no valor y)
    for(int i=0;i<2;i++){
        if(i==1) {
            y1*=-1; //simetrico de y para desenhar face oposta
            x1*=-1; //simetrico de x por causa do vetor normal
        }
        string p1 = to_string(x1) + "," + to_string(y1) + "," + to_string(z1) + "\n";
        string p2 = to_string(x1) + "," + to_string(y1) + "," + to_string(-z1) + "\n";
        string p3 = to_string(-x1) + "," + to_string(y1) + "," + to_string(z1) + "\n";
        string p4 = to_string(-x1) + "," + to_string(y1) + "," + to_string(-z1) + "\n";
        
        s.append(p1);
        s.append(p2);
        s.append(p3);
        s.append(p3);
        s.append(p2);
        s.append(p4);
    }
    y1*=-1; //recuperar valores originais
    x1*=-1;
    
    
    for (int i = 0; i < d; i++, height += div) { // desenhar os varios segmentos da caixa
        double y2 = height+div;
        
        for(int j=0; j<2; j++){ // desenhar faces paralelas ao eixo do x (diferem no valor z)
            if(j==1) {
                z1*=-1; //simetrico de z para desenhar face oposta
                x1*=-1; //simetrico de x por causa do vetor normal
            }
            
            string p1 = to_string(x1) + "," + to_string(height) + "," + to_string(z1) + "\n";
            string p2 = to_string(-x1) + "," + to_string(y2) + "," + to_string(z1) + "\n";
            string p3 = to_string(-x1) + "," + to_string(height) + "," + to_string(z1) + "\n";
            string p4 = to_string(x1) + "," + to_string(y2) + "," + to_string(z1) + "\n";
            
            s.append(p1);
            s.append(p2);
            s.append(p3);
            s.append(p1);
            s.append(p4);
            s.append(p2);
        }
        z1*=-1; // recuperar valores originais
        x1*=-1;
        
        for(int j=0; j<2; j++){ // desenhar faces paralelas ao eixo do z (diferem no valor x)
            if(j==1) {
                z1*=-1; //simetrico de z por causa do vetor normal
                x1*=-1; //simetrico de x para desenhar face oposta
            }
            
            string p1 = to_string(x1) + "," + to_string(height) + "," + to_string(z1) + "\n";
            string p2 = to_string(x1) + "," + to_string(height) + "," + to_string(-z1) + "\n";
            string p3 = to_string(x1) + "," + to_string(y2) + "," + to_string(z1) + "\n";
            string p4 = to_string(x1) + "," + to_string(y2) + "," + to_string(-z1) + "\n";
            
            s.append(p1);
            s.append(p2);
            s.append(p3);
            s.append(p2);
            s.append(p4);
            s.append(p3);
        }
    }

    
	fileWriter(destFile, s);
}

/**
 Função responsável por os pontos dos triângulos que compõem uma figura do tipo 'sphere', centrada
 na origem
 */
void sphereHandler(double raio, int slices, int stacks, char* destFile){
	string s = "";
	double a = 0;
	double stepSide = 2 * M_PI / slices;
	double stepUp = M_PI / stacks;
	double b = 0;

	for (int i = 0; i < slices; i++){
		a = i * stepSide;
		for (int j = 0; j < stacks; j++){
			b = j * stepUp;
            
            double x1 = raio*sin(b)*sin(a);
            double x2 = raio*sin(b + stepUp)*sin(a);
            double x3 = raio*sin(b + stepUp)*sin(a + stepSide);
            double x4 = raio*sin(b)*sin(a + stepSide);
            double y1 = raio*cos(b);
            double y2 = raio*cos(b + stepUp);
            double z1 = raio*sin(b)*cos(a);
            double z2 = raio*sin(b + stepUp)*cos(a);
            double z3 = raio*sin(b + stepUp)*cos(a + stepSide);
            double z4 = raio*sin(b)*cos(a + stepSide);
            
            string p1 = to_string(x1) + "," + to_string(y1) + "," + to_string(z1) + "\n";
            string p2 = to_string(x2) + "," + to_string(y2) + "," + to_string(z2) + "\n";
            string p3 = to_string(x3) + "," + to_string(y2) + "," + to_string(z3) + "\n";
            string p4 = to_string(x4) + "," + to_string(y1) + "," + to_string(z4) + "\n";
		
			s.append(p1);
			s.append(p2);
			s.append(p3);

			s.append(p1);
			s.append(p3);
            s.append(p4);
		}
	}

	fileWriter(destFile, s);
}

/**
 Função auxiliar ao desenho de uma figura do tipo 'cone'. Calcula os pontos
 dos triângulos que compõem uma slice do cone.
 */
string buildSlice(int stacks, double r, double h, string s, double a, double stepSide, double hips) {
	double stepUp = (double)(h / stacks);
	double stepInside = sqrt((hips*hips) - (stepUp*stepUp));
	double height = 0;
    string p1;
    string p2;
    string p3;
    string p4;
    
	for (int i = 0; i < stacks - 1; i++) {
        double x1 = r*cos(a);
        double x2 = (r - stepInside)*cos(a);
        double x3 = (r - stepInside)*cos(a + stepSide);
        double x4 = r*cos(a + stepSide);
        double y1 = height;
        double y2 = height + stepUp;
        double z1 = r*sin(a);
        double z2 = (r - stepInside)*sin(a);
        double z3 = (r - stepInside)*sin(a + stepSide);
        double z4 = r*sin(a + stepSide);
        
        p1 = to_string(x1) + "," + to_string(y1) + "," + to_string(z1) + "\n";
        p2 = to_string(x2) + "," + to_string(y2) + "," + to_string(z2) + "\n";
        p3 = to_string(x3) + "," + to_string(y2) + "," + to_string(z3) + "\n";
        p4 = to_string(x4) + "," + to_string(y1) + "," + to_string(z4) + "\n";
        
        s.append(p1);
        s.append(p2);
        s.append(p3);
        
        s.append(p3);
        s.append(p4);
        s.append(p1);
        
		height += stepUp;
		r -= stepInside;

	}

    // "cobertura" do cone
	s.append("0," + to_string(h) + ",0\n");
    s.append(p3);
    s.append(p2);
    
	return s;
}
/**
 Função responsável por calcular os pontos que formam uma figura do tipo 'cone'.
 */
void coneHandler(double raio, double altura, int slices, int stacks, char* destFile){
	string s;
	double a = 0;
	double step = 2 * M_PI / slices;
	double hip = sqrt((raio*raio) + (altura*altura));
    
	for (int i = 0; i < slices; i++) {
		string x1 = to_string(raio*cos(a));
		string x2 = to_string((raio*cos(a + step)));
		string z1 = to_string(raio * sin(a));
		string z2 = to_string(raio * sin(a + step));
        
		a += step;
		s = buildSlice(stacks, raio, altura, s, a, step, hip / stacks);
		
        // desenhar a base do cone
        s.append("0,0,0\n");
		s.append(x1 + ",0," + z1 +"\n");
        s.append(x2 + ",0," + z2 + "\n");
	}	
	fileWriter(destFile, s);
} 

int main(int argc, char** argv){
	int error_flag=0;

	if (argc == 1) return -1;

	switch (hashF(argv[1])){
    	case PLANE:
        	if(argc == 4) planeHandler(atof(argv[2]), argv[3]);
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
				boxHandler(atof(argv[2]), atof(argv[3]), atof(argv[4]), dim, fdest);
        	}
        	else error_flag = 1;
        	break;

    	case SPHERE:
       	 	if(argc == 6) sphereHandler(atof(argv[2]), atoi(argv[3]), atoi(argv[4]), argv[5]);
       	 	else error_flag = 1;
        	break;

        case CONE:
       	 	if(argc == 7) coneHandler(atof(argv[2]), atof(argv[3]), atoi(argv[4]), atoi(argv[5]), argv[6]);
       	 	else error_flag = 1;
        	break;

    	default:
       		printf("Por favor, insira um sólido válido. \n");
        	break;
    }
    


    if(error_flag) printf("Por favor insira todos os parâmetros necessários. \n");
    printf("Ok\n");
	return 1;

}
