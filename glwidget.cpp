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
    sunAngle = 0;
    speed = SLOW_SPEED;
    reflectionIntensity = 32;
    ambientColor = glm::vec3(0.2f,0.2f,0.2f);
    sunColor = glm::vec3(1.0f,1.0f,1.0f);
    city = NULL;

    for (int i = 0; i < 4; i++)
        textures[i]=0;
    for(int i = 0; i<KEY_NUMBER; i++)
        pressedKey[i] = false;

    //creation d'un timer qui va appeler la fonction de rendu 40 fois par seconde
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
    //initialisation de glew, recuperation des pointeurs vers les fonctions opengl
    glewInit();
    //Definition de la couleur du fond
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    //Augmentation de la qualite de l'effet de perspective
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
    //Augmentation de la qualite des mipmap
    glHint(GL_GENERATE_MIPMAP_HINT, GL_NICEST);
    //specification de la fonction de test de profondeur
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    //specification du culling
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glFrontFace(GL_CCW);
    //chargement et compilation des shaders
    shaders->loadShader("data/fragment_lightning.glsl", GL_FRAGMENT_SHADER);
    shaders->loadShader("data/vertex_lightning.glsl", GL_VERTEX_SHADER);
    shaders->compileShader();
    //recuperation des locations des variables uniformes des shaders
    projectionMatrixUL = glGetUniformLocation(shaders->getShader(), "projectionMatrix");
    viewMatrixUL = glGetUniformLocation(shaders->getShader(), "viewMatrix");
    normalMatrixUL = glGetUniformLocation(shaders->getShader(), "normalMatrix");
    sunDirectionUL = glGetUniformLocation(shaders->getShader(), "sunDirection");
    sunColorUL = glGetUniformLocation(shaders->getShader(), "sunColor");
    ambientColorUL = glGetUniformLocation(shaders->getShader(), "ambientColor");
    reflectionIntensityUL = glGetUniformLocation(shaders->getShader(), "reflectionIntensity");
    samplerUL = glGetUniformLocation(shaders->getShader(), "textureSampler");
    //specification de l'unite de texture à utiliser par le fragment shader
    glUseProgram(shaders->getShader());
    glUniform1i(samplerUL, 0);
    glUseProgram(0);
    //chargement des textures en memoire
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
    //modification de la taille de la zone de rendu
    glViewport(0,0,this->width(), this->height());
    //modification de la matrice de projection et envoi de celle-ci au shader
    projectionMatrix = glm::perspective(yFOV, this->width()/(float)this->height(),0.25f, 500.0f);
    glUseProgram(shaders->getShader());
    glUniformMatrix4fv(projectionMatrixUL, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
    glUseProgram(0);
}

void GLWidget::drawObject()
{
    glUseProgram(shaders->getShader());
    //envoi au shader des variables uniformes
    glUniformMatrix4fv(viewMatrixUL, 1, GL_FALSE, glm::value_ptr(viewMatrix));
    glUniformMatrix3fv(normalMatrixUL, 1, GL_FALSE, glm::value_ptr(normalMatrix));
    glUniform3fv(sunDirectionUL, 1, glm::value_ptr(sunDirection));
    glUniform3fv(sunColorUL, 1, glm::value_ptr(sunColor));
    glUniform3fv(ambientColorUL, 1, glm::value_ptr(ambientColor));
    glUniform1iv(reflectionIntensityUL, 1, &reflectionIntensity);

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    //selection de l'unite de texture 0
    glActiveTexture(GL_TEXTURE0);
    //Rendu des routes
    glBindTexture(GL_TEXTURE_2D, textures[ROAD_BUFFER]);
    buffers->bindBuffer(ROAD_BUFFER);
    glDrawElements(GL_TRIANGLES, buffers->getBufferIndicesNumber(ROAD_BUFFER), GL_UNSIGNED_INT, (GLvoid*)0);
    //Rendu des intersections
    glBindTexture(GL_TEXTURE_2D, textures[INTERSECTION_BUFFER]);
    buffers->bindBuffer(INTERSECTION_BUFFER);
    glDrawElements(GL_TRIANGLES, buffers->getBufferIndicesNumber(INTERSECTION_BUFFER), GL_UNSIGNED_INT, (GLvoid*)0);
    //Rendu des buildings
    glBindTexture(GL_TEXTURE_2D, textures[BUILDING_BUFFER]);
    buffers->bindBuffer(BUILDING_BUFFER);
    glDrawElements(GL_TRIANGLES, buffers->getBufferIndicesNumber(BUILDING_BUFFER), GL_UNSIGNED_INT, (GLvoid*)0);
    //Rendu des toits
    glBindTexture(GL_TEXTURE_2D, textures[ROOF_BUFFER]);
    buffers->bindBuffer(ROOF_BUFFER);
    glDrawElements(GL_TRIANGLES, buffers->getBufferIndicesNumber(ROOF_BUFFER), GL_UNSIGNED_INT, (GLvoid*)0);
    //Rendu des jardins
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

    //Dessine les objects dans la scene seulement si une ville generee est presente
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
    //si le glwidget est clique, on capture ou decapture la souris
    if(mouseCaptured)
    {

        mouseCaptured = false;
        //rend le curseur visible
        setCursor(Qt::ArrowCursor);
    }
    else
    {
        mouseCaptured = true;
        //place le curseur au milieu
        QCursor::setPos(QWidget::mapToGlobal(QPoint(width()/2,height()/2)));
        //rend le curseur invisible
        setCursor(Qt::BlankCursor);
    }
}

