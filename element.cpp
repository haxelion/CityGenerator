#include "element.h"

Element::Element(int x1, int y1, int x2, int y2, float height, ElementType type)
    :Rectangle(x1,y1,x2,y2)
{
    this->height = height;
    this->type = type;
}
