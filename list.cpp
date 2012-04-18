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
    //on revient au début de la liste
    start();
    ListElement *t;
    //on parcourt toute la chaine en supprimant les éléments un à un
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
    //insertion de a au début de la liste
    ListElement *t = first;
    first = new ChainElement(a);
    //lien du reste de la liste au nouveau premier maillon
    first->setNext(t);
    //mise à jour de la taille et de la position de current
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
    //si cet élément se trouve avant current, il faut reparcourir la liste depuis le début
    if(position<this->position)
        start();
    //on parcourt la liste jusqu'à trouver cet élément
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
        //on veut trouver l'élément juste avant celui à supprimer
        goTo(position--);
        //on mémorise l'élément après celui à supprimer
        ListElement *t = (current->getNext())->getNext();
        //on supprime l'élément
        delete current->getNext();
        //on lie l'élément avant avec l'élément après pour reformer la liste
        current->setNext(t);
    }
    //on met à jour la taille
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
        //on veut trouver l'élément juste avant l'endroit d'insertion
        goTo(position--);
        //on mémorise l'élément à la position d'insertion
        ListElement *t = current->getNext();
        //on insère l'élément
        current->setNext(new ChainElement(a));
        //on reforme la liste
        (current->getNext())->setNext(t);

    }
    //mise à jour de la taille et de la position de current
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
    //on ne dépasse pas la fin de la liste
    if(position+1<size)
        next();
    return current->getElement();
}
