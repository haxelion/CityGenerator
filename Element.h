#ifndef ELEMENT_H
#define ELEMENT_H

#include "Rectangle.h"

enum ElementType {ROAD, BUILDING, GARDEN};

class Element : public Rectangle
{
private:

    ElementType type;
    float height;

public:

    Element(int x1, int y1, int x2, int y2, ElementType type);
    ~Element();

    ElementType getType() const {return type;}
    float getHeight() const {return height;}
    void setType(ElementType type) {this->type = type;}
    void setHeight(float height) {this->height = height;}

};

#endif // ELEMENT_H
