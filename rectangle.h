#ifndef RECTANGLE_H
#define RECTANGLE_H

class Rectangle
{
protected:

    int x1, y1, x2, y2;

public:

    Rectangle(int x1, int y1, int x2, int y2)
    {
        this->x1 = x1;
        this->y1 = y1;
        this->x2 = x2;
        this->y2 = y2;
    }

    int getX1() const {return x1;}
    int getY1() const {return y1;}
    int getX2() const {return x2;}
    int getY2() const {return y2;}
    void setX1(int x1){this->x1 = x1;}
    void setY1(int y1){this->y1 = y1;}
    void setX2(int x2){this->x2 = x2;}
    void setY2(int y2){this->y2 = y2;}
    int getXWidth() const {return x2-x1;}
    int getYWidth() const {return y2-y1;}
};

#endif // RECTANGLE_H
