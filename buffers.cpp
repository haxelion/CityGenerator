#include "buffers.h"

Buffers::Buffers(City *city)
{
    glGenVertexArrays(NUMBER_OF_VAO, vao);
    glGenBuffers(NUMBER_OF_VAO*2, vbo);
    generateRoadBuffer(city->getRoadList());
    generateElementBuffer(city->getBlockList());
}

Buffers::~Buffers()
{
    glDeleteVertexArrays(NUMBER_OF_VAO, vao);
    glDeleteBuffers(NUMBER_OF_VAO*2, vbo);
}

void Buffers::VBOGeneration (int n, float* vertices, GLsizei size)
{
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, vbo[n]);
    glBufferData(GL_ARRAY_BUFFER, size*sizeof(float), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0,3,GL_FLOAT, GL_FALSE, 5*sizeof(float), (GLvoid*)0);
    glVertexAttribPointer(1,2,GL_FLOAT, GL_FALSE, 5*sizeof(float), (GLvoid*)(3*sizeof(float)));
}

void Buffers::IBOGeneration(int n, GLuint* indices, GLsizei size)
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo[n+NUMBER_OF_VAO]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, size*sizeof(GLuint), indices, GL_STATIC_DRAW);
}

void Buffers::makeVertex(float *vertex, float x, float y, float z, float u, float v)
{
    vertex[0] = x;
    vertex[1] = y;
    vertex[2] = z;
    vertex[3] = u;
    vertex[4] = v;
}

void Buffers::makeQuadIndices(GLuint *indices, int i)
{
    indices[0]= i;
    indices[1]= i+1;
    indices[2]= i+2;
    indices[3]= i;
    indices[4]= i+2;
    indices[5]= i+3;
}
void Buffers::makeBuildingIndices(GLuint *indices, int i)
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

void Buffers::makeBuildingVBO(float *vertices, Element *building)
{
    // Face 1.
    float h = building->getHeight();
    makeVertex(vertices, building->getX1(), building->getY1(), 0, 0, 0);
    makeVertex(vertices+5, building->getX1(), building->getY1(), h, h, 0);
    makeVertex(vertices+10, building->getX1(), building->getY2(), h, h, building->getYWidth());
    makeVertex(vertices+15, building->getX1(), building->getY2(), 0, 0, building->getYWidth());
    // Face 2.
    makeVertex(vertices+20, building->getX1(), building->getY2(), 0, 0, 0);
    makeVertex(vertices+25, building->getX1(), building->getY2(), h, h, 0);
    makeVertex(vertices+30, building->getX2(), building->getY2(), h, h, building->getXWidth());
    makeVertex(vertices+35, building->getX2(), building->getY2(), 0, 0, building->getXWidth());
    // Face 3.
    makeVertex(vertices+40, building->getX2(), building->getY2(), 0, 0, 0);
    makeVertex(vertices+45, building->getX2(), building->getY2(), h, h, 0);
    makeVertex(vertices+50, building->getX2(), building->getY1(), h, h, building->getYWidth());
    makeVertex(vertices+55, building->getX2(), building->getY1(), 0, 0, building->getYWidth());
    //Face 4
    makeVertex(vertices+60, building->getX2(), building->getY1(), 0, 0, 0);
    makeVertex(vertices+65, building->getX2(), building->getY1(), h, h, 0);
    makeVertex(vertices+70, building->getX1(), building->getY1(), h, h, building->getXWidth());
    makeVertex(vertices+75, building->getX1(), building->getY1(), 0, 0, building->getXWidth());
}

void Buffers::makeGardenVBO(float *vertices, Element *garden)
{
    makeVertex(vertices, garden->getX1(), garden->getY1(), 0, 0, 0);
    makeVertex(vertices+5, garden->getX2(), garden->getY1(), 0, 1, 0);
    makeVertex(vertices+10, garden->getX2(), garden->getY2(), 0, 1, 1);
    makeVertex(vertices+15, garden->getX1(), garden->getY2(), 0, 0, 1);
}

void Buffers::makeRoadVBO(float *vertices, Element *road)
{
    makeVertex(vertices, road->getX1(), road->getY1(), 0, 0, 0);
    makeVertex(vertices+5, road->getX2(), road->getY1(), 0, road->getXWidth(), 0);
    makeVertex(vertices+10, road->getX2(), road->getY2(), 0, road->getXWidth(), road->getYWidth());
    makeVertex(vertices+15, road->getX1(), road->getY2(), 0, 0, road->getYWidth());
}

