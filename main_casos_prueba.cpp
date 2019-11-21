#include "complejo.h"
#include "array.h"
#include "transformadas.h"
#include "leer_cmdline.h"
#include "calcular_error.h"


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
    ifstream iFileReferencia_dft("referencia_dft.txt");
    ifstream iFileReferencia_idft("referencia_idft.txt");
    Array<complejo> (*transformada)(Array<complejo> &x);
    diccionario_transformadas_t dict;

    metodo_t metodo_elegido;
    metodo_elegido = leer_cmdline (argc, argv, &iFile, &oFile);

    transformadas* transf=dict.dict[metodo_elegido];

    Array <complejo> x;
    Array <complejo> X;
    Array <complejo> arr_com;

    while(!(*iFile).eof()){

        x.cargar_array (*iFile, &x, *oFile);

        if ((*iFile).eof())
            break;

        double pot = log2(x.getSize());

        if (pot != floor(pot))
            x = padear_con_ceros(x);

        X=transf->transformar(x);

        (*oFile) << X <<endl;

        ostream *errFile;
        fstream eF;
        string arg = "errores.txt";
        eF.open(arg.c_str(), ios::out);
        errFile = &eF;

        if(metodo_elegido == DFT || metodo_elegido == FFT)
            arr_com.cargar_array(iFileReferencia_dft, &arr_com, *errFile);
        else if(metodo_elegido == IDFT || metodo_elegido == IFFT)
            arr_com.cargar_array(iFileReferencia_idft, &arr_com, *errFile);
        else
            cerr << "method not found" << endl;

        if(calculador_error(X, arr_com) == true)
        {
            (*oFile) << "good" << endl;
        }

        else{
            (*oFile) << "bad" << endl;
        }

    }
    return 0;
}
