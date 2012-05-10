#include "glwidget.h"

GLWidget::GLWidget(QWidget *parent)
    : QGLWidget(QGLFormat(QGL::SampleBuffers), parent)
{
    this->format().setVersion(3,3);
    this->format().setAlpha(true);
    setFocus();
    mouseCaptured = false;

    shaders = new Shaders();
    buffers = 0;

    position.x = 10;
    position.y = 10;
    position.z = 10;
    yFOV = 60.0f;
    angleX = (float)-M_PI/2+0.1f;
    angleY = 0;
    speed = SLOW_SPEED;
    city = NULL;

    for (int i = 0; i < 4; i++)
        textures[i]=0;
    for(int i = 0; i<KEY_NUMBER; i++)
        pressedKey[i] = false;

    renderTimer = new QTimer(this);
    connect(renderTimer, SIGNAL(timeout()), this, SLOT(updateGL()));
    renderTimer->start(25);
}
GLWidget::~GLWidget()
{
    for (int i = 0; i < NUMBER_OF_BUFFER; i++)
    {
        if(textures[i] !=0)
            glDeleteTextures(1, &textures[i]);;
    }
    delete buffers;
    delete shaders;
    delete renderTimer;
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
    loadTexture("data/road_texture.png", ROAD_BUFFER);
    loadTexture("data/building_texture.png", BUILDING_BUFFER);
    loadTexture("data/roof_texture.png", ROOF_BUFFER);
    loadTexture("data/intersection_texture.png", INTERSECTION_BUFFER);
    loadTexture("data/grass.png", GARDEN_BUFFER);

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
    projectionMatrix = glm::perspective(yFOV, this->width()/(float)this->height(),0.25f, 500.0f);
    glUseProgram(shaders->getShader());
    glUniformMatrix4fv(projectionMatrixUL, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
    glUseProgram(0);
}

void GLWidget::drawObject()
{
    glUseProgram(shaders->getShader());

    glUniformMatrix4fv(viewMatrixUL, 1, GL_FALSE, glm::value_ptr(viewMatrix));
    glActiveTexture(GL_TEXTURE0);
    //Draw roads
    glBindTexture(GL_TEXTURE_2D, textures[ROAD_BUFFER]);
    buffers->bindBuffer(ROAD_BUFFER);
    glDrawElements(GL_TRIANGLES, buffers->getBufferIndicesNumber(ROAD_BUFFER), GL_UNSIGNED_INT, (GLvoid*)0);
    //Draw intersections
    glBindTexture(GL_TEXTURE_2D, textures[INTERSECTION_BUFFER]);
    buffers->bindBuffer(INTERSECTION_BUFFER);
    glDrawElements(GL_TRIANGLES, buffers->getBufferIndicesNumber(INTERSECTION_BUFFER), GL_UNSIGNED_INT, (GLvoid*)0);
    //Draw building
    glBindTexture(GL_TEXTURE_2D, textures[BUILDING_BUFFER]);
    buffers->bindBuffer(BUILDING_BUFFER);
    glDrawElements(GL_TRIANGLES, buffers->getBufferIndicesNumber(BUILDING_BUFFER), GL_UNSIGNED_INT, (GLvoid*)0);
    //Draw roof
    glBindTexture(GL_TEXTURE_2D, textures[ROOF_BUFFER]);
    buffers->bindBuffer(ROOF_BUFFER);
    glDrawElements(GL_TRIANGLES, buffers->getBufferIndicesNumber(ROOF_BUFFER), GL_UNSIGNED_INT, (GLvoid*)0);
    //Draw garden
    glBindTexture(GL_TEXTURE_2D, textures[GARDEN_BUFFER]);
    buffers->bindBuffer(GARDEN_BUFFER);
    glDrawElements(GL_TRIANGLES, buffers->getBufferIndicesNumber(GARDEN_BUFFER), GL_UNSIGNED_INT, (GLvoid*)0);

    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);
    glUseProgram(0);
}
void GLWidget::paintGL()
{
    makeCurrent();
    updateCamera();

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
void GLWidget::mousePressEvent(QMouseEvent*)
{
    setFocus();
    if(mouseCaptured)
    {
        mouseCaptured = false;
        setCursor(Qt::ArrowCursor);
    }
    else
    {
        mouseCaptured = true;
        QCursor::setPos(QWidget::mapToGlobal(QPoint(width()/2,height()/2)));
        setCursor(Qt::BlankCursor);
    }
}

void GLWidget::updateCamera()
{
    if(mouseCaptured)
    {
        QPoint pos = QCursor::pos();
        QPoint center = QWidget::mapToGlobal(QPoint(width()/2,height()/2));
        angleX -= (pos.y()-center.y())*ROTATION_SPEED;
        angleY -= (pos.x()-center.x())*ROTATION_SPEED;
        if(angleX<-M_PI/2+0.1)
            angleX = (float)-M_PI/2+0.1f;
        else if(angleX>M_PI/2-0.1)
            angleX = (float)M_PI/2-0.1f;
        float sx = sin(angleX);
        float cx = cos(angleX);
        float sy = sin(angleY);
        float cy = cos(angleY);
        glm::vec3 lookDirection = glm::vec3(cy*cx, sy*cx, sx);
        if(pressedKey[KEY_Z])
            position += speed*lookDirection;
        if(pressedKey[KEY_S])
            position -= speed*lookDirection;
        if(pressedKey[KEY_Q])
            position += speed*glm::vec3(-sy*cx, cy*cx, 0);
        if(pressedKey[KEY_D])
            position -= speed*glm::vec3(-sy*cx, cy*cx, 0);
        if(pressedKey[KEY_A])
            position += speed*glm::vec3(-cy*sx, -sy*sx, cx);
        if(pressedKey[KEY_E])
            position -= speed*glm::vec3(-cy*sx, -sy*sx, cx);

        QCursor::setPos(center);
        viewMatrix = glm::lookAt(position, position+lookDirection, glm::vec3(0,0,2));
    }
}

void GLWidget::keyPressEvent(QKeyEvent *event)
{
    switch(event->key())
    {
        case Qt::Key_Z:
            pressedKey[KEY_Z] = true;
            break;
        case Qt::Key_S :
            pressedKey[KEY_S] = true;
            break;
        case Qt::Key_Q:
            pressedKey[KEY_Q] = true;
            break;
        case Qt::Key_D :
            pressedKey[KEY_D] = true;
            break;
        case Qt::Key_A :
            pressedKey[KEY_A] = true;
            break;
        case Qt::Key_E:
            pressedKey[KEY_E] = true;
            break;
        case Qt::Key_Shift :
            speed = FAST_SPEED;
            break;
        case Qt::Key_Escape:
            mouseCaptured = false;
            setCursor(Qt::ArrowCursor);
            break;
        default:
            break;
    }
}

void GLWidget::keyReleaseEvent(QKeyEvent *event)
{
    switch(event->key())
    {
        case Qt::Key_Z:
            pressedKey[KEY_Z] = false;
            break;
        case Qt::Key_S :
            pressedKey[KEY_S] = false;
            break;
        case Qt::Key_Q:
            pressedKey[KEY_Q] = false;
            break;
        case Qt::Key_D :
            pressedKey[KEY_D] = false;
            break;
        case Qt::Key_A :
            pressedKey[KEY_A] = false;
            break;
        case Qt::Key_E:
            pressedKey[KEY_E] = false;
            break;
        case Qt::Key_Shift :
            speed = SLOW_SPEED;
            break;
        default:
            break;
    }
}


void GLWidget::loadTexture(const char *textureName, int place)
{

    if(place>=NUMBER_OF_BUFFER)
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



