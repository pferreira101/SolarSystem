
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



void planeHandler(int size, char* destFile){

	string s = to_string(size/2) + ", 0, " + to_string(-size/2) + "\n" +
			   to_string(-size/2) + ", 0, " + to_string(-size/2) + "\n" + 
			   to_string(size/2) + ", 0, " + to_string(size/2) + "\n" + 
			   to_string(-size/2) + ", 0, " + to_string(-size/2) + "\n" +
			   to_string(-size/2) + ", 0, " + to_string(size/2) + "\n" +
			   to_string(size/2) + ", 0, " + to_string(size/2);

	fileWriter(destFile, s);
}

void boxHandler(int x, int y, int z, int d, char* destFile){
	string s;
	string x_str = to_string(x);
	string y_str = to_string(y);
	string z_str = to_string(z);
	float div = (float) y / d;
	float height = 0;

	// base
	s += "0, 0, " + z_str + "\n" +
		 x_str + ", 0, 0\n" +
		 x_str + ", 0, " + z_str +"\n" +		 
		 "0, 0, " + z_str + "\n" + 
		 "0, 0, 0\n" +
		 x_str + ", 0, 0\n";

	// faces
	for (int i = 0; i < d; i++, height += div) {
		string h_str = to_string(height);
		string h2_str = to_string(height + div);

		// frontal
		s += "0, " + h_str + ", " + z_str + "\n" +
			 x_str + ", " + h_str + ", " + z_str + "\n" +
			 x_str + ", " + h2_str + ", " + z_str + "\n" +
			 x_str + ", " + h2_str + ", " + z_str + "\n" +
			"0, " + h2_str + ", " + z_str + "\n" +
			"0, " + h_str + ", " + z_str + "\n";	

		// lateral visivel
		s += x_str + ", " + h_str + ", " + z_str + "\n" +
			 x_str + ", " + h_str + ", 0\n" +
			 x_str + ", " + h2_str + ", 0\n" +
			 x_str + ", " + h2_str + ", 0\n" +
			 x_str + ", " + h2_str + ", " + z_str + "\n" +
			 x_str + ", " + h_str + ", " + z_str + "\n";

		// lateral invisivel
		s += "0, " + h_str + ", " + z_str + "\n" +
			 "0, " + h2_str + ", 0\n" +
			 "0, " + h_str + ", 0\n" +
			 "0, " + h2_str + ", " + z_str + "\n" +
			 "0, " + h2_str + ", 0\n" + 
			 "0, " + h_str + ", " + z_str + "\n";

		// traseira
		s += "0, " + h2_str + ", 0\n" +
			 x_str + ", " + h2_str + ", 0\n" +
			 x_str + ", " + h_str + ", 0\n" +
			 "0, " + h2_str + ", 0\n" +
			 x_str + ", " + h_str + ", 0\n" +
			 "0, " + h_str + ", 0\n";
	}

	// topo
	s += "0, " + y_str + ", " + z_str + "\n" +
		 x_str + ", " + y_str + ", " + z_str + "\n" +
		 x_str + ", " + y_str + ", 0\n" +
		 "0, " + y_str + ", " + z_str + "\n" +
		 x_str + ", " + y_str + ", 0\n" +
		 "0, " + y_str + ", 0";

	fileWriter(destFile, s);
}


void sphereHandler(char* r, char* slices, char* stacks, char* destFile){
	string s; // = string("Guardar esfera com raio ") + r + ", " + slices + " slices e " + stacks + " stacks no ficheiro " + destFile + "\n";
	float raio = atof(r);
	int sli = atoi(slices);
	int sta = atoi(stacks);
	
	float a = 0;
	float stepSide = 2 * M_PI / sli;
	float stepUp = M_PI / sta;
	float b = 0;


	for (int i = 0; i < sli; i++) {
		//buildSliceSphere(radius, stacks, a, step);
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
			s.append(x4 + "," + y2 + "," + z4 + "\n");

		

		}

	}

	fileWriter(destFile, s);
}

void buildSlice(int stacks, float r, float h, string s, float a, float stepSide, float hips) {
	float stepUp = (float)(h / stacks);
	float stepInside = sqrt((hips*hips) - (stepUp*stepUp));
	float height = 0;
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
		string x = to_string(raio*cos(a));
		string x2 = to_string((raio*cos(a + step)));
		string z = to_string(raio * sin(a));
		string z2 = to_string(raio * sin(a + step));
		
		s.append("0,0,0\n");
		s.append(x + ",0," + z +"\n");
		s.append(x2 + ",0," + z2 +"\n");
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
