#include "buffers.h"

Buffers::Buffers()
{
}

Buffers::~Buffers()
{
    glDeleteBuffers(1, &roadVBO);
    glDeleteBuffers(1, &roadIBO);
    glDeleteBuffers(1, &roofVBO);
    glDeleteBuffers(1, &roofIBO);
    glDeleteBuffers(1, &buildingVBO);
    glDeleteBuffers(1, &buildingIBO);
    glDeleteBuffers(1, &gardenVBO);
    glDeleteBuffers(1, &gardenIBO);
    glDeleteVertexArrays(1, &roadVBA);
    glDeleteVertexArrays(1, &roofVBA);
    glDeleteVertexArrays(1, &buildingVBA);
    glDeleteVertexArrays(1, &gardenVBA);
}

void Buffers::generateRoadBuffer(List<Element*> *roadList)
{

    float *vertex = new float [5*4*roadList->getSize()];
    float *indice = new float [6*roadList->getSize()];
    roadList->start();
    for(int i = 0;!roadList->isAtTheEnd();i++)
    {
        makeVertex(vertex+(i*4)*5, roadList->getCurrentElement()->getX1(), roadList->getCurrentElement()->getY1(), 0, 0, 0);
        makeVertex(vertex+(i*4+1)*5, roadList->getCurrentElement()->getX1(), roadList->getCurrentElement()->getY2(), 0, 0, 1);
        makeVertex(vertex+(i*4+2)*5, roadList->getCurrentElement()->getX2(), roadList->getCurrentElement()->getY2(), 0, 1, 1);
        makeVertex(vertex+(i*4+3)*5, roadList->getCurrentElement()->getX2(), roadList->getCurrentElement()->getY1(), 0, 1, 0);
        makeQuadIndices(indice+i*6);
        roadList->next();
    }

    // Création VBA
    glGenVertexArrays(1, &roadVBA);
    glBindVertexArray(roadVBA);
    //Generation VBO.
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glGenBuffers(1, &roadVBO);
    glBindBuffer(GL_ARRAY_BUFFER, roadVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertex), vertex, GL_STATIC_DRAW);
    glVertexAttribPointer(0,4,GL_FLOAT, GL_FALSE, 5*sizeof(float), (GLvoid*)0);
    glVertexAttribPointer(1,4,GL_FLOAT, GL_FALSE, 5*sizeof(float), (GLvoid*)(3*sizeof(float)));
    //Generation IBO.
    glGenBuffers(1, &roadIBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, roadIBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indice), indice, GL_STATIC_DRAW);
    glBindVertexArray(0);
}

