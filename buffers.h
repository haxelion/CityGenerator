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
    void bindRoad();
    void bindRoof();
    void bindBuilding();
    void bindGarden();
    GLuint getRoadTrianglesNumber(){return roadNumber*2;}
    GLsizei getRoofTrianglesNumber(){return buildingNumber*2;}
    GLsizei getBuildingTrianglesNumber(){return buildingNumber*8;}
    GLsizei getGardenTrianglesNumber(){return gardenNumber*2;}


private:
    static const int NUMBER_OF_VAO = 4;
    GLuint vao[NUMBER_OF_VAO];
    GLuint vbo[NUMBER_OF_VAO*2];
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
    void VBOGeneration(int n, float* vertices, GLsizei size);
    void IBOGeneration(int n, GLuint* indices, GLsizei size);
    void makeVertex(float *vertex, float x, float y, float z, float u, float v);
    void makeQuadIndices(GLuint *indices, int i);
    void makeBuildingIndices(GLuint *indices, int i);
};
#endif // BUFFERS_H
