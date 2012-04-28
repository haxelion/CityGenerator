#include "buffers.h"

Buffers::Buffers()
{
}

void Buffers::generateRoadBuffer(List<Element> *roadList)
{
    float *vertex = new float [5*4*roadList->getSize()];
    float *indice = new float [6*roadList->getSize()];
    roadList->start();
    for(int i=0;!roadList->isAtTheEnd(); i++)
    {
        // Pour le VBO
        vertex[i] = roadList->getCurrentElement().getX1();
        vertex[i+1] = roadList->getCurrentElement().getY1();
        vertex[i+2] = 0;
        vertex[i+3] = 0;
        vertex[i+4] = 0;
        vertex[i+5] = roadList->getCurrentElement().getX1();
        vertex[i+6] = roadList->getCurrentElement().getY2();
        vertex[i+7] = 0;
        vertex[i+8] = 0;
        vertex[i+9] = 1;
        vertex[i+10] = roadList->getCurrentElement().getX2();
        vertex[i+11] = roadList->getCurrentElement().getY2();
        vertex[i+12] = 0;
        vertex[i+13] = 1;
        vertex[i+14] = 1;
        vertex[i+15] = roadList->getCurrentElement().getX2();
        vertex[i+16] = roadList->getCurrentElement().getY1();
        vertex[i+17] = 0;
        vertex[i+18] = 1;
        vertex[i+19] = 0;

        //Pour le IBO
        indice[i]= i;
        indice[i+1]= i+1;
        indice[i+2]= i+2;
        indice[i+3]= i;
        indice[i+4]= i+2;
        indice[i+5]=i+3;

        roadList->next();
    }

}

void Buffers::generateElementBuffer(List<Element> *BlockList)
{
    /*for(int i=0;!roadList->isAtTheEnd(); i++)
    {
        for (int j = 0; !)
    }
    */
}
