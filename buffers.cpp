#include "buffers.h"

Buffers::Buffers(City *city)
{
    generateRoadBuffer(city->getRoadList());
    generateElementBuffer(city->getBlockList());
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

void Buffers::makeVertex(float *vertices, float x, float y, float z, float u, float v)
{
    vertices[0] = x;
    vertices[1] = y;
    vertices[2] = z;
    vertices[3] = u;
    vertices[4] = v;
}

void Buffers::makeQuadIndices(int *indices, int i)
{
    indices[0]= i;
    indices[1]= i+1;
    indices[2]= i+2;
    indices[3]= i;
    indices[4]= i+2;
    indices[5]= i+3;
}

void Buffers::makeBuildingIndices(int *indices, int i)
{
    indices[0]= i;
    indices[1]= i+1;
    indices[2]= i+2;
    indices[3]= i;
    indices[4]= i+2;
    indices[5]= i+3;
    indices[6]= i+4;
    indices[7]= i+5;
    indices[8]= i+6;
    indices[9]= i+4;
    indices[10]= i+6;
    indices[11]= i+7;
    indices[12]= i+8;
    indices[13]= i+9;
    indices[14]= i+10;
    indices[15]= i+8;
    indices[16]= i+10;
    indices[17]= i+11;
    indices[18]= i+12;
    indices[19]= i+13;
    indices[20]= i+14;
    indices[21]= i+12;
    indices[22]= i+14;
    indices[23]= i+15;

}

void Buffers::VBAGeneration (GLuint *VBA)
{
    glGenVertexArrays(1, VBA);
    glBindVertexArray(*VBA);
}

void Buffers::VBOGeneration (GLuint *VBO, float* vertices)
{
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glGenBuffers(1, VBO);
    glBindBuffer(GL_ARRAY_BUFFER, *VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0,4,GL_FLOAT, GL_FALSE,5*sizeof(float) , (GLvoid*)0);
    glVertexAttribPointer(1,4,GL_FLOAT, GL_FALSE, 5*sizeof(float), (GLvoid*)(3*sizeof(float)));
}

void Buffers::IBOGeneration(GLuint *IBO, float* indices)
{
    glGenBuffers(1, IBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *IBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    glBindVertexArray(0);
}

void makeBuildingVBO(float *vertices, Element *building)
{
    // Face 1.
    float h = building->getHeight();
    makeVertex(vertices, building->getX1(), building->getY1(), 0, 0, 0);
    makeVertex(vertices+5, building->getX1(), building->getY2(), 0, 0, 1);
    makeVertex(vertices+10, building->getX1(), building->getY2(), h, 1, 1);
    makeVertex(vertices+15, building->getX1(), building->getY1(), h, 1, 0);
    // Face 2.
    makeVertex(vertices+20, building->getX1(), building->getY2(), 0, 0, 0);
    makeVertex(vertices+25, building->getX2(), building->getY2(), 0, 0, 1);
    makeVertex(vertices+30, building->getX2(), building->getY2(), h, 1, 1);
    makeVertex(vertices+35, building->getX1(), building->getY2(), h, 1, 0);
    // Face 3.
    makeVertex(vertices+40, building->getX2(), building->getY2(), 0, 0, 0);
    makeVertex(vertices+45, building->getX2(), building->getY1(), 0, 0, 1);
    makeVertex(vertices+50, building->getX2(), building->getY1(), h, 1, 1);
    makeVertex(vertices+55, building->getX2(), building->getY2(), h, 1, 0);
    //Face 4
    makeVertex(vertices+60, building->getX2(), building->getY1(), 0, 0, 0);
    makeVertex(vertices+65, building->getX1(), building->getY1(), 0, 0, 1);
    makeVertex(vertices+70, building->getX1(), building->getY1(), h, 1, 1);
    makeVertex(vertices+75, building->getX2(), building->getY1(), h, 1, 0);
}

void makeGardenVBO(float *vertices, Element *garden)
{
    makeVertex(vertices, garden->getX1(), garden->getY1(), 0, 0, 0);
    makeVertex(vertices+5, garden->getX1(), garden->getY2(), 0, 0, 1);
    makeVertex(vertices+10, garden->getX2(), garden->getY2(), 0, 1, 1);
    makeVertex(vertices+15, garden->getX2(), garden->getY1(), 0, 1, 0);
}

void makeRoadVBO(float *vertices, Element *road)
{
    makeVertex(vertices, road->getX1(), road->getY1(), 0, 0, 0);
    makeVertex(vertices+5, road->getX1(), road->getY2(), 0, 0, 1);
    makeVertex(vertices+10, road->getX2(), road->getY2(), 0, 1, 1);
    makeVertex(vertices+15, road->getX2(), road->getY1(), 0, 1, 0);
}

void makeRoofVBO(float *vertices, Element *building)
{
    float h = building->getHeight();
    makeVertex(vertices, building->getX1(), building->getY1(), h, 0, 0);
    makeVertex(vertices+5, building->getX1(), building->getY2(), h, 0, 1);
    makeVertex(vertices+10, building->getX2(), building->getY2(), h, 1, 1);
    makeVertex(vertices+15, building->getX2(), building->getY1(), h, 1, 0);
}

void Buffers::generateRoadBuffer(List<Element*> *roadList)
{
    float *vertices = new float [5*4*roadList->getSize()];
    float *indices = new float [6*roadList->getSize()];
    roadList->start();
    for(int i = 0;!roadList->isAtTheEnd();i++)
    {
        makeRoadVBO(vertices+i*20, roadList->getCurrentElement());
        makeQuadIndices(indices+i*6);
        roadList->next();
    }

    VBAGeneration(&roadVBA);
    VBOGeneration(&roadVBO, vertices);
    IBOGeneration(&roadIBO, indices);
}

void Buffers::countElements(List<Block *> *b)
{
    gardenNumber = 0;
    buildingNumber = 0;
    b->start();
    while (!b->isAtTheEnd())
    {
        List<Element*> *l = b->getCurrentElement()->getElementList();
        while(!l->isAtTheEnd())
        {
            if(l->getCurrentElement()->getType() == BUILDING)
                buildingNumber++;
            if(l->getCurrentElement()->getType()== GARDEN)
                gardenNumber++;
            l->next();
        }
        b->next();
    }
}

void Buffers::generateElementBuffer(List<Block*> *BlockList)
{
    // Comptage prealable du nombre de jardin et de batiment.
    countElements(BlockList);
    float *gardenVertices = new float [5*4*gardenNumber];
    float *gardenIndices = new float [6*gardenNumber];
    float *buildingVertices = new float [16*5*buildingNumber];
    float *buildingIndices = new float [4*6*buildingNumber];
    float *roofVertices = new float [4*5*buildingNumber];
    float *roofIndices = new float [6*buildingNumber];

    int i=0; // Pour les des jardins.
    int j=0; // Pour les buildings et toits

    // Remplissage des tableaux qui formeront le contenu des VBO et IBO.
    while (!BlockList->isAtTheEnd())
    {
        List<Element*> *l = BlockList->getCurrentElement()->getElementList();
        l->start();
        while (!l->isAtTheEnd())
        {
            if(l->getCurrentElement()->getType() == BUILDING)
            {
                //Pour le VBO des buildings
                makeBuildingVBO(buildingVertices+j*80, l->getCurrentElement());
                //Pour l'IBO des buildings.
                makeBuildingIndices(indices+j*24,j*16);
                // Pour le VBO des toits.
                makeRoofVBO(roofVertices+i*20, l->getCurrentElement());
                //Pour l'IBO des toits.
                makeQuadIndices(roofIndices+6*j, j*4);
                j++;
            }
            else if(l->getCurrentElement()->getType()== GARDEN)
            {
                //Pour le VBO des jardins.
                makeGardenVBO(gardenVertices+i*20, garden);
                //Pour l'IBO des jardins.
                makeQuadIndices(gardenIndices+i*6);
                i++;
            }
            l->next();
        }
        BlockList->next();
    }

    VBAgeneration(gardenVBA);
    VBOgeneration(gardenVBO, gardenVertices);
    IBOgeneration(gardenIBO, gardenIndices);
    VBAgeneration(roofVBA);
    VBOgeneration(roofVBO, roofVertices);
    IBOgeneration(roofIBO, roofIndices);
    VBAgeneration(buildingVBA);
    VBOgeneration(buildingVBO, buildingVertices);
    IBOgeneration(buildingIBO, buildingIndices);
}




