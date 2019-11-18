#ifndef _ARRAY_H_INCLUDED_
#define _ARRAY_H_INCLUDED_

#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <string>
#include <cstdlib>
#include <sstream>
#include <fstream>
#include <math.h>
#include <cstring>

#include <typeinfo>


#define INIT_SIZE 0

using namespace std;

template <class T>
class Array
{
public:
	Array();
	Array(const Array<T> &);
    Array(const int);
	~Array();

	int getSize();
	Array<T> & operator= (const Array<T> &);
	bool operator== (const Array<T> &);
	T & operator[](int);
	T & operator[](int) const;

	Array<T> operator*(const T f);
	Array<T> operator*(Array<T> A2);
	Array<T>& operator+=(const Array<T> &initArray);
	Array<T> operator+(const Array<T> &initArray);
	Array<T>& operator*=(const T f);
	void cargar_array(std::istream &iFile, Array<T>*, std::ostream &oFile);

	Array<T> extraer_impares();
	Array<T> extraer_pares();

template <class Y>	friend std::istream & operator>>(std::istream &file, Array<Y> &x);

template <class Y> friend std::ostream & operator<<(std::ostream &os, Array<Y> &arr);

private:
	int size;
	T * ptr;
};


template <class T>
Array<T> concatenar(const Array<T> &A1, const Array<T> &A2);


template <class T>
Array<T>::Array()
{
	ptr = new T[INIT_SIZE];
	size = INIT_SIZE;
    memset (ptr, 0, INIT_SIZE*sizeof(T));
}

template <class T>
Array<T>::Array(const int sz)
{
	ptr = new T[sz];
	size = sz;
    memset (ptr, 0, sz*sizeof(T));
}

template <class T>
Array<T>::Array(const Array<T> & initArray)
{
	size = initArray.size;
	ptr = new T[size];

	for (int i = 0; i < size; i++)
		ptr[i] = initArray[i];
}

template <class T>
Array<T>::~Array()
{
	if(ptr)
		delete[] ptr;
}

template <class T>
int Array<T>::getSize()
{
	return size;
}

template <class T>
Array<T> & Array<T>::operator=(const Array<T> & initArray)
{
	if(&initArray != this)
	{
		if (size != initArray.size)
		{
			T * aux;
			aux = new T[initArray.size];
			delete[] ptr;
			size = initArray.size;
			ptr = aux;
        }
		for (int i = 0; i < size; i++)
			ptr[i] = initArray.ptr[i];
	}
	return *this;
}

template <class T>
bool Array<T>::operator== (const Array<T> & initArray)
{
	if(size != initArray.size)
		return false;

	for (int i = 0; i < size; i++)
		if (ptr[i] != initArray.ptr[i])
			return false;

	return true;
}

template <class T>
Array<T> Array<T>::operator+(const Array<T> &initArray)
{
	Array<T> outArr = Array(size);

	if(size == initArray.size)
	{
		for(int i = 0; i < size; i++)
		{
			outArr[i] = ptr[i] + initArray.ptr[i];
		}
	}

	return outArr;
}

template <class T>
Array<T>& Array<T>::operator+=(const Array<T> &initArray)
{
	if(size == initArray.size)
	{
		for (int i = 0; i < size; i++)
		{
			ptr[i] = ptr[i] + initArray.ptr[i];
		}
	}

	return *this;
}

template <class T>
Array<T> Array<T>::operator*(const T f)
{
	Array<T> outArr = Array(size);

	for (int i = 0; i < size; i++)
	{
		outArr[i] = ptr[i] * f;
	}

	return outArr;
}

template <class T>
Array<T> Array<T>::operator*(Array<T> A2)
{

	if(this->getSize()!=A2.getSize()){
		return Array();
	}
	
	Array<T> outArr = Array(size);

	for (int i = 0; i < size; i++)
	{
		outArr[i] = ptr[i] * A2[i];
	}

	return outArr;
}

template <class T>
Array<T>& Array<T>::operator*=(const T f)
{
	for (int i = 0; i < size; i++)
	{
		ptr[i] = ptr[i] * f;
	}

	return *this;
}

template <class T>
T & Array<T>::operator[](int subscript)
{
	return ptr[subscript];
}

template <class T>
T & Array<T>::operator[](int subscript) const
{
	return ptr[subscript];
}


template <class T>
std::istream & operator>>(std::istream &file, Array<T> &x)//lee todos los valores de un stream
{
	T data ;

	while(!(file.eof())){
		file >> data; //lee de a un complejo y ve que no haya error

		if(file.fail()){
			return file;
		}

		else{
			Array <T> x_aux(x.getSize() + 1);

			for (int i = 0; i < x.getSize(); i++){
				x_aux[i] = x[i];
			}

			x_aux[x.getSize()] = data;
			x = x_aux;
		}
	}

	return file;
}

template <class T>
std::ostream & operator<<(std::ostream &os, Array<T> &arr) {
    for (int i = 0; i<arr.getSize(); i++)
        os<<arr[i];
    return os;
}

template <class T>
void
Array<T>::cargar_array(std::istream &iFile, Array<T> *arr, std::ostream &oFile){ //lee de a una linea

	(*arr) = 0;
	string s;

    while(getline(iFile, s)){
		std::stringstream ss(s);

		ss >> (*arr);
		if(ss.bad()){
			(*arr) = 0;
			oFile << "reading error" << endl;
			ss.str(std::string());
		    continue;
		}
		ss.str(std::string());
		break;
	}
}


template <class T>
Array<T> Array<T>::extraer_pares()
{
	int sz=ceil(this->getSize()/2.0);
	Array<T> ArrOut=Array(sz);

	for(int i=0;i<sz;i++){
		ArrOut[i]=(*this)[2*i];
	}

	return ArrOut;
}

template <class T>
Array<T> Array<T>::extraer_impares()
{
	int sz=this->getSize()/2;
	Array<T> ArrOut=Array(sz);

	for(int i=0;i<sz;i++){
		ArrOut[i]=(*this)[2*i+1];
	}

	return ArrOut;
}

template <class T>
Array<T> concatenar( Array<T> &A1, Array<T> &A2)
{	
	int sz1=A1.getSize();
	int sz2=A2.getSize();

	Array<T> ArrOut=Array<T>(sz1+sz2);
	for(int i=0;i<sz1;i++)
		ArrOut[i]=A1[i];

	for(int i=sz1;i<sz2+sz1;i++)
		ArrOut[i]=A2[i-sz1];

	return ArrOut;


}

#endif
