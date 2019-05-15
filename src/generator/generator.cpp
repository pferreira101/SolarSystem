#include <fstream>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <hash.h>
#include <figure.h>
#include <matrixOperations.h>

#define _USE_MATH_DEFINES
#include <math.h>

using namespace std;



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
void planeHandler(float size, char* destFile){
    float x1 = size/2;
    float x2 = -1*x1;
    float z1 = size/2;
    float z2 = -1*z1;

    string s = "0\n";
	string n = "";
	string t = "";

    string p1 = to_string(x2) + ",0," + to_string(z2) + "\n";
    string p2 = to_string(x2) + ",0," + to_string(z1) + "\n";
    string p3 = to_string(x1) + ",0," + to_string(z1) + "\n";
    string p4 = to_string(x1) + ",0," + to_string(z2) + "\n";
    
    s.append(p1);
    s.append(p2);
    s.append(p3);
    s.append(p1);
    s.append(p3);
    s.append(p4);

	// normais

	n.append("0,1,0\n");
	n.append("0,1,0\n");
	n.append("0,1,0\n");
	n.append("0,1,0\n");
	n.append("0,1,0\n");
	n.append("0,1,0\n");

	s.append("\n" + n);

	// textura

	t.append("0,1\n");
	t.append("0,0\n");
	t.append("1,0\n");
	t.append("0,1\n");
	t.append("1,0\n");
	t.append("1,1\n");
    
	s.append("\n" + t);

	fileWriter(destFile, s);
}

/**
 Função responsável por calcular os pontos dos triângulos que compõem
 uma figura do tipo 'box', centrada na origem
 */
