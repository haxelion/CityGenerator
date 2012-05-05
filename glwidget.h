#ifndef GLWIDGET_H
#define GLWIDGET_H

#define GLEW_STATIC
#include "GL/glew.h"
#include <QtGui>
#include <QGLWidget>
#include <QString>
#include <QImage>
#include <math.h>
#include "glm.hpp"
#include "city.h"
#include "buffers.h"
#include "shaders.h"
#include "gtc/matrix_transform.hpp"
#include "gtc/type_ptr.hpp"
#include "QPoint"

//#include "model.h"

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

public slots:
    void setXRotation(int angle);
    void setYRotation(int angle);
    void setZRotation(int angle);

protected:
    void initializeGL();
    void paintGL();
    void resizeGL(int width, int height);

    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void wheelEvent(QWheelEvent *event);
    void keyPressEvent(QKeyEvent *event);

private:
    void setView();
    void drawObject();

private:

    float yFOV;
    City *city;
    Buffers *buffers;
    Shaders *shaders;
    GLuint textures[NUMBER_OF_BUFFER];
    QPoint lastPos;
    float angleX,angleY,positionX,positionY,positionZ;


    glm::mat4 projectionMatrix, viewMatrix;
    GLuint projectionMatrixUL, viewMatrixUL, samplerUL;


};

#endif
