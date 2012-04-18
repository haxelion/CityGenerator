#include "list.h"

template <class T> List<T>::List()
{
    first = 0;
    current = 0;
    size = 0;
    position = 0;
}

template <class T> List<T>::~List()
{
    //on revient au d�but de la liste
    start();
    ListElement *t;
    //on parcourt toute la chaine en supprimant les �l�ments un � un
    while(position<size)
    {
        t = current;
        current = current->getNext();
        delete t;
        position++;
    }
}

template <class T> void List<T>::addElement(T a)
{
    //insertion de a au d�but de la liste
    ListElement *t = first;
    first = new ChainElement(a);
    //lien du reste de la liste au nouveau premier maillon
    first->setNext(t);
    //mise � jour de la taille et de la position de current
    size++;
    position++;
}

template <class T> void List<T>::goTo(int position)
{
    //si la position est en dehors de la liste, on la met au borne
    if(position<0)
        position = 0;
    else if(position>=size)
        position = size-1;
    //si cet �l�ment se trouve avant current, il faut reparcourir la liste depuis le d�but
    if(position<this->position)
        start();
    //on parcourt la liste jusqu'� trouver cet �l�ment
    while(this->position != position)
        next();
}

template <class T> void List<T>::removeElement(int position)
{
    if(position == 0)
    {
        ListElement *t = first->getNext();
        delete first;
        first = t;
    }
    else
    {
        //on veut trouver l'�l�ment juste avant celui � supprimer
        goTo(position--);
        //on m�morise l'�l�ment apr�s celui � supprimer
        ListElement *t = (current->getNext())->getNext();
        //on supprime l'�l�ment
        delete current->getNext();
        //on lie l'�l�ment avant avec l'�l�ment apr�s pour reformer la liste
        current->setNext(t);
    }
    //on met � jour la taille
    size--;

}

template <class T> void List<T>::insertElement(T a, int position)
{
    if(position == 0)
    {
        addElement(a);
    }
    else
    {
        //on veut trouver l'�l�ment juste avant l'endroit d'insertion
        goTo(position--);
        //on m�morise l'�l�ment � la position d'insertion
        ListElement *t = current->getNext();
        //on ins�re l'�l�ment
        current->setNext(new ChainElement(a));
        //on reforme la liste
        (current->getNext())->setNext(t);

    }
    //mise � jour de la taille et de la position de current
    size++;
    position++;
}

template <class T> void List<T>::next()
{
    current = current->getNext();
    this->position++;
}

template <class T> void List<T>::start()
{
    current = first;
    this->position = 0;
}

template <class T> void List<T>::setElementAt(T a,int position)
{
    goTo(position);
    current->setElement(a);

}

template <class T> T List<T>::getElementAt(int position) const
{
    goTo(position);
    return current->getElement();
}

template <class T> T List<T>::getNextElement() const
{
    //on ne d�passe pas la fin de la liste
    if(position+1<size)
        next();
    return current->getElement();
}
