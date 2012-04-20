#include "city.h"
#include "mathFunctions.h"

City::City(int xWidth, int yWidth)
{
    this->xWidth = xWidth;
    this->yWidth = yWidth;
    minBlockSize = 3;
    maxBlockSize = 8;
    minBuildingHeight = 0.5;
    maxBuildingHeight = 10000;
    heightMean = 2;
    heightVariance = 0.5;

    blockList = new List<Block*>();
    roadList = new List<Element*>();
}

City::~City()
{
    delete blockList;
    delete roadList;
}

void City::divideInBlocks(Rectangle zone)
{
    int xRoad, yRoad;
    bool xDivide=false, yDivide=false;

    if(zone.getXWidth()>maxBlockSize) // Si la zone est plus grande que la taille maximale d'un bloc.
    {

        xRoad=rand(zone.getX1()+minBlockSize+1, zone.getX2()-maxBlockSize); // On la découpe en prenant soin de ne pas dépasser la taille minimale d'un bloc.
        roadList->addElement(new Element(xRoad,zone.getY1(),xRoad+1, zone.getY2(), 0, ROAD));
        xDivide=true;
    }

    if(zone.getYWidth()>maxBlockSize)
    {
        yRoad=rand(zone.getY1()+minBlockSize+1, zone.getY2()-maxBlockSize);
        yDivide=true;
    }


    if(xDivide && yDivide)
    {
        roadList->addElement(new Element(xRoad,zone.getY1(),xRoad+1, yRoad, 0, ROAD));
        roadList->addElement(new Element(xRoad,yRoad,xRoad+1, yRoad+1, 0, ROAD));
        roadList->addElement(new Element(xRoad,yRoad+1,xRoad+1, zone.getY2(), 0, ROAD));
        roadList->addElement(new Element(zone.getX1(),yRoad,xRoad, yRoad+1, 0, ROAD));
        roadList->addElement(new Element(xRoad+1,yRoad,zone.getX2(), yRoad+1, 0, ROAD));

        divideInBlocks(Rectangle(zone.getX1(),zone.getY1(),xRoad,yRoad));
        divideInBlocks(Rectangle(xRoad+1,zone.getY1(),zone.getX2(),yRoad));
        divideInBlocks(Rectangle(zone.getX1(),yRoad+1,xRoad,zone.getY2()));
        divideInBlocks(Rectangle(xRoad+1,yRoad+1,zone.getX2(),zone.getY2()));
    }
    else if(xDivide)
    {
        roadList->addElement(new Element(xRoad,zone.getY1(),xRoad+1, zone.getY2(), 0, ROAD));
        divideInBlocks(Rectangle(zone.getX1(),zone.getY1(),xRoad,zone.getY2()));
        divideInBlocks(Rectangle(xRoad+1,zone.getY1(),zone.getX2(),zone.getY2()));
    }
    else if(yDivide)
    {
        roadList->addElement(new Element(zone.getX1(),yRoad,zone.getX2(), yRoad+1, 0, ROAD));
        divideInBlocks(Rectangle(zone.getX1(),zone.getY1(),zone.getX2(),yRoad));
        divideInBlocks(Rectangle(zone.getX1(),yRoad+1,zone.getX2(),zone.getY2()));
    }
    else
    {
        //blockList->addElement(new Block());
    }
}
