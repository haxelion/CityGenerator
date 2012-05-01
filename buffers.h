#ifndef BUFFERS_H
#define BUFFERS_H
#define GLEW_STATIC
#include <GL/glew.h>
#include <list.h>
#include <element.h>
#include <block.h>

class Buffers
{
public:
    Buffers();
    ~Buffers();
    void generateRoadBuffer();
    void generateElementBuffer();
    void makeVertex(float *vertex, float x, float y, float z, float u, float v);
    void makeQuadIndices(int *indices, int i);
    void makeTriangleIndices(int *indices, int i, int j, int k);
    void VBAgeneration (GLuint VBA);
    void VBOgeneration (GLuint VBO, float* vertices);
    void IBOgeneration (GLuint IBO, float* indices);
    GLuint getRoadVBA() {return roadVBA;}
    GLuint getRoofVBA() {return roofVBA;}
    GLuint getBuildingVBA() {return buildingVBA;}
    GLuint getGardenVBA() {return gardenVBA;}

private:
    GLuint roadVBO, roadVBA, roadIBO;
    GLuint roofVBO, roofVBA, roofIBO;
    GLuint buildingVBO, buildingVBA, buildingIBO;
    GLuint gardenVBO, gardenVBA, gardenIBO;

};
#endif // BUFFERS_H
