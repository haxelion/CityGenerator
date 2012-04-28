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
    void generateRoadBuffer();
    void generateElementBuffer();
    GLuint getRoadVBA() {return roadVBA;}
    GLuint getRoofVBA() {return roofVBA;}
    GLuint getBuildingVBA() {return buildingVBA;}
    GLuint getGardenVBA() {return gardenVBA;}

private:
    GLuint roadVBO, roadVBA, roadIBO;
    GLuint roofVBO, roofVBA, roofIBO;
    GLuint buildingVBO, buildingVBA, buidlingIBO;
    GLuint gardenVBO, gardenVBA, gardenIBO;
};

#endif // BUFFERS_H
