#ifndef SHADERS_H
#define SHADERS_H
#define GLEW_STATIC
#include <GL/glew.h>
#include <QFile>


class Shaders
{
public:
    Shaders();
    ~Shaders();
    void loadShader(const char *path, GLenum shaderType);
    void compileShader();
    GLuint getShader() {return shader;}


private :
    GLuint shader, vertexShader, fragmentShader;
};

#endif // SHADERS_H
