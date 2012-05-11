#ifndef LIST_H
#define LIST_H

//classes templates implementant une liste liee

template <class T> class ListItem
{

private:

    T element;
    ListItem *next;

public:

    ListItem(T element){this->element = element;}
    ListItem(){}
    T getElement() {return element;}
    ListItem* getNext() {return next;}
    void setElement(T element) {this->element = element;}
    void setNext(ListItem *next) {this->next = next;}
};

template <class T> class List
{
private:

    ListItem<T> *first, *current;
    int size, position;

public:


    List()
    {
        first = 0;
        current = 0;
        size = 0;
        position = 0;
    }

    ~List()
    {
        //on revient au debut de la liste
        start();
        ListItem<T> *t;
        //on parcourt toute la chaine en supprimant les elements un e un
        while(position<size)
        {
            t = current;
            current = current->getNext();
            delete t;
            position++;
        }
    }

    void addElement(T a)
    {
        //insertion de a au debut de la liste
        ListItem<T> *t = first;
        first = new ListItem<T>(a);
        //lien du reste de la liste au nouveau premier maillon
        first->setNext(t);
        //mise e jour de la taille et de la position de current
        size++;
        position++;
    }

    void removeElementAt(int position)
    {
        if(position == 0)
        {
            ListItem<T> *t = first->getNext();
            delete first;
            first = t;
        }
        else
        {
            //on veut trouver l'element juste avant celui e supprimer
            goTo(position--);
            //on memorise l'element après celui e supprimer
            ListItem<T> *t = (current->getNext())->getNext();
            //on supprime l'élément
            delete current->getNext();
            //on lie l'element avant avec l'element apres pour reformer la liste
            current->setNext(t);
        }
        //on met e jour la taille
        size--;

    }

    void insertElementAt(T a, int position)
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
            ListItem<T> *t = current->getNext();
            //on insère l'élément
            current->setNext(new ListItem<T>(a));
            //on reforme la liste
            (current->getNext())->setNext(t);

        }
        //mise à jour de la taille et de la position de current
        size++;
        position++;
    }

    void setElementAt(T a, int position)
    {
        goTo(position);
        current->setElement(a);
    }

    void goTo(int position)
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

    void start()
    {
        current = first;
        this->position = 0;
    }

    void next()
    {
        if(position<size)
        {
            current = current->getNext();
            position++;
        }
    }

    T getElementAt(int position)
    {
        goTo(position);
        return current->getElement();
    }

    T getCurrentElement() const
    {
        return current->getElement();
    }

    T getNextElement()
    {
        //on ne dépasse pas la fin de la liste
        if(position<size)
            next();
        return current->getElement();
    }
    int getSize() const
    {
        return size;
    }

    bool isAtTheEnd() const
    {
        return position >= size;
    }

};
#endif // LIST_H
