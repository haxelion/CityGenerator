#include "shaders.h"
#include <QFile>

Shaders::~Shaders()
{
    vertexShader = 0;
    fragmentShader = 0;
    shader = 0;
}

Shaders::~Shaders()
{
    glDetachShader(shader, fragmentShader);
    glDetachShader(shader, vertexShader);
    glDeleteShader(fragmentShader);
    glDeleteShader(vertexShader);
    glDeleteProgram(shader);
}

void Shaders::loadShader(const char *path, GLenum shaderType)
{
    GLuint shaderID = 0;
    QFile file(path);
    file.open(QIODevice::ReadOnly);
    long fileSize = file.size();
    char *code = new char[fileSize+1];
    file.readData(code,fileSize);
    code[fileSize] = '\0';
    shaderID = glCreateShader(shaderType);
    glShaderSource(shaderID, 1, (const GLchar**)&code, NULL);
    delete code;
    glCompileShader(shaderID);
    file.close();

    if(shaderType == GL_FRAGMENT_SHADER)
    {
        if(fragmentShader != 0)
            glDeleteShader(fragmentShader);
        fragmentShader = shaderID;
    }
    else if(shaderType == GL_VERTEX_SHADER)
    {
        if(vertexShader != 0)
            glDeleteShader(vertexShader);
        vertexShader = shaderID;
    }
}

void shaders::compileShader()
{
    shader = glCreateProgram();
    glAttachShader(shader, fragmentShader);
    glAttachShader(shader, vertexShader);
    glLinkProgram(shader);
}



