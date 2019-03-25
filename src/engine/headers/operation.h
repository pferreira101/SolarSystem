#ifndef OPERATION
#define OPERATION

/* Classe  operation é a superclasse das operaçoes, server para construir um vector com tranlates e rotates,
neste momento possui todo o codigo de ambas as subclasses porque nao estou a conseguir dar cast direito*/
class Operation {
public:
    virtual void transformacao() = 0; // forma de tornar abstrato
};

#endif