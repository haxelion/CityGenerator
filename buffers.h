#ifndef BUFFERS_H
#define BUFFERS_H
#define GLEW_STATIC
#include "GL/glew.h"
#include "list.h"
#include "element.h"
#include "block.h"
#include "city.h"

class Buffers
{
public:
    Buffers(City *city);
    ~Buffers();
    GLuint getRoadVBA() {return roadVBA;}
    GLuint getRoofVBA() {return roofVBA;}
    GLuint getBuildingVBA() {return buildingVBA;}
    GLuint getGardenVBA() {return gardenVBA;}
    GLuint getRoadTrianglesNumber(){return roadNumber*2;}
    GLsizei getRoofTrianglesNumber(){return buildingNumber*2;}
    GLsizei getBuildingTrianglesNumber(){return buildingNumber*8;}
    GLsizei getGardenTrianglesNumber(){return gardenNumber*2;}


private:
    GLuint roadVBO, roadVBA, roadIBO;
    GLuint roofVBO, roofVBA, roofIBO;
    GLuint buildingVBO, buildingVBA, buildingIBO;
    GLuint gardenVBO, gardenVBA, gardenIBO;
    int roadNumber;
    int gardenNumber;
    int buildingNumber;

    void generateRoadBuffer(List<Element*> *roadList);
    void generateElementBuffer(List<Block*> *BlockList);
    void countElements(List<Block*> *b);
    void makeBuildingVBO(float *vertices, Element *building);
    void makeGardenVBO(float *vertices, Element *garden);
    void makeRoadVBO(float *vertices, Element *road);
    void makeRoofVBO(float *vertices, Element *building);
    void VBAGeneration (GLuint *VBA);
    void VBOGeneration (GLuint *VBO, float* vertices);
    void IBOGeneration(GLuint *IBO, int* indices);
    void makeVertex(float *vertex, float x, float y, float z, float u, float v)
    {
        vertex[0] = x;
        vertex[1] = y;
        vertex[2] = z;
        vertex[3] = u;
        vertex[4] = v;
    }

    void makeQuadIndices(int *indices, int i)
    {
        indices[0]= i;
        indices[1]= i+1;
        indices[2]= i+2;
        indices[3]= i;
        indices[4]= i+2;
        indices[5]= i+3;
    }
    void makeBuildingIndices(int *indices, int i)
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
};
#endif // BUFFERS_H
