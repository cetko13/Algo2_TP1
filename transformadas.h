#ifndef _TRANSFORMADAS_H_INCLUDED_
#define _TRANSFORMADAS_H_INCLUDED_

#include <iostream>
#include <map>

#include "array.h"
#include "complejo.h"

#define PI 3.14159265359

using namespace std;

typedef enum {
    FFT,
    IFFT,
    DFT,
    IDFT,
    FFT_ITER,
    IFFT_ITER,
    FFT_IN_PLACE,
    IFFT_IN_PLACE
} metodo_t;

class transformadas{
//_dft y _idft?
public:
	virtual Array<complejo> transformar(Array<complejo> &x) = 0;
};

class dft : public transformadas{
public:	
	Array<complejo> transformar(Array<complejo> &x);
};

class idft : public transformadas{
public:	
	Array<complejo> transformar(Array<complejo> &x);
};
class fft : public transformadas{
public:	
	Array<complejo> transformar(Array<complejo> &x);
};
class ifft : public transformadas{
public:	
	Array<complejo> transformar(Array<complejo> &x);
};

class diccionario_transformadas_t{
public:
	
	std::map<metodo_t, transformadas*> dict;
	
	diccionario_transformadas_t(){	
		dict.insert(std::make_pair(DFT,new dft) );
		dict.insert(std::make_pair(IDFT,new idft) );
		dict.insert(std::make_pair(FFT,new fft) );
		dict.insert(std::make_pair(IFFT,new ifft) );
	}
	
	~diccionario_transformadas_t(){
		while( dict.begin() != dict.end() )
        {
            delete dict.begin()->second;
            dict.erase( dict.begin() );
        }
    }

};


#endif
