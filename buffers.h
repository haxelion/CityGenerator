#ifndef BUFFERS_H
#define BUFFERS_H
#define GLEW_STATIC
#include "GL/glew.h"
#include "list.h"
#include "element.h"
#include "block.h"
#include "city.h"

enum BufferType {ROAD_BUFFER, INTERSECTION_BUFFER, GARDEN_BUFFER, BUILDING_BUFFER, ROOF_BUFFER};
const int NUMBER_OF_BUFFER = 5;

class Buffers
{
public:
    Buffers(City *city);
    ~Buffers();
    void bindBuffer(BufferType type);
    GLsizei getBufferIndicesNumber(BufferType type){return indicesNumber[type];}


private:
    GLuint vao[NUMBER_OF_BUFFER];
    GLuint vbo[NUMBER_OF_BUFFER*2];
    GLsizei verticesNumber[NUMBER_OF_BUFFER];
    GLsizei indicesNumber[NUMBER_OF_BUFFER];

    void generateRoadBuffers(List<Element*> *r);
    void generateElementBuffers(List<Block*> *BlockList);
    void countElements(List<Block*> *b, List<Element *> *r);
    void makeBuildingVBO(float *vertices, Element *building);
    void makeGardenVBO(float *vertices, Element *garden);
    void makeRoadVBO(float *vertices, Element *road);
    void makeRoofVBO(float *vertices, Element *building);
    void makeIntersectionVBO(float *vertices, Element *intersection);
    void VBOGeneration(BufferType type, float* vertices, GLsizei size);
    void IBOGeneration(BufferType type, GLuint* indices, GLsizei size);
    void makeVertex(float *vertex, float x, float y, float z, float u, float v);
    void makeQuadIndices(GLuint *indices, int i);
    void makeBuildingIndices(GLuint *indices, int i);
};
#endif // BUFFERS_H
