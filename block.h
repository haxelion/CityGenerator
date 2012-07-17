#ifndef BLOCK_H
#define BLOCK_H

#include "element.h"
#include "list.h"
#include "zone.h"

class Block : public Zone
{
private:

    List<Element*> *elementList;
    float minBuildingHeight, maxBuildingHeight;
    float heightMean, heightVariance;
    bool garden;

public:

    Block(Zone zone, float minBuildingHeight, float maxBuildingHeight, float heightMean, float heightVariance, bool garden);
    ~Block();

    List<Element*>* getElementList() {return elementList;}
    void divideInElements(Zone zone);
    void makeElement(Zone zone);
    bool checkGarden(Zone zone);

};

#endif // BLOCK_H
