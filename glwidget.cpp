#include "glwidget.h"

GLWidget::GLWidget(QWidget *parent)
    : QGLWidget(QGLFormat(QGL::SampleBuffers), parent)
{
    this->format().setVersion(3,3);
    this->format().setAlpha(true);
    setFocus();

    shaders = new Shaders();
    buffers = 0;

    yFOV = 60.0f;
    angleX = 0;
    angleY = 0;
    positionX = -10;
    positionY = -10;
    positionZ = -20;
    city = NULL;
    for (int i = 0; i < 4; i++)
        textures[i]=0;
}
GLWidget::~GLWidget()
{
    for (int i = 0; i < TEXTURE_NUMBER; i++)
    {
        if(textures[i] !=0)
            glDeleteTextures(1, &textures[i]);;
    }
    delete buffers;
    delete shaders;
}

QSize GLWidget::minimumSizeHint() const
{
    return QSize(50, 50);
}
QSize GLWidget::sizeHint() const
{
    return QSize(400, 400);
}

//Initialisation des paramètres OpenGL
void GLWidget::initializeGL()
{
    makeCurrent();
    glewInit();
    //Definition de la couleur du fond
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    // Augmentation de la qualité du calcul de perspective
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
    glHint(GL_GENERATE_MIPMAP_HINT, GL_NICEST);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glFrontFace(GL_CCW);

    shaders->loadShader("data/fragment_basic.glsl", GL_FRAGMENT_SHADER);
    shaders->loadShader("data/vertex_basic.glsl", GL_VERTEX_SHADER);
    shaders->compileShader();

    projectionMatrixUL = glGetUniformLocation(shaders->getShader(), "projectionMatrix");
    viewMatrixUL = glGetUniformLocation(shaders->getShader(), "viewMatrix");
    samplerUL = glGetUniformLocation(shaders->getShader(), "textureSampler");
    glUseProgram(shaders->getShader());
    glUniform1i(samplerUL, 0);
    glUseProgram(0);
    loadTexture("data/road_texture.png", 0);
    loadTexture("data/building_texture.png", 1);
    loadTexture("data/roof_texture.png", 2);

    setView();
}

void GLWidget::setCity(City *city)
{
    if(city != 0)
    {
        if(buffers !=0)
            delete buffers;
        buffers = new Buffers(city);
    }
    this->city = city;
    updateGL();
}

void GLWidget::setView()
{
    glViewport(0,0,this->width(), this->height());
    projectionMatrix = glm::perspective(yFOV, this->width()/(float)this->height(),1.0f, 1000.0f);
    glUseProgram(shaders->getShader());
    glUniformMatrix4fv(projectionMatrixUL, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
    glUseProgram(0);
}

void GLWidget::drawObject()
{
    glUseProgram(shaders->getShader());
    viewMatrix = glm::translate(glm::mat4(),glm::vec3(positionX,positionY,positionZ));
    viewMatrix = glm::rotate(viewMatrix,angleX,glm::vec3(1.0,0,0));
    viewMatrix = glm::rotate(viewMatrix,angleY,glm::vec3(0,1.0,0));

    glUniformMatrix4fv(viewMatrixUL, 1, GL_FALSE, glm::value_ptr(viewMatrix));
    glActiveTexture(GL_TEXTURE0);
    //Draw roads
    glBindTexture(GL_TEXTURE_2D, textures[0]);
    buffers->bindRoad();
    glDrawElements(GL_TRIANGLES, buffers->getRoadTrianglesNumber()*3, GL_UNSIGNED_INT, (GLvoid*)0);
    //Draw Building
    glBindTexture(GL_TEXTURE_2D, textures[1]);
    buffers->bindBuilding();
    glDrawElements(GL_TRIANGLES, buffers->getBuildingTrianglesNumber()*3, GL_UNSIGNED_INT, (GLvoid*)0);
    //Draw roof
    glBindTexture(GL_TEXTURE_2D, textures[2]);
    buffers->bindRoof();
    glDrawElements(GL_TRIANGLES, buffers->getRoofTrianglesNumber()*3, GL_UNSIGNED_INT, (GLvoid*)0);

    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);
    glUseProgram(0);
}
void GLWidget::paintGL()
{
    makeCurrent();

    //Vide les differents buffers
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

    //Dessine les objects dans la scene
    if(city!=NULL)
        drawObject();

}
void GLWidget::resizeGL(int, int)
{
    setView();
}


