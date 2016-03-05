#include <cstdio>
#include <iostream>

template<class Base_t> class Nodo;
template<class Base_t> std::ostream& operator<<(std::ostream& os, const Nodo<Base_t>& v);

// | Clase Nodo, tipo basico de una lista, ademas incluye un doble enlazado
// en el entre nodos, ademas del uso de templates para poder insertar diferentes 
// tipos de forma fácil
template <class DATO>
class Nodo
{
private:
    DATO dato_;
    Nodo * next_;
    Nodo * back_;
public:
    Nodo(void);
    Nodo(DATO);
    virtual ~Nodo(void);
    void setNext(Nodo *);
    // ^ Establecemos el siguiente

    Nodo * getNext(void);
    // ^ Obtenemos el siguiente

    void setBack(Nodo *);
    // ^ Establecemos el anterior

    Nodo * getBack(void);
    // ^ Obtenemos el anterior

    void setDato(DATO);
    // ^ Establecemos el contenido de dato_

    DATO getDato(void) const;
    // ^ Obtenemos el dato_

    friend std::ostream& operator<< <>(std::ostream & os, const Nodo&);
};

template <class DATO>
std::ostream& operator<<(std::ostream & os, const Nodo<DATO>& n) {
    os << n.dato_;
    return os;
}

template <class DATO>
Nodo<DATO>::Nodo(void):
    next_(NULL),
    back_(NULL) {}

template <class DATO>
Nodo<DATO>::Nodo(DATO dato):
    dato_(dato),
    next_(NULL),
    back_(NULL) {}

template <class DATO>
Nodo<DATO>::~Nodo(void) {}

template <class DATO>
void Nodo<DATO>::setNext(Nodo * x) {
    next_ = x;
}

template <class DATO>
Nodo<DATO> * Nodo<DATO>::getNext(void) {
    return next_;
}

template <class DATO>
void Nodo<DATO>::setBack(Nodo * x) {
    back_ = x;
}

template <class DATO>
Nodo<DATO> * Nodo<DATO>::getBack(void) {
    return back_;
}

template <class DATO>
void Nodo<DATO>::setDato(DATO dato) {
    dato_ = dato;
}

template <class DATO>
DATO Nodo<DATO>::getDato(void) const {
    return dato_;
}


