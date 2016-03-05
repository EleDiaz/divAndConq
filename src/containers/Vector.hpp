///////////////////////
// Eleazar Díaz Delgado
#pragma once
#include <iostream>
#include <functional>
#include <initializer_list>
#include "../CommonExc.hpp"

using namespace std;

template<class Base_t> class Vector;
template<class Base_t> std::ostream& operator<<(std::ostream& os, const Vector<Base_t>& v);

template <class DATO>
class Vector {
private:
    DATO * block;
    int size;
public:
    Vector(void);
    // ^ Se inicializa un Vector con cero elementos
    Vector(int a);
    // ^ Se inicializa un Vector con n elementos a cero
    Vector(initializer_list<DATO> l);
    // ^ incializador mas flexible a la hora de programar
    Vector(const Vector & a);
    // ^ Constructor de copia
    Vector(function<DATO (const int)> func, int a);
    // ^ Se incializa un Vector con n elementos, que dependen de la
    // función generadora, la cual recibe su índice
    ~Vector(void);
    // Destructor
    Vector<DATO>& resize(int a);
    // ^ Redimeniona el vector
    Vector<DATO>& setInPos(int a, DATO dato);
    // ^ Establece un `dato´ dentro del Vector según el índice `a´ pasado
    //   Lanza una execpcion de OutRange
    DATO getInPos(int a, DATO optional) const;
    // ^ Obtengo un elemento dado un índice `a´ en caso de fuera de rango
    // se retorna el elemento `optional´
    int getSize(void) const;
    // ^ Tamaño del Vector
    Vector<DATO>& zipWith(function<DATO (DATO,DATO)>fn, const Vector<DATO> & vec);
    // ^ Aplica una función a "this" y `vec´, aplicando los cambios sobre
    // "this", esto implíca redimensionar el actual al tamaño mínimo de
    // entre los dos.
    // NOTA: Está función debería ser más general:
    //       zipWith :: (a -> b -> c) -> Vec a -> Vec b -> Vec c
    //
    //       Vector<c> zipWith(c (*fn)(a,b), Vector<b>)
    Vector<DATO>& map(function<DATO (DATO)> fn);
    // ^ Aplica `fn´ a cada función

    // void sumVectors(Vector vec) = zipWith([] (int a, int b) { return a+b;}, vec)
    void swap(int a, int b) {
      DATO aux = (*this)[a];
      (*this)[a] = (*this)[b];
        (*this)[b] = aux;
    };

    DATO & operator[](const int a);

    DATO operator[](const int a) const;

    Vector<DATO>& operator=(const Vector<DATO>& vec);

    friend ostream& operator<< <>(ostream& os, const Vector<DATO>& vec);

};


template <class DATO>
Vector<DATO>::Vector(void):
    block(nullptr),
    size(0) {}

template <class DATO>
Vector<DATO>::Vector(int size):
    block(nullptr),
    size(size) {
    try {
        block = new DATO[size];
        for (int i=0; i<size; i++) block[i]= DATO();
    } catch (bad_alloc) {
        throw MemoryAlloc("Vector(int size)");
    }
    }

template <class DATO>
Vector<DATO>::Vector(initializer_list<DATO> list):
  block(nullptr),
  size(list.size())
{
    try {
        block = new DATO[size];
        int i = 0;
        for (DATO a : list) {
          block[i]= a;
          i++;
        }
    } catch (bad_alloc) {
      throw MemoryAlloc("Vector(int size)");
    }
}

template <class DATO>
Vector<DATO>::Vector(const Vector & vec) {
    try {
        block = new DATO[vec.getSize()];
        for (int i=0; i<size; i++) block[i]=vec[i];
    } catch (bad_alloc) {
        throw MemoryAlloc("Vector(int size)");
    }
}

template <class DATO>
Vector<DATO>::Vector(function<DATO (const int)> fn, int size):
    block(nullptr),
    size(size) {
    try {
        block = new DATO[size];
        for (int i=0; i<size; i++) block[i]=fn(i);
    } catch (bad_alloc) {
        throw MemoryAlloc("Vector(fuction<DATO (const int)> fn, int size)");
    }
    }

template <class DATO>
Vector<DATO>::~Vector(void) {
    if (block != nullptr) {
        delete[] block;
        block=nullptr;
    }
}

template <class DATO>
Vector<DATO>& Vector<DATO>::resize(int a) {
    try {
        DATO * aux = new DATO[a];
        for (int i = 0; i<(a>size?size:a); i++)
            aux[i] = block[i];
        delete[] block;
        block = aux;
        size = a;
    } catch (bad_alloc) {
        throw MemoryAlloc("resize(int a)");
    }
    return *this;
}

template <class DATO>
inline Vector<DATO>& Vector<DATO>::setInPos(int pos, DATO dato) {
    if (pos < size && pos >= 0 ) {
        block[pos]=dato;
    } else
        throw OutRange("setInPos(int pos, DATO dato)");
    return *this;
}

template <class DATO>
inline DATO Vector<DATO>::getInPos(int pos, DATO optional) const
{
    if (pos < size && pos >= 0 ) {
        return block[pos];
    } else return optional;
}

template <class DATO>
inline int Vector<DATO>::getSize(void) const {
    return size;
}

template <class DATO>
Vector<DATO>& Vector<DATO>::zipWith(function<DATO (DATO,DATO)> fn, const Vector<DATO> & vec) {
    if (size > vec.getSize())
        resize(vec.getSize());
    
    for (int i=0; i<size; i++)
        block[i] = fn(block[i], vec[i]);
    return *this;
}

template <class DATO>
Vector<DATO>& Vector<DATO>::map(function<DATO (DATO)> fn) {
    for (int i=0; i<size; i++) block[i]=fn(block[i]);
    return *this;
}

template <class DATO>
inline DATO & Vector<DATO>::operator[](const int pos) {
    if (pos < size && pos >= 0 ) {
        return block[pos];
    } else
        throw OutRange("& operator[]");
}

template <class DATO>
inline DATO Vector<DATO>::operator[](const int pos) const {
    if (pos < size && pos >= 0 ) {
        return block[pos];
    } else
        throw OutRange("operator[] const");
}

template <class DATO>
Vector<DATO>& Vector<DATO>::operator=(const Vector<DATO> & vec) {
    if (this != &vec) {
        delete[] block;
        try {
            block = new DATO[vec.getSize()];
            size  = vec.getSize();
            for (int i=0; i<vec.getSize(); i++) {
                block[i] = vec[i];
            }
        } catch (bad_alloc) {
            throw MemoryAlloc("operator=");
        }
    }
    return *this;
}

template <class DATO>
ostream& operator<<(ostream& os, Vector<DATO>& vec) {
    os << "[ ";
    for (int i = 0; i<vec.getSize(); i++)
        os << vec[i] << " ";
    os << "]";
    return os;
}
