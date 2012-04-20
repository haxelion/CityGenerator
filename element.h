#ifndef ELEMENT_H
#define ELEMENT_H

#include "rectangle.h"

enum ElementType {ROAD, BUILDING, GARDEN};

class Element : public Rectangle
{
private:

    ElementType type;
    float height;

public:

    Element(Rectangle zone, float height, ElementType type)
        :Rectangle(zone)
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
