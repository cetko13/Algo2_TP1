#include "complejo.h"
#include "array.h"
#include "transformadas.h"
#include "leer_cmdline.h"



#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <string>
#include <cstdlib>
#include <sstream>
#include <fstream>
#include <math.h>
#include <map>

using namespace std;

int main(int argc, char *argv[]) {
    complejo com;
    istream *iFile;
    ostream *oFile;
    Array<complejo> (*transformada)(Array<complejo> &x);
    diccionario_transformadas_t dict;

    metodo_t metodo_elegido;
    metodo_elegido = leer_cmdline (argc, argv, &iFile, &oFile);

    transformadas* transf=dict.dict[metodo_elegido];

    Array <complejo> x;
    Array <complejo> X;

    while(!(*iFile).eof()){

        x.cargar_array (*iFile, &x, *oFile);

        if ((*iFile).eof())
            break;

        double pot = log2(x.getSize());

        if (pot != floor(pot))
            x = padear_con_ceros(x);

        X=transf->transformar(x);

        (*oFile) << X <<endl;

    }

    return 0;

}

/*
    int metodo_elegido = leer_cmdline (argc, argv, &iFile, &oFile);

        if (metodo_elegido == 1)
            transformada = dft;
        else if (metodo_elegido == -1)
            transformada = idft;
*/
/*
    Array <complejo> x;
    Array <complejo> X;

    while(!(*iFile).eof()){

        x.cargar_array (*iFile, &x, *oFile);

        if ((*iFile).eof())
            break;

        cerr<<"asd"<<endl;

        X=transf->transformar(x);

        cerr<<"pla"<<endl;

        (*oFile) << "in "<<x<<endl;
        (*oFile) << "fft "<<X<<endl;
        

        (*oFile) << "ifft "<<X<<endl;
  

           
    }
  */  