void Buffers::generateElementBuffer(List<Block*> *BlockList)
{

    // Comptage prealable du nombre de jardin et de batiment.
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

    int i=0; // Pour les VBO des jardins.
    int j=0; // Pour les VBO buildings.
    int k=0; // Pour les VBO toits.
    int k2=0; //Pour les IBO des buildings.
    int m=0; // Pour les IBO jardins.
    int n=0; // Pour les IBO toits.

    // Remplissage des tableaux qui formeront le contenu des VBO et IBO.
    while (!BlockList->isAtTheEnd())
    {
        List<Element*> *l = BlockList->getCurrentElement()->getElementList();

        while (!l->isAtTheEnd())
        {
            if(l->getCurrentElement()->getType() == BUILDING)
            {
                // Pour le VBO des buildings.
                // Face 1.
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

                // Face 2.
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

                // Face 3.
                vertexBuilding[j+40] = l->getCurrentElement()->getX2() ;
                vertexBuilding[j+41] = l->getCurrentElement()->getY2();
                vertexBuilding[j+42] = 0;
                vertexBuilding[j+43] = 0;
                vertexBuilding[j+44] = 0;

                vertexBuilding[j+45] = l->getCurrentElement()->getX2();
                vertexBuilding[j+46] = l->getCurrentElement()->getY1();
                vertexBuilding[j+47] = 0;
                vertexBuilding[j+48] = 0;
                vertexBuilding[j+49] = 1;

                vertexBuilding[j+50] = l->getCurrentElement()->getX2();
                vertexBuilding[j+51] = l->getCurrentElement()->getY1();
                vertexBuilding[j+52] = l->getCurrentElement()->getHeight();
                vertexBuilding[j+53] = 1;
                vertexBuilding[j+54] = 1;

                vertexBuilding[j+55] = l->getCurrentElement()->getX2();
                vertexBuilding[j+56] = l->getCurrentElement()->getY2();
                vertexBuilding[j+57] = l->getCurrentElement()->getHeight(;
                vertexBuilding[j+58] = 1;
                vertexBuilding[j+59] = 0;

                // Face 4.
                vertexBuilding[j+60] = l->getCurrentElement()->getX2() ;
                vertexBuilding[j+61] = l->getCurrentElement()->getY1();
                vertexBuilding[j+62] = 0;
                vertexBuilding[j+63] = 0;
                vertexBuilding[j+64] = 0;

                vertexBuilding[j+65] = l->getCurrentElement()->getX1();
                vertexBuilding[j+66] = l->getCurrentElement()->getY1();
                vertexBuilding[j+67] = 0;
                vertexBuilding[j+68] = 0;
                vertexBuilding[j+69] = 1;

                vertexBuilding[j+70] = l->getCurrentElement()->getX1();
                vertexBuilding[j+71] = l->getCurrentElement()->getY1();
                vertexBuilding[j+72] = l->getCurrentElement()->getHeight();
                vertexBuilding[j+73] = 1;
                vertexBuilding[j+74] = 1;
                vertexBuilding[j+75] = l->getCurrentElement()->getX2();
                vertexBuilding[j+76] = l->getCurrentElement()->getY1();
                vertexBuilding[j+77] = l->getCurrentElement()->getHeight();
                vertexBuilding[j+78] = 1;
                vertexBuilding[j+79] = 1;


                //Pour l'IBO des buildings.
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

                // Pour le VBO des toits.
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


                //Pour l'IBO des toits.

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
            else if(l->getCurrentElement()->getType()== GARDEN)
            {
                // Pour le VBO des jardins.
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

                //Pour l'IBO des jardins.

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

    // Generation roofVBA
    glGenVertexArrays(1, &roofVBA);
    glBindVertexArray(roofVBA);
    //Generation roofVBO
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glGenBuffers(1, &roofVBO);
    glBindBuffer(GL_ARRAY_BUFFER, roofVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertexRoof), vertexRoof, GL_STATIC_DRAW);
    glVertexAttribPointer(0,4,GL_FLOAT, GL_FALSE,6*sizeof(float) , (GLvoid*)0);
    glVertexAttribPointer(1,4,GL_FLOAT, GL_FALSE, 6*sizeof(float), (GLvoid*)(3*sizeof(float)));
    //Generation roofIBO
    glGenBuffers(1, &roofIBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, roofIBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(indiceRoof), indiceRoof, GL_STATIC_DRAW);
    glBindVertexArray(0);

    // Generation buildingVBA
    glGenVertexArrays(1, &buildingVBA);
    glBindVertexArray(buildingVBA);
    // Generation buildingVBA
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glGenBuffers(1, &buildingVBO);
    glBindBuffer(GL_ARRAY_BUFFER, buildingVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertexBuilding), vertexBuilding, GL_STATIC_DRAW);
    glVertexAttribPointer(0,4,GL_FLOAT, GL_FALSE, 6*sizeof(float), (GLvoid*)0);
    glVertexAttribPointer(1,4,GL_FLOAT, GL_FALSE, 6*sizeof(float), (GLvoid*)(3*sizeof(float)));
    //Generation buildingIBO
    glGenBuffers(1, &buildingIBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buildingIBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(indiceBuilding), indiceBuilding, GL_STATIC_DRAW);
    glBindVertexArray(0);

    // Generation gardenVBA
    glGenVertexArrays(1, &gardenVBA);
    glBindVertexArray(gardenVBA);
    // Generation gardenVBO
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glGenBuffers(1, &gardenVBO);
    glBindBuffer(GL_ARRAY_BUFFER, gardenVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertexGarden), vertexGarden, GL_STATIC_DRAW);
    glVertexAttribPointer(0,4,GL_FLOAT, GL_FALSE, 6*sizeof(float), (GLvoid*)0);
    glVertexAttribPointer(1,4,GL_FLOAT, GL_FALSE, 6*sizeof(float), (GLvoid*)(3*sizeof(float)));
    //Generation gardenIBO
    glGenBuffers(1, &gardenIBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, gardenIBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(indiceGarden), indiceGarden, GL_STATIC_DRAW);
    glBindVertexArray(0);
}




