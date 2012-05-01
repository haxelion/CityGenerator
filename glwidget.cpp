#include "glwidget.h"

GLWidget::GLWidget(QWidget *parent)
    : QGLWidget(QGLFormat(QGL::SampleBuffers), parent)
{
    this->format().setVersion(3,3);
    this->format().setAlpha(true);
    setFocus();

    buffers = new Buffers();
    shaders = new Shaders();

    yFOV = 1.04;
    city = NULL;
    for (int i = 0; i < 4; i++)
    {
        texture[i]=0;
    }
}
GLWidget::~GLWidget()
{
   glDeleteTextures(4, texture);;
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
    glClearColor(0.8f, 1.0f, 1.0f, 0.01f);
    // Augmentation de la qualité du calcul de perspective
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
    // Choix du shader;
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glFrontFace(GL_CCW);

    setView();
}

void GLWidget::setCity(City *city)
{
    this->city = 0;
    delete buffers;
    buffers = new Buffers(city);
    this->city = city;
}

void GLWidget::setView()
{
    projectionMatrix = glm::perspective(mFov, this->width()/(float)this->height(),1, 100);
}

void GLWidget::drawObject()
{

}
void GLWidget::paintGL()
{
    makeCurrent();

    //Vide les differents buffers
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

    //Sauvegarde la matrice ModelView initiale, avant de la modifier
    glPushMatrix();

    //Applique la transformation
    glLoadIdentity();
    glTranslatef(mXTranslate, mYTranslate, mZTranslate+5.0);
    glRotatef(mXRotate / 16.0, 1.0, 0.0, 0.0);
    glRotatef(mYRotate / 16.0, 0.0, 1.0, 0.0);
    glRotatef(mZRotate / 16.0, 0.0, 0.0, 1.0);
    glScalef(mScale, mScale, mScale);

    GLfloat lightPos[4] = {20.0f, -10.0f, 50.f, 0.0f };
    glLightfv(GL_LIGHT0, GL_POSITION, lightPos);

    //Dessine les objects dans la scene
    if(city!=NULL)
        drawObject();

    glPopMatrix();
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
}
void GLWidget::mouseMoveEvent(QMouseEvent *event)
{
    int dx = event->x() - lastPos.x();
    int dy = event->y() - lastPos.y();

    if (event->buttons() & Qt::LeftButton)
    {
        setXRotation(mXRotate + 8 * dy);
        setYRotation(mYRotate + 8 * dx);
    }
    else if (event->buttons() & Qt::RightButton)
    {
        setXRotation(mXRotate + 8 * dy);
        setZRotation(mZRotate + 8 * dx);
    }
    lastPos = event->pos();
}
void GLWidget::wheelEvent(QWheelEvent *event)
{
    float notch = event->delta()/ 120.0f;

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
    update();
}

//Gestion du clavier
void GLWidget::keyPressEvent(QKeyEvent *event)
{
    switch(event->key())
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
    update();
}

static void qNormalizeAngle(int &angle)
{
    while (angle < 0)
        angle += 360 * 16;
    while (angle > 360 * 16)
        angle -= 360 * 16;
}
void GLWidget::setXRotation(int angle)
{
    qNormalizeAngle(angle);
    if (angle != mXRotate) {
        mXRotate = angle;
        emit xRotationChanged(angle);
        updateGL();
    }
}
void GLWidget::setYRotation(int angle)
{
    qNormalizeAngle(angle);
    if (angle != mYRotate) {
        mYRotate = angle;
        emit yRotationChanged(angle);
        updateGL();
    }
}
void GLWidget::setZRotation(int angle)
{
    qNormalizeAngle(angle);
    if (angle != mZRotate) {
        mZRotate = angle;
        emit zRotationChanged(angle);
        updateGL();
    }
}

void GLWidget::loadTexture(QString textureName, )
{

    if ()
        glDeleteTextures(1, );
    QImage Texture;
    QImage TempTexture;
    TempTexture.load(textureName);
    Texture = GLWidget.convertToGLFormat(TempTexture);
    glGenTextures( 1,  );
    glBindTexture( GL_TEXTURE_2D, );
    glTexImage2D( GL_TEXTURE_2D, 0, 3, Texture.width(), Texture.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, Texture.bits() );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
}



