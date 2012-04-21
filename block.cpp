#include "block.h"
#include "mathFunctions.h"

Block::Block(Rectangle zone, float minBuildingHeight, float maxBuildingHeight, float heightMean, float heightVariance, bool garden)
    :Rectangle(zone)
{
    this->minBuildingHeight = minBuildingHeight;
    this->maxBuildingHeight = maxBuildingHeight;
    this->heightMean = heightMean;
    this->heightVariance = heightVariance;
    this->garden = garden;
}

void Block::divideInElements(Rectangle zone)
{
    bool divideX = false, divideY = false;
    int midX,midY;

    if(zone.getXWidth()>1 && randUniform()>=0.5) // Une chance sur deux de diviser et seulement si il y a de la place.
    {
        midX = rand(zone.getX1()+1,zone.getX2()-1); // Laisse au moins une colonne libre de chaque côté.
        divideX = true;
    }
    if(zone.getYWidth()>1 && randUniform()>=0.5)
    {
        midY = rand(zone.getY1()+1,zone.getY2()-1);
        divideY = true;
    }

    if(divideX && divideY)
    {
        divideInElements(Rectangle(zone.getX1(),zone.getY1(),midX,midY));
        divideInElements(Rectangle(midX,zone.getY1(),zone.getX2(),midY));
        divideInElements(Rectangle(zone.getX1(),midY,midX,zone.getY2()));
        divideInElements(Rectangle(midX,midY,zone.getX2(),zone.getY2()));
    }
    else if(divideX)
    {
        divideInElements(Rectangle(zone.getX1(),zone.getY1(),midX,zone.getY2()));
        divideInElements(Rectangle(midX,zone.getY1(),zone.getX2(),zone.getY2()));
    }
    else if(divideY)
    {
        divideInElements(Rectangle(zone.getX1(),zone.getY1(),zone.getX2(),midY));
        divideInElements(Rectangle(zone.getX1(),midY,zone.getX2(),zone.getY2()));
    }
    else
    {
        makeElement(zone);
    }
}

bool Block::checkGarden(Rectangle zone)
{
    if(zone.getX1() == this->getX1())
        return false;
    else if (zone.getY1() == this->getY1())
        return false;
    else if(zone.getX2() == this->getX2())
        return false;
    else if(zone.getY2() == this->getY2())
        return false;
    return true;
}

void Block::makeElement(Rectangle zone)
{
    if(garden&&checkGarden(zone))
    {
        elementList->addElement(new Element(zone,0, GARDEN));
    }
    else
    {
        float height = maxf(minBuildingHeight, minf(maxBuildingHeight, (float)randNormal(heightMean,heightVariance)));
        elementList->addElement(new Element(zone,height, BUILDING));
    }
}
