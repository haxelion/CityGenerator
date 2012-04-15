#ifndef CHAIN_H
#define CHAIN_H

//classe template impl�mentant une liste li�e

template <class T> class Chain
{
private:

    T *current, *next;

public:

    //constructeur et destructeur
    Chain(T *current){this->current = current;}
    ~Chain() {delete current;}

    //getter et setter pour les variables priv�es
    T* getCurrent() {return current;}
    T* getNext() {return next;}
    void setCurrent(T *current) {this->current = current;}
    void setNext(T *next) {this->next = next;}

    //m�thodes
    T* getElementAt(int position);

};


#endif // CHAIN_H
