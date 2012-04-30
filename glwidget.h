#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QGLWidget>
#include "city.h"
#include <QString>
#include <QImage>
#include "glm.hpp"
//#include "model.h"

class GLWidget : public QGLWidget
{
    Q_OBJECT

public:
    GLWidget(QWidget *parent = 0);
    ~GLWidget();

    QSize minimumSizeHint() const;
    QSize sizeHint() const;
    void setCity(City *city) {this->city = city;}
    void loadTexture (QString textureName);

public slots:
    void setXRotation(int angle);
    void setYRotation(int angle);
    void setZRotation(int angle);

signals:
    void xRotationChanged(int angle);
    void yRotationChanged(int angle);
    void zRotationChanged(int angle);

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
    int mXRotate;
    int mYRotate;
    int mZRotate;
    float mScale;
    int place;
    float mXTranslate;
    float mYTranslate;
    float mZTranslate;
    float mFov;
    float mFarRatio;
    float mNearRatio;
    City *city;
    GLuint textureRoof;
    GLuint textureRoad;
    GLuint textureBuilding;
    GLuint textureGarden;
    QPoint lastPos;

    glm::mat4 projectionMatrix, viewMatrix;
    GLuint projectionMatrixUL, viewMatrixUL;

};

#endif
