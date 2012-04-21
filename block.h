#ifndef BLOCK_H
#define BLOCK_H

#include "element.h"
#include "list.h"
#include "rectangle.h"

class Block : public Rectangle
{
private:

    List<Element*> *elementList;
    float minBuildingHeight, maxBuildingHeight;
    float heightMean, heightVariance;
    bool garden;

public:

    Block(Rectangle zone, float minBuildingHeight, float maxBuildingHeight, float heightMean, float heightVariance, bool garden);
    ~Block();

    List<Element*>* getElementList() {return elementList;}
    void divideInElements(Rectangle zone);
    void makeElement(Rectangle zone);
    bool checkGarden(Rectangle zone);

};

#endif // BLOCK_H