void boxHandler(float x, float y, float z, int d, char* destFile){
	string s="1\n";
	string n = "";
	float divY = (float) y / d;
    float divZ = (float) z / d;
    float divX = (float) x / d;
    float x1, y1, z1, x2, y2, z2;

    
    //pontos da base e do topo (diferem no valor y) (faces paralelas ao plano xOz)
    x1=x/2;
    y1=y/2;
    z1=z/2;
    for(int i=0; i<d; i++, x1 -= divX){
        x2 = x1-divX;
        for (int j = 0; j < d; j++, z1 -= divZ) {
            z2 = z1-divZ;
            for(int k=0;k<2;k++){
                if(k==1) {
                    y1*=-1; //simetrico de y para desenhar face oposta
                    x1*=-1; //simetrico de x por causa do vetor normal
                    x2*=-1;
                }
                string p1 = to_string(x1) + "," + to_string(y1) + "," + to_string(z1) + "\n";
                string p2 = to_string(x1) + "," + to_string(y1) + "," + to_string(z2) + "\n";
                string p3 = to_string(x2) + "," + to_string(y1) + "," + to_string(z1) + "\n";
                string p4 = to_string(x2) + "," + to_string(y1) + "," + to_string(z2) + "\n";
                
                s.append(p1);
                s.append(p2);
                s.append(p3);
                s.append(p3);
                s.append(p2);
                s.append(p4);

				//normais base e topo 
				float normal[3] = { 0,y1,0 };
				normalize(normal);
				string n1 = to_string(normal[0]) + "," + to_string(normal[1]) + "," + to_string(normal[2]) + "\n";
				n.append(n1);
				n.append(n1);
				n.append(n1);
				n.append(n1);
				n.append(n1);
				n.append(n1);

            }
    
            y1*=-1; //recuperar valores originais
            x1*=-1;
            x2*=-1;
            
        }
        z1 = z/2;
    }

	
  
    //pontos das faces paralelas ao plano xOy (diferem no valor z)
    x1 = x/2;
    z1 = z/2;
    y1 = -y/2; // vai ser feito desenho bottom up
    for(int i=0; i<d; i++, x1-=divX){
        x2 = x1-divX;
        for (int j = 0; j < d; j++, y1 += divY) {
            y2 = y1+divY;
            for(int k=0; k<2; k++){
                if(k==1) {
                    z1*=-1; //simetrico de z para desenhar face oposta
                    x1*=-1; //simetrico de x por causa do vetor normal
                    x2*=-1;
                }
            
                string p1 = to_string(x1) + "," + to_string(y1) + "," + to_string(z1) + "\n"; // A
                string p2 = to_string(x2) + "," + to_string(y2) + "," + to_string(z1) + "\n"; // H
                string p3 = to_string(x2) + "," + to_string(y1) + "," + to_string(z1) + "\n"; // D
                string p4 = to_string(x1) + "," + to_string(y2) + "," + to_string(z1) + "\n"; // E
            
                s.append(p1);
                s.append(p4);
                s.append(p3);
                s.append(p4);
                s.append(p2);
                s.append(p3);


				//normais faces paralelas ao plano xOy 
				float normal[3] = { 0,0,z1 };
				normalize(normal);
				string n1 = to_string(normal[0]) + "," + to_string(normal[1]) + "," + to_string(normal[2]) + "\n"; n.append(n1);
				n.append(n1);
				n.append(n1);
				n.append(n1);
				n.append(n1);
				n.append(n1);

            }
            z1*=-1; // recuperar valores originais
            x1*=-1;
            x2*=-1;
        }
        y1 = -y/2; // volta a começar a desenhar por baixo
    }

	

    
    x1 = x/2;
    z1 = z/2;
    y1 = -y/2;
    // desenhar faces paralelas ao plano yOz (diferem no valor x)
    for(int i = 0; i < d; i++, z1-=divZ){
        z2 = z1-divZ;
        for (int j = 0; j < d; j++, y1 += divY) {
            y2 = y1+divY;
            for(int k=0; k<2; k++){
                if(k==1) {
                    x1*=-1; //simetrico de x para desenhar face oposta
                    z1*=-1; //simetrico de z por causa do vetor normal
                    z2*=-1;
                }
            
                string p1 = to_string(x1) + "," + to_string(y1) + "," + to_string(z1) + "\n"; // H - C
                string p2 = to_string(x1) + "," + to_string(y1) + "," + to_string(z2) + "\n"; // D - G
                string p3 = to_string(x1) + "," + to_string(y2) + "," + to_string(z1) + "\n"; // E - B
                string p4 = to_string(x1) + "," + to_string(y2) + "," + to_string(z2) + "\n"; // A - F
            
                s.append(p1);
                s.append(p2);
                s.append(p4);
                s.append(p1);
                s.append(p4);
                s.append(p3);

				//normais faces paralelas ao plano xOy 
				float normal[3] = { x1,0,0 };
				normalize(normal);
				string n1 = to_string(normal[0]) + "," + to_string(normal[1]) + "," + to_string(normal[2]) + "\n";
				n.append(n1);
				n.append(n1);
				n.append(n1);
				n.append(n1);
				n.append(n1);
				n.append(n1);
            }
            z1*=-1; // recuperar valores originais
            z2*=-1;
            x1*=-1;
        }
        y1 = -y/2;
    }


	s.append("\n" + n);
	

	// textura

	fileWriter(destFile, s);
}

string computeNormalsSphere(string s, float x1, float x2, float x3, float x4, float y1, float y2, float z1, float z2, float z3, float z4) {
	string n = s;
	
	float n1[3] = { x1,y1,z1 };
	float n2[3] = { x2,y2,z2 };
	float n3[3] = { x3,y2,z3 };
	float n4[3] = { x4,y1,z4 };
	normalize(n1);
	normalize(n2);
	normalize(n3);
	normalize(n4);
	n.append(to_string(n1[0]) + "," + to_string(n1[1]) + "," + to_string(n1[2]) + "\n");
	n.append(to_string(n2[0]) + "," + to_string(n2[1]) + "," + to_string(n2[2]) + "\n");
	n.append(to_string(n3[0]) + "," + to_string(n3[1]) + "," + to_string(n3[2]) + "\n");

	n.append(to_string(n1[0]) + "," + to_string(n1[1]) + "," + to_string(n1[2]) + "\n");
	n.append(to_string(n3[0]) + "," + to_string(n3[1]) + "," + to_string(n3[2]) + "\n");
	n.append(to_string(n4[0]) + "," + to_string(n4[1]) + "," + to_string(n4[2]) + "\n");

	return n;
}

/**
 Função responsável por os pontos dos triângulos que compõem uma figura do tipo 'sphere', centrada
 na origem
 */