//Gestion de la souris
void GLWidget::mousePressEvent(QMouseEvent *event)
{
    setFocus();
    lastPos = event->pos();
    updateGL();
}
void GLWidget::mouseMoveEvent(QMouseEvent *event)
{
    int dx = event->x() - lastPos.x();
    int dy = event->y() - lastPos.y();
    int constant = 8;
    angleY += constant*dx;
    angleX += constant*dy;
    lastPos = event->pos();
}

void GLWidget::keyPressEvent(QKeyEvent *event)
{
    float constant = 1;
    float rayon = sqrt(positionX*positionX+positionY*positionY+positionZ*positionZ);
    switch(event->key())
    {
    case Qt::Key_Down:
         rayon-=constant;
         positionX= rayon*cos(angleX)*cos(angleY);
         positionY= rayon*sin(angleX);
         positionZ= rayon*cos(angleX)*sin(angleY);
        break;
    case Qt::Key_Up :
         rayon+=constant;
         positionX= rayon*cos(angleX)*cos(angleY);
         positionY= rayon*sin(angleX);
         positionZ= rayon*cos(angleX)*sin(angleY);
        break;
    case Qt::Key_Left:
        positionZ += constant*sin(angleY);
        positionX += constant*cos(angleY);
        break;
    case Qt::Key_Right :
        positionZ -= constant*sin(angleY);
        positionX -= constant*cos(angleY);
        break;

    case Qt::Key_PageDown :
         positionY-= constant;
        break;

    case Qt::Key_PageUp:
         positionY+= constant;
        break;

    default:
        break;
    }
    update();
}


void GLWidget::wheelEvent(QWheelEvent *event)
{
    /*float notch = event->delta()/ 120.0f;

    switch(event->modifiers())
    {
    case Qt::ShiftModifier :
        mFov = max(mFov * powf(1.2f, notch), 10.0f);
        mFov = min(mFov, 90.0f);
        setView();
        break;
    default:
        mScale *= pow(1.2f, -notch);
        break;
    }
    update();*/
}

//Gestion du clavier
//void GLWidget::keyPressEvent(QKeyEvent *event)
//{
    /*switch(event->key())
    {
    case Qt::Key_Down:
        mYTranslate -= 0.5;
        break;
    case Qt::Key_Up :
        mYTranslate += 0.5;
        break;
    case Qt::Key_Left:
        mXTranslate -= 0.5;
        break;
    case Qt::Key_Right :
        mXTranslate += 0.5;
        break;
    case Qt::Key_PageDown :
        mZTranslate -= 0.5;
        break;
    case Qt::Key_PageUp:
        mZTranslate += 0.5;
        break;
    default:
        break;
    }
    update();*/
//}

void GLWidget::setXRotation(int angle)
{
    /*qNormalizeAngle(angle);
    if (angle != mXRotate) {
        mXRotate = angle;
        emit xRotationChanged(angle);
        updateGL();
    }*/
}
void GLWidget::setYRotation(int angle)
{
    /*qNormalizeAngle(angle);
    if (angle != mYRotate) {
        mYRotate = angle;
        emit yRotationChanged(angle);
        updateGL();
    }*/
}
void GLWidget::setZRotation(int angle)
{
    /*qNormalizeAngle(angle);
    if (angle != mZRotate) {
        mZRotate = angle;
        emit zRotationChanged(angle);
        updateGL();
    }*/
}

void GLWidget::loadTexture(const char *textureName, int place)
{

    if(place>=TEXTURE_NUMBER)
        return;
    if (textures[place]==0)
        glDeleteTextures(1, &textures[place]);
    QImage textureImage;
    QImage tempTextureImage;
    tempTextureImage.load(textureName);
    textureImage = QGLWidget::convertToGLFormat(tempTextureImage);
    glGenTextures( 1, &textures[place] );
    glBindTexture( GL_TEXTURE_2D, textures[place] );
    glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, textureImage.width(), textureImage.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, textureImage.bits() );
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR );
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_BASE_LEVEL, 0);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, 1000);
    glGenerateMipmap(GL_TEXTURE_2D);
}



