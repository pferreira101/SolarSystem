#include <hash.h>
/**
 Função auxiliar para calcular o valor da operaçao a usar
 */
int hashF(char* s){
	int r = 0;
	for (int i = 0; s[i]; i++) {
		r += (s[i] * (10 ^ i));
	}
	return r;
}