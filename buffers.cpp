#include "buffers.h"

Buffers::Buffers()
{
}

Buffers::~Buffers()
{

}

void Buffers::generateRoadBuffer(List<Element*> *roadList)
{
    float *vertex = new float [5*4*roadList->getSize()];
    float *indice = new float [6*roadList->getSize()];
    roadList->start();

    int i=0; // Pour les VBO des routes
    int j=0; // Pour les IBO des routes

    while(!roadList->isAtTheEnd())
    {
        // Pour le VBO des routes, toutes les "5 lignes" représente 3 vertices (3 première lignes) ainsi que
        // les coordonnées pour la texture (2 dernière lignes). Cette convention sera respectée pour chaque VBO
        vertex[i] = roadList->getCurrentElement()->getX1();
        vertex[i+1] = roadList->getCurrentElement()->getY1();
        vertex[i+2] = 0;
        vertex[i+3] = 0;
        vertex[i+4] = 0;

        vertex[i+5] = roadList->getCurrentElement()->getX1();
        vertex[i+6] = roadList->getCurrentElement()->getY2();
        vertex[i+7] = 0;
        vertex[i+8] = 0;
        vertex[i+9] = 1;

        vertex[i+10] = roadList->getCurrentElement()->getX2();
        vertex[i+11] = roadList->getCurrentElement()->getY2();
        vertex[i+12] = 0;
        vertex[i+13] = 1;
        vertex[i+14] = 1;

        vertex[i+15] = roadList->getCurrentElement()->getX2();
        vertex[i+16] = roadList->getCurrentElement()->getY1();
        vertex[i+17] = 0;
        vertex[i+18] = 1;
        vertex[i+19] = 0;

        // Pour le IBO des routes
        // Chaque bloc de 3 ligne représente une face (triangulaire)
        // La même convention sera utilisé pour tous les IBO

        indice[j]= j;
        indice[j+1]= j+1;
        indice[j+2]= j+2;

        indice[j+3]= j;
        indice[j+4]= j+2;
        indice[j+5]= j+3;


        i+=20;
        j+=6;
        roadList->next();
    }

}

