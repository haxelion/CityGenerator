#include "buffers.h"

Buffers::Buffers(City *city)
{
    glGenVertexArrays(NUMBER_OF_BUFFER, vao);
    glGenBuffers(NUMBER_OF_BUFFER*2, vbo);
    countElements(city->getBlockList(), city->getRoadList());
    generateRoadBuffers(city->getRoadList());
    generateElementBuffers(city->getBlockList());
}

Buffers::~Buffers()
{
    glDeleteVertexArrays(NUMBER_OF_BUFFER, vao);
    glDeleteBuffers(NUMBER_OF_BUFFER*2, vbo);
}

void Buffers::VBOGeneration (BufferType type, float* vertices, GLsizei size)
{
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, vbo[type]);
    glBufferData(GL_ARRAY_BUFFER, size*sizeof(float), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0,3,GL_FLOAT, GL_FALSE, 5*sizeof(float), (GLvoid*)0);
    glVertexAttribPointer(1,2,GL_FLOAT, GL_FALSE, 5*sizeof(float), (GLvoid*)(3*sizeof(float)));
}

void Buffers::IBOGeneration(BufferType type, GLuint* indices, GLsizei size)
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo[type+NUMBER_OF_BUFFER]);
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
    if(road->getType() == X_ROAD)
    {
        makeVertex(vertices, road->getX1(), road->getY1(), 0, 0, 0);
        makeVertex(vertices+5, road->getX2(), road->getY1(), 0, 0, road->getXWidth());
        makeVertex(vertices+10, road->getX2(), road->getY2(), 0, road->getYWidth(), road->getXWidth());
        makeVertex(vertices+15, road->getX1(), road->getY2(), 0, road->getYWidth(), 0);
    }
    else if(road->getType() == Y_ROAD)
    {
        makeVertex(vertices, road->getX1(), road->getY1(), 0, 0, 0);
        makeVertex(vertices+5, road->getX2(), road->getY1(), 0, road->getXWidth(), 0);
        makeVertex(vertices+10, road->getX2(), road->getY2(), 0, road->getXWidth(), road->getYWidth());
        makeVertex(vertices+15, road->getX1(), road->getY2(), 0, 0, road->getYWidth());
    }
}

void Buffers::makeIntersectionVBO(float *vertices, Element *intersection)
{
    makeVertex(vertices, intersection->getX1(), intersection->getY1(), 0, 0, 0);
    makeVertex(vertices+5, intersection->getX2(), intersection->getY1(), 0, 1, 0);
    makeVertex(vertices+10, intersection->getX2(), intersection->getY2(), 0, 1, 1);
    makeVertex(vertices+15, intersection->getX1(), intersection->getY2(), 0, 0, 1);
}

void Buffers::makeRoofVBO(float *vertices, Element *building)
{
    float h = building->getHeight();
    makeVertex(vertices, building->getX1(), building->getY1(), h, 0, 0);
    makeVertex(vertices+5, building->getX2(), building->getY1(), h, building->getXWidth(), 0);
    makeVertex(vertices+10, building->getX2(), building->getY2(), h, building->getXWidth(), building->getYWidth());
    makeVertex(vertices+15, building->getX1(), building->getY2(), h, 0, building->getYWidth());
}

void Buffers::generateRoadBuffers(List<Element*> *r)
{
    float *roadVertices = new float [verticesNumber[ROAD_BUFFER]];
    GLuint *roadIndices = new GLuint [indicesNumber[ROAD_BUFFER]];
    float *intersectionVertices = new float [verticesNumber[INTERSECTION_BUFFER]];
    GLuint *intersectionIndices = new GLuint [indicesNumber[INTERSECTION_BUFFER]];
    int i = 0;
    int j = 0;
    r->start();
    while(!r->isAtTheEnd())
    {
        if(r->getCurrentElement()->getType() == X_ROAD || r->getCurrentElement()->getType() == Y_ROAD)
        {
            makeRoadVBO(roadVertices+i*20, r->getCurrentElement());
            makeQuadIndices(roadIndices+i*6, i*4);
            i++;
        }
        else if(r->getCurrentElement()->getType() == INTERSECTION)
        {
            makeIntersectionVBO(intersectionVertices+j*20, r->getCurrentElement());
            makeQuadIndices(intersectionIndices+j*6, j*4);
            j++;
        }
        r->next();
    }

    glBindVertexArray(vao[ROAD_BUFFER]);
    VBOGeneration(ROAD_BUFFER, roadVertices, verticesNumber[ROAD_BUFFER]);
    IBOGeneration(ROAD_BUFFER, roadIndices, indicesNumber[ROAD_BUFFER]);
    glBindVertexArray(vao[INTERSECTION_BUFFER]);
    VBOGeneration(INTERSECTION_BUFFER, intersectionVertices, verticesNumber[INTERSECTION_BUFFER]);
    IBOGeneration(INTERSECTION_BUFFER, intersectionIndices, indicesNumber[INTERSECTION_BUFFER]);
    glBindVertexArray(0);
    delete[] roadVertices;
    delete[] roadIndices;
    delete[] intersectionVertices;
    delete[] intersectionIndices;
}

