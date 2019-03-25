#ifndef GROUP_CLASS
#define GROUP_CLASS

#include "operation.h"
#include "figure.h"

using namespace std;

class Group {
	vector<Figure> figures;
	vector<Operation*> operations; // vetor de apontadores por causa de polimorfismo
	vector<Group> subGroups;

public:
	void set_values(vector<Figure> fig, vector<Operation*> ops, vector<Group> g) {
		figures = fig;
		operations = ops;
		subGroups = g;
	}

	vector<Figure> getFigures() {
		return figures;
	}

	vector<Operation*> getOperations() {
		return operations;
	}

	vector<Group> getSubGroups() {
		return subGroups;
	}

};

#endif