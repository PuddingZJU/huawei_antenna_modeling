#ifndef ANTENNAGLWIDGET_H
#define ANTENNAGLWIDGET_H

#include <QtOpenGL/QtOpenGL>
#include <QtOpenGL/QGLWidget>
#include <QtGui>

class AntennaGLWidget : public QGLWidget
{
    Q_OBJECT
public:
    explicit AntennaGLWidget(QWidget *parent = 0);
    ~AntennaGLWidget();
signals:

public slots:
};

#endif // ANTENNAGLWIDGET_H
