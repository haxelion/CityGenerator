#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QGLWidget>


class GLWidget : public QGLWidget
{

public:
    GLWidget(QWidget * parent =0);
    ~GLWidget();
};

#endif // GLWIDGET_H
