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
    GLuint getRoadVBA() {return roadVBA;}
    GLuint getRoofVBA() {return roofVBA;}
    GLuint getBuildingVBA() {return buildingVBA;}
    GLuint getGardenVBA() {return gardenVBA;}

private:
    GLuint roadVBO, roadVBA, roadIBO;
    GLuint roofVBO, roofVBA, roofIBO;
    GLuint buildingVBO, buildingVBA, buildingIBO;
    GLuint gardenVBO, gardenVBA, gardenIBO;

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
};
#endif // BUFFERS_H
