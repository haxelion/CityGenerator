#ifndef BLOCK_H
#define BLOCK_H

#include "Element.h"
#include "Chain.h"
#include "Rectangle.h"

class Block : public Rectangle
{
private:

    Chain<Element> *elementChain;

public:

    Block(int x1, int y1, int x2, int y2);
    ~Block();

    Chain<Element>* getElementChain() {return elementChain;}
    void divideInElements();

};

#endif // BLOCK_H
