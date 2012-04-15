#ifndef ELEMENT_H
#define ELEMENT_H

#include "Rectangle.h"

enum ElementType {ROAD, BUILDING, GARDEN};

class Element
{
public:

    ElementType type;
    Rectangle *zone;
    float height;

    //constructeur et destructeur
    Element(Rectangle *zone, ElementType type);
    ~Element();

};

#endif // ELEMENT_H
