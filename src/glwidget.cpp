#include "glwidget.h"

#if defined(__linux__)
#include <GL/gl.h>
#include <GL/glu.h>
#endif
#if defined(__APPLE__)
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#endif
// #include <math.h>
#include <iostream>

GLWidget::GLWidget(QWidget* parent) : QOpenGLWidget(parent) {}

GLWidget::~GLWidget() {}

void GLWidget::initializeGL() {
  initializeOpenGLFunctions();
  glEnable(GL_DEPTH_TEST);
}

void GLWidget::resizeGL(int w, int h) {
  glViewport(0, 0, w, h);
  update();
}

void GLWidget::paintGL() {
  if (controller_->get_count_facets()) {
    if (backColor == 0) {
      glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    } else if (backColor == 1) {
      glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    } else if (backColor == 2) {
      glClearColor(0.0f, 0.3f, 0.0f, 0.0f);
    }
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if (pType) {
      glClear(GL_DEPTH_BUFFER_BIT);
      glEnable(GL_DEPTH_TEST);
      glOrtho(-5, 5, -5, 5, -5, 5);
    } else {
      glFrustum(-2, 2, -2, 2, 0.5, 3.5);
    }

    glTranslatef(0.0, 0.0, -1.);

    glRotated(xRot, 1, 0, 0);
    glRotated(yRot, 0, 1, 0);

    glVertexPointer(3, GL_FLOAT, 0, controller_->get_vertexes().data());
    glEnableClientState(GL_VERTEX_ARRAY);
    if (vertexColor == 0) {
      glColor3d(0.0, 0.0, 0.0);
    } else if (vertexColor == 1) {
      glColor3d(1, 0.9, 0);
    } else if (vertexColor == 2) {
      glColor3d(1, 0.0, 0.9);
    }
    glPointSize(pointSize);
    if (vertexType != 2) {
      if (vertexType == 1) {
        glEnable(GL_POINT_SMOOTH);
      }
      glDrawArrays(GL_POINTS, 0, controller_->get_count_vertexes());
    }
    if (vertexType == 1) {
      glDisable(GL_POINT_SMOOTH);
    }
    if (facetColor == 0) {
      glColor3d(0.0, 0.0, 0.0);
    } else if (facetColor == 1) {
      glColor3d(1, 0.9, 0);
    } else if (facetColor == 2) {
      glColor3d(1, 0.0, 0.9);
    }
    glLineWidth(facetWigth);
    if (facetType == 1) {
      glEnable(GL_LINE_STIPPLE);
      glLineStipple(1, 0x00ff);
    }
    glDrawElements(GL_LINES, controller_->get_count_facets(), GL_UNSIGNED_INT,
                   controller_->get_facets().data());
    glDisableClientState(GL_VERTEX_ARRAY);
    if (facetType == 1) {
      glDisable(GL_LINE_STIPPLE);
    }
  }
}

void GLWidget::mousePressEvent(QMouseEvent* mo) { mPos = mo->pos(); }

void GLWidget::mouseMoveEvent(QMouseEvent* mo) {
  xRot = 1 / PI * (mo->pos().y() - mPos.y());
  yRot = 1 / PI * (mo->pos().x() - mPos.x());
  update();
}
