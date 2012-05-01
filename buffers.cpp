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

void Buffers::makeVertex(float *vertex, float x, float y, float z, float u, float v)
{
    vertex[0] = x;
    vertex[1] = y;
    vertex[2] = z;
    vertex[3] = u;
    vertex[4] = v;
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

void Buffers::makeTriangleIndices(int *indices, int i, int j, int k)
{
    indices[0]= i;
    indices[1]= j;
    indices[2]= k;
}

void Buffers::VBAGeneration (GLuint VBA)
{
    glGenVertexArrays(1, &VBA);
    glBindVertexArray(VBA);
}

void Buffers::VBOGeneration (GLuint VBO, float* vertices)
{
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0,4,GL_FLOAT, GL_FALSE,6*sizeof(float) , (GLvoid*)0);
    glVertexAttribPointer(1,4,GL_FLOAT, GL_FALSE, 6*sizeof(float), (GLvoid*)(3*sizeof(float)));
}

void Buffers::IBOGeneration(GLuint IBO, float* indices)
{
    glGenBuffers(1, &IBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    glBindVertexArray(0);
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
    VBAgeneration(roadVBA);
    VBOgeneration(roadVBO, vertex);
    IBOgeneration(roadIBO, indice);
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

    int i=0; // Pour les des jardins.
    int j=0; // Pour les buildings et toits

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
                float h = l->getCurrentElement()->getHeight();
                makeVertex(vertexBuilding+(j*4)*5, l->getCurrentElement()->getX1(), l->getCurrentElement()->getY1(), 0, 0, 0);
                makeVertex(vertexBuilding+(j*4+1)*5, l->getCurrentElement()->getX1(), l->getCurrentElement()->getY2(), 0, 0, 1);
                makeVertex(vertexBuilding+(j*4+2)*5, l->getCurrentElement()->getX2(), l->getCurrentElement()->getY2(), h, 1, 1);
                makeVertex(vertexBuilding+(j*4+3)*5, l->getCurrentElement()->getX1(), l->getCurrentElement()->getY1(), h, 1, 0);
                // Face 2.
                makeVertex(vertexBuilding+(j*4+4)*5, l->getCurrentElement()->getX1(), l->getCurrentElement()->getY2(), 0, 0, 0);
                makeVertex(vertexBuilding+(j*4+5)*5, l->getCurrentElement()->getX2(), l->getCurrentElement()->getY2(), 0, 0, 1);
                makeVertex(vertexBuilding+(j*4+6)*5, l->getCurrentElement()->getX2(), l->getCurrentElement()->getY2(), h, 1, 1);
                makeVertex(vertexBuilding+(j*4+7)*5, l->getCurrentElement()->getX1(), l->getCurrentElement()->getY2(), h, 1, 0);
                // Face 3.
                makeVertex(vertexBuilding+(j*4+8)*5, l->getCurrentElement()->getX2(), l->getCurrentElement()->getY2(), 0, 0, 0);
                makeVertex(vertexBuilding+(j*4+9)*5, l->getCurrentElement()->getX2(), l->getCurrentElement()->getY1(), 0, 0, 1);
                makeVertex(vertexBuilding+(j*4+10)*5, l->getCurrentElement()->getX2(), l->getCurrentElement()->getY1(), h, 1, 1);
                makeVertex(vertexBuilding+(j*4+11)*5, l->getCurrentElement()->getX2(), l->getCurrentElement()->getY2(), h, 1, 0);
                //Face 4
                makeVertex(vertexBuilding+(j*4+12)*5, l->getCurrentElement()->getX2(), l->getCurrentElement()->getY1(), 0, 0, 0);
                makeVertex(vertexBuilding+(j*4+13)*5, l->getCurrentElement()->getX1(), l->getCurrentElement()->getY1(), 0, 0, 1);
                makeVertex(vertexBuilding+(j*4+14)*5, l->getCurrentElement()->getX1(), l->getCurrentElement()->getY1(), h, 1, 1);
                makeVertex(vertexBuilding+(j*4+15)*5, l->getCurrentElement()->getX2(), l->getCurrentElement()->getY1(), h, 1, 0);
                //Pour l'IBO des buildings.
                makeTriangleIndices(indiceBuilding+(j*8*3,j,j+5,j+4);
                makeTriangleIndices(indiceBuilding+((j*8)+1)*3,j,j+1,j+5);
                makeTriangleIndices(indiceBuilding+((j*8)+2)*3,j+1,j+6,j+5);
                makeTriangleIndices(indiceBuilding+((j*8)+3)*3,j+1,j+2,j+6);
                makeTriangleIndices(indiceBuilding+((j*8)+4)*3,j+2,j+7,j+6);
                makeTriangleIndices(indiceBuilding+((j*8)+5)*3,j+2,j+3,j+7);
                makeTriangleIndices(indiceBuilding+((j*8)+6)*3,j+3,j+4,j+7);
                makeTriangleIndices(indiceBuilding+((j*8)+7)*3,j+3,j,j+4);
                // Pour le VBO des toits.
                makeVertex(vertexRoof+(j*4)*5, l->getCurrentElement()->getX1(), l->getCurrentElement()->getY1(), l->getCurrentElement()->getHeight(), 0, 0);
                makeVertex(vertexRoof+(j*4+1)*5, l->getCurrentElement()->getX1(), l->getCurrentElement()->getY2(), l->getCurrentElement()->getHeight(), 0, 1);
                makeVertex(vertexRoof+(j*4+2)*5, l->getCurrentElement()->getX2(), l->getCurrentElement()->getY2(), l->getCurrentElement()->getHeight(), 1, 1);
                makeVertex(vertexRoof+(j*4+3)*5, l->getCurrentElement()->getX2(), l->getCurrentElement()->getY1(), l->getCurrentElement()->getHeight(), 1, 0);
                //Pour l'IBO des toits.
                makeQuadIndices(indiceRoof+6*j);

                j++;
            }
            else if(l->getCurrentElement()->getType()== GARDEN)
            {
                // Pour le VBO des jardins.                
                makeVertex(vertexGarden+(i*4)*5, l->getCurrentElement()->getX1(), l->getCurrentElement()->getY1(), 0, 0, 0);
                makeVertex(vertexGarden+(i*4+1)*5, l->getCurrentElement()->getX1(), l->getCurrentElement()->getY2(), 0, 0, 1);
                makeVertex(vertexGarden+(i*4+2)*5, l->getCurrentElement()->getX2(), l->getCurrentElement()->getY2(), 0, 1, 1);
                makeVertex(vertexGarden+(i*4+3)*5, l->getCurrentElement()->getX2(), l->getCurrentElement()->getY1(), 0, 1, 0);
                //Pour l'IBO des jardins.
                makeQuadIndices(indiceGarden+m*6);

                i++;
                m++;
            }
            l->next();
        }
        BlockList->next();
    }

    // Generation  des VBA
    VBAgeneration(gardenVBA);
    VBAgeneration(roofVBA);
    VBAgeneration(buildingVBA);
    //Generation  des VBO
    VBOgeneration(gardenVBO, vertexGarden);
    VBOgeneration(roofVBO, vertexRoof);
    VBOgeneration(buildingVBO, vertexBuilding);
    //Generation des IBO
    IBOgeneration(gardenIBO, indiceGarden);
    IBOgeneration(roofIBO, indiceRoof);
    IBOgeneration(buildingIBO, indiceBuilding);
}




