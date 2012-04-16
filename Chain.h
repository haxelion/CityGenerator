#ifndef CHAIN_H
#define CHAIN_H

//classe template implémentant une liste liée

template <class T> class ChainElement
{

private:

    T *current, *next;

public:

    ChainElement(T *current){this->current = current;}
    ~ChainElement() {delete current;}
    T* getCurrent() {return current;}
    T* getNext() {return next;}
    void setCurrent(T* current) {this->current = current;}
    void setNext(T* next) {this->next = next;}
};

template <class T> class Chain
{
private:

    ChainElement<T> *first, *current;
    int size, position;

public:


    Chain();
    ~Chain();
    void addElement(T* a);
    void insertElement(T* a, int position);
    void next();
    void start();
    T* getElementAt(int position);
    T* getFirstElement(){return first;}
    T* getCurrentElement(){return current;}
    T* getNextElement();
    int getSize() const {return size;}

};


#endif // CHAIN_H