void sphereHandler(float raio, int slices, int stacks, char* destFile){
	string s = "2\n";
	string n = "";
	string t = "";
	float a = 0;
	float stepSide = 2 * M_PI / slices;
	float stepUp = M_PI / stacks;
	float b = 0;

	float sizeW = (float)1 / slices;
	float sizeH = (float)1 / stacks;

	for (int i = 0; i < slices; i++){
		a = i * stepSide;
		for (int j = 0; j < stacks; j++){
			b = j * stepUp;
            
            float x1 = raio*sin(b)*sin(a);
            float x2 = raio*sin(b + stepUp)*sin(a);
            float x3 = raio*sin(b + stepUp)*sin(a + stepSide);
            float x4 = raio*sin(b)*sin(a + stepSide);
            float y1 = raio*cos(b);
            float y2 = raio*cos(b + stepUp);
            float z1 = raio*sin(b)*cos(a);
            float z2 = raio*sin(b + stepUp)*cos(a);
            float z3 = raio*sin(b + stepUp)*cos(a + stepSide);
            float z4 = raio*sin(b)*cos(a + stepSide);

			float tx1 = i * sizeW;
			float tx2 = (i + 1) * sizeW;
			float ty1 = 1 - j * sizeH;
			float ty2 = 1 - (j + 1) * sizeH;
            
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

			n = computeNormalsSphere(n, x1, x2, x3, x4, y1, y2, z1, z2, z3, z4);

			t.append(to_string(tx1) + "," + to_string(ty1) + "\n");
			t.append(to_string(tx1) + "," + to_string(ty2) + "\n");
			t.append(to_string(tx2) + "," + to_string(ty2) + "\n");

			t.append(to_string(tx1) + "," + to_string(ty1) + "\n");
			t.append(to_string(tx2) + "," + to_string(ty2) + "\n");
			t.append(to_string(tx2) + "," + to_string(ty1) + "\n");

			
		}
	}

	s.append("\n" + n);
	s.append("\n" + t);
	

	fileWriter(destFile, s);
}





/**
 Função auxiliar ao desenho de uma figura do tipo 'cone'. Calcula os pontos
 dos triângulos que compõem uma slice do cone.
 */
string buildSlice(int stacks, float r, float h, string s, float a, float stepSide, float hips, string* normals) {
	
	float nX1, nZ1, nX2, nZ2;
	float stepUp = (float)(h / stacks);
	float stepInside = sqrt((hips*hips) - (stepUp*stepUp));
	float height = 0;
    string p1;
    string p2;
    string p3;
    string p4;
    
	float x1 = r * cos(a);
	float x2 = (r - stepInside)*cos(a);
	float x3 = (r - stepInside)*cos(a + stepSide);
	float x4 = r * cos(a + stepSide);
	float y1 = height;
	float y2 = height + stepUp;
	float z1 = r * sin(a);
	float z2 = (r - stepInside)*sin(a);
	float z3 = (r - stepInside)*sin(a + stepSide);
	float z4 = r * sin(a + stepSide);


	for (int i = 0; i < stacks - 1; i++) {
        
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

	
		nX1 = h * cos(a);
		nZ1 = h * sin(a);
		nX2= h * cos(a+stepSide);
		nZ2 = h * sin(a+stepSide);

		float n1[3] = { nX1,r,nZ1 }; 
		float n2[3] = { nX2,r,nZ2 };

		normalize(n1);
		normalize(n2);
		(*normals).append(to_string(n1[0]) + "," + to_string(n1[1]) + "," + to_string(n1[2]));
		(*normals).append(to_string(n1[0]) + "," + to_string(n1[1]) + "," + to_string(n1[2]));
		(*normals).append(to_string(n2[0]) + "," + to_string(n2[1]) + "," + to_string(n2[2]));
		
		(*normals).append(to_string(n2[0]) + "," + to_string(n2[1]) + "," + to_string(n2[2]));
		(*normals).append(to_string(n2[0]) + "," + to_string(n2[1]) + "," + to_string(n2[2]));
		(*normals).append(to_string(n1[0]) + "," + to_string(n1[1]) + "," + to_string(n1[2]));


		height += stepUp;
		r -= stepInside;

	}

    // "cobertura" do cone
	s.append("0," + to_string(h) + ",0\n");
    s.append(p3);
    s.append(p2);
    

	float n1[3] = { nX1,r,nZ1 };
	float n2[3] = { nX2,r,nZ2 };
	
	(*normals).append("0,1,0\n");
	(*normals).append(to_string(n2[0]) + "," + to_string(n2[1]) + "," + to_string(n2[2]));
	(*normals).append(to_string(n1[0]) + "," + to_string(n1[1]) + "," + to_string(n1[2])); \

	return s;
}
/**
 Função responsável por calcular os pontos que formam uma figura do tipo 'cone'.
 */
