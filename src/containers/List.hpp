
#pragma once
#include <cstdio>
#include <iostream>
#include <functional>
#include "Nodo.hpp"
#include "../CommonExc.hpp"

using namespace std;

template<class DATO> class List;
template<class DATO> ostream& operator<<(ostream& os, const List<DATO>& v);

template <class DATO>
class List {
private:
    Nodo<DATO> * inicio_;
    Nodo<DATO> * fin_;
    inline void insertEmpty(DATO);
public:
    List(void);
    // ^ Lista vacia
    List(function<DATO (int)>, int);
    // ^ Genera una lista a partir de una funcion y un tamaño
    virtual ~List(void);
    inline bool isEmpty(void) const;
    // ^ Indica si esta vacia
    friend ostream& operator<< <>(ostream & os, const List<DATO>&);
    DATO operator[](int pos) const;
    DATO& operator[](int pos);
    List<DATO>& insert(DATO, int);
    // ^ inserta un dato en la determinada posicion
    inline List<DATO>& cons(DATO);
    // ^ Añade un elemento al principio
    inline List<DATO>& snoc(DATO);
    // ^ Añade un elemento al final
    inline DATO head(void) const;
    // ^ Obserbamos el primer elemento
    inline DATO last(void) const;
    // ^ Observamos el ultimo elemento
    inline DATO pop(void);
    // ^ Hacemos pop del final de la lista
    inline List<DATO>& push(DATO);
    // ^ Ponemos al final de la lista push ≡ snoc
    inline DATO popFront(void);
    // ^ Hacemos un pop al principio de la lista
    int length(void);
    // ^ Devuelve el tamaño de la lista
    List<DATO>& map(function<DATO (DATO)>);
    // ^ aplica cada elemento una funcion
    List<DATO>& liftIO(function<void (void)> fn) {
        fn();
        return *this;
    }
};

template <class DATO>
ostream& operator<<(ostream & os, const List<DATO>& list) {
   Nodo<DATO> * aux = list.inicio_;
   os << "( ";
   while (aux != nullptr) {
       os << (*aux);
       os << " ";
       aux = aux->getNext();
   }
   os << ")";
   return os;
}

template <class DATO>
List<DATO>::List(void):
    inicio_(nullptr),
    fin_(nullptr) {}

template <class DATO>
List<DATO>::~List(void) {
    Nodo<DATO> * aux = inicio_;
    while (inicio_!=nullptr) {
        inicio_ = inicio_->getNext();
        delete aux;
        aux = inicio_;
    }
}

template <class DATO>
bool List<DATO>::isEmpty(void) const {
    if (inicio_ == nullptr)
        return true;
    else
        return false;
}

template <class  DATO>
DATO List<DATO>::operator[](int pos) const {
    int count = 0;
    Nodo<DATO> * aux = inicio_;
    while (aux!=nullptr) {
        if (count == pos) {
            return aux->getDato();
        }
        aux = aux->getNext();
        count++;
    }
    throw OutRange("List: operator[](int pos)");
}

template <class  DATO>
DATO& List<DATO>::operator[](int pos) {
    int count = 0;
    Nodo<DATO> * aux = inicio_;
    while (aux!=nullptr) {
        if (count == pos) {
            return aux->getDato();
        }
        aux = aux->getNext();
        count++;
    }
    throw OutRange("List: & operator[](int pos)");
}

template <class DATO>
List<DATO>& List<DATO>::insert(DATO d, int pos){
    int count = 0;
    Nodo<DATO> * aux = inicio_;
    bool seted = false;
    while (aux!=nullptr || seted) {
        if (count == pos ) {
            try {
                Nodo<DATO> * add = new Nodo<DATO>(d);
                add->setNext(aux);
                add->setBack(aux->getBack);
                aux->getBack->setNext(add);
                aux->setBack(add);
                seted = true;
            } catch (bad_alloc) {
                throw MemoryAlloc("List: insert");
            }
        } else {
            aux = aux->getNext();
            count++;
        }
    }
    if (not seted)
        throw OutRange("List: insert");
    return *this;
}

template <class DATO>
void List<DATO>::insertEmpty(DATO dato) {
    try {
        Nodo<DATO> * aux = new Nodo<DATO>(dato);
        inicio_ = aux;
        fin_ = aux;
    } catch (bad_alloc) {
        throw MemoryAlloc("List: insertEmpty");
    }

}

template <class DATO>
List<DATO>& List<DATO>::cons(DATO dato) {
    if (isEmpty())
        insertEmpty(dato);
    else {
        try {
            Nodo<DATO> * aux = new Nodo<DATO>(dato);
            inicio_->setBack(aux);
            aux->setNext(inicio_);
            inicio_ = aux;
        } catch (bad_alloc) {
            throw MemoryAlloc("List: cons");
        }
    }
    return *this;
}

template <class DATO>
List<DATO>& List<DATO>::snoc(DATO dato) {
    if (isEmpty())
        insertEmpty(dato);
    else {
        try {
            Nodo<DATO> * aux = new Nodo<DATO>(dato);
            fin_->setNext(aux);
            aux->setBack(fin_);
            fin_ = aux;
        } catch (bad_alloc) {
            throw MemoryAlloc("List: snoc");
        }
    }
    return *this;
}

template <class DATO>
List<DATO>& List<DATO>::push(DATO dato) {
    return snoc(dato);
}

template <class DATO>
DATO List<DATO>::head(void) const {
    return inicio_->getDato();
}

template <class DATO>
DATO List<DATO>::last(void) const {
    return fin_->getDato();
}

template <class DATO>
DATO List<DATO>::pop(void) {
    if (inicio_==fin_) {
        if (inicio_ == nullptr)
            throw EmptyContainer("List: pop");
        DATO aux = inicio_->getDato();
        delete inicio_;
        inicio_ = nullptr;
        fin_ = nullptr;
        return aux;
    } else {
        DATO aux = fin_->getDato();
        Nodo<DATO> * temp = fin_;
        fin_ = fin_->getBack();
        fin_->setNext(nullptr);
        delete temp;
        return aux;
    }
}

template <class DATO>
DATO List<DATO>::popFront(void) {
    if (inicio_==fin_) {
        if (inicio_ == nullptr)
            throw EmptyContainer("List: push");
        DATO aux = inicio_->getDato();
        delete inicio_;
        inicio_ = nullptr;
        fin_ = nullptr;
        return aux;
    } else {
        DATO aux = inicio_->getDato();
        Nodo<DATO> * temp = inicio_;
        inicio_ = inicio_->getNext();
        inicio_->setBack(nullptr);
        delete temp;
        return aux;
    }
}

template <class DATO>
int List<DATO>::length(void) {
  int count = 0;
  map([&count](DATO a){count++; return a;});
  return count;
}

template <class DATO>
List<DATO>& List<DATO>::map(function<DATO (DATO)> fn) {
    Nodo<DATO> * aux = inicio_;
    while (aux!=nullptr) {
        aux->setDato(fn(aux->getDato()));
        aux = aux->getNext();
    }
    return *this;
}