void Buffers::generateElementBuffer(List<Block*> *BlockList)
{
    int gardenNumber = 0;
    int buildingNumber = 0;
    blockList->start();
    while (!BlockList->isAtTheEnd())
    {
        List<Element*> *l = BlockList->getCurrentElement()->getElementList();
        while(!l->isAtTheEnd())
        {
            if(l->getCurrentElement()->getType() == BUILDING)
                buildingNumber++;
            if(l->getCurrentElement()->getType()== GARDEN)
                gardenNumber++;
            l->next();
        }
        BlockList->next();
    }
    float *vertexGarden = new float [5*4*gardenNumber];
    float *indiceGarden = new float [6*gardenNumber];
    float *vertexBuilding = new float [16*5*buildingNumber];
    float *indiceBuilding = new float [4*6*buildingNumber];
    float *vertexRoof = new float [4*5*buildingNumber];
    float *indiceRoof = new float [6*buildingNumber];

    int i=0; // Pour les VBO des jardins
    int j=0; // Pour les VBO buildings
    int k=0; // Pour les VBO toits
    int k2=0; //Pour les IBO des buildings
    int m=0; // Pour les IBO jardins
    int n=0; // Pour les IBO toits
    while (!BlockList->isAtTheEnd())
    {
        List<Element*> *l = BlockList->getCurrentElement()->getElementList();

        while (!l->isAtTheEnd())
        {
            if(l->getCurrentElement()->getType() == BUILDING)
            {
                // Pour le VBO des buildings
                // Face 1
                vertexBuilding[j] = l->getCurrentElement()->getX1() ;
                vertexBuilding[j+1] = l->getCurrentElement()->getY1();
                vertexBuilding[j+2] = 0;
                vertexBuilding[j+3] = 0;
                vertexBuilding[j+4] = 0;

                vertexBuilding[j+5] = l->getCurrentElement()->getX1();
                vertexBuilding[j+6] = l->getCurrentElement()->getY2();
                vertexBuilding[j+7] = 0;
                vertexBuilding[j+8] = 0;
                vertexBuilding[j+9] = 1;

                vertexBuilding[j+10] = l->getCurrentElement()->getX1();
                vertexBuilding[j+11] = l->getCurrentElement()->getY2();
                vertexBuilding[j+12] = l->getCurrentElement()->getHeight();
                vertexBuilding[j+13] = 1;
                vertexBuilding[j+14] = 1;

                vertexBuilding[j+15] = l->getCurrentElement()->getX1();
                vertexBuilding[j+16] = l->getCurrentElement()->getY1();
                vertexBuilding[j+17] = l->getCurrentElement()->getHeight();
                vertexBuilding[j+18] = 1;
                vertexBuilding[j+19] = 0;

                // Face 2
                vertexBuilding[j+20] = l->getCurrentElement()->getX1() ;
                vertexBuilding[j+21] = l->getCurrentElement()->getY2();
                vertexBuilding[j+22] = 0;
                vertexBuilding[j+23] = 0;
                vertexBuilding[j+24] = 0;

                vertexBuilding[j+25] = l->getCurrentElement()->getX2();
                vertexBuilding[j+26] = l->getCurrentElement()->getY2();
                vertexBuilding[j+27] = 0;
                vertexBuilding[j+28] = 0;
                vertexBuilding[j+29] = 1;

                vertexBuilding[j+30] = l->getCurrentElement()->getX2();
                vertexBuilding[j+31] = l->getCurrentElement()->getY2();
                vertexBuilding[j+32] = l->getCurrentElement()->getHeight();
                vertexBuilding[j+33] = 1;
                vertexBuilding[j+34] = 1;

                vertexBuilding[j+35] = l->getCurrentElement()->getX1();
                vertexBuilding[j+36] = l->getCurrentElement()->getY2();
                vertexBuilding[j+37] = l->getCurrentElement()->getHeight();
                vertexBuilding[j+38] = 1;
                vertexBuilding[j+39] = 0;

                // Face 3
                vertexBuilding[j+20] = l->getCurrentElement()->getX2() ;
                vertexBuilding[j+21] = l->getCurrentElement()->getY2();
                vertexBuilding[j+22] = 0;
                vertexBuilding[j+23] = 0;
                vertexBuilding[j+24] = 0;

                vertexBuilding[j+25] = l->getCurrentElement()->getX2();
                vertexBuilding[j+26] = l->getCurrentElement()->getY1();
                vertexBuilding[j+27] = 0;
                vertexBuilding[j+28] = 0;
                vertexBuilding[j+29] = 1;

                vertexBuilding[j+30] = l->getCurrentElement()->getX2();
                vertexBuilding[j+31] = l->getCurrentElement()->getY1();
                vertexBuilding[j+32] = l->getCurrentElement()->getHeight();
                vertexBuilding[j+33] = 1;
                vertexBuilding[j+34] = 1;

                vertexBuilding[j+35] = l->getCurrentElement()->getX2();
                vertexBuilding[j+36] = l->getCurrentElement()->getY2();
                vertexBuilding[j+37] = l->getCurrentElement()->getHeight(;
                vertexBuilding[j+38] = 1;
                vertexBuilding[j+39] = 0;

                // Face 4
                vertexBuilding[j+20] = l->getCurrentElement()->getX2() ;
                vertexBuilding[j+21] = l->getCurrentElement()->getY1();
                vertexBuilding[j+22] = 0;
                vertexBuilding[j+23] = 0;
                vertexBuilding[j+24] = 0;

                vertexBuilding[j+25] = l->getCurrentElement()->getX1();
                vertexBuilding[j+26] = l->getCurrentElement()->getY1();
                vertexBuilding[j+27] = 0;
                vertexBuilding[j+28] = 0;
                vertexBuilding[j+29] = 1;

                vertexBuilding[j+30] = l->getCurrentElement()->getX1();
                vertexBuilding[j+31] = l->getCurrentElement()->getY1();
                vertexBuilding[j+32] = l->getCurrentElement()->getHeight();
                vertexBuilding[j+33] = 1;
                vertexBuilding[j+34] = 1;

                vertexBuilding[j+35] = l->getCurrentElement()->getX2();
                vertexBuilding[j+36] = l->getCurrentElement()->getY1();
                vertexBuilding[j+37] = l->getCurrentElement()->getHeight();
                vertexBuilding[j+38] = 1;
                vertexBuilding[j+39] = 1;


                //Pour l'IBO des buildings
                indiceBuilding[k2]= k2;
                indiceBuilding[k2]= k2+5;
                indiceBuilding[k2]= k2+4;

                indiceBuilding[k2]= k2;
                indiceBuilding[k2]= k2+1;
                indiceBuilding[k2]= k2+5;

                indiceBuilding[k2]= k2+1;
                indiceBuilding[k2]= k2+6;
                indiceBuilding[k2]= k2+5;

                indiceBuilding[k2]= k2+1;
                indiceBuilding[k2]= k2+2;
                indiceBuilding[k2]= k2+6;

                indiceBuilding[k2]= k2+2;
                indiceBuilding[k2]= k2+7;
                indiceBuilding[k2]= k2+6;

                indiceBuilding[k2]= k2+2;
                indiceBuilding[k2]= k2+3;
                indiceBuilding[k2]= k2+7;

                indiceBuilding[k2]= k2+3;
                indiceBuilding[k2]= k2+4;
                indiceBuilding[k2]= k2+7;

                indiceBuilding[k2]= k2+3;
                indiceBuilding[k2]= k2;
                indiceBuilding[k2]= k2+4;

                // Pour le VBO des toits
                vertexRoof[k] = l->getCurrentElement()->getX1();
                vertexRoof[k+1] = l->getCurrentElement()->getY1();
                vertexRoof[k+2] = l->getCurrentElement()->getHeight();
                vertexRoof[k+3] = 0;
                vertexRoof[k+4] = 0;

                vertexRoof[k+5] = l->getCurrentElement()->getX1();
                vertexRoof[k+6] = l->getCurrentElement()->getY2();
                vertexRoof[k+7] = l->getCurrentElement()->getHeight();
                vertexRoof[k+8] = 0;
                vertexRoof[k+9] = 1;

                vertexRoof[k+10] = l->getCurrentElement()->getX2();
                vertexRoof[k+11] = l->getCurrentElement()->getY2();
                vertexRoof[k+12] = l->getCurrentElement()->getHeight();
                vertexRoof[k+13] = 1;
                vertexRoof[k+14] = 1;

                vertexRoof[k+15] = l->getCurrentElement()->getX2();
                vertexRoof[k+16] = l->getCurrentElement()->getY1();
                vertexRoof[k+17] = l->getCurrentElement()->getHeight();
                vertexRoof[k+18] = 1;
                vertexRoof[k+19] = 0;


                //Pour l'IBO des toîts

                indiceRoof[n] = n;
                indiceRoof[n+1] = n+1;
                indiceRoof[n+2] = n+2;

                indiceRoof[n+3] = n;
                indiceRoof[n+4] = n+2;
                indiceRoof[n+5] = n+3;

                j += 80;
                k += 20;
                k2 += 24;
                n += 6;
            }
            if(l->getCurrentElement()->getType()== GARDEN)
            {
                // Pour le VBO des jardins
                vertexGarden[i] = l->getCurrentElement()->getX1();
                vertexGarden[i+1] = l->getCurrentElement()->getY1();
                vertexGarden[i+2] = 0;
                vertexGarden[i+3] = 0;
                vertexGarden[i+4] = 0;

                vertexGarden[i+5] = l->getCurrentElement()->getX1();
                vertexGarden[i+6] = l->getCurrentElement()->getY2();
                vertexGarden[i+7] = 0;
                vertexGarden[i+8] = 0;
                vertexGarden[i+9] = 1;

                vertexGarden[i+10] = l->getCurrentElement()->getX2();
                vertexGarden[i+11] = l->getCurrentElement()->getY2();
                vertexGarden[i+12] = 0;
                vertexGarden[i+13] = 1;
                vertexGarden[i+14] = 1;

                vertexGarden[i+15] = l->getCurrentElement()->getX2();
                vertexGarden[i+16] = l->getCurrentElement()->getY1();
                vertexGarden[i+17] = 0;
                vertexGarden[i+18] = 1;
                vertexGarden[i+19] = 0;

                //Pour le IBO des jardins

                indiceGarden[m]= m;
                indiceGarden[m+1]= m+1;
                indiceGarden[m+2]= m+2;

                indiceGarden[m+3]= m;
                indiceGarden[m+4]= m+2;
                indiceGarden[m+5]= m+3;

                i +=20;
                m +=6;
            }
            l->next();
        }
        BlockList->next();
    }


}