void coneHandler(float raio, float altura, int slices, int stacks, char* destFile){
	string s = "3\n";
	string n = "";
	float a = 0;
	float step = 2 * M_PI / slices;
	float hip = sqrt((raio*raio) + (altura*altura));
    
	for (int i = 0; i < slices; i++) {
		string x1 = to_string(raio*cos(a));
		string x2 = to_string((raio*cos(a + step)));
		string z1 = to_string(raio * sin(a));
		string z2 = to_string(raio * sin(a + step));

		string t1 = to_string(0.5 + cos(i)*step);
		string t2 = to_string(0.5 + cos(i+1)*step);
		string t3 = to_string(0.5 + sin(i)*step);
		string t4 = to_string(0.5 + sin(i+1)*step);
        
		a += step;
		s.append( buildSlice(stacks, raio, altura, s, a, step, hip / stacks, &n));
		
        // desenhar a base do cone
        s.append("0,0,0\n");
		s.append(x1 + ",0," + z1 +"\n");
        s.append(x2 + ",0," + z2 + "\n");

		n.append("0,-1,0\n");
		n.append("0,-1,0\n");
		n.append("0,-1,0\n");


	}	

	s.append("\n" + n);

	fileWriter(destFile, s);
} 


/**
 Função responsável por calcular os pontos que formam uma figura do tipo 'ring'.
 */
void ringHandler(float r, float R, int slices, char* destFile) {
	string s = "4\n";
	string n = "";
	string t = "";
	float a = 0;
	float step = 2 * M_PI / slices;
	float size = (float)1 / slices;

	for (int i = 0; i < slices; i++, a+=step) {
		string x1 = to_string(r * cos(a));
		string z1 = to_string(r * sin(a));
		string x2 = to_string((r * cos(a + step)));		
		string z2 = to_string(r * sin(a + step));
		string x3 = to_string(R * cos(a));
		string z3 = to_string(R * sin(a));
		string x4 = to_string((R * cos(a + step)));
		string z4 = to_string(R * sin(a + step));

		string tx1 = to_string(0);
		string tx2 = to_string(1);
		string ty1 = to_string(0);
		string ty2 = to_string(1);
		

		// Draw top
		s.append(x2 + ",0," + z2 + "\n");
		s.append(x1 + ",0," + z1 + "\n");
		s.append(x3 + ",0," + z3 + "\n");

		s.append(x3 + ",0," + z3 + "\n");
		s.append(x4 + ",0," + z4 + "\n");
		s.append(x2 + ",0," + z2 + "\n");

		// normais

		n.append("0,1,0\n");
		n.append("0,1,0\n");
		n.append("0,1,0\n");

		n.append("0,1,0\n");
		n.append("0,1,0\n");
		n.append("0,1,0\n");

		// texturas

		t.append(tx1 + "," + ty2 + "\n");
		t.append(tx1 + "," + ty1 + "\n");
		t.append(tx2 + "," + ty1 + "\n");

		t.append(tx2 + "," + ty1 + "\n");
		t.append(tx2 + "," + ty2 + "\n");
		t.append(tx1 + "," + ty2 + "\n");


		// Draw bottom
		s.append(x1 + ",0," + z1 + "\n");
		s.append(x2 + ",0," + z2 + "\n");
		s.append(x3 + ",0," + z3 + "\n");

		s.append(x3 + ",0," + z3 + "\n");
		s.append(x2 + ",0," + z2 + "\n");
		s.append(x4 + ",0," + z4 + "\n");

		// normais

		n.append("0,-1,0\n");
		n.append("0,-1,0\n");
		n.append("0,-1,0\n");

		n.append("0,-1,0\n");
		n.append("0,-1,0\n");
		n.append("0,-1,0\n");

		// texturas

		t.append(tx1 + "," + ty1 + "\n");
		t.append(tx1 + "," + ty2 + "\n");
		t.append(tx2 + "," + ty1 + "\n");

		t.append(tx2 + "," + ty1 + "\n");
		t.append(tx1 + "," + ty2 + "\n");
		t.append(tx2 + "," + ty2 + "\n");


	}
	
	s.append("\n" + n);
	s.append("\n" + t);


	fileWriter(destFile, s);
}




