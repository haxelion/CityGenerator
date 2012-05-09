#ifndef GLWIDGET_H
#define GLWIDGET_H

#define GLEW_STATIC
#include "GL/glew.h"
#include <QtGui>
#include <QGLWidget>
#include <QString>
#include <QImage>
#include <QCursor>
#include <math.h>
#include "glm.hpp"
#include "city.h"
#include "buffers.h"
#include "shaders.h"
#include "gtc/matrix_transform.hpp"
#include "gtc/type_ptr.hpp"
#include "QPoint"

//#include "model.h"

enum Keys {KEY_Z, KEY_S, KEY_Q, KEY_D, KEY_A, KEY_E};
const int KEY_NUMBER = 6;
const float ROTATION_SPEED = 0.02f;
const float FAST_SPEED = 0.4;
const float SLOW_SPEED = 0.2;

class GLWidget : public QGLWidget
{
    Q_OBJECT

public:
    GLWidget(QWidget *parent = 0);
    ~GLWidget();

    QSize minimumSizeHint() const;
    QSize sizeHint() const;
    void setCity(City *city);
    void loadTexture(const char *textureName, int place);

protected:
    void initializeGL();
    void paintGL();
    void resizeGL(int width, int height);

    void mousePressEvent(QMouseEvent *event);
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent * event);

private:
    void setView();
    void drawObject();
    void updateCamera();

private:

    float yFOV;
    City *city;
    Buffers *buffers;
    Shaders *shaders;
    GLuint textures[NUMBER_OF_BUFFER];
    QTimer *renderTimer;
    bool mouseCaptured;
    bool pressedKey[KEY_NUMBER];
    float angleX,angleY;
    glm::vec3 position;
    float speed;

    glm::mat4 projectionMatrix, viewMatrix;
    GLuint projectionMatrixUL, viewMatrixUL, samplerUL;


};

#endif
