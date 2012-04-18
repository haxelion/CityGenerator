#ifndef CHAIN_H
#define CHAIN_H

//classe template implémentant une liste liée

template <class T> class ListElement
{

private:

    T element;
    ListElement *next;

public:

    ListElement(T current){this->current = current;}
    ListElement(){}
    T getElement() {return current;}
    ListElement* getNext() {return next;}
    void setElement(T current) {this->current = current;}
    void setNext(ListElement *next) {this->next = next;}
};

template <class T> class List
{
private:

    ListElement<T> *first, *current;
    int size, position;

    void goTo(int position);
    void next();
    void start();

public:


    List();
    ~List();
    void addElement(T a);
    void removeElement(int position);
    void insertElement (T a, int position);
    void setElementAt(T a, int position);
    T getElementAt(int position) const;
    T getCurrentElement() const {return current;}
    T getNextElement() const;
    int getSize() const {return size;}
    bool isAtTheEnd() const {return position+1 == size;}

};


#endif // CHAIN_H