/********************
*					*
*	   BEZIER		*
*					*
********************/

int nr_patches = 0;
int** patch_indices;
int nr_pts_ctrl;
Point* pts_ctrl;




int bezierPatchParser(char *patch) {
	string line;
	ifstream file(patch);

	if (!file) return -1;

	// Verifica o número de patches
	getline(file, line);
	nr_patches = atoi((char*)line.c_str());
	if (nr_patches < 1) return -1;
	printf("Numero de patches = %d\n", nr_patches);

	// Preenche array dos indices de cada patch
	patch_indices = (int**)malloc(sizeof(int*) * nr_patches); 

	for (int i = 0; i < nr_patches; i++){
		getline(file, line);
		patch_indices[i] = (int*)malloc(sizeof(int) * 16);

		char* token = strtok((char*)line.c_str(), ", ");
		for (int j = 0; j < 16 && token != NULL; token = strtok(NULL, ", "), j++) {
			patch_indices[i][j] = atoi(token);
		}
	}

	// Verifica o número de pontos de controlo
	getline(file, line);
	nr_pts_ctrl = atoi((char*)line.c_str());
	if (nr_pts_ctrl < 1) return -1;
	printf("Numero de pontos de controlo = %d\n", nr_pts_ctrl);


	// Preenche o array dos pontos de controlo
	pts_ctrl = (Point*)malloc(sizeof(Point) * nr_pts_ctrl);
	for (int i = 0; i < nr_pts_ctrl; i++) {
		float x, y, z;
		getline(file, line);

		sscanf(line.c_str(), "%f, %f, %f", &x, &y, &z);

		pts_ctrl[i] = *new Point(x, y, z);
	}

	return 1;
}


Point getBezierPatchPoint(float u, float v, Point *pts) {
	//vector U
	float U[4] = { u*u*u, u*u, u, 1 };
	//vectorV
	float V[4] = { v*v*v, v*v, v, 1 };
	//Matrix M (= transpose M )
	float M[4][4] = { {-1.0f,  3.0f, -3.0f, 1.0f},
					{3.0f, -6.0f,  3.0f, 0.0f},
					{-3.0f,  3.0f,  0.0f, 0.0f},
					{ 1.0f,  0.0f,  0.0f, 0.0f} };

	// x, y, z
	float Px[4][4] = {
		{ pts[0].getX(), pts[1].getX(), pts[2].getX(), pts[3].getX() },
		{ pts[4].getX(), pts[5].getX(), pts[6].getX(), pts[7].getX() },
		{ pts[8].getX(), pts[9].getX(), pts[10].getX(), pts[11].getX() },
		{ pts[12].getX(), pts[13].getX(), pts[14].getX(), pts[15].getX() }
	};

	float Py[4][4] = {
		{ pts[0].getY(), pts[1].getY(), pts[2].getY(), pts[3].getY() },
		{ pts[4].getY(), pts[5].getY(), pts[6].getY(), pts[7].getY() },
		{ pts[8].getY(), pts[9].getY(), pts[10].getY(), pts[11].getY() },
		{ pts[12].getY(), pts[13].getY(), pts[14].getY(), pts[15].getY() }
	};

	float Pz[4][4] = {
		{ pts[0].getZ(), pts[1].getZ(), pts[2].getZ(), pts[3].getZ() },
		{ pts[4].getZ(), pts[5].getZ(), pts[6].getZ(), pts[7].getZ() },
		{ pts[8].getZ(), pts[9].getZ(), pts[10].getZ(), pts[11].getZ() },
		{ pts[12].getZ(), pts[13].getZ(), pts[14].getZ(), pts[15].getZ() }
	};	
				
	// transpose M * V
	float MV[4];
	multMatrixVector((float *)M, V, MV);


	// P * MV
	float PxMV[4], PyMV[4], PzMV[4];
	multMatrixVector((float*)Px, MV, PxMV);
	multMatrixVector((float*)Py, MV, PyMV);
 	multMatrixVector((float*)Pz, MV, PzMV);

	// M * PMV
	float MPxMV[4], MPyMV[4], MPzMV[4];
	multMatrixVector((float*)M, PxMV, MPxMV);
	multMatrixVector((float*)M, PyMV, MPyMV);
 	multMatrixVector((float*)M, PzMV, MPzMV);

	// U * MPMV
	float res[3];
	multLVectorCVector(U, MPxMV, res);
	multLVectorCVector(U, MPyMV, res+1);
	multLVectorCVector(U, MPzMV, res+2);

	return * new Point(res[0], res[1], res[2]);

}

