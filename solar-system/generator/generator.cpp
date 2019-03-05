#include <fstream>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>

using namespace std;
#define _USE_MATH_DEFINES

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
Função responsável por calcular os pontos dos dois triângulos que compêm
uma figura do tipo 'plane'
*/
void planeHandler(float size, char* destFile){
    float x1 = size/2;
    float x2 = -1*x1;
    float z1 = size/2;
    float z2 = -1*z1;
    char* p;
    asprintf(&p,
            "%f,0,%f\n"
            "%f,0,%f\n"
            "%f,0,%f\n"
            "%f,0,%f\n"
            "%f,0,%f\n"
            "%f,0,%f",
            x1,z2,
            x2,z2,
            x1,z1,
            x2,z2,
            x2,z1,
            x1,z1);

	fileWriter(destFile, p);
    free(p);
}

/**
 Função responsável por calcular os pontos dos triângulos que compêm
 uma figura do tipo 'box', centrada na origem
 */
void boxHandler(float x, float y, float z, int d, char* destFile){
	string s;
	string x_str = to_string(x);
	string y_str = to_string(y);
	string z_str = to_string(z);
	double div = (double) y / d;
	double height = 0;
    float x1 = x/2;
    float y1 = y/2;
    float z1 = z/2;
    

    

    // topo
    /*
             s += "0," + y_str + "," + z_str + "\n" +
             x_str + "," + y_str + "," + z_str + "\n" +
             x_str + "," + y_str + ",0\n" +
             "0," + y_str + "," + z_str + "\n" +
             x_str + "," + y_str + ",0\n" +
             "0," + y_str + ",0";
    */
    /*
	// faces
	for (int i = 0; i < d; i++, height += div) {
		string h_str = to_string(height);
		string h2_str = to_string(height + div);

		// frontal
		s += "0," + h_str + "," + z_str + "\n" +
			 x_str + "," + h_str + "," + z_str + "\n" +
			 x_str + "," + h2_str + "," + z_str + "\n" +
			 x_str + "," + h2_str + "," + z_str + "\n" +
			"0," + h2_str + "," + z_str + "\n" +
			"0," + h_str + "," + z_str + "\n";	

		// lateral visivel
		s += x_str + "," + h_str + "," + z_str + "\n" +
			 x_str + "," + h_str + ",0\n" +
			 x_str + "," + h2_str + ",0\n" +
			 x_str + "," + h2_str + ",0\n" +
			 x_str + "," + h2_str + "," + z_str + "\n" +
			 x_str + "," + h_str + "," + z_str + "\n";

		// lateral invisivel
		s += "0," + h_str + "," + z_str + "\n" +
			 "0," + h2_str + ",0\n" +
			 "0," + h_str + ",0\n" +
			 "0," + h2_str + "," + z_str + "\n" +
			 "0," + h2_str + ",0\n" + 
			 "0," + h_str + "," + z_str + "\n";

		// traseira
		s += "0," + h2_str + ",0\n" +
			 x_str + "," + h2_str + ",0\n" +
			 x_str + "," + h_str + ",0\n" +
			 "0," + h2_str + ",0\n" +
			 x_str + "," + h_str + ",0\n" +
			 "0," + h_str + ",0\n";
	}
    */
    //calcular pontos da base e do topo (diferem no valor y)
    for(int i=0;i<2;i++){
        if(i==1) {y1*=-1;x1*=-1;}//inverte y e x para desenhar face oposta
        
        char* base;
        asprintf(&base,
                 "%f,%f,%f\n"
                 "%f,%f,%f\n"
                 "%f,%f,%f\n"
                 "%f,%f,%f\n"
                 "%f,%f,%f\n"
                 "%f,%f,%f",
                 x1,y1,z1,
                 x1,y1,-z1,
                 -x1,y1,-z1,
                 -x1,y1,-z1,
                 -x1,y1,z1,
                 x1,y1,z1);
        s.append(base);
        if(i==0)s.append("\n");
        free(base);
    }
    y1*=-1; //recuperar valores originais
    x1*=-1;

    
	fileWriter(destFile, s);
}