void GLWidget::updateCamera()
{
    if(mouseCaptured)
    {
        //on recupere la position actuelle du curseur et celle du centre du glwidget
        QPoint pos = QCursor::pos();
        QPoint center = QWidget::mapToGlobal(QPoint(width()/2,height()/2));
        //on augmente les angles de vue en fonction du deplacement de la souris
        angleX -= (pos.y()-center.y())*ROTATION_SPEED;
        angleY -= (pos.x()-center.x())*ROTATION_SPEED;
        //on empeche l'angle verticale de depasser pi/2 ou -pi/2
        if(angleX<-M_PI/2+0.1)
            angleX = (float)-M_PI/2+0.1f;
        else if(angleX>M_PI/2-0.1)
            angleX = (float)M_PI/2-0.1f;
        //precalcul des sinus et cosinus
        float sx = sin(angleX);
        float cx = cos(angleX);
        float sy = sin(angleY);
        float cy = cos(angleY);
        //definition du vecteur du regard
        glm::vec3 lookDirection = glm::vec3(cy*cx, sy*cx, sx);
        //deplacement en fonction des touches appuyees
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
        //remise du curseur au centre
        QCursor::setPos(center);
        //calcul des matrices de transformation
        viewMatrix = glm::lookAt(position, position+lookDirection, glm::vec3(0,0,2));
        normalMatrix = glm::mat3(viewMatrix);
    }
    //rotation du soleil et calcul de sa direction dans les coordonnees de la camera
    sunAngle+= 0.01;
    sunDirection = glm::normalize(normalMatrix*glm::vec3(sin(sunAngle),cos(sunAngle),1.0f));
}

void GLWidget::keyPressEvent(QKeyEvent *event)
{
    //enregistrement des touches pressees
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
    //enregistrement des touches relachees
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
    //evite un depassement d'indice
    if(place>=NUMBER_OF_BUFFER)
        return;
    //supprime la texture si elle existe deja
    if (textures[place]==0)
        glDeleteTextures(1, &textures[place]);
    //chargement de la texture et conversion en format opengl
    QImage textureImage;
    QImage tempTextureImage;
    tempTextureImage.load(textureName);
    textureImage = QGLWidget::convertToGLFormat(tempTextureImage);
    //generation d'un nom de texture
    glGenTextures( 1, &textures[place] );
    //generation d'une texture 2D
    glBindTexture( GL_TEXTURE_2D, textures[place] );
    //chargement de la texture en memoire
    glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, textureImage.width(), textureImage.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, textureImage.bits() );
    //activation de la repetition de la texture sur les bords
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    //selection des filtres de mise à l'echelle de la texture
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR );
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
    //selection des niveaux de mipmap a generer (tous)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_BASE_LEVEL, 0);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, 1000);
    //generation des mipmaps
    glGenerateMipmap(GL_TEXTURE_2D);
}