int patchHandler(char* patch_file, int tesselationLevel, char *dest_file) {
	bezierPatchParser(patch_file);
	Point pv[16];
	float inc = 1.0 /tesselationLevel; // change this to change the tesselation level
	string points_str;
	string s;


	for (int i = 0; i < nr_patches; i++) {
		for (int j = 0; j < 16; j++) {
			// load control points for current patch
			pv[j] = pts_ctrl[patch_indices[i][j]];
		}
		for (int u = 0; u < tesselationLevel; u++) {

			for (int v = 0; v < tesselationLevel; v++) {
				float u1 = (float) u * inc;
				float u2 = (float) (u + 1) * inc;
				float v1 = (float) v * inc;
				float v2 = (float) (v+1) * inc;

				Point p0 = getBezierPatchPoint(u1, v1, pv);
				Point p1 = getBezierPatchPoint(u1, v2, pv);
				Point p2 = getBezierPatchPoint(u2, v1, pv);
				Point p3 = getBezierPatchPoint(u2, v2, pv);

				s.append(p0.toString());
				s.append(p1.toString());
				s.append(p3.toString());

				s.append(p2.toString());
				s.append(p0.toString());
				s.append(p3.toString());

			}
		}
	}

	fileWriter(dest_file, s);
	return 0;
}



void help() {
	string s;
	s.append("+---------------------------------------------------+\n" +
		string("|                        HELP                       |\n") + // nao sei porque mas estava a dar erro nesta linha e assim com "string" nao da... tudo dentro do printf não dava tambem
		"+---------------------------------------------------+\n" +
		"| Primitive |               Parameters              |\n" +
		"+-----------+---------------------------------------+\n" +
		"| box       | edge output                           |\n" +
		"+-----------+---------------------------------------+\n" +
		"| plane     | x z [divisons] output                 |\n" +
		"+-----------+---------------------------------------+\n" +
		"| sphere    | radius slices stacks output           |\n" +
		"+-----------+---------------------------------------+\n" +
		"| cone      | radius height slices stacks output    |\n" +
		"+-----------+---------------------------------------+\n" +
		"| ring      | innerRadius outerRadius slices output |\n" +
		"+-----------+---------------------------------------+\n" +
		"| patch     | patchFile tesselation output          |\n" +
		"+-----------+---------------------------------------+\n");
	printf("%s\n", s.c_str());
}

int main(int argc, char** argv){
	int error_flag = 0; 

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

		case RING:
			if (argc == 6) ringHandler(atof(argv[2]), atof(argv[3]), atoi(argv[4]), argv[5]);
			else error_flag = 1;
			break;

		case PATCH:
			if(argc == 5) patchHandler(argv[2], atoi(argv[3]), argv[4]);
			else error_flag = 1;
			break;

		case HELP:
			help();
			error_flag = 2;
			break;

    	default:
			error_flag = 1;
        	break;
    }
    

    if(error_flag) printf("Por favor insira todos os parâmetros necessários. \n");
    else printf("Pontos gerados com sucesso\n");

	return 1;

}

