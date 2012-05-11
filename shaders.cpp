#include "shaders.h"

Shaders::Shaders()
{
    vertexShader = 0;
    fragmentShader = 0;
    shader = 0;
}

Shaders::~Shaders()
{
    //detache les fragment et vertex shader du shader principale
    glDetachShader(shader, fragmentShader);
    glDetachShader(shader, vertexShader);
    //supprime les shaders
    glDeleteShader(fragmentShader);
    glDeleteShader(vertexShader);
    glDeleteProgram(shader);
}

void Shaders::loadShader(const char *path, GLenum shaderType)
{
    GLuint shaderID;
    //ouvre le fichier contenant le shader
    QFile file(path);
    file.open(QIODevice::ReadOnly);
    //recupere la taille du fichier et cree une chaine de caractere capable de contenir tout le code
    long fileSize = file.size();
    char *code = new char[fileSize+1];
    //lis le code en memoire
    file.read(code,fileSize);
    code[fileSize] = '\0';
    //creer un nom de shader
    shaderID = glCreateShader(shaderType);
    //envoi le code source du shader a la carte graphique
    glShaderSource(shaderID, 1, (const GLchar**)&code, NULL);
    delete code;
    //compile le code
    glCompileShader(shaderID);
    file.close();
    //memorise le nom du code compile
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

void Shaders::compileShader()
{
    //lie le vertex et le fragment shader pour creer le shader final
    shader = glCreateProgram();
    glAttachShader(shader, fragmentShader);
    glAttachShader(shader, vertexShader);
    glLinkProgram(shader);
}



