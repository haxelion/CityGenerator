#include "buffers.h"

Buffers::Buffers()
{
}

void Buffers::generateRoadBuffer(List<Element*> *roadList)
{
    float *vertex = new float [5*4*roadList->getSize()];
    float *indice = new float [6*roadList->getSize()];
    roadList->start();
    for(int i=0;!roadList->isAtTheEnd(); i+=20)
    {
        // Pour le VBO des routes, toutes les "5 lignes" représente une demi face = 3 vertices (3 première lignes)
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

        //Pour le IBO des routes
        indice[i]= i;
        indice[i+1]= i+1;
        indice[i+2]= i+2;
        indice[i+3]= i;
        indice[i+4]= i+2;
        indice[i+5]=i+3;

        roadList->next();
    }

}

void Buffers::generateElementBuffer(List<Block*> *BlockList)
{
    int nombreJardin = 0;
    int nombreBuilding = 0;
    blockList->start();
    while (!BlockList->isAtTheEnd())
    {
        List<Element*> *l = BlockList->getCurrentElement()->getElementList();
        while(!l->isAtTheEnd())
        {
            if(l->getCurrentElement()->getType() == BUILDING)
                nombreBuilding++;
            if(l->getCurrentElement()->getType()== GARDEN)
                nombreJardin++;
            l->next();
        }
        BlockList->next();
    }
    float *vertexJardin = new float [5*4*nombreJardin];
    float *indiceJardin = new float [6*nombreJardin];
    float *vertexBuilding = new float [16*5*nombreBuilding];
    float *indiceBuilding = new float [4*6*nombreBuilding];
    float *vertexRoof = new float [4*5*nombreBuilding];
    float *indiceRoof = new float [6*nombreBuilding];

    int i=0; // Pour les jardins
    int j=0; // Pour les buildings
    int k=0; // Pour les toits
    while (!BlockList->isAtTheEnd())
    {
        List<Element*> *l = BlockList->getCurrentElement()->getElementList();

        while (!l->isAtTheEnd())
        {
            if(l->getCurrentElement()->getType() == BUILDING)
            {
                // Pour le VBO des buildings
                //Face (carré) 1
                vertex[i] = l->getCurrentElement()->getX1() ;
                vertex[i+1] = l->getCurrentElement()->getY1();
                vertex[i+2] = 0;
                vertex[i+3] = ;
                vertex[i+4] = ;

                vertex[i+5] = l->getCurrentElement()->getX1();
                vertex[i+6] = l->getCurrentElement()->getY2();
                vertex[i+7] = 0;
                vertex[i+8] = ;
                vertex[i+9] = ;

                vertex[i+10] = l->getCurrentElement()->getX1();
                vertex[i+11] = l->getCurrentElement()->getY2();
                vertex[i+12] = l->getCurrentElement()->getHeight();
                vertex[i+13] = ;
                vertex[i+14] = ;

                vertex[i+15] = l->getCurrentElement()->getX1();
                vertex[i+16] = l->getCurrentElement()->getY1();
                vertex[i+17] = l->getCurrentElement()->getHeight();
                vertex[i+18] = ;
                vertex[i+19] = ;

                //Face 2
                vertex[i+20] = l->getCurrentElement()->getX1() ;
                vertex[i+21] = l->getCurrentElement()->getY2();
                vertex[i+22] = 0;
                vertex[i+23] = ;
                vertex[i+24] = ;

                vertex[i+25] = l->getCurrentElement()->getX1();
                vertex[i+26] = l->getCurrentElement()->getY2();
                vertex[i+27] = l->getCurrentElement()->getHeight();
                vertex[i+28] = ;
                vertex[i+29] = ;

                vertex[i+30] = ;
                vertex[i+31] = ;
                vertex[i+32] = ;
                vertex[i+33] = ;
                vertex[i+34] = ;

                vertex[i+35] = ;
                vertex[i+36] = ;
                vertex[i+37] = ;
                vertex[i+38] = ;
                vertex[i+39] = ;

                //Pour l'IBO des buildings

                indice[i]= ;
                indice[i]= ;
                indice[i]= ;
                indice[i]= ;
                indice[i]= ;
                indice[i]=;

                indice[i]= ;
                indice[i]= ;
                indice[i]= ;
                indice[i]= ;
                indice[i]= ;
                indice[i]=;

                indice[i]= ;
                indice[i]= ;
                indice[i]= ;
                indice[i]= ;
                indice[i]= ;
                indice[i]=;

                indice[i]=;
                indice[i]=;
                indice[i]=;
                indice[i]=;
                indice[i]=;
                indice[i]=;



            }
            if(l->getCurrentElement()->getType()== GARDEN)
            {
                // Pour le VBO des routes
                vertex[i] = l->getCurrentElement()->getX1();
                vertex[i+1] = l->getCurrentElement()->getY1();
                vertex[i+2] = 0;
                vertex[i+3] = 0;
                vertex[i+4] = 0;

                vertex[i+5] = l->getCurrentElement()->getX1();
                vertex[i+6] = l->getCurrentElement()->getY2();
                vertex[i+7] = 0;
                vertex[i+8] = 0;
                vertex[i+9] = 1;

                vertex[i+10] = l->getCurrentElement()->getX2();
                vertex[i+11] = l->getCurrentElement()->getY2();
                vertex[i+12] = 0;
                vertex[i+13] = 1;
                vertex[i+14] = 1;

                vertex[i+15] = l->getCurrentElement()->getX2();
                vertex[i+16] = l->getCurrentElement()->getY1();
                vertex[i+17] = 0;
                vertex[i+18] = 1;
                vertex[i+19] = 0;

                //Pour le IBO des routes
                indice[i]= i;
                indice[i+1]= i+1;
                indice[i+2]= i+2;
                indice[i+3]= i;
                indice[i+4]= i+2;
                indice[i+5]=i+3;

                i +=20;
            }
            l->next();
        }
        BlockList->next();
    }


}
