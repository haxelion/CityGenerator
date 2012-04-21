#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QGLWidget>
#include "city.h"
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
    float mXTranslate;
    float mYTranslate;
    float mZTranslate;
    float mFov;
    float mFarRatio;
    float mNearRatio;
    City *city;

    QPoint lastPos;
};

#endif
