#ifndef RECTANGLE_H
#define RECTANGLE_H

class Rectangle
{
public:

    int x1, y1, x2, y2;

    Rectangle(int x1, int y1, int x2, int y2);

    int getWidth() const {return x2-x1;}
    int getHeight() const {return y2-y1;}
};

#endif // RECTANGLE_H
