#ifndef ELEMENT_H
#define ELEMENT_H

#include "zone.h"

enum ElementType {ROAD, BUILDING, GARDEN};

class Element : public Zone
{
private:

    ElementType type;
    float height;

public:

    Element(Zone zone, float height, ElementType type)
        :Zone(zone)
    {
        this->height = height;
        this->type = type;
    }
    ~Element();

    ElementType getType() const {return type;}
    float getHeight() const {return height;}
    void setType(ElementType type) {this->type = type;}
    void setHeight(float height) {this->height = height;}

};

#endif // ELEMENT_H