void sphereHandler(char* r, char* slices, char* stacks, char* destFile){
	string s = ""; // = string("Guardar esfera com raio ") + r + "," + slices + " slices e " + stacks + " stacks no ficheiro " + destFile + "\n";
	double raio = atof(r);
	int sli = atoi(slices);
	int sta = atoi(stacks);
	
	double a = 0;
	double stepSide = 2 * M_PI / sli;
	double stepUp = M_PI / sta;
	double b = 0;


	for (int i = 0; i < sli; i++) {
		a = i * stepSide;
		for (int j = 0; j < sta; j++) {
			b = j * stepUp;

			string x = to_string(raio*sin(b)*sin(a));
			string x2 = to_string(raio*sin(b + stepUp)*sin(a));
			string x3 = to_string(raio*sin(b + stepUp)*sin(a + stepSide));
			string x4 = to_string(raio*sin(b)*sin(a + stepSide));
			string y = to_string(raio*cos(b));
			string y2 = to_string(raio*cos(b + stepUp));
			string z = to_string(raio*sin(b)*cos(a));
			string z2 = to_string(raio*sin(b + stepUp)*cos(a));
			string z3 = to_string(raio*sin(b + stepUp)*cos(a + stepSide));
			string z4 = to_string(raio*sin(b)*cos(a + stepSide));

		
			s.append(x + "," + y + "," + z + "\n");
			s.append(x2 + "," + y2 + "," + z2 + "\n");
			s.append(x3 + "," + y2 + "," + z3 + "\n");

			s.append(x + "," + y + "," + z + "\n");
			s.append(x3 + "," + y2 + "," + z3 + "\n");
			if (i == sli - 1 && j == sta - 1) {
				s.append(x4 + "," + y+ "," + z4);
			}
			else {
				s.append(x4 + "," + y + "," + z4 + "\n");
			}
		

		}

	}

	fileWriter(destFile, s);
}

string buildSlice(int stacks, double r, double h, string s, double a, double stepSide, double hips) {
	double stepUp = (double)(h / stacks);
	double stepInside = sqrt((hips*hips) - (stepUp*stepUp));
	double height = 0;
	for (int i = 0; i < stacks - 1; i++) {
		string x = to_string(r*cos(a));
		string x2 = to_string((r - stepInside)*cos(a));
		string x3 = to_string((r - stepInside)*cos(a + stepSide));
		string x4 = to_string(r*cos(a + stepSide));
		string y = to_string(height);
		string y2 = to_string(height + stepUp);
		string z = to_string(r*sin(a));
		string z2 = to_string((r - stepInside)*sin(a));
		string z3 = to_string((r - stepInside)*sin(a + stepSide));
		string z4 = to_string(r*sin(a + stepSide));

		s.append(x + "," + y + "," + z + "\n");
		s.append(x2 + "," + y2 + "," + z2 + "\n");
		s.append(x3 + "," + y2 + "," + z3 + "\n");

		
		s.append(x3 + "," + y2 + "," + z3 + "\n");
		s.append(x4 + "," + y + ","+ z4 + "\n");
		s.append(x + "," + y + "," + z + "\n");
		
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

	return s;
}

void coneHandler(char* r, char* h, char* slices, char* stacks, char* destFile){
	string s;// = string("Guardar cone cujo raio da base é ")+ r +", tem altura "+ h +" com "+ slices +" slices e "+ stacks +" stacks no ficheiro "+ destFile +" \n";
	double raio = atof(r);
	double altura = atof(h);
	int sli = atoi(slices);
	int sta = atoi(stacks);
	double a = 0;
	double step = 2 * M_PI / sli;
	double hip = sqrt((raio*raio) + (altura*altura));
	for (int i = 0; i < sli; i++) {
		string x = to_string(raio*cos(a));
		string x2 = to_string((raio*cos(a + step)));
		string z = to_string(raio * sin(a));
		string z2 = to_string(raio * sin(a + step));
		a += step;
		s = buildSlice(sta, raio, altura, s, a, step, hip / atoi(stacks));
		s.append("0,0,0\n");
		s.append(x + ",0," + z +"\n");
		if (i == sli - 1) {
			s.append(x2 + ",0," + z2);
		}
		else {
			s.append(x2 + ",0," + z2 + "\n");
		}
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
    printf("Ok\n");
	return 1;

}
