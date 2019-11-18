#include "complejo.h"
#include "array.h"
#include "dft.h"
#include "leer_cmdline.h"

#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <string>
#include <cstdlib>
#include <sstream>
#include <fstream>
#include <math.h>

using namespace std;

int main(int argc, char *argv[]) {
    complejo com;
    istream *iFile;
    ostream *oFile;
    Array<complejo> (*transformada)(Array<complejo> &x);

    int metodo_elegido = leer_cmdline (argc, argv, &iFile, &oFile);

        if (metodo_elegido == 1)
            transformada = dft;
        else if (metodo_elegido == -1)
            transformada = idft;


    Array <complejo> x;
    Array <complejo> X;

    while(!(*iFile).eof()){

        x.cargar_array (*iFile, &x, *oFile);

        if ((*iFile).eof())
            break;

        X=fft(x);

        (*oFile) << "in "<<x<<endl;
        (*oFile) << "fft "<<X<<endl;
        
        X=ifft(x);
        (*oFile) << "ifft "<<X<<endl;
        

           
    }
    return 0;

}
