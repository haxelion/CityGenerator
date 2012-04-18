#ifndef BLOCK_H
#define BLOCK_H

#include "element.h"
#include "list.h"
#include "rectangle.h"

class Block : public Rectangle
{
private:

    List<Element> *elementList;

public:

    Block(int x1, int y1, int x2, int y2);
    ~Block();

    List<Element>* getElementList() {return elementList;}
    void divideInElements();

};

#endif // BLOCK_H