void Buffers::makeRoofVBO(float *vertices, Element *building)
{
    float h = building->getHeight();
    makeVertex(vertices, building->getX1(), building->getY1(), h, 0, 0);
    makeVertex(vertices+5, building->getX2(), building->getY1(), h, building->getXWidth(), 0);
    makeVertex(vertices+10, building->getX2(), building->getY2(), h, building->getXWidth(), building->getYWidth());
    makeVertex(vertices+15, building->getX1(), building->getY2(), h, 0, building->getYWidth());
}

void Buffers::generateRoadBuffer(List<Element*> *roadList)
{
    roadNumber = roadList->getSize();
    float *vertices = new float [20*roadNumber];
    GLuint *indices = new GLuint [6*roadNumber];
    roadList->start();
    for(int i = 0;!roadList->isAtTheEnd();i++)
    {
        makeRoadVBO(vertices+i*20, roadList->getCurrentElement());
        makeQuadIndices(indices+i*6, i*4);
        roadList->next();
    }

    glBindVertexArray(vao[0]);
    VBOGeneration(0, vertices, 20*roadNumber);
    IBOGeneration(0, indices, 6*roadNumber);
    glBindVertexArray(0);
    delete[] vertices;
    delete[] indices;
}

void Buffers::countElements(List<Block *> *b)
{
    gardenNumber = 0;
    buildingNumber = 0;
    b->start();
    while (!b->isAtTheEnd())
    {
        List<Element*> *l = b->getCurrentElement()->getElementList();
        l->start();
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
    float *gardenVertices = new float [20*gardenNumber];
    GLuint *gardenIndices = new GLuint [6*gardenNumber];
    float *buildingVertices = new float [80*buildingNumber];
    GLuint *buildingIndices = new GLuint [24*buildingNumber];
    float *roofVertices = new float [20*buildingNumber];
    GLuint *roofIndices = new GLuint [6*buildingNumber];

    int i=0; // Pour les des jardins.
    int j=0; // Pour les buildings et toits

    // Remplissage des tableaux qui formeront le contenu des VBO et IBO.
    BlockList->start();
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
                makeBuildingIndices(buildingIndices+j*24,j*16);
                // Pour le VBO des toits.
                makeRoofVBO(roofVertices+j*20, l->getCurrentElement());
                //Pour l'IBO des toits.
                makeQuadIndices(roofIndices+6*j, j*4);
                j++;
            }
            else if(l->getCurrentElement()->getType()== GARDEN)
            {
                //Pour le VBO des jardins.
                makeGardenVBO(gardenVertices+i*20, l->getCurrentElement());
                //Pour l'IBO des jardins.
                makeQuadIndices(gardenIndices+i*6, i*4);
                i++;
            }
            l->next();
        }
        BlockList->next();
    }

    glBindVertexArray(vao[1]);
    VBOGeneration(1, gardenVertices, 20*gardenNumber);
    IBOGeneration(1, gardenIndices, 6*gardenNumber);
    glBindVertexArray(vao[2]);
    VBOGeneration(2, roofVertices, 20*buildingNumber);
    IBOGeneration(2, roofIndices, 6*buildingNumber);
    glBindVertexArray(vao[3]);
    VBOGeneration(3, buildingVertices, 80*buildingNumber);
    IBOGeneration(3, buildingIndices, 24*buildingNumber);
    glBindVertexArray(0);

    delete[] gardenVertices;
    delete[] gardenIndices;
    delete[] roofVertices;
    delete[] roofIndices;
    delete[] buildingVertices;
    delete[] buildingIndices;
}

void Buffers::bindRoad()
{
    glBindVertexArray(vao[0]);
    glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo[0+NUMBER_OF_VAO]);
}

void Buffers::bindRoof()
{
    glBindVertexArray(vao[2]);
    glBindBuffer(GL_ARRAY_BUFFER, vbo[2]);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo[2+NUMBER_OF_VAO]);
}

void Buffers::bindBuilding()
{
    glBindVertexArray(vao[3]);
    glBindBuffer(GL_ARRAY_BUFFER, vbo[3]);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo[3+NUMBER_OF_VAO]);
}
void Buffers::bindGarden()
{
    glBindVertexArray(vao[1]);
    glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo[1+NUMBER_OF_VAO]);
}



