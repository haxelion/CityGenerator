#ifndef BLOCK_H
#define BLOCK_H

#include "element.h"
#include "chain.h"
#include "rectangle.h"

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