void Buffers::countElements(List<Block *> *b, List<Element*> *r)
{
    int gardenNumber = 0;
    int buildingNumber = 0;
    int roadNumber = 0;
    int intersectionNumber = 0;
    r->start();
    while(!r->isAtTheEnd())
    {
        if(r->getCurrentElement()->getType() == X_ROAD || r->getCurrentElement()->getType() == Y_ROAD)
            roadNumber++;
        else if(r->getCurrentElement()->getType() == INTERSECTION)
            intersectionNumber++;
        r->next();
    }
    b->start();
    while (!b->isAtTheEnd())
    {
        List<Element*> *l = b->getCurrentElement()->getElementList();
        l->start();
        while(!l->isAtTheEnd())
        {
            if(l->getCurrentElement()->getType() == BUILDING)
                buildingNumber++;
            else if(l->getCurrentElement()->getType()== GARDEN)
                gardenNumber++;
            l->next();
        }
        b->next();
    }
    verticesNumber[GARDEN_BUFFER] = 20*gardenNumber;
    indicesNumber[GARDEN_BUFFER] = 6*gardenNumber;
    verticesNumber[BUILDING_BUFFER] = 80*buildingNumber;
    indicesNumber[BUILDING_BUFFER] = 24*buildingNumber;
    verticesNumber[ROOF_BUFFER] = 20*buildingNumber;
    indicesNumber[ROOF_BUFFER] = 6*buildingNumber;
    verticesNumber[ROAD_BUFFER] = 20*roadNumber;
    indicesNumber[ROAD_BUFFER] = 6*roadNumber;
    verticesNumber[INTERSECTION_BUFFER] = 20*intersectionNumber;
    indicesNumber[INTERSECTION_BUFFER] = 6*intersectionNumber;
}

void Buffers::generateElementBuffers(List<Block*> *BlockList)
{
    float *gardenVertices = new float [verticesNumber[GARDEN_BUFFER]];
    GLuint *gardenIndices = new GLuint [indicesNumber[GARDEN_BUFFER]];
    float *buildingVertices = new float [verticesNumber[BUILDING_BUFFER]];
    GLuint *buildingIndices = new GLuint [indicesNumber[BUILDING_BUFFER]];
    float *roofVertices = new float [verticesNumber[ROOF_BUFFER]];
    GLuint *roofIndices = new GLuint [indicesNumber[ROOF_BUFFER]];

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

    glBindVertexArray(vao[GARDEN_BUFFER]);
    VBOGeneration(GARDEN_BUFFER, gardenVertices, verticesNumber[GARDEN_BUFFER]);
    IBOGeneration(GARDEN_BUFFER, gardenIndices, indicesNumber[GARDEN_BUFFER]);
    glBindVertexArray(vao[ROOF_BUFFER]);
    VBOGeneration(ROOF_BUFFER, roofVertices, verticesNumber[ROOF_BUFFER]);
    IBOGeneration(ROOF_BUFFER, roofIndices, indicesNumber[ROOF_BUFFER]);
    glBindVertexArray(vao[BUILDING_BUFFER]);
    VBOGeneration(BUILDING_BUFFER, buildingVertices, verticesNumber[BUILDING_BUFFER]);
    IBOGeneration(BUILDING_BUFFER, buildingIndices, indicesNumber[BUILDING_BUFFER]);
    glBindVertexArray(0);

    delete[] gardenVertices;
    delete[] gardenIndices;
    delete[] roofVertices;
    delete[] roofIndices;
    delete[] buildingVertices;
    delete[] buildingIndices;
}

void Buffers::bindBuffer(BufferType type)
{
    glBindVertexArray(vao[type]);
    glBindBuffer(GL_ARRAY_BUFFER, vbo[type]);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo[type+NUMBER_OF_BUFFER]);
}

